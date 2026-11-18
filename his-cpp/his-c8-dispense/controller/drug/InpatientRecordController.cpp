/*
 Copyright Zero One Star. All rights reserved.

 @Author: zjb517
 @Date: 2026/07/19 17:30:00

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
#include "InpatientRecordController.h"
#include "../../service/drug/InpatientRecordService.h"

bool InpatientRecordController::validateQuery(const InpatientRecordQuery::Wrapper& query, std::string& errMsg)
{
	if (!query) {
		errMsg = "Query parameter is required.";
		return false;
	}
	// Validate page index
	if (query->pageIndex && *query->pageIndex < 1) {
		errMsg = "Page index must be >= 1.";
		return false;
	}
	// Validate page size
	if (query->pageSize && (*query->pageSize < 1 || *query->pageSize > 100)) {
		errMsg = "Page size must be between 1 and 100.";
		return false;
	}
	// Validate date range
	if (query->startDate && !query->startDate->empty()
		&& query->endDate && !query->endDate->empty()) {
		if (*query->startDate > *query->endDate) {
			errMsg = "Start date must not be after end date.";
			return false;
		}
	}
	// Validate record type
	if (query->recordType && !query->recordType->empty()) {
		std::string rt = query->recordType.getValue("");
		if (rt != "dispense" && rt != "return") {
			errMsg = "Record type must be 'dispense' or 'return'.";
			return false;
		}
	}
	return true;
}

InpatientRecordPageJsonVO::Wrapper InpatientRecordController::execQueryInpatientRecords(const InpatientRecordQuery::Wrapper& query)
{
	std::string errMsg;
	if (!validateQuery(query, errMsg)) {
		auto jvo = InpatientRecordPageJsonVO::createShared();
		jvo->init(nullptr, ResultStatus(errMsg, 9995));
		return jvo;
	}
	try {
		return InpatientRecordService().listByCondition(query);
	}
	catch (const std::exception& e) {
		auto jvo = InpatientRecordPageJsonVO::createShared();
		jvo->init(nullptr, ResultStatus(e.what(), 9999));
		return jvo;
	}
}

StringJsonVO::Wrapper InpatientRecordController::execExportInpatientRecords(const InpatientRecordExportDTO::Wrapper& dto)
{
	if (!dto) {
		auto jvo = StringJsonVO::createShared();
		jvo->init("Export parameters are required.", RS_PARAMS_INVALID);
		return jvo;
	}
	try {
		return InpatientRecordService().exportRecords(dto);
	}
	catch (const std::exception& e) {
		auto jvo = StringJsonVO::createShared();
		jvo->init(e.what(), RS_FAIL);
		return jvo;
	}
}
