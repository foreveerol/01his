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
#include "stdafx.h"
#include "InpatientRecordDAO.h"

std::string InpatientRecordDAO::queryConditionBuilder(const InpatientRecordQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE d.is_deleted=0";

	if (query->drugName && !query->drugName->empty()) {
		// Support fuzzy search by drug name, code (bus_no), and pinyin (py_str)
		sqlCondition << " AND (m.name LIKE CONCAT('%',?,'%')"
			<< " OR m.bus_no LIKE CONCAT('%',?,'%')"
			<< " OR m.py_str LIKE CONCAT('%',?,'%'))";
		std::string kw = query->drugName.getValue("");
		SQLPARAMS_PUSH(params, "s", std::string, kw);
		SQLPARAMS_PUSH(params, "s", std::string, kw);
		SQLPARAMS_PUSH(params, "s", std::string, kw);
	}

	if (query->recordType && !query->recordType->empty()) {
		sqlCondition << " AND d.dispense_enum=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->recordType.getValue(""));
	}

	if (query->pharmacy && !query->pharmacy->empty()) {
		sqlCondition << " AND disp_loc.name LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->pharmacy.getValue(""));
	}

	if (query->projectType && !query->projectType->empty()) {
		sqlCondition << " AND req.category_enum=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->projectType.getValue(""));
	}

	if (query->dispenseName && !query->dispenseName->empty()) {
		sqlCondition << " AND pr.name LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->dispenseName.getValue(""));
	}

	if (query->name && !query->name->empty()) {
		sqlCondition << " AND p.name LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}

	if (query->hospitalizationNo && !query->hospitalizationNo->empty()) {
		sqlCondition << " AND e.bus_no=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->hospitalizationNo.getValue(""));
	}

	if (query->recordNo && !query->recordNo->empty()) {
		sqlCondition << " AND d.bus_no=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->recordNo.getValue(""));
	}

	if (query->startDate && !query->startDate->empty()) {
		sqlCondition << " AND d.dispense_time>=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->startDate.getValue(""));
	}
	if (query->endDate && !query->endDate->empty()) {
		sqlCondition << " AND d.dispense_time<=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->endDate.getValue(""));
	}

	return sqlCondition.str();
}

std::list<InpatientRecordDO> InpatientRecordDAO::selectWithCondition(const InpatientRecordQuery::Wrapper& query)
{
	SqlParams params;
	std::string sql = "SELECT "
		"req.prescription_no, d.dispense_enum, p.name, "
		"e.bus_no, COALESCE(enc_loc.name,''), '' AS bed_no, "
		"m.name, m.total_volume, "
		"d.dispense_quantity, 0 AS unit_price, 0 AS total_amount, "
		"d.lot_number, d.trace_no, "
		"COALESCE(m.manufacturer_text,''), d.bus_no, "
		"COALESCE(req_loc.name,'') "
		"FROM med_medication_dispense d "
		"LEFT JOIN med_medication_request req ON d.med_req_id=req.id AND req.is_deleted=0 "
		"LEFT JOIN med_medication_definition m ON d.medication_id=m.id AND m.is_deleted=0 "
		"LEFT JOIN adm_patient p ON d.patient_id=p.id AND p.is_deleted=0 "
		"LEFT JOIN adm_encounter e ON d.encounter_id=e.id AND e.is_deleted=0 "
		"LEFT JOIN adm_location enc_loc ON e.location_id=enc_loc.id AND enc_loc.is_deleted=0 "
		"LEFT JOIN adm_location req_loc ON req.location_id=req_loc.id AND req_loc.is_deleted=0 "
		"LEFT JOIN adm_location disp_loc ON d.location_id=disp_loc.id AND disp_loc.is_deleted=0 "
		"LEFT JOIN adm_practitioner pr ON d.practitioner_id=pr.id AND pr.is_deleted=0 ";
	sql += queryConditionBuilder(query, params);
	sql += " ORDER BY d.dispense_time DESC";

	int pageIndex = query->pageIndex ? (int)(*query->pageIndex) : 1;
	int pageSize = query->pageSize ? (int)(*query->pageSize) : 10;
	int offset = (pageIndex - 1) * pageSize;
	sql += " LIMIT " + std::to_string(pageSize) + " OFFSET " + std::to_string(offset);

	return sqlSession->executeQuery<InpatientRecordDO>(sql, InpatientRecordMapper(), params);
}

uint64_t InpatientRecordDAO::countWithCondition(const InpatientRecordQuery::Wrapper& query)
{
	SqlParams params;
	std::string sql = "SELECT COUNT(DISTINCT d.id) FROM med_medication_dispense d "
		"LEFT JOIN med_medication_request req ON d.med_req_id=req.id AND req.is_deleted=0 "
		"LEFT JOIN med_medication_definition m ON d.medication_id=m.id AND m.is_deleted=0 "
		"LEFT JOIN adm_patient p ON d.patient_id=p.id AND p.is_deleted=0 "
		"LEFT JOIN adm_encounter e ON d.encounter_id=e.id AND e.is_deleted=0 "
		"LEFT JOIN adm_location enc_loc ON e.location_id=enc_loc.id AND enc_loc.is_deleted=0 "
		"LEFT JOIN adm_location req_loc ON req.location_id=req_loc.id AND req_loc.is_deleted=0 "
		"LEFT JOIN adm_location disp_loc ON d.location_id=disp_loc.id AND disp_loc.is_deleted=0 "
		"LEFT JOIN adm_practitioner pr ON d.practitioner_id=pr.id AND pr.is_deleted=0 ";
	sql += queryConditionBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}
