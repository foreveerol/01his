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
#include "StockInService.h"
#include "../../dao/pharmacy/StockInDAO.h"
#include "../../dao/pharmacy/StockInMapper.h"
#include "SimpleDateTimeFormat.h"

StockInPageJsonVO::Wrapper StockInService::listByCondition(const StockInQuery::Wrapper& query)
{
	auto jvo = StockInPageJsonVO::createShared();
	auto pageDTO = StockInPageDTO::createShared();
	pageDTO->pageIndex = query->pageIndex;
	pageDTO->pageSize = query->pageSize;

	StockInDAO dao;
	auto list = dao.selectList(query);
	uint64_t total = dao.countList(query);

	pageDTO->total = UInt64(total);
	pageDTO->calcPages();

	auto rows = oatpp::List<StockInListItemDTO::Wrapper>::createShared();
	for (auto& item : list) {
		auto dto = StockInListItemDTO::createShared();
		dto->orderNo = item.getBusNo();
		dto->supplierName = item.getSupplierName();
		dto->stockInDate = item.getCreatedAt();
		dto->drugCount = Int32(item.getDrugCount());
		dto->totalAmount = Float64(item.getTotalAmount());
		dto->status = item.getStatusEnum();
		dto->creator = item.getCreator();
		rows->push_back(dto);
	}
	pageDTO->rows = rows;
	jvo->success(pageDTO);
	return jvo;
}

StockInJsonVO::Wrapper StockInService::queryOne(const String& orderNo)
{
	auto jvo = StockInJsonVO::createShared();

	if (!orderNo || orderNo->empty()) {
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	StockInDAO dao;
	auto detail = dao.selectByBusNo(orderNo);
	if (detail.getBusNo().empty()) {
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	auto result = StockInDTO::createShared();
	result->orderNo = detail.getBusNo();
	result->supplierName = detail.getSupplierName();
	result->stockInType = detail.getIntentEnum();
	result->stockInDate = detail.getCreatedAt();
	result->status = detail.getStatusEnum();
	result->remark = detail.getRemake();

	// TODO: query detail items via wkf_supply_delivery
	auto drugList = oatpp::List<StockInDrugItemDTO::Wrapper>::createShared();
	result->drugList = drugList;

	jvo->success(result);
	return jvo;
}

StringJsonVO::Wrapper StockInService::create()
{
	auto jvo = StringJsonVO::createShared();
	std::string orderNo = generateOrderNo();
	jvo->success(orderNo);
	return jvo;
}

StringJsonVO::Wrapper StockInService::saveDraft(const StockInSaveDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	if (!dto->supplierName || dto->supplierName->empty()) {
		jvo->init("supplierName is required.", RS_PARAMS_INVALID);
		return jvo;
	}

	// TODO: persist to wkf_supply_request
	jvo->success("Draft saved successfully");
	return jvo;
}

StringJsonVO::Wrapper StockInService::saveAndSubmit(const StockInSaveDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	if (!dto->supplierName || dto->supplierName->empty()) {
		jvo->init("supplierName is required.", RS_PARAMS_INVALID);
		return jvo;
	}

	// TODO: persist and submit
	jvo->success("Saved and submitted successfully");
	return jvo;
}

StringJsonVO::Wrapper StockInService::submit(const StockInRemoveDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	if (!dto->orderNo || dto->orderNo->empty()) {
		jvo->init("orderNo is required.", RS_PARAMS_INVALID);
		return jvo;
	}

	// TODO: update status to PENDING_APPROVAL
	jvo->success("Submitted successfully");
	return jvo;
}

StringJsonVO::Wrapper StockInService::withdraw(const StockInRemoveDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	if (!dto->orderNo || dto->orderNo->empty()) {
		jvo->init("orderNo is required.", RS_PARAMS_INVALID);
		return jvo;
	}

	// TODO: update status back to DRAFT
	jvo->success("Withdrawn successfully");
	return jvo;
}

StringJsonVO::Wrapper StockInService::approve(const StockInApprovalDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	if (!dto->orderNo || dto->orderNo->empty()) {
		jvo->init("orderNo is required.", RS_PARAMS_INVALID);
		return jvo;
	}

	// TODO: update status to APPROVED and adjust inventory
	jvo->success("Approved successfully");
	return jvo;
}

StringJsonVO::Wrapper StockInService::reject(const StockInApprovalDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	if (!dto->orderNo || dto->orderNo->empty()) {
		jvo->init("orderNo is required.", RS_PARAMS_INVALID);
		return jvo;
	}

	// TODO: update status to REJECTED with reason
	jvo->success("Rejected successfully");
	return jvo;
}

StringJsonVO::Wrapper StockInService::remove(const StockInRemoveDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	if (!dto->orderNo || dto->orderNo->empty()) {
		jvo->init("orderNo is required.", RS_PARAMS_INVALID);
		return jvo;
	}

	// TODO: soft delete
	jvo->success("Removed successfully");
	return jvo;
}

std::string StockInService::generateOrderNo()
{
	auto now = std::chrono::system_clock::now();
	std::time_t t = std::chrono::system_clock::to_time_t(now);
	std::tm tm;
	localtime_s(&tm, &t);

	char dateBuf[16];
	strftime(dateBuf, sizeof(dateBuf), "%Y%m%d", &tm);

	// Simple incrementing sequence (TODO: use DB sequence)
	static int seq = 0;
	seq++;

	char result[32];
	snprintf(result, sizeof(result), "RK%s%04d", dateBuf, seq);
	return std::string(result);
}
