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
#ifndef _INVENTORY_CHECK_DAO_
#define _INVENTORY_CHECK_DAO_

#include "BaseDAO.h"
#include "InventoryCheckMapper.h"
#include "../../domain/do/pharmacy/InventoryCheckDO.h"
#include "../../domain/query/pharmacy/InventoryCheckQuery.h"

class InventoryCheckDAO : public BaseDAO
{
private:
	std::string queryConditionBuilder(const InventoryCheckQuery::Wrapper& query, SqlParams& params);

public:
	// 条件分页查询盘点单列表
	std::list<InvCheckListDO> selectList(const InventoryCheckQuery::Wrapper& query);
	// 统计符合条件的总记录数
	uint64_t countList(const InventoryCheckQuery::Wrapper& query);
	// 按单号查询盘点单详情
	InvCheckDetailDO selectByCheckNo(const std::string& checkNo);
	// 查询盘点单关联的药品明细
	std::list<InvCheckDrugDO> selectCheckItems(const std::string& requestId);
	// 新增盘点单
	uint64_t insertRequest(const InventoryCheckDO& record);
	// 更新单据状态
	int updateStatus(const std::string& id, const std::string& status, const std::string& updatedBy);
	// 软删除盘点单
	int softDelete(const std::string& id, const std::string& deletedAt, const std::string& deletedBy);
};

#endif // !_INVENTORY_CHECK_DAO_
