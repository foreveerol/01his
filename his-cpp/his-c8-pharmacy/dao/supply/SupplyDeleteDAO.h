#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 14:23:49

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
#ifndef _SUPPLY_DELETE_DAO_
#define _SUPPLY_DELETE_DAO_
#include "BaseDAO.h"
#include "../../domain/do/supply/SupplyDeleteDO.h"

/**
 * Supply delete data access object
 */
class SupplyDeleteDAO : public BaseDAO
{
public:
	// Query document by ID (not deleted only)
	PtrSupplyDeleteDO selectById(std::string id);
	// Soft delete stocktake document
	int softDelete(std::string id, std::string deletedAt, std::string deletedBy);
	// Check for active (non-cancelled) delivery records
	uint64_t countActiveDeliveryByRequestId(std::string requestId);
	// Soft delete associated delivery records
	int softDeleteDeliveries(std::string requestId, std::string deletedAt, std::string deletedBy);
};
#endif // !_SUPPLY_DELETE_DAO_
