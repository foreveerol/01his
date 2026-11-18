#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:36:29

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
#ifndef _DISPENSE_RECORD_QUERY_
#define _DISPENSE_RECORD_QUERY_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 门诊发退药记录导出查询条件
 */
class DispenseRecordQuery : public oatpp::DTO
{
	DTO_INIT(DispenseRecordQuery, DTO);
	// 发药开始时间（必填）
	DTO_FIELD(String, startTime);
	DTO_FIELD_INFO(startTime) {
		info->description = ZH_WORDS_GETTER("dispense.field.startTime");
	}
	// 发药结束时间（必填）
	DTO_FIELD(String, endTime);
	DTO_FIELD_INFO(endTime) {
		info->description = ZH_WORDS_GETTER("dispense.field.endTime");
	}
	// 状态列表，逗号分隔，如 COMPLETED,REFUNDED,DECLINED
	DTO_FIELD(String, statusList);
	DTO_FIELD_INFO(statusList) {
		info->description = ZH_WORDS_GETTER("dispense.field.statusList");
	}
	// 患者姓名（可选模糊查询）
	DTO_FIELD(String, patientName);
	DTO_FIELD_INFO(patientName) {
		info->description = ZH_WORDS_GETTER("dispense.field.patientName");
	}
	// 药品名称（可选模糊查询）
	DTO_FIELD(String, medicationName);
	DTO_FIELD_INFO(medicationName) {
		info->description = ZH_WORDS_GETTER("dispense.field.medicationName");
	}
	// 发药人姓名（可选模糊查询）
	DTO_FIELD(String, practitionerName);
	DTO_FIELD_INFO(practitionerName) {
		info->description = ZH_WORDS_GETTER("dispense.field.practitionerName");
	}
	// 药房ID（可选精确匹配）
	DTO_FIELD(String, locationId);
	DTO_FIELD_INFO(locationId) {
		info->description = ZH_WORDS_GETTER("dispense.field.locationId");
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_DISPENSE_RECORD_QUERY_
