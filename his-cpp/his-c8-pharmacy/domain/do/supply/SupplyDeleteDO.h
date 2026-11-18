#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:52:32

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
#ifndef _SUPPLY_DELETE_DO_
#define _SUPPLY_DELETE_DO_
#include "../DoInclude.h"

/**
 * 供应申请删除文档数据库实体（wkf_supply_request 表）
 */
class SupplyDeleteDO : public BaseDO
{
	// 主键
	MYSQL_SYNTHESIZE(string, id, Id);
	// 供应申请聚合根
	MYSQL_SYNTHESIZE(string, bus_no, BusNo);
	// 供应类型枚举代码
	MYSQL_SYNTHESIZE(string, type_enum, TypeEnum);
	// 供应状态枚举代码
	MYSQL_SYNTHESIZE(string, status_enum, StatusEnum);
	// 物品标识
	MYSQL_SYNTHESIZE(string, item_id, ItemId);
	// 物品关联表名
	MYSQL_SYNTHESIZE(string, item_table, ItemTable);
	// 批号
	MYSQL_SYNTHESIZE(string, lot_number, LotNumber);
	// 乐观锁版本
	MYSQL_SYNTHESIZE(int, version, Version);
	// 软删除标记
	MYSQL_SYNTHESIZE(int, is_deleted, IsDeleted);
	// 更新时间
	MYSQL_SYNTHESIZE(string, updated_at, UpdatedAt);
	// 删除时间
	MYSQL_SYNTHESIZE(string, deleted_at, DeletedAt);
	// 删除操作人
	MYSQL_SYNTHESIZE(string, deleted_by, DeletedBy);
	// 更新操作人
	MYSQL_SYNTHESIZE(string, updated_by, UpdatedBy);
public:
	SupplyDeleteDO() : BaseDO("wkf_supply_request")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("bus_no", "s", bus_no);
		MYSQL_ADD_FIELD("type_enum", "s", type_enum);
		MYSQL_ADD_FIELD("status_enum", "s", status_enum);
		MYSQL_ADD_FIELD("item_id", "s", item_id);
		MYSQL_ADD_FIELD("item_table", "s", item_table);
		MYSQL_ADD_FIELD("lot_number", "s", lot_number);
		MYSQL_ADD_FIELD("version", "i", version);
		MYSQL_ADD_FIELD("is_deleted", "i", is_deleted);
		MYSQL_ADD_FIELD("updated_at", "s", updated_at);
		MYSQL_ADD_FIELD("deleted_at", "s", deleted_at);
		MYSQL_ADD_FIELD("deleted_by", "s", deleted_by);
		MYSQL_ADD_FIELD("updated_by", "s", updated_by);
	}

	SupplyDeleteDO(SupplyDeleteDO&&) = default;
	SupplyDeleteDO& operator=(SupplyDeleteDO&&) = default;
};

typedef std::shared_ptr<SupplyDeleteDO> PtrSupplyDeleteDO;
#endif // !_SUPPLY_DELETE_DO_
