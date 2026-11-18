#pragma once
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
#ifndef _INPATIENT_RECORD_CONTROLLER_
#define _INPATIENT_RECORD_CONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/drug/InpatientRecordVO.h"
#include "domain/query/drug/InpatientRecordQuery.h"
#include "domain/dto/drug/InpatientRecordDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("dispense.inpatient-record.tag")

/**
 * Inpatient dispensing/return record controller
 * Provides conditional pagination query and export for inpatient dispensing and return history records
 */
class InpatientRecordController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(InpatientRecordController);
public:
	// Inpatient dispensing/return record query - endpoint definition
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("dispense.inpatient-record.query.summary"),
		queryInpatientRecords,
		InpatientRecordQuery,
		InpatientRecordPageJsonVO::Wrapper,
		API_TAG
	);
	// Inpatient dispensing/return record query - endpoint binding
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/dispense/inpatient-records", queryInpatientRecords,
		InpatientRecordQuery,
		execQueryInpatientRecords(query));

	// Inpatient dispensing/return record export - endpoint definition
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("dispense.inpatient-record.export.summary"),
		exportInpatientRecords,
		StringJsonVO::Wrapper,
		API_TAG
	);
	// Inpatient dispensing/return record export - endpoint binding
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/dispense/inpatient-records-export", exportInpatientRecords,
		BODY_DTO(InpatientRecordExportDTO::Wrapper, dto),
		execExportInpatientRecords(dto));

private:
	// Validate query parameters: page index, page size, date range, record type
	bool validateQuery(const InpatientRecordQuery::Wrapper& query, std::string& errMsg);
	InpatientRecordPageJsonVO::Wrapper execQueryInpatientRecords(const InpatientRecordQuery::Wrapper& query);
	StringJsonVO::Wrapper execExportInpatientRecords(const InpatientRecordExportDTO::Wrapper& dto);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)
#endif // !_INPATIENT_RECORD_CONTROLLER_
