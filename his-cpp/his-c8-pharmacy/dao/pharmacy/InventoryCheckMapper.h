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
#ifndef _INVENTORY_CHECK_MAPPER_
#define _INVENTORY_CHECK_MAPPER_

#include "Mapper.h"
#include "../../domain/DoInclude.h"

/**
 * 盘点单列表查询结果 DO（只读）
 */
class InvCheckListDO : public BaseDO
{
	// 盘点单号
	MYSQL_SYNTHESIZE(string, bus_no, BusNo);
	// 盘点类型
	MYSQL_SYNTHESIZE(string, intent_enum, IntentEnum);
	// 盘点日期
	MYSQL_SYNTHESIZE(string, created_at, CreatedAt);
	// 药品数量
	MYSQL_SYNTHESIZE(int, drug_count, DrugCount);
	// 单据状态
	MYSQL_SYNTHESIZE(string, status_enum, StatusEnum);
	// 盘点人
	MYSQL_SYNTHESIZE(string, checker, Checker);
public:
	InvCheckListDO() : BaseDO("wkf_supply_request") {}
	InvCheckListDO(InvCheckListDO&&) = default;
	InvCheckListDO& operator=(InvCheckListDO&&) = default;
};

/**
 * 盘点单列表查询字段映射
 * SELECT 列顺序：
 * sr.bus_no(1), sr.intent_enum(2), sr.created_at(3),
 * COUNT(sd.id)(4), sr.status_enum(5), COALESCE(u.name, sr.created_by)(6)
 */
class InvCheckListMapper : public Mapper<InvCheckListDO>
{
public:
	InvCheckListDO mapper(ResultSet* resultSet) const override
	{
		InvCheckListDO data;
		data.setBusNo(resultSet->getString(1));
		data.setIntentEnum(resultSet->getString(2));
		data.setCreatedAt(resultSet->getString(3));
		data.setDrugCount(resultSet->getInt(4));
		data.setStatusEnum(resultSet->getString(5));
		data.setChecker(resultSet->getString(6));
		return data;
	}
};

/**
 * 盘点单详情查询结果 DO（只读）
 */
class InvCheckDetailDO : public BaseDO
{
	// 盘点单号
	MYSQL_SYNTHESIZE(string, bus_no, BusNo);
	// 盘点类型
	MYSQL_SYNTHESIZE(string, intent_enum, IntentEnum);
	// 单据状态
	MYSQL_SYNTHESIZE(string, status_enum, StatusEnum);
	// 创建时间
	MYSQL_SYNTHESIZE(string, created_at, CreatedAt);
	// 备注
	MYSQL_SYNTHESIZE(string, remake, Remake);
	// 驳回原因
	MYSQL_SYNTHESIZE(string, reason, Reason);
public:
	InvCheckDetailDO() : BaseDO("wkf_supply_request") {}
	InvCheckDetailDO(InvCheckDetailDO&&) = default;
	InvCheckDetailDO& operator=(InvCheckDetailDO&&) = default;
};

/**
 * 盘点单详情查询字段映射
 * SELECT 列顺序：
 * sr.bus_no(1), sr.intent_enum(2), sr.status_enum(3),
 * sr.created_at(4), sr.remake(5), sr.reason(6)
 */
class InvCheckDetailMapper : public Mapper<InvCheckDetailDO>
{
public:
	InvCheckDetailDO mapper(ResultSet* resultSet) const override
	{
		InvCheckDetailDO data;
		data.setBusNo(resultSet->getString(1));
		data.setIntentEnum(resultSet->getString(2));
		data.setStatusEnum(resultSet->getString(3));
		data.setCreatedAt(resultSet->getString(4));
		data.setRemake(resultSet->getString(5));
		data.setReason(resultSet->getString(6));
		return data;
	}
};

/**
 * 盘点单药品明细查询结果 DO（只读）
 */
class InvCheckDrugDO : public BaseDO
{
	// 明细ID
	MYSQL_SYNTHESIZE(string, id, Id);
	// 药品名称
	MYSQL_SYNTHESIZE(string, drug_name, DrugName);
	// 规格
	MYSQL_SYNTHESIZE(string, specification, Specification);
	// 批号
	MYSQL_SYNTHESIZE(string, lot_number, LotNumber);
	// 系统数量
	MYSQL_SYNTHESIZE(double, system_qty, SystemQty);
	// 实盘数量
	MYSQL_SYNTHESIZE(double, actual_qty, ActualQty);
	// 差异数量
	MYSQL_SYNTHESIZE(double, diff_qty, DiffQty);
	// 差异原因
	MYSQL_SYNTHESIZE(string, diff_reason, DiffReason);
public:
	InvCheckDrugDO() : BaseDO("wkf_supply_delivery") {}
	InvCheckDrugDO(InvCheckDrugDO&&) = default;
	InvCheckDrugDO& operator=(InvCheckDrugDO&&) = default;
};

/**
 * 盘点单药品明细字段映射
 * SELECT 列顺序：
 * sd.id(1), m.name(2), m.total_volume(3),
 * sd.lot_number(4), sd.quantity(5), sd.price(6),
 * (sd.price - sd.quantity)(7), sd.status_enum(8)
 */
class InvCheckDrugMapper : public Mapper<InvCheckDrugDO>
{
public:
	InvCheckDrugDO mapper(ResultSet* resultSet) const override
	{
		InvCheckDrugDO data;
		data.setId(resultSet->getString(1));
		data.setDrugName(resultSet->getString(2));
		data.setSpecification(resultSet->getString(3));
		data.setLotNumber(resultSet->getString(4));
		data.setSystemQty(resultSet->getDouble(5));
		data.setActualQty(resultSet->getDouble(6));
		data.setDiffQty(resultSet->getDouble(7));
		data.setDiffReason(resultSet->getString(8));
		return data;
	}
};

#endif // !_INVENTORY_CHECK_MAPPER_
