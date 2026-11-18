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
#ifndef _OUTPATIENT_RECORD_MAPPER_
#define _OUTPATIENT_RECORD_MAPPER_

#include "Mapper.h"

/**
 * 门诊发药/退药记录查询结果 DO（只读）
 * 用于展示完整的门诊药品记录信息
 */
class OutpatientRecordDO : public BaseDO
{
	// 处方号
	MYSQL_SYNTHESIZE(string, prescription_no, PrescriptionNo);
	// 记录类型（发药/退药）
	MYSQL_SYNTHESIZE(string, record_type, RecordType);
	// 患者姓名
	MYSQL_SYNTHESIZE(string, patient_name, PatientName);
	// 门诊就诊号
	MYSQL_SYNTHESIZE(string, outpatient_no, OutpatientNo);
	// 药品名称
	MYSQL_SYNTHESIZE(string, drug_name, DrugName);
	// 药品规格
	MYSQL_SYNTHESIZE(string, specification, Specification);
	// 发药数量
	MYSQL_SYNTHESIZE(string, quantity, Quantity);
	// Unit price
	MYSQL_SYNTHESIZE(double, unit_price, UnitPrice);
	// Total price
	MYSQL_SYNTHESIZE(double, total_price, TotalPrice);
	// 批号
	MYSQL_SYNTHESIZE(string, lot_number, LotNumber);
	// 追溯码
	MYSQL_SYNTHESIZE(string, trace_code, TraceCode);
	// 生产厂家
	MYSQL_SYNTHESIZE(string, manufacturer, Manufacturer);
	// 科室名称
	MYSQL_SYNTHESIZE(string, department, Department);
	// 发药日期
	MYSQL_SYNTHESIZE(string, dispense_date, DispenseDate);
	// 药房名称
	MYSQL_SYNTHESIZE(string, pharmacy, Pharmacy);
	// 发药人姓名
	MYSQL_SYNTHESIZE(string, dispense_name, DispenseName);
public:
	OutpatientRecordDO() : BaseDO("med_medication_dispense") {}
	OutpatientRecordDO(OutpatientRecordDO&&) = default;
	OutpatientRecordDO& operator=(OutpatientRecordDO&&) = default;
};

/**
 * 门诊记录字段映射
 * SELECT 列顺序（与SQL一致，位置不能错）：
 * req.prescription_no(1), d.dispense_enum(2), p.name(3),
 * e.bus_no(4), m.name(5), m.total_volume(6),
 * d.dispense_quantity(7), COALESCE(c.unit_price,0)(8), COALESCE(c.total_price,0)(9),
 * d.lot_number(10), d.trace_no(11),
 * COALESCE(m.manufacturer_text,'')(12), COALESCE(req_loc.name,'')(13),
 * d.dispense_time(14), COALESCE(loc.name,'')(15), COALESCE(pr.name,'')(16)
 * Note: c = adm_charge_item (收费项表),通过dispense_id关联d.id
 */
class OutpatientRecordMapper : public Mapper<OutpatientRecordDO>
{
public:
	OutpatientRecordDO mapper(ResultSet* resultSet) const override
	{
		OutpatientRecordDO data;
		data.setPrescriptionNo(resultSet->getString(1));
		data.setRecordType(resultSet->getString(2));
		data.setPatientName(resultSet->getString(3));
		data.setOutpatientNo(resultSet->getString(4));
		data.setDrugName(resultSet->getString(5));
		data.setSpecification(resultSet->getString(6));
		data.setQuantity(resultSet->getString(7));
		data.setUnitPrice(resultSet->getDouble(8));
		data.setTotalPrice(resultSet->getDouble(9));
		data.setLotNumber(resultSet->getString(10));
		data.setTraceCode(resultSet->getString(11));
		data.setManufacturer(resultSet->getString(12));
		data.setDepartment(resultSet->getString(13));
		data.setDispenseDate(resultSet->getString(14));
		data.setPharmacy(resultSet->getString(15));
		data.setDispenseName(resultSet->getString(16));
		return data;
	}
};

#endif // !_OUTPATIENT_RECORD_MAPPER_