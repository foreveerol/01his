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
#ifndef _SUPPLY_REJECT_MAPPER_
#define _SUPPLY_REJECT_MAPPER_

#include "Mapper.h"
#include "../../domain/do/supply/SupplyRejectDO.h"

/**
 * Supply reject field mapping
 * SELECT column order:
 * id(1), bus_no(2), type_enum(3), status_enum(4),
 * item_quantity(5), total_quantity(6), item_id(7), item_table(8),
 * lot_number(9), source_location_id(10), purpose_location_id(11),
 * applicant_id(12), apply_time(13), approver_id(14), approval_time(15),
 * version(16), is_deleted(17)
 */
class SupplyRejectMapper : public Mapper<SupplyRejectDO>
{
public:
	SupplyRejectDO mapper(ResultSet* resultSet) const override
	{
		SupplyRejectDO data;
		data.setId(resultSet->getString(1));
		data.setBusNo(resultSet->getString(2));
		data.setTypeEnum(resultSet->getString(3));
		data.setStatusEnum(resultSet->getString(4));
		data.setItemQuantity(resultSet->getString(5));
		data.setTotalQuantity(resultSet->getString(6));
		data.setItemId(resultSet->getString(7));
		data.setItemTable(resultSet->getString(8));
		data.setLotNumber(resultSet->getString(9));
		data.setSourceLocationId(resultSet->getString(10));
		data.setPurposeLocationId(resultSet->getString(11));
		data.setApplicantId(resultSet->getString(12));
		data.setApplyTime(resultSet->getString(13));
		data.setApproverId(resultSet->getString(14));
		data.setApprovalTime(resultSet->getString(15));
		data.setVersion(resultSet->getInt(16));
		data.setIsDeleted(resultSet->getInt(17));
		return data;
	}
};

/**
 * Supply reject field mapping - shared_ptr version
 */
class PtrSupplyRejectMapper : public Mapper<PtrSupplyRejectDO>
{
public:
	PtrSupplyRejectDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<SupplyRejectDO>();
		data->setId(resultSet->getString(1));
		data->setBusNo(resultSet->getString(2));
		data->setTypeEnum(resultSet->getString(3));
		data->setStatusEnum(resultSet->getString(4));
		data->setItemQuantity(resultSet->getString(5));
		data->setTotalQuantity(resultSet->getString(6));
		data->setItemId(resultSet->getString(7));
		data->setItemTable(resultSet->getString(8));
		data->setLotNumber(resultSet->getString(9));
		data->setSourceLocationId(resultSet->getString(10));
		data->setPurposeLocationId(resultSet->getString(11));
		data->setApplicantId(resultSet->getString(12));
		data->setApplyTime(resultSet->getString(13));
		data->setApproverId(resultSet->getString(14));
		data->setApprovalTime(resultSet->getString(15));
		data->setVersion(resultSet->getInt(16));
		data->setIsDeleted(resultSet->getInt(17));
		return data;
	}
};

#endif // !_SUPPLY_REJECT_MAPPER_
