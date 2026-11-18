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
#include "OutpatientReturnDAO.h"

std::list<OutpatientReturnQueueDO> OutpatientReturnDAO::selectReturnQueue(const OutpatientReturnQuery::Wrapper& query)
{
	SqlParams params;
	std::string sql = "SELECT d.id, p.name, d.dispense_time, "
		"COUNT(d.id), d.status_enum "
		"FROM med_medication_dispense d "
		"LEFT JOIN adm_patient p ON d.patient_id=p.id AND p.is_deleted=0 "
		"WHERE d.is_deleted=0 AND d.dispense_enum='RETURN'";

	if (query->keyword && !query->keyword->empty()) {
		sql += " AND p.name LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->keyword.getValue(""));
	}

	sql += " GROUP BY d.id, p.name, d.dispense_time, d.status_enum ORDER BY d.dispense_time DESC";

	int pageIndex = query->pageIndex ? (int)(*query->pageIndex) : 1;
	int pageSize = query->pageSize ? (int)(*query->pageSize) : 10;
	int offset = (pageIndex - 1) * pageSize;
	sql += " LIMIT " + std::to_string(pageSize) + " OFFSET " + std::to_string(offset);

	return sqlSession->executeQuery<OutpatientReturnQueueDO>(sql, OutpatientReturnQueueMapper(), params);
}

uint64_t OutpatientReturnDAO::countReturnQueue(const OutpatientReturnQuery::Wrapper& query)
{
	SqlParams params;
	std::string sql = "SELECT COUNT(DISTINCT d.id) FROM med_medication_dispense d "
		"LEFT JOIN adm_patient p ON d.patient_id=p.id AND p.is_deleted=0 "
		"WHERE d.is_deleted=0 AND d.dispense_enum='RETURN'";

	if (query->keyword && !query->keyword->empty()) {
		sql += " AND p.name LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->keyword.getValue(""));
	}

	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<OutpatientReturnDetailDO> OutpatientReturnDAO::selectReturnDetail(const std::string& returnId)
{
	SqlParams params;
	std::string sql = "SELECT d.id, m.name, CAST(d.dispense_quantity AS SIGNED), d.dispense_time "
		"FROM med_medication_dispense d "
		"LEFT JOIN med_medication_definition m ON d.medication_id=m.id AND m.is_deleted=0 "
		"WHERE d.is_deleted=0 AND d.bus_no=?";
	SQLPARAMS_PUSH(params, "s", std::string, returnId);
	return sqlSession->executeQuery<OutpatientReturnDetailDO>(sql, OutpatientReturnDetailMapper(), params);
}

int OutpatientReturnDAO::confirmReturn(const std::string& returnId)
{
	std::string sql = "UPDATE med_medication_dispense SET "
		"status_enum='REFUNDED', updated_at=NOW() "
		"WHERE bus_no=? AND is_deleted=0";
	return sqlSession->executeUpdate(sql, "%s", returnId);
}

int OutpatientReturnDAO::rejectReturn(const std::string& returnId, const std::string& reason)
{
	std::string sql = "UPDATE med_medication_dispense SET "
		"status_enum='RETURN_REJECTED', not_performed_reason_enum=?, updated_at=NOW() "
		"WHERE bus_no=? AND is_deleted=0";
	return sqlSession->executeUpdate(sql, "%s%s", reason, returnId);
}