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
#ifndef _INVENTORY_CHECK_VO_
#define _INVENTORY_CHECK_VO_

#include "../../GlobalInclude.h"
#include "../../dto/pharmacy/InventoryCheckDTO.h"
#include "domain/vo/BaseJsonVO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Inventory check list response JsonVO
 */
class InventoryCheckPageJsonVO : public JsonVO<InventoryCheckPageDTO::Wrapper> {
	DTO_INIT(InventoryCheckPageJsonVO, JsonVO<InventoryCheckPageDTO::Wrapper>);
};

/**
 * Inventory check detail response JsonVO
 */
class InventoryCheckJsonVO : public JsonVO<InventoryCheckDTO::Wrapper> {
	DTO_INIT(InventoryCheckJsonVO, JsonVO<InventoryCheckDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_INVENTORY_CHECK_VO_
