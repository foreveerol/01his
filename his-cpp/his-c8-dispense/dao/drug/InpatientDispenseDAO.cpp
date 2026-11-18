/*
 Copyright Zero One Star. All rights reserved.

 @Author: juhao
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
#include "InpatientDispenseDAO.h"

/**
 * 根据查询参数动态构建 SQL WHERE 条件
 * @param query 包含筛选条件的查询包装器
 * @param params SQL 参数集合
 * @return SQL WHERE 子句字符串
 */
std::string InpatientDispenseDAO::queryConditionBuilder(const InpatientDispenseQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE d.is_deleted=0 AND d.summary_no IS NOT NULL AND d.summary_no!=''"
		<< " AND e.class_enum='IMP'";

	if (query->dispenseStatus && !query->dispenseStatus->empty()) {
		std::string status = query->dispenseStatus.getValue("");
		if (status != "ALL") {
			sqlCondition << " AND d.status_enum=?";
			SQLPARAMS_PUSH(params, "s", std::string, status);
		}
	}

	if (query->summaryNo && !query->summaryNo->empty()) {
		sqlCondition << " AND d.summary_no=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->summaryNo.getValue(""));
	}

	if (query->startDate && !query->startDate->empty()) {
		sqlCondition << " AND d.created_at>=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->startDate.getValue(""));
	}
	if (query->endDate && !query->endDate->empty()) {
		sqlCondition << " AND d.created_at<=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->endDate.getValue(""));
	}

	return sqlCondition.str();
}

/**
 * 分页查询住院发药汇总队列
 * 按 summary_no 分组获取唯一汇总单据
 * @param query 查询参数，包括状态、汇总单号、日期范围、页码、页大小
 * @return 包含汇总队列信息的 InpatientSummaryDO 列表
 */
std::list<InpatientSummaryDO> InpatientDispenseDAO::selectSummaryQueue(const InpatientDispenseQuery::Wrapper& query)
{
	SqlParams params;
	std::string sql = "SELECT d.summary_no, d.summary_no, d.status_enum, "
		"MIN(d.created_at), COALESCE(loc.name,''), COALESCE(pr.name,'') "
		"FROM med_medication_dispense d "
		"LEFT JOIN adm_encounter e ON d.encounter_id=e.id AND e.is_deleted=0 "
		"LEFT JOIN adm_location loc ON d.location_id=loc.id AND loc.is_deleted=0 "
		"LEFT JOIN adm_practitioner pr ON d.practitioner_id=pr.id AND pr.is_deleted=0 ";
	sql += queryConditionBuilder(query, params);
	sql += " GROUP BY d.summary_no, d.status_enum, loc.name, pr.name ORDER BY MIN(d.created_at) DESC";

	int pageIndex = query->pageIndex ? (int)(*query->pageIndex) : 1;
	int pageSize = query->pageSize ? (int)(*query->pageSize) : 10;
	int offset = (pageIndex - 1) * pageSize;
	sql += " LIMIT " + std::to_string(pageSize) + " OFFSET " + std::to_string(offset);

	return sqlSession->executeQuery<InpatientSummaryDO>(sql, InpatientSummaryMapper(), params);
}

/**
 * 统计住院发药汇总队列记录数
 * @param query 查询参数
 * @return 唯一汇总单据总数
 */
uint64_t InpatientDispenseDAO::countSummaryQueue(const InpatientDispenseQuery::Wrapper& query)
{
	SqlParams params;
	std::string sql = "SELECT COUNT(DISTINCT d.summary_no) FROM med_medication_dispense d "
		"LEFT JOIN adm_encounter e ON d.encounter_id=e.id AND e.is_deleted=0 ";
	sql += queryConditionBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}

/**
 * 查询指定汇总单据的药品明细
 * @param summaryNo 汇总单据号
 * @return 包含药品项目的 InpatientDrugItemDO 列表
 */
std::list<InpatientDrugItemDO> InpatientDispenseDAO::selectDrugDetail(const std::string& summaryNo)
{
	SqlParams params;
	std::string sql = "SELECT d.id, ROW_NUMBER() OVER (ORDER BY d.id), "
		"m.name, CAST(d.dispense_quantity AS CHAR), m.total_volume "
		"FROM med_medication_dispense d "
		"LEFT JOIN med_medication_definition m ON d.medication_id=m.id AND m.is_deleted=0 "
		"LEFT JOIN adm_encounter e ON d.encounter_id=e.id AND e.is_deleted=0 "
		"WHERE d.is_deleted=0 AND d.summary_no=? AND e.class_enum='IMP'";
	SQLPARAMS_PUSH(params, "s", std::string, summaryNo);
	return sqlSession->executeQuery<InpatientDrugItemDO>(sql, InpatientDrugItemMapper(), params);
}

int InpatientDispenseDAO::verifyDispense(const std::string& summaryNo, const std::string& practitionerId)
{
	std::string sql = "UPDATE med_medication_dispense SET "
		"status_enum='DISPENSED', practitioner_id=?, updated_at=NOW() "
		"WHERE summary_no=? AND is_deleted=0";
	return sqlSession->executeUpdate(sql, "%s%s", practitionerId, summaryNo);
}

int InpatientDispenseDAO::rejectDispense(const std::string& summaryNo, const std::string& auditor, const std::string& reason)
{
	std::string sql = "UPDATE med_medication_dispense SET "
		"status_enum='REJECTED', updated_by=?, not_performed_reason_enum=?, updated_at=NOW() "
		"WHERE summary_no=? AND is_deleted=0";
	return sqlSession->executeUpdate(sql, "%s%s%s", auditor, reason, summaryNo);
}