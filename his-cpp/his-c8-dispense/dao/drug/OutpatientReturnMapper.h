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
#ifndef _OUTPATIENT_RETURN_MAPPER_
#define _OUTPATIENT_RETURN_MAPPER_

#include "Mapper.h"

/**
 * Outpatient return queue query result DO (read-only)
 */
class OutpatientReturnQueueDO : public BaseDO
{
	// Return record ID
	MYSQL_SYNTHESIZE(string, id, Id);
	// Patient name
	MYSQL_SYNTHESIZE(string, patient_name, PatientName);
	// Return date
	MYSQL_SYNTHESIZE(string, return_date, ReturnDate);
	// Drug count
	MYSQL_SYNTHESIZE(int, drug_count, DrugCount);
	// Return status
	MYSQL_SYNTHESIZE(string, return_status, ReturnStatus);
public:
	OutpatientReturnQueueDO() : BaseDO("med_medication_dispense") {}
	OutpatientReturnQueueDO(OutpatientReturnQueueDO&&) = default;
	OutpatientReturnQueueDO& operator=(OutpatientReturnQueueDO&&) = default;
};

/**
 * Outpatient return queue field mapping
 * SELECT column order:
 * d.id(1), p.name(2), d.dispense_time(3),
 * COUNT(d.id)(4), d.status_enum(5)
 */
class OutpatientReturnQueueMapper : public Mapper<OutpatientReturnQueueDO>
{
public:
	OutpatientReturnQueueDO mapper(ResultSet* resultSet) const override
	{
		OutpatientReturnQueueDO data;
		data.setId(resultSet->getString(1));
		data.setPatientName(resultSet->getString(2));
		data.setReturnDate(resultSet->getString(3));
		data.setDrugCount(resultSet->getInt(4));
		data.setReturnStatus(resultSet->getString(5));
		return data;
	}
};

/**
 * Outpatient return detail query result DO (read-only)
 */
class OutpatientReturnDetailDO : public BaseDO
{
	// Drug ID
	MYSQL_SYNTHESIZE(string, drug_id, DrugId);
	// Drug name
	MYSQL_SYNTHESIZE(string, drug_name, DrugName);
	// Quantity
	MYSQL_SYNTHESIZE(int, quantity, Quantity);
	// Dispense date
	MYSQL_SYNTHESIZE(string, dispense_date, DispenseDate);
public:
	OutpatientReturnDetailDO() : BaseDO("med_medication_dispense") {}
	OutpatientReturnDetailDO(OutpatientReturnDetailDO&&) = default;
	OutpatientReturnDetailDO& operator=(OutpatientReturnDetailDO&&) = default;
};

/**
 * Outpatient return detail field mapping
 * SELECT column order:
 * d.id(1), m.name(2), d.dispense_quantity(3), d.dispense_time(4)
 */
class OutpatientReturnDetailMapper : public Mapper<OutpatientReturnDetailDO>
{
public:
	OutpatientReturnDetailDO mapper(ResultSet* resultSet) const override
	{
		OutpatientReturnDetailDO data;
		data.setDrugId(resultSet->getString(1));
		data.setDrugName(resultSet->getString(2));
		data.setQuantity(resultSet->getInt(3));
		data.setDispenseDate(resultSet->getString(4));
		return data;
	}
};

#endif // !_OUTPATIENT_RETURN_MAPPER_
