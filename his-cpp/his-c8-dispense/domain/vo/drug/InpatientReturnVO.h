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
#ifndef _INPATIENT_RETURN_VO_
#define _INPATIENT_RETURN_VO_

#include "../../GlobalInclude.h"
#include "../../dto/drug/InpatientReturnDTO.h"
#include "domain/vo/BaseJsonVO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 住院退药患者队列响应JsonVO
 */
class InpatientReturnQueueJsonVO : public JsonVO<oatpp::List<InpatientReturnPatientDTO::Wrapper>> {
	DTO_INIT(InpatientReturnQueueJsonVO, JsonVO<oatpp::List<InpatientReturnPatientDTO::Wrapper>>);
};

/**
 * 住院退药明细响应JsonVO，包含患者信息及药品列表
 */
class InpatientReturnJsonVO : public JsonVO<InpatientReturnDTO::Wrapper> {
	DTO_INIT(InpatientReturnJsonVO, JsonVO<InpatientReturnDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_INPATIENT_RETURN_VO_
