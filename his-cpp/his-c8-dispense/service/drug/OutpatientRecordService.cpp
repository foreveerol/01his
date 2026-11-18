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
#include "stdafx.h"
#include "OutpatientRecordService.h"
#include "../../dao/drug/OutpatientRecordDAO.h"

/**
 * 分页查询门诊发药/退药记录
 * 通过多条件（记录类型、患者姓名等）分页查询门诊记录
 * @param query 查询参数（包含分页参数 pageIndex、pageSize 及筛选条件）
 * @return 包含分页门诊记录列表和总记录数的 VO
 */
OutpatientRecordPageJsonVO::Wrapper OutpatientRecordService::listByCondition(const OutpatientRecordQuery::Wrapper& query)
{
	// 初始化顶层 VO 包装器用于响应
	auto jvo = OutpatientRecordPageJsonVO::createShared();
	// 初始化分页 DTO 包装器，使用 query 中的分页参数
	auto pageDTO = OutpatientRecordPageDTO::createShared();
	pageDTO->pageIndex = query->pageIndex;
	pageDTO->pageSize = query->pageSize;

	// 创建 DAO 实例访问数据库
	OutpatientRecordDAO dao;
	// 步骤1：统计符合条件的总记录数（优化：无数据时避免查询）
	uint64_t total = dao.countWithCondition(query);
	// 无匹配记录时直接返回空页（减少数据库负担）
	if (total <= 0)
	{
		jvo->success(pageDTO);
		return jvo;
	}
	// 步骤2：设置总记录数并计算总页数
	pageDTO->total = Int64(total);
	pageDTO->calcPages();

	// 步骤3：分页查询记录列表（仅在 total > 0 时执行）
	auto list = dao.selectWithCondition(query);
	// 初始化列表存储转换后的记录 DTO
	auto rows = oatpp::List<OutpatientRecordItemDTO::Wrapper>::createShared();
	// 将 DO（数据库实体）转换为 DTO（客户端响应对象）
	for (auto& item : list)
	{
		auto dto = OutpatientRecordItemDTO::createShared();
		// 将 DO 字段映射到 DTO 字段（字段名已重命名为客户端友好的名称）
		dto->prescriptionNumber = item.getPrescriptionNo(); // 重命名：prescription_no -> prescription_number
		dto->recordType = item.getRecordType();
		dto->name = item.getPatientName(); // 重命名：patient_name -> name（简化客户端字段名）
		dto->outpatientNumber = item.getOutpatientNo(); // 重命名：outpatient_no -> outpatient_number
		dto->drugName = item.getDrugName();
		dto->drugSpecifications = item.getSpecification(); // 重命名：specification -> drug_specifications（更清晰）
		dto->quantity = item.getQuantity();
		dto->unitPrice = item.getUnitPrice();
		dto->totalPrice = item.getTotalPrice();
		dto->batchNumber = item.getLotNumber(); // 重命名：lot_number -> batch_number（规范术语）
		dto->traceCode = item.getTraceCode();
		dto->manufacturer = item.getManufacturer();
		dto->department = item.getDepartment();
		dto->dispenseDate = item.getDispenseDate();
		dto->pharmacy = item.getPharmacy();
		dto->dispenseName = item.getDispenseName();
		rows->push_back(dto);
	}
	// 将转换后的记录列表附加到分页 DTO
	pageDTO->rows = rows;
	// 将 DTO 包装到 VO 并返回成功响应
	jvo->success(pageDTO);
	return jvo;
}

StringJsonVO::Wrapper OutpatientRecordService::exportRecords(const OutpatientRecordExportDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();
	// TODO：生成 Excel 报表并上传至 FastDFS
	jvo->success("Export initiated");
	return jvo;
}
