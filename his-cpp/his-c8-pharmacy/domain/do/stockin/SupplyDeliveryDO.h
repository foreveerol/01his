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
#ifndef _STOCKIN_DELIVERY_DO_
#define _STOCKIN_DELIVERY_DO_

#include "../DoInclude.h"

/**
 * 入库配送数据库实体（wkf_supply_delivery 表）
 * 入库场景下的完整配送字段视图
 */
class StockInDeliveryDO : public BaseDO
{
	// 系统字段
	MYSQL_SYNTHESIZE(string, id, Id);
	MYSQL_SYNTHESIZE(string, tenantId, TenantId);
	MYSQL_SYNTHESIZE(string, createdAt, CreatedAt);
	MYSQL_SYNTHESIZE(string, updatedAt, UpdatedAt);
	MYSQL_SYNTHESIZE(string, createdBy, CreatedBy);
	MYSQL_SYNTHESIZE(string, updatedBy, UpdatedBy);
	MYSQL_SYNTHESIZE(int, isDeleted, IsDeleted);

	// 业务字段
	MYSQL_SYNTHESIZE(string, requestId, RequestId);
	MYSQL_SYNTHESIZE(string, statusEnum, StatusEnum);
	MYSQL_SYNTHESIZE(string, typeEnum, TypeEnum);
	MYSQL_SYNTHESIZE(string, itemTable, ItemTable);
	MYSQL_SYNTHESIZE(string, itemId, ItemId);
	MYSQL_SYNTHESIZE(double, quantity, Quantity);
	MYSQL_SYNTHESIZE(string, unitCode, UnitCode);
	MYSQL_SYNTHESIZE(string, supplierId, SupplierId);
	MYSQL_SYNTHESIZE(string, practitionerId, PractitionerId);
	MYSQL_SYNTHESIZE(string, occurrenceTime, OccurrenceTime);

public:
	StockInDeliveryDO()
		: BaseDO("wkf_supply_delivery")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD_NULLABLE("tenant_id", "s", tenantId, true);
		MYSQL_ADD_FIELD_NULLABLE("created_at", "s", createdAt, false);
		MYSQL_ADD_FIELD_NULLABLE("updated_at", "s", updatedAt, true);
		MYSQL_ADD_FIELD_NULLABLE("created_by", "s", createdBy, true);
		MYSQL_ADD_FIELD_NULLABLE("updated_by", "s", updatedBy, true);
		MYSQL_ADD_FIELD_NULLABLE("is_deleted", "i", isDeleted, false);
		MYSQL_ADD_FIELD_NULLABLE("request_id", "s", requestId, true);
		MYSQL_ADD_FIELD_NULLABLE("status_enum", "s", statusEnum, true);
		MYSQL_ADD_FIELD_NULLABLE("type_enum", "s", typeEnum, true);
		MYSQL_ADD_FIELD_NULLABLE("item_table", "s", itemTable, true);
		MYSQL_ADD_FIELD_NULLABLE("item_id", "s", itemId, true);
		MYSQL_ADD_FIELD_NULLABLE("quantity", "d", quantity, true);
		MYSQL_ADD_FIELD_NULLABLE("unit_code", "s", unitCode, true);
		MYSQL_ADD_FIELD_NULLABLE("supplier_id", "s", supplierId, true);
		MYSQL_ADD_FIELD_NULLABLE("practitioner_id", "s", practitionerId, true);
		MYSQL_ADD_FIELD_NULLABLE("occurrence_time", "s", occurrenceTime, true);
	}

	StockInDeliveryDO(StockInDeliveryDO&&) = default;
	StockInDeliveryDO& operator=(StockInDeliveryDO&&) = default;
};

typedef std::shared_ptr<StockInDeliveryDO> PtrStockInDeliveryDO;

#endif // !_STOCKIN_DELIVERY_DO_
