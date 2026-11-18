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
#ifndef _DRUG_RETURN_MAPPER_
#define _DRUG_RETURN_MAPPER_

#include "Mapper.h"

/**
 * Inpatient return queue query result DO (read-only)
 */
class InpatientReturnQueueDO : public BaseDO
{
	// Patient name
	MYSQL_SYNTHESIZE(string, patient_name, PatientName);
	// Hospitalization number
	MYSQL_SYNTHESIZE(string, hospitalization_no, HospitalizationNo);
	// Ward
	MYSQL_SYNTHESIZE(string, ward, Ward);
	// Bed number
	MYSQL_SYNTHESIZE(string, bed_no, BedNo);
	// Refund status
	MYSQL_SYNTHESIZE(string, refund_status, RefundStatus);
public:
	InpatientReturnQueueDO() : BaseDO("med_medication_dispense") {}
	InpatientReturnQueueDO(InpatientReturnQueueDO&&) = default;
	InpatientReturnQueueDO& operator=(InpatientReturnQueueDO&&) = default;
};

/**
 * Inpatient return queue field mapping
 * SELECT column order:
 * p.name(1), e.bus_no(2), COALESCE(enc_loc.name,'')(3),
 * '' AS bed_no(4), d.status_enum(5)
 */
class InpatientReturnQueueMapper : public Mapper<InpatientReturnQueueDO>
{
public:
	InpatientReturnQueueDO mapper(ResultSet* resultSet) const override
	{
		InpatientReturnQueueDO data;
		data.setPatientName(resultSet->getString(1));
		data.setHospitalizationNo(resultSet->getString(2));
		data.setWard(resultSet->getString(3));
		data.setBedNo(resultSet->getString(4));
		data.setRefundStatus(resultSet->getString(5));
		return data;
	}
};

/**
 * Inpatient return drug detail query result DO (read-only)
 */
class InpatientReturnDrugDO : public BaseDO
{
	// Detail ID
	MYSQL_SYNTHESIZE(string, detail_id, DetailId);
	// Serial number
	MYSQL_SYNTHESIZE(int, serial_no, SerialNo);
	// Drug name
	MYSQL_SYNTHESIZE(string, drug_name, DrugName);
	// Quantity
	MYSQL_SYNTHESIZE(string, quantity, Quantity);
	// Dispense date
	MYSQL_SYNTHESIZE(string, dispense_date, DispenseDate);
public:
	InpatientReturnDrugDO() : BaseDO("med_medication_dispense") {}
	InpatientReturnDrugDO(InpatientReturnDrugDO&&) = default;
	InpatientReturnDrugDO& operator=(InpatientReturnDrugDO&&) = default;
};

/**
 * Inpatient return drug detail field mapping
 * SELECT column order:
 * d.id(1), ROW_NUMBER(2), m.name(3), d.dispense_quantity(4), d.dispense_time(5)
 */
class InpatientReturnDrugMapper : public Mapper<InpatientReturnDrugDO>
{
public:
	InpatientReturnDrugDO mapper(ResultSet* resultSet) const override
	{
		InpatientReturnDrugDO data;
		data.setDetailId(resultSet->getString(1));
		data.setSerialNo(resultSet->getInt(2));
		data.setDrugName(resultSet->getString(3));
		data.setQuantity(resultSet->getString(4));
		data.setDispenseDate(resultSet->getString(5));
		return data;
	}
};

/**
 * Inpatient return patient info query result DO (read-only)
 */
class InpatientReturnPatientDO : public BaseDO
{
	// Patient name
	MYSQL_SYNTHESIZE(string, name, Name);
	// Gender
	MYSQL_SYNTHESIZE(string, gender, Gender);
	// Birth date (used to calculate age)
	MYSQL_SYNTHESIZE(string, birth_date, BirthDate);
	// Hospitalization number
	MYSQL_SYNTHESIZE(string, hospitalization_no, HospitalizationNo);
	// Ward
	MYSQL_SYNTHESIZE(string, ward, Ward);
	// Bed number
	MYSQL_SYNTHESIZE(string, bed_no, BedNo);
	// Refund status
	MYSQL_SYNTHESIZE(string, refund_status, RefundStatus);
public:
	InpatientReturnPatientDO() : BaseDO("med_medication_dispense") {}
	InpatientReturnPatientDO(InpatientReturnPatientDO&&) = default;
	InpatientReturnPatientDO& operator=(InpatientReturnPatientDO&&) = default;
};

/**
 * Inpatient return patient info field mapping
 * SELECT column order:
 * p.name(1), p.gender_enum(2), p.birth_date(3),
 * e.bus_no(4), COALESCE(enc_loc.name,'')(5),
 * '' AS bed_no(6), d.status_enum(7)
 */
class InpatientReturnPatientMapper : public Mapper<InpatientReturnPatientDO>
{
public:
	InpatientReturnPatientDO mapper(ResultSet* resultSet) const override
	{
		InpatientReturnPatientDO data;
		data.setName(resultSet->getString(1));
		data.setGender(resultSet->getString(2));
		data.setBirthDate(resultSet->getString(3));
		data.setHospitalizationNo(resultSet->getString(4));
		data.setWard(resultSet->getString(5));
		data.setBedNo(resultSet->getString(6));
		data.setRefundStatus(resultSet->getString(7));
		return data;
	}
};

#endif // !_DRUG_RETURN_MAPPER_
