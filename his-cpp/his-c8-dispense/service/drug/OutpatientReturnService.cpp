/*
 Copyright Zero One Star. All rights reserved.

 @Author: zjb517
 @Date: 2026/07/26 10:00:00

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#include "stdafx.h"
#include "OutpatientReturnService.h"
#include "../../dao/drug/OutpatientReturnDAO.h"

OutpatientReturnQueuePageJsonVO::Wrapper OutpatientReturnService::listReturnQueue(const OutpatientReturnQuery::Wrapper& query)
{
	auto jvo = OutpatientReturnQueuePageJsonVO::createShared();
	auto pageDTO = PageDTO<OutpatientReturnQueueItemDTO::Wrapper>::createShared();
	pageDTO->pageIndex = query->pageIndex;
	pageDTO->pageSize = query->pageSize;

	OutpatientReturnDAO dao;
	auto list = dao.selectReturnQueue(query);
	uint64_t total = dao.countReturnQueue(query);

	pageDTO->total = Int64(total);
	pageDTO->calcPages();

	auto rows = oatpp::List<OutpatientReturnQueueItemDTO::Wrapper>::createShared();
	for (auto& item : list) {
		auto dto = OutpatientReturnQueueItemDTO::createShared();
		dto->id = item.getId();
		rows->push_back(dto);
	}
	pageDTO->rows = rows;
	jvo->success(pageDTO);
	return jvo;
}

OutpatientReturnJsonVO::Wrapper OutpatientReturnService::getReturnDetail(const OutpatientReturnDrugDTO::Wrapper& dto)
{
	auto jvo = OutpatientReturnJsonVO::createShared();

	if (!dto->drugId || dto->drugId->empty()) {
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	OutpatientReturnDAO dao;
	auto list = dao.selectReturnDetail(dto->drugId.getValue(""));

	auto result = OutpatientReturnDTO::createShared();
	result->returnId = dto->drugId;
	jvo->success(result);
	return jvo;
}

StringJsonVO::Wrapper OutpatientReturnService::confirmReturn(const OutpatientReturnConfirmDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	if (!dto->returnId || dto->returnId->empty()) {
		jvo->init("returnId is required.", RS_PARAMS_INVALID);
		return jvo;
	}

	OutpatientReturnDAO dao;
	int updated = dao.confirmReturn(dto->returnId.getValue(""));
	if (updated > 0) {
		jvo->success("Return confirmed successfully");
	} else {
		jvo->init("No records were updated.", RS_PARAMS_INVALID);
	}
	return jvo;
}

StringJsonVO::Wrapper OutpatientReturnService::rejectReturn(const OutpatientReturnRejectDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	if (!dto->returnId || dto->returnId->empty()) {
		jvo->init("returnId is required.", RS_PARAMS_INVALID);
		return jvo;
	}

	OutpatientReturnDAO dao;
	int updated = dao.rejectReturn(dto->returnId.getValue(""), "Rejected by operator");
	if (updated > 0) {
		jvo->success("Return rejected successfully");
	} else {
		jvo->init("No records were updated.", RS_PARAMS_INVALID);
	}
	return jvo;
}
