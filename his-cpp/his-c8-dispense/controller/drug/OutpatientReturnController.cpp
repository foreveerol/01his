#include "stdafx.h"
#include "OutpatientReturnController.h"
#include "../../service/drug/OutpatientReturnService.h"

// ==========================================
// 1. 分页查询退药队列
// ==========================================
OutpatientReturnQueuePageJsonVO::Wrapper OutpatientReturnController::execGetQueue(const OutpatientReturnQuery::Wrapper& query)
{
	// 【数据校验】防止空指针异常
	if (!query) {
		auto jvo = OutpatientReturnQueuePageJsonVO::createShared();
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// 【数据校验】分页参数合法性校验与默认值兜底
	if (!query->pageIndex || query->pageIndex <= 0) query->pageIndex = 1;
	if (!query->pageSize || query->pageSize <= 0) query->pageSize = 10;

	// 【异常处理】捕获底层可能抛出的异常，防止服务崩溃
	try {
		return OutpatientReturnService().listReturnQueue(query);
	}
	catch (const std::exception& e) {
		auto jvo = OutpatientReturnQueuePageJsonVO::createShared();
		jvo->init(nullptr, RS_FAIL);
		return jvo;
	}
}

// ==========================================
// 2. 查询退药明细
// ==========================================
OutpatientReturnJsonVO::Wrapper OutpatientReturnController::execGetDetail(const OutpatientReturnQuery::Wrapper& query)
{
	// 【数据校验】校验查询参数及关键字（退药单号）是否为空
	if (!query || !query->keyword || query->keyword->empty()) {
		auto jvo = OutpatientReturnJsonVO::createShared();
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// 组装 DTO 传给 Service[cite: 1]
	auto dto = OutpatientReturnDrugDTO::createShared();
	dto->drugId = query->keyword;

	// 【异常处理】
	try {
		return OutpatientReturnService().getReturnDetail(dto);
	}
	catch (const std::exception& e) {
		auto jvo = OutpatientReturnJsonVO::createShared();
		jvo->init(nullptr, RS_FAIL);
		return jvo;
	}
}

// ==========================================
// 3. 确认退药
// ==========================================
StringJsonVO::Wrapper OutpatientReturnController::execConfirmReturn(const OutpatientReturnConfirmDTO::Wrapper& dto)
{
	// 【数据校验】严格校验业务必需字段
	if (!dto) {
		auto jvo = StringJsonVO::createShared();
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	if (!dto->returnId || dto->returnId->empty()) {
		auto jvo = StringJsonVO::createShared();
		jvo->init("确认退药失败：退药单号不能为空", RS_PARAMS_INVALID);
		return jvo;
	}

	// 【异常处理】
	try {
		return OutpatientReturnService().confirmReturn(dto);
	}
	catch (const std::exception& e) {
		auto jvo = StringJsonVO::createShared();
		jvo->init(nullptr, RS_FAIL);
		return jvo;
	}
}

// ==========================================
// 4. 拒绝退药
// ==========================================
StringJsonVO::Wrapper OutpatientReturnController::execRejectReturn(const OutpatientReturnRejectDTO::Wrapper& dto)
{
	// 【数据校验】严格校验单号与拒绝原因
	if (!dto) {
		auto jvo = StringJsonVO::createShared();
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	if (!dto->returnId || dto->returnId->empty()) {
		auto jvo = StringJsonVO::createShared();
		jvo->init("拒绝退药失败：退药单号不能为空", RS_PARAMS_INVALID);
		return jvo;
	}

	// 【异常处理】
	try {
		return OutpatientReturnService().rejectReturn(dto);
	}
	catch (const std::exception& e) {
		auto jvo = StringJsonVO::createShared();
		jvo->init(nullptr, RS_FAIL);
		return jvo;
	}
}