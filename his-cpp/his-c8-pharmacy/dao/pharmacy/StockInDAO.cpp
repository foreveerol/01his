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
#include "StockInDAO.h"

std::string StockInDAO::queryConditionBuilder(const StockInQuery::Wrapper& query, SqlParams& params)
{
	stringstream sqlCondition;
	sqlCondition << " WHERE sr.type_enum='PHARMACY_STOCK_IN' AND sr.is_deleted=0";

	if (query->orderNo && !query->orderNo->empty()) {
		sqlCondition << " AND sr.bus_no=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->orderNo.getValue(""));
	}

	if (query->supplierName && !query->supplierName->empty()) {
		sqlCondition << " AND s.name LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->supplierName.getValue(""));
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

std::list<StockInListDO> StockInDAO::selectList(const StockInQuery::Wrapper& query)
{
	SqlParams params;
	std::string sql = "SELECT sr.bus_no, COALESCE(s.name,''), sr.created_at, "
		"COUNT(sd.id), COALESCE(SUM(sd.quantity * sd.price), 0), "
		"sr.status_enum, COALESCE(u.name,sr.created_by) "
		"FROM wkf_supply_request sr "
		"LEFT JOIN adm_supplier s ON sr.supplier_id=s.id AND s.is_deleted=0 "
		"LEFT JOIN wkf_supply_delivery sd ON sr.id=sd.request_id AND sd.is_deleted=0 "
		"LEFT JOIN adm_user u ON sr.created_by=u.id AND u.is_deleted=0 ";
	sql += queryConditionBuilder(query, params);
	sql += " GROUP BY sr.id ORDER BY sr.created_at DESC";

	int pageIndex = query->pageIndex ? (int)(*query->pageIndex) : 1;
	int pageSize = query->pageSize ? (int)(*query->pageSize) : 10;
	int offset = (pageIndex - 1) * pageSize;
	sql += " LIMIT " + std::to_string(pageSize) + " OFFSET " + std::to_string(offset);

	return sqlSession->executeQuery<StockInListDO>(sql, StockInMapper(), params);
}

uint64_t StockInDAO::countList(const StockInQuery::Wrapper& query)
{
	SqlParams params;
	std::string sql = "SELECT COUNT(DISTINCT sr.id) FROM wkf_supply_request sr "
		"LEFT JOIN adm_supplier s ON sr.supplier_id=s.id AND s.is_deleted=0 "
		"LEFT JOIN adm_user u ON sr.created_by=u.id AND u.is_deleted=0 ";
	sql += queryConditionBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}

StockInDetailDO StockInDAO::selectByBusNo(const std::string& busNo)
{
	SqlParams params;
	std::string sql = "SELECT sr.bus_no, sr.intent_enum, sr.status_enum, "
		"sr.created_at, sr.remake, sr.supplier_id, COALESCE(s.name,'') "
		"FROM wkf_supply_request sr "
		"LEFT JOIN adm_supplier s ON sr.supplier_id=s.id AND s.is_deleted=0 "
		"WHERE sr.bus_no=? AND sr.type_enum='PHARMACY_STOCK_IN' AND sr.is_deleted=0";
	SQLPARAMS_PUSH(params, "s", std::string, busNo);
	auto results = sqlSession->executeQuery<StockInDetailDO>(sql, StockInDetailMapper(), params);
	if (results.empty()) {
		return StockInDetailDO();
	}
	return std::move(results.front());
}

std::list<StockInDrugDetailDO> StockInDAO::selectDetailItems(const std::string& requestId)
{
	SqlParams params;
	std::string sql = "SELECT sd.id, COALESCE(m.name,''), COALESCE(m.total_volume,''), "
		"COALESCE(m.manufacturer_text,''), COALESCE(sd.lot_number,''), "
		"COALESCE(ii.expiration_date,''), sd.unit_code, sd.quantity, sd.price "
		"FROM wkf_supply_delivery sd "
		"LEFT JOIN med_medication_definition m ON sd.item_id=m.id AND m.is_deleted=0 "
		"LEFT JOIN wkf_inventory_item ii ON sd.item_id=ii.item_id AND sd.lot_number=ii.lot_number AND ii.is_deleted=0 "
		"WHERE sd.request_id=? AND sd.is_deleted=0";
	SQLPARAMS_PUSH(params, "s", std::string, requestId);
	return sqlSession->executeQuery<StockInDrugDetailDO>(sql, StockInDrugDetailMapper(), params);
}

uint64_t StockInDAO::insertRequest(const InventoryCheckDO& record)
{
	return insert(record);
}

int StockInDAO::updateStatus(const std::string& id, const std::string& status, const std::string& updatedBy)
{
	std::string sql = "UPDATE wkf_supply_request SET "
		"status_enum=?, updated_by=?, updated_at=NOW() "
		"WHERE id=? AND is_deleted=0";
	return sqlSession->executeUpdate(sql, "%s%s%s", status, updatedBy, id);
}

int StockInDAO::softDelete(const std::string& id, const std::string& deletedAt, const std::string& deletedBy)
{
	std::string sql = "UPDATE wkf_supply_request SET "
		"is_deleted=1, deleted_at=?, deleted_by=?, updated_at=? "
		"WHERE id=? AND status_enum IN ('DRAFT','PENDING_APPROVAL','REJECTED') AND is_deleted=0";
	return sqlSession->executeUpdate(sql, "%s%s%s%s", deletedAt, deletedBy, deletedAt, id);
}

// === 入库审批专用实现 ===

StockInApprovalDO StockInDAO::selectForApproval(const std::string& busNo)
{
	SqlParams params;
	std::string sql =
		"SELECT sr.id, sr.bus_no, sr.status_enum, "
		"sr.applicant_id, sr.item_id, sr.item_quantity, "
		"sr.purpose_location_id, sr.version "
		"FROM wkf_supply_request sr "
		"WHERE sr.bus_no=? AND sr.is_deleted=0 "
		"LIMIT 1";
	SQLPARAMS_PUSH(params, "s", std::string, busNo);
	auto results = sqlSession->executeQuery<StockInApprovalDO>(sql, StockInApprovalMapper(), params);
	if (results.empty()) {
		return StockInApprovalDO();
	}
	return std::move(results.front());
}

int StockInDAO::withdrawOrder(const std::string& id, const std::string& updatedBy)
{
	std::string sql =
		"UPDATE wkf_supply_request SET "
		"status_enum='WITHDRAWN', updated_by=?, updated_at=NOW(), version=version+1 "
		"WHERE id=? AND is_deleted=0 AND status_enum='PENDING_APPROVAL'";
	return sqlSession->executeUpdate(sql, "%s%s", updatedBy, id);
}

int StockInDAO::approveOrder(const std::string& id, const std::string& approverId, const std::string& updatedBy)
{
	std::string sql =
		"UPDATE wkf_supply_request SET "
		"status_enum='APPROVED', approver_id=?, approval_time=NOW(), "
		"updated_by=?, updated_at=NOW(), version=version+1 "
		"WHERE id=? AND is_deleted=0 AND status_enum='PENDING_APPROVAL'";
	return sqlSession->executeUpdate(sql, "%s%s%s", approverId, updatedBy, id);
}

int StockInDAO::rejectOrder(const std::string& id, const std::string& reason, const std::string& approverId, const std::string& updatedBy)
{
	std::string sql =
		"UPDATE wkf_supply_request SET "
		"status_enum='REJECTED', remake=?, approver_id=?, approval_time=NOW(), "
		"updated_by=?, updated_at=NOW(), version=version+1 "
		"WHERE id=? AND is_deleted=0 AND status_enum='PENDING_APPROVAL'";
	return sqlSession->executeUpdate(sql, "%s%s%s%s", reason, approverId, updatedBy, id);
}

int StockInDAO::increaseQuantity(const std::string& itemId, const std::string& locationId, double delta)
{
	std::string sql =
		"UPDATE wkf_inventory_item SET "
		"quantity=quantity+?, updated_at=NOW(), version=version+1 "
		"WHERE item_id=? AND location_id=? AND is_deleted=0";
	return sqlSession->executeUpdate(sql, "%d%s%s", delta, itemId, locationId);
}
