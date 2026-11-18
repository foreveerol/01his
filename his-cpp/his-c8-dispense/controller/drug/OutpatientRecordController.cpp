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
#include "OutpatientRecordController.h"
#include "../../service/drug/OutpatientRecordService.h"
#include <regex>

bool OutpatientRecordController::isValidDateFormat(const std::string& dateStr)
{
	// Check if date matches YYYY-MM-DD format
	std::regex datePattern(R"(^\d{4}-\d{2}-\d{2}$)");
	if (!std::regex_match(dateStr, datePattern)) {
		return false;
	}
	// Basic validation for month and day ranges
	int year = std::stoi(dateStr.substr(0, 4));
	int month = std::stoi(dateStr.substr(5, 2));
	int day = std::stoi(dateStr.substr(8, 2));
	if (year < 2000 || year > 2100) return false;
	if (month < 1 || month > 12) return false;
	if (day < 1 || day > 31) return false;
	return true;
}

bool OutpatientRecordController::validateOutpatientRecordQuery(const OutpatientRecordQuery::Wrapper& query, std::string& errMsg)
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
	// Validate start date format
	if (query->startDate && !query->startDate->empty()) {
		if (!isValidDateFormat(*query->startDate)) {
			errMsg = "Start date must be in YYYY-MM-DD format.";
			return false;
		}
	}
	// Validate end date format
	if (query->endDate && !query->endDate->empty()) {
		if (!isValidDateFormat(*query->endDate)) {
			errMsg = "End date must be in YYYY-MM-DD format.";
			return false;
		}
	}
	// Validate date range
	if (query->startDate && !query->startDate->empty()
		&& query->endDate && !query->endDate->empty()) {
		if (*query->startDate > *query->endDate) {
			errMsg = "Start date must not be after end date.";
			return false;
		}
	}
	// Validate record type enum values (DISPENSE=发药, REFUND=退药)
	if (query->recordType && !query->recordType->empty()) {
		std::string rt = query->recordType.getValue("");
		if (rt != "DISPENSE" && rt != "REFUND") {
			errMsg = "Record type must be 'DISPENSE' (dispense) or 'REFUND' (return).";
			return false;
		}
	}
	return true;
}

OutpatientRecordPageJsonVO::Wrapper OutpatientRecordController::executeQueryOutpatientRecords(const OutpatientRecordQuery::Wrapper& query)
{
	std::string errMsg;
	if (!validateOutpatientRecordQuery(query, errMsg)) {
		auto jvo = OutpatientRecordPageJsonVO::createShared();
		jvo->init(nullptr, ResultStatus(errMsg, 9995));
		return jvo;
	}
	try {
		return OutpatientRecordService().listByCondition(query);
	} catch (const std::exception& e) {
		auto jvo = OutpatientRecordPageJsonVO::createShared();
		jvo->init(nullptr, ResultStatus(e.what(), 9999));
		return jvo;
	}
}

StringJsonVO::Wrapper OutpatientRecordController::executeExportOutpatientRecords(const OutpatientRecordExportDTO::Wrapper& dto)
{
	if (!dto) {
		auto jvo = StringJsonVO::createShared();
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	try {
		return OutpatientRecordService().exportRecords(dto);
	} catch (const std::exception&) {
		auto jvo = StringJsonVO::createShared();
		jvo->init(nullptr, RS_FAIL);
		return jvo;
	}
}
