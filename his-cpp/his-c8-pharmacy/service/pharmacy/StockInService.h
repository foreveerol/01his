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
#ifndef _STOCKIN_SERVICE_
#define _STOCKIN_SERVICE_

#include "domain/query/pharmacy/StockInQuery.h"
#include "domain/vo/pharmacy/StockInVO.h"
#include "domain/dto/pharmacy/StockInDTO.h"

class StockInService
{
public:
	// 条件分页查询入库单列表
	StockInPageJsonVO::Wrapper listByCondition(const StockInQuery::Wrapper& query);
	// 按单号查询入库单详情
	StockInJsonVO::Wrapper queryOne(const String& orderNo);
	// 创建空白入库单（生成单号）
	StringJsonVO::Wrapper create();
	// 保存草稿
	StringJsonVO::Wrapper saveDraft(const StockInSaveDTO::Wrapper& dto);
	// 保存并提交审批
	StringJsonVO::Wrapper saveAndSubmit(const StockInSaveDTO::Wrapper& dto);
	// 提交审批
	StringJsonVO::Wrapper submit(const StockInRemoveDTO::Wrapper& dto);
	// 撤回
	StringJsonVO::Wrapper withdraw(const StockInRemoveDTO::Wrapper& dto);
	// 审批通过
	StringJsonVO::Wrapper approve(const StockInApprovalDTO::Wrapper& dto);
	// 审批驳回
	StringJsonVO::Wrapper reject(const StockInApprovalDTO::Wrapper& dto);
	// 删除入库单
	StringJsonVO::Wrapper remove(const StockInRemoveDTO::Wrapper& dto);

private:
	// 生成入库单号（格式：RK + yyyyMMdd + 4位流水号）
	std::string generateOrderNo();
};

#endif // !_STOCKIN_SERVICE_
