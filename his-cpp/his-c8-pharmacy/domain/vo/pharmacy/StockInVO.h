#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: zjb517
 @Date: 2026/07/19 18:00:00

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
#ifndef _STOCKIN_VO_
#define _STOCKIN_VO_

#include "../../GlobalInclude.h"
#include "../../dto/pharmacy/StockInDTO.h"
#include "domain/vo/BaseJsonVO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 入库单列表响应JsonVO
 */
class StockInPageJsonVO : public JsonVO<StockInPageDTO::Wrapper> {
	DTO_INIT(StockInPageJsonVO, JsonVO<StockInPageDTO::Wrapper>);
};

/**
 * 入库单详情响应JsonVO
 */
class StockInJsonVO : public JsonVO<StockInDTO::Wrapper> {
	DTO_INIT(StockInJsonVO, JsonVO<StockInDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_STOCKIN_VO_
