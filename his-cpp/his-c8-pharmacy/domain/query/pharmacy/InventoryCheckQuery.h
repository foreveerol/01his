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
#ifndef _INVENTORY_CHECK_QUERY_
#define _INVENTORY_CHECK_QUERY_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Pharmacy inventory check query object
 */
class InventoryCheckQuery : public PageQuery
{
	DTO_INIT(InventoryCheckQuery, PageQuery);
	// Check document number
	DTO_FIELD(String, checkNo);
	DTO_FIELD_INFO(checkNo) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.checkNo");
	}
	// Check type
	DTO_FIELD(String, checkType);
	DTO_FIELD_INFO(checkType) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.checkType");
	}
	// Status
	DTO_FIELD(String, status);
	DTO_FIELD_INFO(status) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.status");
	}
	// Start date
	DTO_FIELD(String, startDate);
	DTO_FIELD_INFO(startDate) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.startDate");
	}
	// End date
	DTO_FIELD(String, endDate);
	DTO_FIELD_INFO(endDate) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.endDate");
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_INVENTORY_CHECK_QUERY_
