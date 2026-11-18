/*
 Copyright Zero One Star. All rights reserved.

 @Author: zjb517
 @Date: 2026/07/26 10:00:00

 Licensed under the Apache License, Version 2.0 (the "License");
 You may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#include "stdafx.h"
#include "InpatientDispenseService.h"
#include "../../dao/drug/InpatientDispenseDAO.h"

/**
 * 分页查询住院发药汇总队列
 * 分页获取所有发药汇总单据，支持按状态、汇总单号、时间范围筛选
 * InpatientDispenseSummaryPageDTO 为自定义 DTO，未继承 PageDTO，分页由 DAO 内部处理
 * @param query 查询参数（包含分页参数 pageIndex、pageSize 及筛选条件）
 * @return 包含汇总列表和总记录数的 VO
 */
InpatientDispenseSummaryPageJsonVO::Wrapper InpatientDispenseService::listSummaryQueue(const InpatientDispenseQuery::Wrapper& query)
{
	// 初始化顶层 VO 包装器用于响应
	auto jvo = InpatientDispenseSummaryPageJsonVO::createShared();
	// 初始化住院专用分页 DTO（自定义 DTO，仅含 total 和 summaryList 字段）
	auto pageDTO = InpatientDispenseSummaryPageDTO::createShared();

	// 创建 DAO 实例访问数据库
	InpatientDispenseDAO dao;
	// 步骤1：获取汇总单据总数（供前端计算分页）
	uint64_t total = dao.countSummaryQueue(query);
	// 将总记录数设置到 DTO 字段
	pageDTO->total = UInt64(total);

	// 步骤2：分页查询汇总列表（DAO 内部使用 query 的 pageIndex/pageSize 处理分页）
	auto list = dao.selectSummaryQueue(query);
	// 初始化列表存储转换后的 DTO 项
	auto rows = oatpp::List<InpatientDispenseSummaryItemDTO::Wrapper>::createShared();
	// 将 DO（DAO 结果）转换为 DTO（客户端响应格式）
	for (auto& item : list)
	{
		auto dto = InpatientDispenseSummaryItemDTO::createShared();
		// 将 DO 字段映射到 DTO 字段（确认 getter/setter 在 DO 中存在）
		dto->id = item.getId();
		dto->summaryNo = item.getSummaryNo();
		dto->summaryStatus = item.getSummaryStatus();
		dto->createTime = item.getCreateTime();
		dto->pharmacy = item.getPharmacy();
		dto->applicant = item.getApplicant();
		rows->push_back(dto);
	}
	// 将转换后的列表设置到自定义 DTO 字段
	pageDTO->summaryList = rows;

	// 将 DTO 包装到顶层 VO 并返回成功
	jvo->success(pageDTO);
	return jvo;
}

/**
 * 获取指定住院发药汇总单的药品明细
 * 查询给定汇总单号下的所有药品项目，若无药品则返回空列表
 * @param query 查询参数（必须包含有效的 summaryNo）
 * @return 包含药品列表和基本汇总信息的 VO，若 summaryNo 无效则返回错误
 */
InpatientDrugDetailJsonVO::Wrapper InpatientDispenseService::getDrugDetail(const InpatientDrugDetailQuery::Wrapper& query)
{
	// 初始化顶层 VO 包装器用于响应
	auto jvo = InpatientDrugDetailJsonVO::createShared();

	// 校验必填参数：summaryNo（必须非空）
	if (!query->summaryNo || query->summaryNo->empty())
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// 创建 DAO 实例查询药品明细
	InpatientDispenseDAO dao;
	// 按汇总单号从数据库查询药品列表（若无药品则返回空列表）
	auto list = dao.selectDrugDetail(query->summaryNo.getValue(""));

	// 初始化结果 DTO 存储汇总基本信息 + 转换后的药品列表
	auto result = InpatientDrugDetailDTO::createShared();
	result->summaryNo = query->summaryNo;

	// 初始化列表存储转换后的药品项目 DTO
	auto drugList = oatpp::List<InpatientDrugItemDTO::Wrapper>::createShared();
	// 将 DO（数据库结果）转换为 DTO（客户端响应格式）
	for (auto& item : list)
	{
		auto dto = InpatientDrugItemDTO::createShared();
		// 将 DO 字段映射到 DTO 字段（确保 getter/setter 名称匹配）
		dto->detailId = item.getDetailId();
		dto->serialNo = Int32(item.getSerialNo());
		dto->drugName = item.getDrugName();
		dto->quantity = item.getQuantity();
		dto->specification = item.getSpecification();
		drugList->push_back(dto);
	}
	// 将转换后的药品列表附加到结果 DTO
	result->drugList = drugList;

	// 将结果 DTO 包装到顶层 VO 并返回成功响应
	jvo->success(result);
	return jvo;
}

StringJsonVO::Wrapper InpatientDispenseService::verifyDispense(const InpatientDispenseVerifyDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	if (!dto->Dispenseld || *dto->Dispenseld == 0) {
		jvo->init("Dispenseld is required.", RS_PARAMS_INVALID);
		return jvo;
	}

	// TODO：通过汇总单号查找并更新状态
	jvo->success("Dispense verified successfully");
	return jvo;
}

StringJsonVO::Wrapper InpatientDispenseService::rejectDispense(const InpatientDispenseRejectDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	if (!dto->dispenseld || *dto->dispenseld == 0) {
		jvo->init("dispenseld is required.", RS_PARAMS_INVALID);
		return jvo;
	}

	// TODO：更新状态为已拒绝
	jvo->success("Dispense rejected successfully");
	return jvo;
}
