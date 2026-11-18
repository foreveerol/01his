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
#ifndef _SUPPLY_REJECT_DO_
#define _SUPPLY_REJECT_DO_
#include "../DoInclude.h"

/**
 * 供应审批驳回数据库实体（wkf_supply_request 表）
 */
class SupplyRejectDO : public BaseDO
{
	// 主键
	MYSQL_SYNTHESIZE(string, id, Id);
	// 供应申请聚合根
	MYSQL_SYNTHESIZE(string, bus_no, BusNo);
	// 供应类型枚举代码
	MYSQL_SYNTHESIZE(string, type_enum, TypeEnum);
	// 供应状态枚举代码
	MYSQL_SYNTHESIZE(string, status_enum, StatusEnum);
	// 行项数量
	MYSQL_SYNTHESIZE(string, item_quantity, ItemQuantity);
	// 总量/实发量
	MYSQL_SYNTHESIZE(string, total_quantity, TotalQuantity);
	// 物品标识
	MYSQL_SYNTHESIZE(string, item_id, ItemId);
	// 物品关联表名
	MYSQL_SYNTHESIZE(string, item_table, ItemTable);
	// 批号
	MYSQL_SYNTHESIZE(string, lot_number, LotNumber);
	// 来源库房
	MYSQL_SYNTHESIZE(string, source_location_id, SourceLocationId);
	// 目标库房
	MYSQL_SYNTHESIZE(string, purpose_location_id, PurposeLocationId);
	// 申请人
	MYSQL_SYNTHESIZE(string, applicant_id, ApplicantId);
	// 申请时间
	MYSQL_SYNTHESIZE(string, apply_time, ApplyTime);
	// 审批人
	MYSQL_SYNTHESIZE(string, approver_id, ApproverId);
	// 审批时间
	MYSQL_SYNTHESIZE(string, approval_time, ApprovalTime);
	// 乐观锁版本
	MYSQL_SYNTHESIZE(int, version, Version);
	// 软删除标记
	MYSQL_SYNTHESIZE(int, is_deleted, IsDeleted);
	// 创建时间
	MYSQL_SYNTHESIZE(string, created_at, CreatedAt);
	// 更新时间
	MYSQL_SYNTHESIZE(string, updated_at, UpdatedAt);
	// 创建操作人
	MYSQL_SYNTHESIZE(string, created_by, CreatedBy);
	// 更新操作人
	MYSQL_SYNTHESIZE(string, updated_by, UpdatedBy);
public:
	SupplyRejectDO() : BaseDO("wkf_supply_request")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("bus_no", "s", bus_no);
		MYSQL_ADD_FIELD("type_enum", "s", type_enum);
		MYSQL_ADD_FIELD("status_enum", "s", status_enum);
		MYSQL_ADD_FIELD("item_quantity", "s", item_quantity);
		MYSQL_ADD_FIELD("total_quantity", "s", total_quantity);
		MYSQL_ADD_FIELD("item_id", "s", item_id);
		MYSQL_ADD_FIELD("item_table", "s", item_table);
		MYSQL_ADD_FIELD("lot_number", "s", lot_number);
		MYSQL_ADD_FIELD("source_location_id", "s", source_location_id);
		MYSQL_ADD_FIELD("purpose_location_id", "s", purpose_location_id);
		MYSQL_ADD_FIELD("applicant_id", "s", applicant_id);
		MYSQL_ADD_FIELD("apply_time", "s", apply_time);
		MYSQL_ADD_FIELD("approver_id", "s", approver_id);
		MYSQL_ADD_FIELD("approval_time", "s", approval_time);
		MYSQL_ADD_FIELD("version", "i", version);
		MYSQL_ADD_FIELD("is_deleted", "i", is_deleted);
		MYSQL_ADD_FIELD("created_at", "s", created_at);
		MYSQL_ADD_FIELD("updated_at", "s", updated_at);
		MYSQL_ADD_FIELD("created_by", "s", created_by);
		MYSQL_ADD_FIELD("updated_by", "s", updated_by);
	}

	SupplyRejectDO(SupplyRejectDO&&) = default;
	SupplyRejectDO& operator=(SupplyRejectDO&&) = default;
};

typedef std::shared_ptr<SupplyRejectDO> PtrSupplyRejectDO;
#endif // !_SUPPLY_REJECT_DO_
