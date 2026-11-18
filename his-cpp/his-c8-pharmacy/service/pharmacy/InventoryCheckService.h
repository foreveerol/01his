#pragma once

#ifndef _INVENTORY_CHECK_SERVICE_
#define _INVENTORY_CHECK_SERVICE_

#include "domain/query/pharmacy/InventoryCheckQuery.h"
#include "domain/vo/pharmacy/InventoryCheckVO.h"
#include "domain/dto/pharmacy/InventoryCheckDTO.h"

class InventoryCheckService
{
public:
	// 条件分页查询盘点单列表
	InventoryCheckPageJsonVO::Wrapper listByCondition(const InventoryCheckQuery::Wrapper& query);
	// 按单号查询盘点单详情
	InventoryCheckJsonVO::Wrapper queryOne(const String& checkNo);
	// 创建空白盘点单（生成单号）
	StringJsonVO::Wrapper create();
	// 保存草稿
	StringJsonVO::Wrapper saveDraft(const InventoryCheckSaveDTO::Wrapper& dto);
	// 保存并提交审批
	StringJsonVO::Wrapper saveAndSubmit(const InventoryCheckSaveDTO::Wrapper& dto);
	// 提交审批
	StringJsonVO::Wrapper submit(const InventoryCheckRemoveDTO::Wrapper& dto);
	// 撤回
	StringJsonVO::Wrapper withdraw(const InventoryCheckRemoveDTO::Wrapper& dto);
	// 审批通过
	StringJsonVO::Wrapper approve(const InventoryCheckApprovalDTO::Wrapper& dto);
	// 审批驳回
	StringJsonVO::Wrapper reject(const InventoryCheckApprovalDTO::Wrapper& dto);
	// 删除盘点单
	StringJsonVO::Wrapper remove(const InventoryCheckRemoveDTO::Wrapper& dto);

private:
	// 生成盘点单号（格式：PD + yyyyMMdd + 4位流水号）
	std::string generateCheckNo();
};

#endif // !_INVENTORY_CHECK_SERVICE_
