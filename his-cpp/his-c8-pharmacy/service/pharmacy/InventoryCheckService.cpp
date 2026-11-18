
#include "stdafx.h"
#include "InventoryCheckService.h"
#include "../../dao/pharmacy/InventoryCheckDAO.h"
#include "../../../lib-common/include/SimpleDateTimeFormat.h"

InventoryCheckPageJsonVO::Wrapper InventoryCheckService::listByCondition(const InventoryCheckQuery::Wrapper& query)
{
	auto jvo = InventoryCheckPageJsonVO::createShared();
	auto pageDTO = InventoryCheckPageDTO::createShared();
	pageDTO->pageIndex = query->pageIndex;
	pageDTO->pageSize = query->pageSize;

	InventoryCheckDAO dao;
	auto list = dao.selectList(query);
	uint64_t total = dao.countList(query);

	pageDTO->total = UInt64(total);
	pageDTO->calcPages();

	auto rows = oatpp::List<InventoryCheckListItemDTO::Wrapper>::createShared();
	for (auto& item : list) {
		auto dto = InventoryCheckListItemDTO::createShared();
		dto->checkNo = item.getBusNo();
		dto->checkType = item.getIntentEnum();
		dto->checkDate = item.getCreatedAt();
		dto->drugCount = Int32(item.getDrugCount());
		dto->status = item.getStatusEnum();
		dto->checker = item.getChecker();
		rows->push_back(dto);
	}
	pageDTO->rows = rows;
	jvo->success(pageDTO);
	return jvo;
}

InventoryCheckJsonVO::Wrapper InventoryCheckService::queryOne(const String& checkNo)
{
	auto jvo = InventoryCheckJsonVO::createShared();

	if (!checkNo || checkNo->empty()) {
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	InventoryCheckDAO dao;
	auto detail = dao.selectByCheckNo(checkNo);
	if (detail.getBusNo().empty()) {
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	auto result = InventoryCheckDTO::createShared();
	result->checkNo = detail.getBusNo();
	result->checkType = detail.getIntentEnum();
	result->checkDate = detail.getCreatedAt();
	result->status = detail.getStatusEnum();
	result->remark = detail.getRemake();

	auto drugList = oatpp::List<CheckDrugItemDTO::Wrapper>::createShared();
	result->drugList = drugList;

	jvo->success(result);
	return jvo;
}

StringJsonVO::Wrapper InventoryCheckService::create()
{
	auto jvo = StringJsonVO::createShared();
	std::string checkNo = generateCheckNo();
	jvo->success(checkNo);
	return jvo;
}

StringJsonVO::Wrapper InventoryCheckService::saveDraft(const InventoryCheckSaveDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	if (!dto->checkType || dto->checkType->empty()) {
		jvo->init("checkType is required.", RS_PARAMS_INVALID);
		return jvo;
	}

	// TODO: persist to wkf_supply_request
	jvo->success("Draft saved successfully");
	return jvo;
}

StringJsonVO::Wrapper InventoryCheckService::saveAndSubmit(const InventoryCheckSaveDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	if (!dto->checkType || dto->checkType->empty()) {
		jvo->init("checkType is required.", RS_PARAMS_INVALID);
		return jvo;
	}

	// TODO: persist and submit
	jvo->success("Saved and submitted successfully");
	return jvo;
}

// 提交盘点单，发起审批
StringJsonVO::Wrapper InventoryCheckService::submit(const InventoryCheckRemoveDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	if (!dto->checkNo || dto->checkNo->empty())
	{
		jvo->init("checkNo is required.", RS_PARAMS_INVALID);
		return jvo;
	}
	std::string checkNo(dto->checkNo->c_str());

	InventoryCheckDAO dao;
	InvCheckDetailDO detail = dao.selectByCheckNo(checkNo);

	// 判断单据是否存在
	if (detail.getBusNo().empty())
	{
		jvo->init("Inventory check document not found.", RS_PARAMS_INVALID);
		return jvo;
	}
	// 状态校验：仅草稿允许提交
	if (detail.getStatusEnum() != "DRAFT")
	{
		jvo->init("Only draft document can be submitted.", RS_FAIL);
		return jvo;
	}

	// 获取主键ID
	std::string recordId = detail.getBusNo();
	// 调用DAO现成状态更新接口
	int affectRows = dao.updateStatus(recordId, "PENDING_APPROVAL", "0");

	if (affectRows > 0)
	{
		jvo->success("Submitted successfully");
	}
	else
	{
		jvo->init("Submit failed, database update error.", RS_FAIL);
	}
	return jvo;
}

// 撤回盘点单
StringJsonVO::Wrapper InventoryCheckService::withdraw(const InventoryCheckRemoveDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	if (!dto->checkNo || dto->checkNo->empty())
	{
		jvo->init("checkNo is required.", RS_PARAMS_INVALID);
		return jvo;
	}
	std::string checkNo(dto->checkNo->c_str());

	InventoryCheckDAO dao;
	InvCheckDetailDO detail = dao.selectByCheckNo(checkNo);

	if (detail.getBusNo().empty())
	{
		jvo->init("Inventory check document not found.", RS_PARAMS_INVALID);
		return jvo;
	}
	if (detail.getStatusEnum() != "PENDING_APPROVAL")
	{
		jvo->init("Only pending approval document can be withdrawn.", RS_FAIL);
		return jvo;
	}

	std::string primaryKey = detail.getBusNo();
	int affectRows = dao.updateStatus(primaryKey, "DRAFT", "0");

	if (affectRows > 0)
	{
		jvo->success("Withdrawn successfully");
	}
	else
	{
		jvo->init("Withdraw failed, database update error.", RS_FAIL);
	}
	return jvo;
}

// 审批通过
StringJsonVO::Wrapper InventoryCheckService::approve(const InventoryCheckApprovalDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	if (!dto->checkNo || dto->checkNo->empty())
	{
		jvo->init("checkNo is required.", RS_PARAMS_INVALID);
		return jvo;
	}
	std::string checkNo(dto->checkNo->c_str());

	InventoryCheckDAO dao;
	InvCheckDetailDO detail = dao.selectByCheckNo(checkNo);

	if (detail.getBusNo().empty())
	{
		jvo->init("Inventory check document not found.", RS_PARAMS_INVALID);
		return jvo;
	}
	if (detail.getStatusEnum() != "PENDING_APPROVAL")
	{
		jvo->init("Only pending approval document can be approved.", RS_FAIL);
		return jvo;
	}

	std::string primaryKey = detail.getBusNo();
	int affectRows = dao.updateStatus(primaryKey, "APPROVED", "0");

	if (affectRows > 0)
	{
		jvo->success("Approved successfully");
	}
	else
	{
		jvo->init("Approve failed, database update error.", RS_FAIL);
	}
	return jvo;
}

StringJsonVO::Wrapper InventoryCheckService::reject(const InventoryCheckApprovalDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	if (!dto->checkNo || dto->checkNo->empty()) {
		jvo->init("checkNo is required.", RS_PARAMS_INVALID);
		return jvo;
	}

	// TODO: update status to REJECTED with reason
	jvo->success("Rejected successfully");
	return jvo;
}

StringJsonVO::Wrapper InventoryCheckService::remove(const InventoryCheckRemoveDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	if (!dto->checkNo || dto->checkNo->empty()) {
		jvo->init("checkNo is required.", RS_PARAMS_INVALID);
		return jvo;
	}

	// TODO: soft delete
	jvo->success("Removed successfully");
	return jvo;
}

std::string InventoryCheckService::generateCheckNo()
{
	auto now = std::chrono::system_clock::now();
	std::time_t t = std::chrono::system_clock::to_time_t(now);
	std::tm tm;
	localtime_s(&tm, &t);

	char dateBuf[16];
	strftime(dateBuf, sizeof(dateBuf), "%Y%m%d", &tm);

	static int seq = 0;
	seq++;

	char result[32];
	snprintf(result, sizeof(result), "PD%s%04d", dateBuf, seq);
	return std::string(result);
}
