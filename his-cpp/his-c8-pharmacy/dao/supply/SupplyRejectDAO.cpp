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
#include "SupplyRejectDAO.h"
#include "SupplyRejectMapper.h"

PtrSupplyRejectDO SupplyRejectDAO::selectById(std::string id)
{
	string sql = "SELECT id, bus_no, type_enum, status_enum, item_quantity, total_quantity, "
		"item_id, item_table, lot_number, source_location_id, purpose_location_id, "
		"applicant_id, apply_time, approver_id, approval_time, version, is_deleted "
		"FROM wkf_supply_request WHERE `id`=? AND is_deleted=0";
	return sqlSession->executeQueryOne<PtrSupplyRejectDO>(sql, PtrSupplyRejectMapper(), "%s", id);
}

int SupplyRejectDAO::updateRejectStatus(std::string id, std::string approverId, std::string approvalTime, std::string updatedBy)
{
	string sql = "UPDATE wkf_supply_request SET "
		"status_enum='REJECTED', "
		"approver_id=?, "
		"approval_time=?, "
		"updated_at=?, "
		"updated_by=?, "
		"version=version+1 "
		"WHERE id=? AND status_enum='PENDING_APPROVAL' AND is_deleted=0";
	return sqlSession->executeUpdate(sql, "%s%s%s%s%s", approverId, approvalTime, approvalTime, updatedBy, id);
}

int SupplyRejectDAO::updateRejectStatusWithVersion(std::string id, int version, std::string approverId, std::string approvalTime, std::string updatedBy)
{
	string sql = "UPDATE wkf_supply_request SET "
		"status_enum='REJECTED', "
		"approver_id=?, "
		"approval_time=?, "
		"updated_at=?, "
		"updated_by=?, "
		"version=version+1 "
		"WHERE id=? AND status_enum='PENDING_APPROVAL' AND version=? AND is_deleted=0";
	return sqlSession->executeUpdate(sql, "%s%s%s%s%s%d", approverId, approvalTime, approvalTime, updatedBy, id, version);
}
