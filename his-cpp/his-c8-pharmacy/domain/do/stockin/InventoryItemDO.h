#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: zjb517
 @Date: 2026/07/26 10:00:00

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
#ifndef _INVENTORY_ITEM_DO_
#define _INVENTORY_ITEM_DO_

#include "../DoInclude.h"

/**
 * 库存物品数据库实体（wkf_inventory_item 表）
 */
class InventoryItemDO : public BaseDO
{
	// 通用审计字段
	MYSQL_SYNTHESIZE(string, id, Id);
	MYSQL_SYNTHESIZE(string, tenantId, TenantId);
	MYSQL_SYNTHESIZE(string, createdAt, CreatedAt);
	MYSQL_SYNTHESIZE(string, updatedAt, UpdatedAt);
	MYSQL_SYNTHESIZE(int, isDeleted, IsDeleted);

	// 业务字段
	MYSQL_SYNTHESIZE(string, itemTable, ItemTable);
	MYSQL_SYNTHESIZE(string, itemId, ItemId);
	MYSQL_SYNTHESIZE(string, name, Name);
	MYSQL_SYNTHESIZE(string, inventoryStatusEnum, InventoryStatusEnum);
	MYSQL_SYNTHESIZE(string, supplierId, SupplierId);
	MYSQL_SYNTHESIZE(string, unitCode, UnitCode);
	MYSQL_SYNTHESIZE(double, quantity, Quantity);
	MYSQL_SYNTHESIZE(string, lotNumber, LotNumber);
	MYSQL_SYNTHESIZE(string, productionDate, ProductionDate);
	MYSQL_SYNTHESIZE(string, expirationDate, ExpirationDate);
	MYSQL_SYNTHESIZE(string, locationId, LocationId);
	MYSQL_SYNTHESIZE(string, traceNo, TraceNo);

public:
	InventoryItemDO()
		: BaseDO("wkf_inventory_item")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD_NULLABLE("tenant_id", "s", tenantId, true);
		MYSQL_ADD_FIELD_NULLABLE("created_at", "s", createdAt, false);
		MYSQL_ADD_FIELD_NULLABLE("updated_at", "s", updatedAt, true);
		MYSQL_ADD_FIELD_NULLABLE("is_deleted", "i", isDeleted, false);
		MYSQL_ADD_FIELD_NULLABLE("item_table", "s", itemTable, true);
		MYSQL_ADD_FIELD_NULLABLE("item_id", "s", itemId, true);
		MYSQL_ADD_FIELD_NULLABLE("name", "s", name, true);
		MYSQL_ADD_FIELD_NULLABLE("inventory_status_enum", "s", inventoryStatusEnum, true);
		MYSQL_ADD_FIELD_NULLABLE("supplier_id", "s", supplierId, true);
		MYSQL_ADD_FIELD_NULLABLE("unit_code", "s", unitCode, true);
		MYSQL_ADD_FIELD_NULLABLE("quantity", "d", quantity, true);
		MYSQL_ADD_FIELD_NULLABLE("lot_number", "s", lotNumber, true);
		MYSQL_ADD_FIELD_NULLABLE("production_date", "s", productionDate, true);
		MYSQL_ADD_FIELD_NULLABLE("expiration_date", "s", expirationDate, true);
		MYSQL_ADD_FIELD_NULLABLE("location_id", "s", locationId, false);
		MYSQL_ADD_FIELD_NULLABLE("trace_no", "s", traceNo, true);
	}

	InventoryItemDO(InventoryItemDO&&) = default;
	InventoryItemDO& operator=(InventoryItemDO&&) = default;
};

typedef std::shared_ptr<InventoryItemDO> PtrInventoryItemDO;

#endif // !_INVENTORY_ITEM_DO_
