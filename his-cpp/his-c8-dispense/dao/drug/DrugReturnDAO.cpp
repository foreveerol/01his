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
#include "DrugReturnDAO.h"

std::list<InpatientReturnQueueDO> DrugReturnDAO::selectReturnQueue(const InpatientReturnQuery::Wrapper& query)
{
	SqlParams params;
	std::string sql = "SELECT p.name, e.bus_no, COALESCE(enc_loc.name,''), "
		"'' AS bed_no, d.status_enum "
		"FROM med_medication_dispense d "
		"LEFT JOIN adm_patient p ON d.patient_id=p.id AND p.is_deleted=0 "
		"LEFT JOIN adm_encounter e ON d.encounter_id=e.id AND e.is_deleted=0 "
		"LEFT JOIN adm_location enc_loc ON e.location_id=enc_loc.id AND enc_loc.is_deleted=0 "
		"WHERE d.is_deleted=0 AND d.status_enum='DISPENSED'";

	if (query->hospitalizationNo && !query->hospitalizationNo->empty()) {
		sql += " AND e.bus_no=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->hospitalizationNo.getValue(""));
	}

	if (query->name && !query->name->empty()) {
		sql += " AND p.name LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}

	if (query->ward && !query->ward->empty()) {
		sql += " AND enc_loc.name LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->ward.getValue(""));
	}

	sql += " GROUP BY p.id, e.id, enc_loc.name, d.status_enum ORDER BY p.name ASC";

	int pageIndex = query->pageIndex ? (int)(*query->pageIndex) : 1;
	int pageSize = query->pageSize ? (int)(*query->pageSize) : 10;
	if (pageIndex < 1) pageIndex = 1;
	if (pageSize <= 0 || pageSize > 200) pageSize = 200;
	int offset = (pageIndex - 1) * pageSize;
	sql += " LIMIT " + std::to_string(pageSize) + " OFFSET " + std::to_string(offset);

	return sqlSession->executeQuery<InpatientReturnQueueDO>(sql, InpatientReturnQueueMapper(), params);
}

uint64_t DrugReturnDAO::countReturnQueue(const InpatientReturnQuery::Wrapper& query)
{
	SqlParams params;
	std::string sql = "SELECT COUNT(DISTINCT d.patient_id) FROM med_medication_dispense d "
		"LEFT JOIN adm_patient p ON d.patient_id=p.id AND p.is_deleted=0 "
		"LEFT JOIN adm_encounter e ON d.encounter_id=e.id AND e.is_deleted=0 "
		"LEFT JOIN adm_location enc_loc ON e.location_id=enc_loc.id AND enc_loc.is_deleted=0 "
		"WHERE d.is_deleted=0 AND d.status_enum='DISPENSED'";

	if (query->hospitalizationNo && !query->hospitalizationNo->empty()) {
		sql += " AND e.bus_no=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->hospitalizationNo.getValue(""));
	}

	if (query->name && !query->name->empty()) {
		sql += " AND p.name LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
	}

	if (query->ward && !query->ward->empty()) {
		sql += " AND enc_loc.name LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->ward.getValue(""));
	}

	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<InpatientReturnDrugDO> DrugReturnDAO::selectReturnDrugs(const std::string& hospitalizationNo)
{
	SqlParams params;
	std::string sql = "SELECT d.id, ROW_NUMBER() OVER (ORDER BY d.id), "
		"m.name, d.dispense_quantity, d.dispense_time "
		"FROM med_medication_dispense d "
		"LEFT JOIN med_medication_definition m ON d.medication_id=m.id AND m.is_deleted=0 "
		"LEFT JOIN adm_encounter e ON d.encounter_id=e.id AND e.is_deleted=0 "
		"WHERE d.is_deleted=0 AND d.status_enum='DISPENSED' AND e.bus_no=?";
	SQLPARAMS_PUSH(params, "s", std::string, hospitalizationNo);
	return sqlSession->executeQuery<InpatientReturnDrugDO>(sql, InpatientReturnDrugMapper(), params);
}

std::list<InpatientReturnPatientDO> DrugReturnDAO::selectReturnPatient(const std::string& hospitalizationNo)
{
	SqlParams params;
	std::string sql = "SELECT p.name, p.gender_enum, p.birth_date, "
		"e.bus_no, COALESCE(enc_loc.name,''), '' AS bed_no, d.status_enum "
		"FROM med_medication_dispense d "
		"LEFT JOIN adm_patient p ON d.patient_id=p.id AND p.is_deleted=0 "
		"LEFT JOIN adm_encounter e ON d.encounter_id=e.id AND e.is_deleted=0 "
		"LEFT JOIN adm_location enc_loc ON e.location_id=enc_loc.id AND enc_loc.is_deleted=0 "
		"WHERE d.is_deleted=0 AND d.status_enum='DISPENSED' AND e.bus_no=? "
		"LIMIT 1";
	SQLPARAMS_PUSH(params, "s", std::string, hospitalizationNo);
	return sqlSession->executeQuery<InpatientReturnPatientDO>(sql, InpatientReturnPatientMapper(), params);
}

int DrugReturnDAO::confirmReturn(const std::string& hospitalizationNo, const std::vector<std::string>& detailIds)
{
	if (detailIds.empty()) return 0;

	std::string sql = "UPDATE med_medication_dispense d "
		"INNER JOIN adm_encounter e ON d.encounter_id=e.id AND e.is_deleted=0 "
		"SET d.status_enum='REFUNDED', d.updated_at=NOW() "
		"WHERE d.id IN (";
	for (size_t i = 0; i < detailIds.size(); i++) {
		if (i > 0) sql += ",";
		sql += "?";
	}
	sql += ") AND d.is_deleted=0 AND d.status_enum='DISPENSED' AND e.bus_no=?";

	SqlParams params;
	for (auto& id : detailIds) {
		SQLPARAMS_PUSH(params, "s", std::string, id);
	}
	SQLPARAMS_PUSH(params, "s", std::string, hospitalizationNo);

	return sqlSession->executeUpdate(sql, params);
}
