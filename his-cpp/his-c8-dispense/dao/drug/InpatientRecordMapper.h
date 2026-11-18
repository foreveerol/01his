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
#ifndef _INPATIENT_RECORD_MAPPER_
#define _INPATIENT_RECORD_MAPPER_

#include "Mapper.h"

/**
 * Inpatient dispense/return record query result DO (read-only)
 * Used for displaying complete inpatient drug record information
 */
class InpatientRecordDO : public BaseDO
{
	// Prescription number
	MYSQL_SYNTHESIZE(string, prescription_no, PrescriptionNo);
	// Record type (dispense/return)
	MYSQL_SYNTHESIZE(string, record_type, RecordType);
	// Patient name
	MYSQL_SYNTHESIZE(string, patient_name, PatientName);
	// Hospitalization number
	MYSQL_SYNTHESIZE(string, hospitalization_no, HospitalizationNo);
	// Ward
	MYSQL_SYNTHESIZE(string, ward, Ward);
	// Bed number
	MYSQL_SYNTHESIZE(string, bed_no, BedNo);
	// Drug name
	MYSQL_SYNTHESIZE(string, drug_name, DrugName);
	// Specification
	MYSQL_SYNTHESIZE(string, specification, Specification);
	// Quantity
	MYSQL_SYNTHESIZE(string, quantity, Quantity);
	// Unit price
	MYSQL_SYNTHESIZE(double, unit_price, UnitPrice);
	// Total amount
	MYSQL_SYNTHESIZE(double, total_amount, TotalAmount);
	// Batch number
	MYSQL_SYNTHESIZE(string, batch_no, BatchNo);
	// Trace code
	MYSQL_SYNTHESIZE(string, trace_code, TraceCode);
	// Manufacturer
	MYSQL_SYNTHESIZE(string, manufacturer, Manufacturer);
	// Summary number
	MYSQL_SYNTHESIZE(string, summary_no, SummaryNo);
	// Department name
	MYSQL_SYNTHESIZE(string, dept_name, DeptName);
public:
	InpatientRecordDO() : BaseDO("med_medication_dispense") {}
	InpatientRecordDO(InpatientRecordDO&&) = default;
	InpatientRecordDO& operator=(InpatientRecordDO&&) = default;
};

/**
 * Inpatient record field mapping
 * SELECT column order:
 * req.prescription_no(1), d.dispense_enum(2), p.name(3),
 * e.bus_no(4), COALESCE(enc_loc.name,'')(5), '' AS bed_no(6),
 * m.name(7), m.total_volume(8),
 * d.dispense_quantity(9), 0 AS unit_price(10), 0 AS total_amount(11),
 * d.lot_number(12), d.trace_no(13),
 * COALESCE(m.manufacturer_text,'')(14), d.bus_no(15),
 * COALESCE(req_loc.name,'')(16)
 */
class InpatientRecordMapper : public Mapper<InpatientRecordDO>
{
public:
	InpatientRecordDO mapper(ResultSet* resultSet) const override
	{
		InpatientRecordDO data;
		data.setPrescriptionNo(resultSet->getString(1));
		data.setRecordType(resultSet->getString(2));
		data.setPatientName(resultSet->getString(3));
		data.setHospitalizationNo(resultSet->getString(4));
		data.setWard(resultSet->getString(5));
		data.setBedNo(resultSet->getString(6));
		data.setDrugName(resultSet->getString(7));
		data.setSpecification(resultSet->getString(8));
		data.setQuantity(resultSet->getString(9));
		data.setUnitPrice(resultSet->getDouble(10));
		data.setTotalAmount(resultSet->getDouble(11));
		data.setBatchNo(resultSet->getString(12));
		data.setTraceCode(resultSet->getString(13));
		data.setManufacturer(resultSet->getString(14));
		data.setSummaryNo(resultSet->getString(15));
		data.setDeptName(resultSet->getString(16));
		return data;
	}
};

#endif // !_INPATIENT_RECORD_MAPPER_
