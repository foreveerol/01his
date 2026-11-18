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
#ifndef _STOCKIN_MAPPER_
#define _STOCKIN_MAPPER_

#include "Mapper.h"
#include "../../domain/DoInclude.h"

/**
 * 入库单列表查询结果 DO（只读）
 */
class StockInListDO : public BaseDO
{
	// 入库单号
	MYSQL_SYNTHESIZE(string, bus_no, BusNo);
	// 供应商名称
	MYSQL_SYNTHESIZE(string, supplier_name, SupplierName);
	// 入库日期
	MYSQL_SYNTHESIZE(string, created_at, CreatedAt);
	// 药品数量
	MYSQL_SYNTHESIZE(int, drug_count, DrugCount);
	// 总金额
	MYSQL_SYNTHESIZE(double, total_amount, TotalAmount);
	// 单据状态
	MYSQL_SYNTHESIZE(string, status_enum, StatusEnum);
	// 制单人
	MYSQL_SYNTHESIZE(string, creator, Creator);
public:
	StockInListDO() : BaseDO("wkf_supply_request") {}
	StockInListDO(StockInListDO&&) = default;
	StockInListDO& operator=(StockInListDO&&) = default;
};

/**
 * 入库单列表查询字段映射
 * SELECT 列顺序：
 * sr.bus_no(1), s.name(2), sr.created_at(3),
 * COUNT(sd.id)(4), COALESCE(SUM(sd.quantity * sd.price), 0)(5),
 * sr.status_enum(6), u.name(7)
 */
class StockInMapper : public Mapper<StockInListDO>
{
public:
	StockInListDO mapper(ResultSet* resultSet) const override
	{
		StockInListDO data;
		data.setBusNo(resultSet->getString(1));
		data.setSupplierName(resultSet->getString(2));
		data.setCreatedAt(resultSet->getString(3));
		data.setDrugCount(resultSet->getInt(4));
		data.setTotalAmount(resultSet->getDouble(5));
		data.setStatusEnum(resultSet->getString(6));
		data.setCreator(resultSet->getString(7));
		return data;
	}
};

/**
 * 入库单详情查询结果 DO（只读）
 */
class StockInDetailDO : public BaseDO
{
	// 入库单号
	MYSQL_SYNTHESIZE(string, bus_no, BusNo);
	// 入库类型
	MYSQL_SYNTHESIZE(string, intent_enum, IntentEnum);
	// 单据状态
	MYSQL_SYNTHESIZE(string, status_enum, StatusEnum);
	// 创建时间
	MYSQL_SYNTHESIZE(string, created_at, CreatedAt);
	// 驳回原因/备注
	MYSQL_SYNTHESIZE(string, remake, Remake);
	// 供应商ID
	MYSQL_SYNTHESIZE(string, supplier_id, SupplierId);
	// 供应商名称（JOIN）
	MYSQL_SYNTHESIZE(string, supplier_name, SupplierName);
public:
	StockInDetailDO() : BaseDO("wkf_supply_request") {}
	StockInDetailDO(StockInDetailDO&&) = default;
	StockInDetailDO& operator=(StockInDetailDO&&) = default;
};

/**
 * 入库单详情查询字段映射
 * SELECT 列顺序：
 * sr.bus_no(1), sr.intent_enum(2), sr.status_enum(3),
 * sr.created_at(4), sr.remake(5), sr.supplier_id(6), s.name(7)
 */
class StockInDetailMapper : public Mapper<StockInDetailDO>
{
public:
	StockInDetailDO mapper(ResultSet* resultSet) const override
	{
		StockInDetailDO data;
		data.setBusNo(resultSet->getString(1));
		data.setIntentEnum(resultSet->getString(2));
		data.setStatusEnum(resultSet->getString(3));
		data.setCreatedAt(resultSet->getString(4));
		data.setRemake(resultSet->getString(5));
		data.setSupplierId(resultSet->getString(6));
		data.setSupplierName(resultSet->getString(7));
		return data;
	}
};

/**
 * 入库单药品明细查询结果 DO（只读）
 */
class StockInDrugDetailDO : public BaseDO
{
	// 明细ID
	MYSQL_SYNTHESIZE(string, id, Id);
	// 药品名称
	MYSQL_SYNTHESIZE(string, drug_name, DrugName);
	// 规格
	MYSQL_SYNTHESIZE(string, specification, Specification);
	// 生产厂家
	MYSQL_SYNTHESIZE(string, manufacturer, Manufacturer);
	// 批号
	MYSQL_SYNTHESIZE(string, lot_number, LotNumber);
	// 有效期
	MYSQL_SYNTHESIZE(string, expiration_date, ExpirationDate);
	// 单位
	MYSQL_SYNTHESIZE(string, unit_code, UnitCode);
	// 数量
	MYSQL_SYNTHESIZE(double, quantity, Quantity);
	// 单价
	MYSQL_SYNTHESIZE(double, price, Price);
public:
	StockInDrugDetailDO() : BaseDO("wkf_supply_delivery") {}
	StockInDrugDetailDO(StockInDrugDetailDO&&) = default;
	StockInDrugDetailDO& operator=(StockInDrugDetailDO&&) = default;
};

/**
 * 入库单药品明细字段映射
 * SELECT 列顺序：
 * sd.id(1), m.name(2), m.total_volume(3), m.manufacturer_id->manufacturer(4),
 * sd.lot_number(5), ii.expiration_date(6), sd.unit_code(7),
 * sd.quantity(8), sd.price(9)
 */
class StockInDrugDetailMapper : public Mapper<StockInDrugDetailDO>
{
public:
	StockInDrugDetailDO mapper(ResultSet* resultSet) const override
	{
		StockInDrugDetailDO data;
		data.setId(resultSet->getString(1));
		data.setDrugName(resultSet->getString(2));
		data.setSpecification(resultSet->getString(3));
		data.setManufacturer(resultSet->getString(4));
		data.setLotNumber(resultSet->getString(5));
		data.setExpirationDate(resultSet->getString(6));
		data.setUnitCode(resultSet->getString(7));
		data.setQuantity(resultSet->getDouble(8));
		data.setPrice(resultSet->getDouble(9));
		return data;
	}
};

/**
 * 入库单审批查询结果 DO（只读）
 * 用于撤回/通过/驳回审批时查询订单核心字段
 */
class StockInApprovalDO : public BaseDO
{
	// 主键
	MYSQL_SYNTHESIZE(string, id, Id);
	// 业务号
	MYSQL_SYNTHESIZE(string, bus_no, BusNo);
	// 单据状态
	MYSQL_SYNTHESIZE(string, status_enum, StatusEnum);
	// 申请人ID
	MYSQL_SYNTHESIZE(string, applicant_id, ApplicantId);
	// 药品ID
	MYSQL_SYNTHESIZE(string, item_id, ItemId);
	// 药品数量
	MYSQL_SYNTHESIZE(double, item_quantity, ItemQuantity);
	// 目标库房
	MYSQL_SYNTHESIZE(string, purpose_location_id, PurposeLocationId);
	// 乐观锁版本
	MYSQL_SYNTHESIZE(int, version, Version);
public:
	StockInApprovalDO() : BaseDO("wkf_supply_request") {}
	StockInApprovalDO(StockInApprovalDO&&) = default;
	StockInApprovalDO& operator=(StockInApprovalDO&&) = default;
};

/**
 * 入库单审批查询字段映射
 * SELECT 列顺序：
 * sr.id(1), sr.bus_no(2), sr.status_enum(3),
 * sr.applicant_id(4), sr.item_id(5),
 * sr.item_quantity(6), sr.purpose_location_id(7), sr.version(8)
 */
class StockInApprovalMapper : public Mapper<StockInApprovalDO>
{
public:
	StockInApprovalDO mapper(ResultSet* resultSet) const override
	{
		StockInApprovalDO data;
		data.setId(resultSet->getString(1));
		data.setBusNo(resultSet->getString(2));
		data.setStatusEnum(resultSet->getString(3));
		data.setApplicantId(resultSet->getString(4));
		data.setItemId(resultSet->getString(5));
		data.setItemQuantity(resultSet->getDouble(6));
		data.setPurposeLocationId(resultSet->getString(7));
		data.setVersion(resultSet->getInt(8));
		return data;
	}
};

#endif // !_STOCKIN_MAPPER_
