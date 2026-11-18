#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: zjb517
 @Date: 2026/07/20 19:30:00

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
#ifndef _OUTPATIENT_DISPENSE_VO_
#define _OUTPATIENT_DISPENSE_VO_

#include "../../GlobalInclude.h"
#include "../../dto/drug/OutpatientDispenseDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 门诊待发药患者分页列表响应VO
 */
class OutpatientQueuePageJsonVO : public JsonVO<OutpatientDispenseDTO::Wrapper> {
	DTO_INIT(OutpatientQueuePageJsonVO, JsonVO<OutpatientDispenseDTO::Wrapper>);
};

/**
 * 门诊处方详情（处方+药品明细）单条数据响应VO
 */
class OutpatientDispenseJsonVO : public JsonVO<OutpatientDrugDetailInfDTO::Wrapper> {
	DTO_INIT(OutpatientDispenseJsonVO, JsonVO<OutpatientDrugDetailInfDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_OUTPATIENT_DISPENSE_VO_
