/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:13:11

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
#include "SupplyRejectService.h"
#include "../../dao/supply/SupplyRejectDAO.h"
#include "SimpleDateTimeFormat.h"

std::string SupplyRejectService::rejectApproval(const RejectApprovalDTO::Wrapper& dto)
{
	// Parameter validation
	if (!dto->requestId || dto->requestId->empty())
	{
		return "requestId不能为空";
	}

	std::string requestId = dto->requestId.getValue({});

	// Query document
	SupplyRejectDAO dao;
	auto record = dao.selectById(requestId);
	if (!record)
	{
		return "单据不存在或已被删除";
	}

	// Verify stocktake type
	std::string typeEnum = record->getTypeEnum();
	if (typeEnum != "PHARMACY_STOCKTAKE" && typeEnum != "CABINET_STOCKTAKE")
	{
		return "该单据不是盘点类单据，不可驳回";
	}

	// Verify status is pending approval
	std::string statusEnum = record->getStatusEnum();
	if (statusEnum != "PENDING_APPROVAL")
	{
		return "单据已处理，不可驳回";
	}

	// Get current user info
	std::string userId = dto->getPayload() ? dto->getPayload()->getId() : "system";
	std::string username = dto->getPayload() ? dto->getPayload()->getUsername() : "system";
	std::string now = SimpleDateTimeFormat::format();

	// Execute reject update
	int rows = dao.updateRejectStatus(requestId, username, now, userId);
	if (rows != 1)
	{
		return "驳回审批失败，单据状态可能已变更";
	}

	// Success
	return "";
}
