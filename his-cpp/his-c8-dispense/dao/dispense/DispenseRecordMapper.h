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
#ifndef _DISPENSE_RECORD_MAPPER_
#define _DISPENSE_RECORD_MAPPER_

#include "Mapper.h"
#include "../../domain/do/dispense/DispenseRecordDO.h"

/**
 * 门诊发退药记录字段映射
 * SELECT 字段顺序：
 * d.bus_no(1), d.status_enum(2), d.dispense_time(3),
 * p.name(4), p.id_card(5),
 * e.bus_no(6),
 * m.name(7), m.total_volume(8), m.dose_form_code(9),
 * d.quantity(10), d.dispense_quantity(11), d.unit_code(12), d.lot_number(13),
 * pr.name(14),
 * loc.name(15),
 * req.prescription_no(16), req.requester_id(17),
 * d.created_at(18)
 */
class DispenseRecordMapper : public Mapper<DispenseRecordDO>
{
public:
	DispenseRecordDO mapper(ResultSet* resultSet) const override
	{
		DispenseRecordDO data;
		data.setBusNo(resultSet->getString(1));
		data.setStatusEnum(resultSet->getString(2));
		data.setDispenseTime(resultSet->getString(3));
		data.setPatientName(resultSet->getString(4));
		data.setIdCard(resultSet->getString(5));
		data.setEncounterBusNo(resultSet->getString(6));
		data.setMedicationName(resultSet->getString(7));
		data.setTotalVolume(resultSet->getString(8));
		data.setDoseFormCode(resultSet->getString(9));
		data.setQuantity(resultSet->getString(10));
		data.setDispenseQuantity(resultSet->getString(11));
		data.setUnitCode(resultSet->getString(12));
		data.setLotNumber(resultSet->getString(13));
		data.setPractitionerName(resultSet->getString(14));
		data.setLocationName(resultSet->getString(15));
		data.setPrescriptionNo(resultSet->getString(16));
		data.setRequesterId(resultSet->getString(17));
		data.setCreatedAt(resultSet->getString(18));
		return data;
	}
};

#endif // !_DISPENSE_RECORD_MAPPER_
