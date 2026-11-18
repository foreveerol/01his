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
#include "DispenseRecordDAO.h"
#include "DispenseRecordMapper.h"

std::string DispenseRecordDAO::queryConditionBuilder(const DispenseRecordQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE d.is_deleted=0";

	// 发药时间范围（必填）
	if (query->startTime) {
		sqlCondition << " AND d.dispense_time>=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->startTime.getValue(""));
	}
	if (query->endTime) {
		sqlCondition << " AND d.dispense_time<?";
		SQLPARAMS_PUSH(params, "s", std::string, query->endTime.getValue(""));
	}

	// 状态列表（可选，格式：COMPLETED,REFUNDED,DECLINED）
	if (query->statusList && !query->statusList->empty()) {
		std::string statusStr = query->statusList.getValue("");
		// 将逗号分隔的状态转换为 IN 子句
		sqlCondition << " AND d.status_enum IN (";
		std::stringstream ss(statusStr);
		std::string item;
		bool first = true;
		while (std::getline(ss, item, ',')) {
			if (!first) sqlCondition << ",";
			sqlCondition << "?";
			SQLPARAMS_PUSH(params, "s", std::string, item);
			first = false;
		}
		sqlCondition << ")";
	}

	// 患者姓名（可选模糊查询）
	if (query->patientName && !query->patientName->empty()) {
		sqlCondition << " AND p.name LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->patientName.getValue(""));
	}

	// 药品名称（可选模糊查询）
	if (query->medicationName && !query->medicationName->empty()) {
		sqlCondition << " AND m.name LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->medicationName.getValue(""));
	}

	// 发药人姓名（可选模糊查询）
	if (query->practitionerName && !query->practitionerName->empty()) {
		sqlCondition << " AND pr.name LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->practitionerName.getValue(""));
	}

	// 药房ID（可选精确匹配）
	if (query->locationId && !query->locationId->empty()) {
		sqlCondition << " AND d.location_id=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->locationId.getValue(""));
	}

	return sqlCondition.str();
}

std::list<DispenseRecordDO> DispenseRecordDAO::selectWithCondition(const DispenseRecordQuery::Wrapper& query)
{
	SqlParams params;
	string sql = "SELECT "
		"d.bus_no, d.status_enum, d.dispense_time, "
		"p.name, p.id_card, "
		"e.bus_no, "
		"m.name, m.total_volume, m.dose_form_code, "
		"d.quantity, d.dispense_quantity, d.unit_code, d.lot_number, "
		"pr.name, "
		"loc.name, "
		"req.prescription_no, req.requester_id, "
		"d.created_at "
		"FROM med_medication_dispense d "
		"LEFT JOIN med_medication_request req ON d.med_req_id=req.id AND req.is_deleted=0 "
		"LEFT JOIN med_medication_definition m ON d.medication_id=m.id AND m.is_deleted=0 "
		"LEFT JOIN adm_patient p ON d.patient_id=p.id AND p.is_deleted=0 "
		"LEFT JOIN adm_encounter e ON d.encounter_id=e.id AND e.is_deleted=0 "
		"LEFT JOIN adm_practitioner pr ON d.practitioner_id=pr.id AND pr.is_deleted=0 "
		"LEFT JOIN adm_location loc ON d.location_id=loc.id AND loc.is_deleted=0 ";

	// 构建查询条件
	sql += queryConditionBuilder(query, params);
	// 排序
	sql += " ORDER BY d.dispense_time DESC";

	return sqlSession->executeQuery<DispenseRecordDO>(sql, DispenseRecordMapper(), params);
}
