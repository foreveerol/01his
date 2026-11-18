#pragma once
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
#ifndef _INPATIENT_RETURN_QUERY_
#define _INPATIENT_RETURN_QUERY_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 住院退药患者队列查询对象，用于分页查询待退药患者列表
 */
class InpatientReturnQuery : public PageQuery
{
	DTO_INIT(InpatientReturnQuery, PageQuery);
	// 住院号（精确匹配）
	DTO_FIELD(String, hospitalizationNo);
	DTO_FIELD_INFO(hospitalizationNo) {
		info->description = ZH_WORDS_GETTER("dispense.return.field.hospitalizationNo");
		info->required = true;
	}
	// 患者姓名（模糊匹配）
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("dispense.return.field.name");
	}
	// 病区
	DTO_FIELD(String, ward);
	DTO_FIELD_INFO(ward) {
		info->description = ZH_WORDS_GETTER("dispense.return.field.ward");
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_INPATIENT_RETURN_QUERY_
