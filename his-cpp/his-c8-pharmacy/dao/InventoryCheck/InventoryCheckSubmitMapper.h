#pragma once

#ifndef _INVENTORY_CHECK_SUBMIT_MAPPER_
#define _INVENTORY_CHECK_SUBMIT_MAPPER_
#include "Mapper.h"
#include "../../domain/do/pharmacy/InventoryCheckDO.h"
#include "../../domain/do/pharmacy/MedicationDefinitionDO.h"

/**
 * 普通实体Mapper
 */
class InventoryCheckSubmitMapper : public Mapper<InventoryCheckDO>
{
public:
	InventoryCheckDO mapper(ResultSet* resultSet) const override
	{
		InventoryCheckDO data;
		data.setId(resultSet->getInt64(1));
		data.setStatusEnum(resultSet->getString(2));
		data.setApproverId(resultSet->getInt64(3));
		data.setApprovalTime(resultSet->getString(4));
		data.setApplicantId(resultSet->getInt64(5));
		data.setApplyTime(resultSet->getString(6));
		data.setRemake(resultSet->getString(7));
		data.setTotalPrice(resultSet->getDouble(8));
		return data;
	}
};

/**
 * 智能指针DO专用Mapper（供selectById查询使用）
 */
class PtrInventoryCheckSubmitMapper : public Mapper<PtrInventoryCheckDO>
{
public:
	PtrInventoryCheckDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<InventoryCheckDO>();
		data->setId(resultSet->getInt64(1));
		data->setStatusEnum(resultSet->getString(2));
		data->setApproverId(resultSet->getInt64(3));
		data->setApprovalTime(resultSet->getString(4));
		data->setApplicantId(resultSet->getInt64(5));
		data->setApplyTime(resultSet->getString(6));
		data->setRemake(resultSet->getString(7));
		data->setTotalPrice(resultSet->getDouble(8));
		return data;
	}
};
#endif // _INVENTORY_CHECK_SUBMIT_MAPPER_
