/*
 * Copyright Zero One Star. All rights reserved.
 *
 * @Author: stellablack528
 * @Date: 2026/07/27 10:00:00
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "stdafx.h"
#include "StockInApprovalController.hpp"
#include "service/pharmacy/approval/StockInApprovalService.hpp"

// ==================== 撤回 ====================

vo::StockInOperationResultVO::Wrapper StockInApprovalController::execWithdrawStockIn(
	const oatpp::Object<dto::StockInWithdrawDTO>& body)
{
	return PharmacyStockInApprovalService().withdraw(body);
}

// ==================== 审批通过 ====================

vo::StockInOperationResultVO::Wrapper StockInApprovalController::execApproveStockIn(
	const oatpp::Object<dto::StockInApprovalDTO>& body)
{
	return PharmacyStockInApprovalService().approve(body);
}

// ==================== 驳回 ====================

vo::StockInOperationResultVO::Wrapper StockInApprovalController::execRejectStockIn(
	const oatpp::Object<dto::StockInRejectDTO>& body)
{
	return PharmacyStockInApprovalService().reject(body);
}