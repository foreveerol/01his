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
#include "SupplyDeleteDAO.h"
#include "SupplyDeleteMapper.h"

PtrSupplyDeleteDO SupplyDeleteDAO::selectById(std::string id)
{
	string sql = "SELECT id, bus_no, type_enum, status_enum, item_id, item_table, lot_number, "
		"version, is_deleted, updated_at, deleted_at, deleted_by, updated_by "
		"FROM wkf_supply_request WHERE `id`=? AND is_deleted=0";
	return sqlSession->executeQueryOne<PtrSupplyDeleteDO>(sql, PtrSupplyDeleteMapper(), "%s", id);
}

int SupplyDeleteDAO::softDelete(std::string id, std::string deletedAt, std::string deletedBy)
{
	string sql = "UPDATE wkf_supply_request SET "
		"is_deleted=1, "
		"deleted_at=?, "
		"deleted_by=?, "
		"updated_at=? "
		"WHERE id=? AND status_enum IN ('DRAFT','PENDING_APPROVAL') AND is_deleted=0";
	return sqlSession->executeUpdate(sql, "%s%s%s%s", deletedAt, deletedBy, deletedAt, id);
}

uint64_t SupplyDeleteDAO::countActiveDeliveryByRequestId(std::string requestId)
{
	string sql = "SELECT COUNT(1) FROM wkf_supply_delivery "
		"WHERE request_id=? AND is_deleted=0 AND status_enum!='CANCELLED'";
	SqlParams params;
	return sqlSession->executeQueryNumerical(sql, "%s", requestId);
}

int SupplyDeleteDAO::softDeleteDeliveries(std::string requestId, std::string deletedAt, std::string deletedBy)
{
	string sql = "UPDATE wkf_supply_delivery SET "
		"is_deleted=1, "
		"deleted_at=?, "
		"deleted_by=?, "
		"status_enum='CANCELLED' "
		"WHERE request_id=? AND is_deleted=0";
	return sqlSession->executeUpdate(sql, "%s%s%s", deletedAt, deletedBy, requestId);
}
