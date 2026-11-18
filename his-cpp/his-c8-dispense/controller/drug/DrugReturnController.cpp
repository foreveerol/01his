/*
 Copyright Zero One Star. All rights reserved.

 @Author: zjb517
 @Date: 2026/07/19 17:02:00

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
#include "DrugReturnController.h"
#include "../../service/drug/DrugReturnService.h"

InpatientReturnQueueJsonVO::Wrapper DrugReturnController::execQueryInpatientReturnQueue(const InpatientReturnQuery::Wrapper& query)
{
	if (!query) {
		auto jvo = InpatientReturnQueueJsonVO::createShared();
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	try {
		return DrugReturnService().listReturnQueue(query);
	} catch (const std::exception&) {
		auto jvo = InpatientReturnQueueJsonVO::createShared();
		jvo->init(nullptr, RS_FAIL);
		return jvo;
	}
}

InpatientReturnJsonVO::Wrapper DrugReturnController::execQueryInpatientReturn(const String& hospitalizationNo)
{
	if (!hospitalizationNo || hospitalizationNo->empty()) {
		auto jvo = InpatientReturnJsonVO::createShared();
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	try {
		return DrugReturnService().getReturnDetail(hospitalizationNo.getValue(""));
	} catch (const std::exception&) {
		auto jvo = InpatientReturnJsonVO::createShared();
		jvo->init(nullptr, RS_FAIL);
		return jvo;
	}
}

StringJsonVO::Wrapper DrugReturnController::execConfirmInpatientReturn(const InpatientReturnConfirmDTO::Wrapper& dto)
{
	if (!dto) {
		auto jvo = StringJsonVO::createShared();
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	if (!dto->hospitalizationNo || dto->hospitalizationNo->empty()) {
		auto jvo = StringJsonVO::createShared();
		jvo->init("hospitalizationNo is required.", RS_PARAMS_INVALID);
		return jvo;
	}
	if (!dto->refundDetailIds || dto->refundDetailIds->empty()) {
		auto jvo = StringJsonVO::createShared();
		jvo->init("refundDetailIds is required.", RS_PARAMS_INVALID);
		return jvo;
	}
	try {
		return DrugReturnService().confirmReturn(dto);
	} catch (const std::exception&) {
		auto jvo = StringJsonVO::createShared();
		jvo->init(nullptr, RS_FAIL);
		return jvo;
	}
}
