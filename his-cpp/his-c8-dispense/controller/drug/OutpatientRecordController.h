#pragma once
#ifndef _OUTPATIENT_RECORD_CONTROLLER_H_
#define _OUTPATIENT_RECORD_CONTROLLER_H_

#include "../../domain/query/drug/OutpatientRecordQuery.h"
#include "../../domain/vo/drug/OutpatientRecordVO.h"
#include "domain/vo/BaseJsonVO.h"

using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG_OUTPATIENT_RECORD ZH_WORDS_GETTER("dispense.outpatient-record.tag")

// Outpatient drug dispensing/return record controller
// Provides query and export functionality for outpatient dispensing and return records
class OutpatientRecordController : public oatpp::web::server::api::ApiController {
	API_ACCESS_DECLARE(OutpatientRecordController);
public:
	// Query outpatient dispensing/return records - endpoint definition
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("dispense.outpatient-record.query.summary"),
		queryOutpatientRecords, OutpatientRecordQuery,
		OutpatientRecordPageJsonVO::Wrapper, API_TAG_OUTPATIENT_RECORD);
	// Query outpatient dispensing/return records - endpoint binding
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/dispense/outpatient-records", queryOutpatientRecords,
		OutpatientRecordQuery, executeQueryOutpatientRecords(query));

	// Export outpatient dispensing/return records - endpoint definition
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("dispense.outpatient-record.export.summary"),
		exportOutpatientRecords, StringJsonVO::Wrapper, API_TAG_OUTPATIENT_RECORD);
	// Export outpatient dispensing/return records - endpoint binding
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/dispense/outpatient-records-export", exportOutpatientRecords,
		BODY_DTO(OutpatientRecordExportDTO::Wrapper, dto),
		executeExportOutpatientRecords(dto));

private:
	// Validate query parameters for outpatient records
	bool validateOutpatientRecordQuery(const OutpatientRecordQuery::Wrapper& query, std::string& errMsg);
	// Check if date string matches YYYY-MM-DD format
	bool isValidDateFormat(const std::string& dateStr);
	
	// Execute query for outpatient dispensing/return records
	OutpatientRecordPageJsonVO::Wrapper executeQueryOutpatientRecords(const OutpatientRecordQuery::Wrapper& query);
	// Execute export for outpatient dispensing/return records
	StringJsonVO::Wrapper executeExportOutpatientRecords(const OutpatientRecordExportDTO::Wrapper& dto);
};

#undef API_TAG_OUTPATIENT_RECORD

#include OATPP_CODEGEN_END(ApiController)

#endif // !_OUTPATIENT_RECORD_CONTROLLER_H_
