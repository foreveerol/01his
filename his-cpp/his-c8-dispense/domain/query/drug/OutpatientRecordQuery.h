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
#ifndef _OUTPATIENT_RECORD_QUERY_
#define _OUTPATIENT_RECORD_QUERY_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 门诊发退药记录查询对象
 */
class OutpatientRecordQuery : public PageQuery
{
	DTO_INIT(OutpatientRecordQuery, PageQuery);

	//药品名称
	DTO_FIELD(String, drugName);
	DTO_FIELD_INFO(drugName) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.drugName");
	}

	// 记录类型（发药/退药）
	DTO_FIELD(String, recordType);
	DTO_FIELD_INFO(recordType) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.recordType");
	}

	//药房
	DTO_FIELD(String, pharmacy);
	DTO_FIELD_INFO(pharmacy) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.pharmacy");
	}

	// 项目类型
	DTO_FIELD(String, projectType);
	DTO_FIELD_INFO(projectType) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.projectType");
	}

	//发药人
	DTO_FIELD(String, dispenseName);
	DTO_FIELD_INFO(dispenseName) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.dispenseName");
	}

	// 患者姓名（模糊匹配）
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.name");
	}

	// 开始日期
	DTO_FIELD(String, startDate);
	DTO_FIELD_INFO(startDate) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.startDate");
	}

	// 结束日期
	DTO_FIELD(String, endDate);
	DTO_FIELD_INFO(endDate) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.endDate");
	}

};

#include OATPP_CODEGEN_END(DTO)

#endif // !_OUTPATIENT_RECORD_QUERY_
