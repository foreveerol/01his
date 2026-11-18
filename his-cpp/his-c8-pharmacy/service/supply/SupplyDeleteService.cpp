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
#include "SupplyDeleteService.h"
#include "../../dao/supply/SupplyDeleteDAO.h"
#include "SimpleDateTimeFormat.h"

std::string SupplyDeleteService::deleteDocument(const DeleteDocumentDTO::Wrapper& dto)
{
	// Parameter validation
	if (!dto->requestId || dto->requestId->empty())
	{
		return "requestId不能为空";
	}

	std::string requestId = dto->requestId.getValue({});

	SupplyDeleteDAO dao;

	// 1. Query current document status
	auto record = dao.selectById(requestId);
	if (!record)
	{
		return "单据不存在或已被删除";
	}

	// 2. Verify status allows deletion
	std::string statusEnum = record->getStatusEnum();
	if (statusEnum != "DRAFT" && statusEnum != "PENDING_APPROVAL")
	{
		return "该单据状态不允许删除（仅草稿和待审批状态可删除）";
	}

	// 3. Check for active delivery records
	uint64_t deliveryCount = dao.countActiveDeliveryByRequestId(requestId);
	if (deliveryCount > 0)
	{
		return "该盘点单已执行，不可删除，请先作废发放单";
	}

	// 4. Get current user info
	std::string userId = dto->getPayload() ? dto->getPayload()->getId() : "system";
	std::string now = SimpleDateTimeFormat::format();

	// 5. Soft delete main document
	int rows = dao.softDelete(requestId, now, userId);
	if (rows != 1)
	{
		return "删除单据失败，单据状态可能已变更";
	}

	// 6. Soft delete associated delivery records
	dao.softDeleteDeliveries(requestId, now, userId);

	// Success
	return "";
}
