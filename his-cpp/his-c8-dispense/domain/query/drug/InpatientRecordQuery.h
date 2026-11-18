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
#ifndef _INPATIENT_RECORD_QUERY_
#define _INPATIENT_RECORD_QUERY_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Inpatient dispense/return record query object
 * Supports multi-condition combination query with pagination
 */
class InpatientRecordQuery : public PageQuery
{
	DTO_INIT(InpatientRecordQuery, PageQuery);

	// Drug name (fuzzy match on name/code/pinyin)
	DTO_FIELD(String, drugName);
	DTO_FIELD_INFO(drugName) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.drugName");
	}

	// Record type (dispense/return)
	DTO_FIELD(String, recordType);
	DTO_FIELD_INFO(recordType) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.recordType");
	}

	// Pharmacy name
	DTO_FIELD(String, pharmacy);
	DTO_FIELD_INFO(pharmacy) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.pharmacy");
	}

	// Project type
	DTO_FIELD(String, projectType);
	DTO_FIELD_INFO(projectType) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.projectType");
	}

	// Dispenser name
	DTO_FIELD(String, dispenseName);
	DTO_FIELD_INFO(dispenseName) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.dispenseName");
	}

	// Patient name (fuzzy match)
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.name");
	}

	// Hospitalization number
	DTO_FIELD(String, hospitalizationNo);
	DTO_FIELD_INFO(hospitalizationNo) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.hospitalizationNo");
	}

	// Record number
	DTO_FIELD(String, recordNo);
	DTO_FIELD_INFO(recordNo) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.recordNo");
	}

	// Start date
	DTO_FIELD(String, startDate);
	DTO_FIELD_INFO(startDate) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.startDate");
	}

	// End date
	DTO_FIELD(String, endDate);
	DTO_FIELD_INFO(endDate) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.endDate");
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_INPATIENT_RECORD_QUERY_
