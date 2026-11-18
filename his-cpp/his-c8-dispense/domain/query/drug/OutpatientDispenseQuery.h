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
#ifndef _OUTPATIENT_DISPENSE_QUERY_
#define _OUTPATIENT_DISPENSE_QUERY_

#include "../../GlobalInclude.h"
#include "../../lib-oatpp/include/domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 门诊发药患者队列查询参数（支持分页）
class OutpatientDispenseQuery : public PageQuery
{
	DTO_INIT(OutpatientDispenseQuery, DTO);
	//患者姓名
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.name"), true);
	//患者性别
	API_DTO_FIELD_REQUIRE(String, sex, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.gender"), true);
	//患者待发药状态
	API_DTO_FIELD_REQUIRE(String, dispense_status, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.dispense_status"), true);
	

};
//
class OutpatientDrugDetailQuery : public oatpp::DTO
{
	DTO_INIT(OutpatientDrugDetailQuery, DTO);
	//处方号
	API_DTO_FIELD_REQUIRE(String, prescription_no, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.prescriptionNo"), true);
};
#include OATPP_CODEGEN_END(DTO)

#endif
