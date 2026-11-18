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
#include "OutpatientRecordDAO.h"

/**
 * 根据查询参数动态构建 SQL WHERE 条件
 * 支持门诊记录查询的多种筛选条件
 * @param query 包含筛选条件的查询包装器
 * @param params SQL 参数集合
 * @return SQL WHERE 子句字符串
 */
std::string OutpatientRecordDAO::queryConditionBuilder(const OutpatientRecordQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE d.is_deleted=0"
		<< " AND e.class_enum='AMB'";

	if (query->drugName && !query->drugName->empty()) {
		sqlCondition << " AND m.name LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->drugName.getValue(""));
	}

	if (query->recordType && !query->recordType->empty()) {
		std::string recordType = query->recordType.getValue("");
		if (recordType == "DISPENSE") {
			// DISPENSE matches both DISPENSED and OUTPATIENT in database
			sqlCondition << " AND d.dispense_enum='DISPENSE'";
		} else if (recordType == "REFUND") {
			sqlCondition << " AND d.dispense_enum='REFUND'";
		}
	}

	if (query->pharmacy && !query->pharmacy->empty()) {
		sqlCondition << " AND loc.name LIKE CONCAT('%',?,'%')";
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

/**
 * 多条件分页查询门诊发药/退药记录
 * 关联多张表获取完整的记录信息
 * @param query 查询参数，包括药品名称、记录类型、药房、项目类型、发药人、患者姓名、日期范围、页码、页大小
 * @return 包含完整记录信息的 OutpatientRecordDO 列表
 */
std::list<OutpatientRecordDO> OutpatientRecordDAO::selectWithCondition(const OutpatientRecordQuery::Wrapper& query)
{
	SqlParams params;
	std::string sql = "SELECT "
		"req.prescription_no, d.dispense_enum, p.name, "
		"e.bus_no, m.name, m.total_volume, "
		"d.dispense_quantity, COALESCE(c.unit_price,0), COALESCE(c.total_price,0), "
		"d.lot_number, d.trace_no, "
		"COALESCE(m.manufacturer_text,''), COALESCE(req_loc.name,''), "
		"d.dispense_time, COALESCE(loc.name,''), COALESCE(pr.name,'') "
		"FROM med_medication_dispense d "
		"LEFT JOIN med_medication_request req ON d.med_req_id=req.id AND req.is_deleted=0 "
		"LEFT JOIN med_medication_definition m ON d.medication_id=m.id AND m.is_deleted=0 "
		"LEFT JOIN adm_patient p ON d.patient_id=p.id AND p.is_deleted=0 "
		"LEFT JOIN adm_encounter e ON d.encounter_id=e.id AND e.is_deleted=0 "
		"LEFT JOIN adm_practitioner pr ON d.practitioner_id=pr.id AND pr.is_deleted=0 "
		"LEFT JOIN adm_location loc ON d.location_id=loc.id AND loc.is_deleted=0 "
		"LEFT JOIN adm_location req_loc ON req.location_id=req_loc.id AND req_loc.is_deleted=0 "
		"LEFT JOIN adm_charge_item c ON d.id=c.dispense_id AND c.is_deleted=0 ";
	sql += queryConditionBuilder(query, params);
	sql += " ORDER BY d.dispense_time DESC";

	int pageIndex = query->pageIndex ? (int)(*query->pageIndex) : 1;
	int pageSize = query->pageSize ? (int)(*query->pageSize) : 10;
	int offset = (pageIndex - 1) * pageSize;
	sql += " LIMIT " + std::to_string(pageSize) + " OFFSET " + std::to_string(offset);

	return sqlSession->executeQuery<OutpatientRecordDO>(sql, OutpatientRecordMapper(), params);
}

/**
 * 统计符合条件的门诊发药/退药记录数
 * @param query 查询参数
 * @return 记录总数
 */
uint64_t OutpatientRecordDAO::countWithCondition(const OutpatientRecordQuery::Wrapper& query)
{
	SqlParams params;
	// Note: countWithCondition不需要JOIN adm_charge_item，因为我们只统计发药记录数，不需要价格信息
	// 使用COUNT(DISTINCT d.id)避免JOIN其他表导致的重复计数
	std::string sql = "SELECT COUNT(DISTINCT d.id) FROM med_medication_dispense d "
		"LEFT JOIN med_medication_request req ON d.med_req_id=req.id AND req.is_deleted=0 "
		"LEFT JOIN med_medication_definition m ON d.medication_id=m.id AND m.is_deleted=0 "
		"LEFT JOIN adm_patient p ON d.patient_id=p.id AND p.is_deleted=0 "
		"LEFT JOIN adm_encounter e ON d.encounter_id=e.id AND e.is_deleted=0 "
		"LEFT JOIN adm_practitioner pr ON d.practitioner_id=pr.id AND pr.is_deleted=0 "
		"LEFT JOIN adm_location loc ON d.location_id=loc.id AND loc.is_deleted=0 "
		"LEFT JOIN adm_location req_loc ON req.location_id=req_loc.id AND req_loc.is_deleted=0 ";
	sql += queryConditionBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}