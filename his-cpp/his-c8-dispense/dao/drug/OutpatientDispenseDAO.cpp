/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 14:26:52

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
#include "stdafx.h"
#include "OutpatientdispenseDAO.h"
#include "OutpatientdispenseMapper.h"



inline std::string OutpatientDispenseDao::query_condition_builder(const OutpatientDispenseQuery::Wrapper& query, SqlParams& params)

{
	
	stringstream sqlCondition;
	sqlCondition << " WHERE 1=1 AND d.is_deleted = 0";
	if (query->name) {

		sqlCondition << "AND p.name LIKE CONCAT('%', ? , '%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}
	if (query->sex) {

		sqlCondition << " AND p.gender_enum = ?";
		SQLPARAMS_PUSH(params, "s", std::string, query->sex.getValue(""));
	}
	if (query->dispense_status) {

		sqlCondition << " AND d.status_enmu = ?";
		SQLPARAMS_PUSH(params, "s", string, query->dispense_status.getValue(""));

	}

	return sqlCondition.str();
}

std::list<OutpatientDispenseDo> OutpatientDispenseDao::select_with_condition(const OutpatientDispenseQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT "
		"d.status_enum, d.quantity, d.dispense_quantity, "
		"d.lot_number, req.prescription_no, "
		"m.name,m.total_volume,m.manufacturer_text,p.name,p.gender_enum,e.bus_no,loc.name"
		"FROM med_medication_dispense d "
		"LEFT JOIN med_medication_request req ON d.med_req_id=req.id AND req.is_deleted=0 "
		"LEFT JOIN med_medication_definition m ON d.medication_id=m.id AND m.is_deleted=0 "
		"LEFT JOIN adm_patient p ON d.patient_id=p.id AND p.is_deleted=0 "
		"LEFT JOIN adm_encounter e ON d.encounter_id=e.id AND e.is_deleted=0 "
		"LEFT JOIN adm_location loc ON d.location_id=loc.id AND loc.is_deleted=0 ";

	// 构建查询条件
	sql += query_condition_builder(query, params);
	// 排序
	sql += " ORDER BY d.dispense_time DESC";
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);
	return sqlSession->executeQuery<OutpatientDispenseDo>(sql, OutpatientdispenseMapper(), params);
}

int64_t OutpatientDispenseDao::count_with_condition(const OutpatientDispenseQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT COUNT (DISTINCT d.id) FROM med_medication_dispense d "
		"LEFT JOIN med_medication_request req ON d.med_req_id=req.id AND req.is_deleted=0 "
		"LEFT JOIN med_medication_definition m ON d.medication_id=m.id AND m.is_deleted=0 "
		"LEFT JOIN adm_patient p ON d.patient_id=p.id AND p.is_deleted=0 "
		"LEFT JOIN adm_encounter e ON d.encounter_id=e.id AND e.is_deleted=0 "
		"LEFT JOIN adm_location loc ON d.location_id=loc.id AND loc.is_deleted=0 ";
	sql += query_condition_builder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<OutpatientDispenseDo> OutpatientDispenseDao::select_drug_detail_with_condition(const OutpatientDrugDetailQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT "
		"d.status_enum, d.quantity, d.dispense_quantity, "
		"d.lot_number, req.prescription_no, "
		"m.name,m.total_volume,m.manufacturer_text,p.name,p.gender_enum,e.bus_no,loc.name"
		"FROM med_medication_dispense d "
		"LEFT JOIN med_medication_request req ON d.med_req_id=req.id AND req.is_deleted=0 "
		"LEFT JOIN med_medication_definition m ON d.medication_id=m.id AND m.is_deleted=0 "
		"LEFT JOIN adm_patient p ON d.patient_id=p.id AND p.is_deleted=0 "
		"LEFT JOIN adm_encounter e ON d.encounter_id=e.id AND e.is_deleted=0 "
		"WHERE req.prescription_no = ? AND d.is_deleted=0";
	SQLPARAMS_PUSH(params, "s", std::string, query->prescription_no.getValue(""));
	sql += " ORDER BY d.dispense_time DESC";
	return sqlSession->executeQuery<OutpatientDispenseDo>(sql, OutpatientdispenseMapper(), params);
}
