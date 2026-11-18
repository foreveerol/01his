#include "stdafx.h"
#include "InventoryCheckSubmitDAO.h"
#include "InventoryCheckSubmitMapper.h"
#include <sstream>
#include <ctime>

// 1. 提交盘点单进入审批流
int InventoryCheckSubmitDAO::submitInventoryCheck(long long checkId, long long applicantId, const std::string& flowInstanceId)
{
	SqlParams params;
	std::string sql = R"(
		UPDATE wkf_supply_request
		SET status_enum = 'AUDITING', applicant_id = ?, apply_time = NOW(), remake = ?, updated_at = NOW()
		WHERE id = ? AND status_enum = 'DRAFT' AND is_deleted = 0
	)";
	SQLPARAMS_PUSH(params, "ll", long long, applicantId);
	SQLPARAMS_PUSH(params, "s", std::string, flowInstanceId);
	SQLPARAMS_PUSH(params, "ll", long long, checkId);
	return sqlSession->executeUpdate(sql, params);
}

// 2. 撤回已提交审批的盘点单
int InventoryCheckSubmitDAO::revokeInventoryCheck(long long checkId)
{
	SqlParams params;
	std::string sql = R"(
		UPDATE wkf_supply_request
		SET status_enum = 'DRAFT', remake = '', updated_at = NOW()
		WHERE id = ? AND status_enum = 'AUDITING' AND is_deleted = 0
	)";
	SQLPARAMS_PUSH(params, "ll", long long, checkId);
	return sqlSession->executeUpdate(sql, params);
}

// 3. 审批通过，盘点结果生效
int InventoryCheckSubmitDAO::approveInventoryCheck(long long checkId, long long approverId)
{
	SqlParams params;
	std::string sql = R"(
		UPDATE wkf_supply_request
		SET status_enum = 'EFFECTIVE', approver_id = ?, approval_time = NOW(), updated_at = NOW()
		WHERE id = ? AND status_enum = 'AUDITING' AND is_deleted = 0
	)";
	SQLPARAMS_PUSH(params, "ll", long long, approverId);
	SQLPARAMS_PUSH(params, "ll", long long, checkId);
	return sqlSession->executeUpdate(sql, params);
}

// 根据ID查询盘点单
PtrInventoryCheckDO InventoryCheckSubmitDAO::selectById(long long id)
{
	std::string sql = R"(
		SELECT id,status_enum,approver_id,approval_time,applicant_id,apply_time,remake,total_price
		FROM wkf_supply_request WHERE id = ? AND is_deleted = 0
	)";
	return sqlSession->executeQueryOne<PtrInventoryCheckDO>(sql, PtrInventoryCheckSubmitMapper(), "%lld", id);
}