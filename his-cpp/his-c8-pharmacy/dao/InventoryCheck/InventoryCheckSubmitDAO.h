#pragma once


#ifndef _INVENTORY_CHECK_SUBMIT_DAO_
#define _INVENTORY_CHECK_SUBMIT_DAO_
#include "BaseDAO.h"
#include "InventoryCheckSubmitMapper.h"
#include "../../domain/do/pharmacy/InventoryCheckDO.h"
#include "../../domain/do/pharmacy/MedicationDefinitionDO.h"

/**
 * 盘点单审批操作DAO：提交/撤回/审批通过 + 根据ID查询单据
 */
class InventoryCheckSubmitDAO : public BaseDAO
{
public:
	// 1.提交盘点单，发起审批（状态改为AUDITING，写入申请时间、流程id到remake）
	int submitInventoryCheck(long long checkId, long long applicantId, const std::string& flowInstanceId);

	// 2.撤回审批单据（状态恢复DRAFT，清空流程信息）
	int revokeInventoryCheck(long long checkId);

	// 3.审批通过生效（填入审批人、审批时间，状态修改EFFECTIVE）
	int approveInventoryCheck(long long checkId, long long approverId);

	// 根据ID查询单据（携带审批字段+总金额）
	PtrInventoryCheckDO selectById(long long id);
};
#endif // _INVENTORY_CHECK_SUBMIT_DAO_
