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
#include "InventoryCheckDAO.h"

std::string InventoryCheckDAO::queryConditionBuilder(const InventoryCheckQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE sr.type_enum='PHARMACY_STOCKTAKE' AND sr.is_deleted=0";

	if (query->checkNo && !query->checkNo->empty()) {
		sqlCondition << " AND sr.bus_no=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->checkNo.getValue(""));
	}

	if (query->checkType && !query->checkType->empty()) {
		sqlCondition << " AND sr.intent_enum=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->checkType.getValue(""));
	}

	if (query->status && !query->status->empty()) {
		sqlCondition << " AND sr.status_enum=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->status.getValue(""));
	}

	if (query->startDate && !query->startDate->empty()) {
		sqlCondition << " AND sr.created_at>=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->startDate.getValue(""));
	}
	if (query->endDate && !query->endDate->empty()) {
		sqlCondition << " AND sr.created_at<=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->endDate.getValue(""));
	}

	return sqlCondition.str();
}

std::list<InvCheckListDO> InventoryCheckDAO::selectList(const InventoryCheckQuery::Wrapper& query)
{
	SqlParams params;
	std::string sql = "SELECT sr.bus_no, sr.intent_enum, sr.created_at, "
		"COUNT(sd.id), sr.status_enum, COALESCE(u.name, sr.created_by) "
		"FROM wkf_supply_request sr "
		"LEFT JOIN wkf_supply_delivery sd ON sr.id=sd.request_id AND sd.is_deleted=0 "
		"LEFT JOIN adm_user u ON sr.created_by=u.id AND u.is_deleted=0 ";
	sql += queryConditionBuilder(query, params);
	sql += " GROUP BY sr.id ORDER BY sr.created_at DESC";

	int pageIndex = query->pageIndex ? (int)(*query->pageIndex) : 1;
	int pageSize = query->pageSize ? (int)(*query->pageSize) : 10;
	int offset = (pageIndex - 1) * pageSize;
	sql += " LIMIT " + std::to_string(pageSize) + " OFFSET " + std::to_string(offset);

	return sqlSession->executeQuery<InvCheckListDO>(sql, InvCheckListMapper(), params);
}

uint64_t InventoryCheckDAO::countList(const InventoryCheckQuery::Wrapper& query)
{
	SqlParams params;
	std::string sql = "SELECT COUNT(DISTINCT sr.id) FROM wkf_supply_request sr "
		"LEFT JOIN adm_user u ON sr.created_by=u.id AND u.is_deleted=0 ";
	sql += queryConditionBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}

InvCheckDetailDO InventoryCheckDAO::selectByCheckNo(const std::string& checkNo)
{
	SqlParams params;
	std::string sql = "SELECT sr.bus_no, sr.intent_enum, sr.status_enum, "
		"sr.created_at, sr.remake, sr.reason "
		"FROM wkf_supply_request sr "
		"WHERE sr.bus_no=? AND sr.type_enum='PHARMACY_STOCKTAKE' AND sr.is_deleted=0";
	SQLPARAMS_PUSH(params, "s", std::string, checkNo);
	auto results = sqlSession->executeQuery<InvCheckDetailDO>(sql, InvCheckDetailMapper(), params);
	if (results.empty()) {
		return InvCheckDetailDO();
	}
	return std::move(results.front());
}

std::list<InvCheckDrugDO> InventoryCheckDAO::selectCheckItems(const std::string& requestId)
{
	SqlParams params;
	std::string sql = "SELECT sd.id, COALESCE(m.name,''), COALESCE(m.total_volume,''), "
		"COALESCE(sd.lot_number,''), sd.quantity, sd.price, "
		"(sd.price - sd.quantity), COALESCE(sd.status_enum,'') "
		"FROM wkf_supply_delivery sd "
		"LEFT JOIN med_medication_definition m ON sd.item_id=m.id AND m.is_deleted=0 "
		"WHERE sd.request_id=? AND sd.is_deleted=0";
	SQLPARAMS_PUSH(params, "s", std::string, requestId);
	return sqlSession->executeQuery<InvCheckDrugDO>(sql, InvCheckDrugMapper(), params);
}

uint64_t InventoryCheckDAO::insertRequest(const InventoryCheckDO& record)
{
	return insert(record);
}

int InventoryCheckDAO::updateStatus(const std::string& id, const std::string& status, const std::string& updatedBy)
{
	std::string sql = "UPDATE wkf_supply_request SET "
		"status_enum=?, updated_by=?, updated_at=NOW() "
		"WHERE id=? AND is_deleted=0";
	return sqlSession->executeUpdate(sql, "%s%s%s", status, updatedBy, id);
}

int InventoryCheckDAO::softDelete(const std::string& id, const std::string& deletedAt, const std::string& deletedBy)
{
	std::string sql = "UPDATE wkf_supply_request SET "
		"is_deleted=1, deleted_at=?, deleted_by=?, updated_at=? "
		"WHERE id=? AND status_enum IN ('DRAFT','PENDING_APPROVAL','REJECTED') AND is_deleted=0";
	return sqlSession->executeUpdate(sql, "%s%s%s%s", deletedAt, deletedBy, deletedAt, id);
}
