#pragma once
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
#ifndef _STOCKIN_DAO_
#define _STOCKIN_DAO_

#include "BaseDAO.h"
#include "StockInMapper.h"
#include "../../domain/do/pharmacy/InventoryCheckDO.h"
#include "../../domain/query/pharmacy/StockInQuery.h"

class StockInDAO : public BaseDAO
{
private:
	std::string queryConditionBuilder(const StockInQuery::Wrapper& query, SqlParams& params);

public:
	// 条件分页查询入库单列表
	std::list<StockInListDO> selectList(const StockInQuery::Wrapper& query);
	// 统计符合条件的总记录数
	uint64_t countList(const StockInQuery::Wrapper& query);
	// 按单号查询入库单详情
	StockInDetailDO selectByBusNo(const std::string& busNo);
	// 查询入库单关联的药品明细
	std::list<StockInDrugDetailDO> selectDetailItems(const std::string& requestId);
	// 新增入库单
	uint64_t insertRequest(const InventoryCheckDO& record);
	// 更新单据状态
	int updateStatus(const std::string& id, const std::string& status, const std::string& updatedBy);
	// 软删除入库单
	int softDelete(const std::string& id, const std::string& deletedAt, const std::string& deletedBy);

	// === 入库审批专用方法 ===
	// 按bus_no查询审批所需字段（含id/status/item信息）
	StockInApprovalDO selectForApproval(const std::string& busNo);
	// 撤回审批：状态改为WITHDRAWN（带PENDING守卫）
	int withdrawOrder(const std::string& id, const std::string& updatedBy);
	// 通过审批：状态改为APPROVED，记录审批人和时间（带PENDING守卫）
	int approveOrder(const std::string& id, const std::string& approverId, const std::string& updatedBy);
	// 驳回审批：状态改为REJECTED，记录原因、审批人和时间（带PENDING守卫）
	int rejectOrder(const std::string& id, const std::string& reason, const std::string& approverId, const std::string& updatedBy);
	// 原子更新库存数量（quantity = quantity + delta）
	int increaseQuantity(const std::string& itemId, const std::string& locationId, double delta);
};

#endif // !_STOCKIN_DAO_
