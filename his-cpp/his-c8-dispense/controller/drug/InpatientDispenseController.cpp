#include "stdafx.h"
#include "InpatientDispenseController.h"
#include "../../service/drug/InpatientDispenseService.h"
#include <regex>

bool InpatientDispenseController::isValidDateFormat(const std::string& dateStr)
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

bool InpatientDispenseController::validateSummaryQueueQuery(const InpatientDispenseQuery::Wrapper& query, std::string& errMsg)
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
	// Validate dispense status enum values
	if (query->dispenseStatus && !query->dispenseStatus->empty()) {
		std::string status = query->dispenseStatus.getValue("");
		if (status != "PENDING" && status != "DISPENSED" && status != "COMPLETED" && status != "REJECTED" && status != "ALL") {
			errMsg = "Dispense status must be one of: PENDING, DISPENSED, COMPLETED, REJECTED, ALL.";
			return false;
		}
	}
	return true;
}

bool InpatientDispenseController::validateDrugDetailQuery(const InpatientDrugDetailQuery::Wrapper& query, std::string& errMsg)
{
	if (!query) {
		errMsg = "Query parameter is required.";
		return false;
	}
	// Validate summary number (required)
	if (!query->summaryNo || query->summaryNo->empty()) {
		errMsg = "Summary number is required.";
		return false;
	}
	return true;
}

InpatientDispenseSummaryPageJsonVO::Wrapper InpatientDispenseController::executeQuerySummaryQueue(const InpatientDispenseQuery::Wrapper& query)
{
	std::string errMsg;
	if (!validateSummaryQueueQuery(query, errMsg)) {
		auto jvo = InpatientDispenseSummaryPageJsonVO::createShared();
		jvo->init(nullptr, ResultStatus(errMsg, 9995));
		return jvo;
	}
	try {
		return InpatientDispenseService().listSummaryQueue(query);
	} catch (const std::exception& e) {
		auto jvo = InpatientDispenseSummaryPageJsonVO::createShared();
		jvo->init(nullptr, ResultStatus(e.what(), 9999));
		return jvo;
	}
}

InpatientDrugDetailJsonVO::Wrapper InpatientDispenseController::executeQueryDrugDetail(const InpatientDrugDetailQuery::Wrapper& query)
{
	std::string errMsg;
	if (!validateDrugDetailQuery(query, errMsg)) {
		auto jvo = InpatientDrugDetailJsonVO::createShared();
		jvo->init(nullptr, ResultStatus(errMsg, 9995));
		return jvo;
	}
	try {
		return InpatientDispenseService().getDrugDetail(query);
	} catch (const std::exception& e) {
		auto jvo = InpatientDrugDetailJsonVO::createShared();
		jvo->init(nullptr, ResultStatus(e.what(), 9999));
		return jvo;
	}
}

StringJsonVO::Wrapper InpatientDispenseController::executeVerifyDispense(const InpatientDispenseVerifyDTO::Wrapper& dto)
{
	if (!dto) {
		auto jvo = StringJsonVO::createShared();
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	if (!dto->Dispenseld || *dto->Dispenseld == 0) {
		auto jvo = StringJsonVO::createShared();
		jvo->init("Dispenseld is required.", RS_PARAMS_INVALID);
		return jvo;
	}
	try {
		return InpatientDispenseService().verifyDispense(dto);
	} catch (const std::exception&) {
		auto jvo = StringJsonVO::createShared();
		jvo->init(nullptr, RS_FAIL);
		return jvo;
	}
}

StringJsonVO::Wrapper InpatientDispenseController::executeRejectDispense(const InpatientDispenseRejectDTO::Wrapper& dto)
{
	if (!dto) {
		auto jvo = StringJsonVO::createShared();
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	if (!dto->dispenseld || *dto->dispenseld == 0) {
		auto jvo = StringJsonVO::createShared();
		jvo->init("dispenseld is required.", RS_PARAMS_INVALID);
		return jvo;
	}
	try {
		return InpatientDispenseService().rejectDispense(dto);
	} catch (const std::exception&) {
		auto jvo = StringJsonVO::createShared();
		jvo->init(nullptr, RS_FAIL);
		return jvo;
	}
}
