#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 14:21:55

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
#ifndef _SUPPLY_DELETE_MAPPER_
#define _SUPPLY_DELETE_MAPPER_

#include "Mapper.h"
#include "../../domain/do/supply/SupplyDeleteDO.h"

/**
 * Supply delete field mapping
 * SELECT column order:
 * id(1), bus_no(2), type_enum(3), status_enum(4),
 * item_id(5), item_table(6), lot_number(7),
 * version(8), is_deleted(9), updated_at(10),
 * deleted_at(11), deleted_by(12), updated_by(13)
 */
class SupplyDeleteMapper : public Mapper<SupplyDeleteDO>
{
public:
	SupplyDeleteDO mapper(ResultSet* resultSet) const override
	{
		SupplyDeleteDO data;
		data.setId(resultSet->getString(1));
		data.setBusNo(resultSet->getString(2));
		data.setTypeEnum(resultSet->getString(3));
		data.setStatusEnum(resultSet->getString(4));
		data.setItemId(resultSet->getString(5));
		data.setItemTable(resultSet->getString(6));
		data.setLotNumber(resultSet->getString(7));
		data.setVersion(resultSet->getInt(8));
		data.setIsDeleted(resultSet->getInt(9));
		data.setUpdatedAt(resultSet->getString(10));
		data.setDeletedAt(resultSet->getString(11));
		data.setDeletedBy(resultSet->getString(12));
		data.setUpdatedBy(resultSet->getString(13));
		return data;
	}
};

/**
 * Supply delete field mapping - shared_ptr version
 */
class PtrSupplyDeleteMapper : public Mapper<PtrSupplyDeleteDO>
{
public:
	PtrSupplyDeleteDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<SupplyDeleteDO>();
		data->setId(resultSet->getString(1));
		data->setBusNo(resultSet->getString(2));
		data->setTypeEnum(resultSet->getString(3));
		data->setStatusEnum(resultSet->getString(4));
		data->setItemId(resultSet->getString(5));
		data->setItemTable(resultSet->getString(6));
		data->setLotNumber(resultSet->getString(7));
		data->setVersion(resultSet->getInt(8));
		data->setIsDeleted(resultSet->getInt(9));
		data->setUpdatedAt(resultSet->getString(10));
		data->setDeletedAt(resultSet->getString(11));
		data->setDeletedBy(resultSet->getString(12));
		data->setUpdatedBy(resultSet->getString(13));
		return data;
	}
};

#endif // !_SUPPLY_DELETE_MAPPER_
