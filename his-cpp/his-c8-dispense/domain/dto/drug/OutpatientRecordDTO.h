#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: zjb517
 @Date: 2026/07/19 17:30:00

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
#ifndef _OUTPATIENT_RECORD_DTO_
#define _OUTPATIENT_RECORD_DTO_
#include "../../GlobalInclude.h"
#include "domain/dto/PageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 门诊发退药记录项DTO
 */
class OutpatientRecordItemDTO : public oatpp::DTO
{
	DTO_INIT(OutpatientRecordItemDTO, DTO);
	// 处方号/退药号
	DTO_FIELD(String, prescriptionNumber);
	DTO_FIELD_INFO(prescriptionNumber) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.prescriptionNumber");
	}
	//类型（发药/退药）
	DTO_FIELD(String, recordType);
	DTO_FIELD_INFO(recordType) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.recordType");
	}
	// 患者姓名
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.name");
	}
	//门诊号
	DTO_FIELD(String, outpatientNumber);
	DTO_FIELD_INFO(outpatientNumber) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.outpatientNumber");
	}
	//药品名称
	DTO_FIELD(String, drugName);
	DTO_FIELD_INFO(drugName) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.drugName");
	}
	// 规格
	DTO_FIELD(String, drugSpecifications);
	DTO_FIELD_INFO(drugSpecifications) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.drugSpecifications");
	}
	// 数量
	DTO_FIELD(String, quantity);
	DTO_FIELD_INFO(quantity) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.quantity");
	}
	// 单价
	DTO_FIELD(Float64, unitPrice);
	DTO_FIELD_INFO(unitPrice) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.unitPrice");
	}
	// 金额
	DTO_FIELD(Float64, totalPrice);
	DTO_FIELD_INFO(totalPrice) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.totalPrice");
	}
	// 批号
	DTO_FIELD(String, batchNumber);
	DTO_FIELD_INFO(batchNumber) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.batchNumber");
	}
	// 追溯码
	DTO_FIELD(String, traceCode);
	DTO_FIELD_INFO(traceCode) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.traceCode");
	}
	//厂家
	DTO_FIELD(String, manufacturer);
	DTO_FIELD_INFO(manufacturer) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.manufacturer");
	}
	// 开单科室
	DTO_FIELD(String, department);
	DTO_FIELD_INFO(department) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.department");
	}
	// 发药时间
	DTO_FIELD(String, dispenseDate);
	DTO_FIELD_INFO(dispenseDate) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.dispenseDate");
	}
	//药房
	DTO_FIELD(String, pharmacy);
	DTO_FIELD_INFO(pharmacy) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.pharmacy");
	}
	// 发药人
	DTO_FIELD(String, dispenseName);
	DTO_FIELD_INFO(dispenseName) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.dispenseName");
	}
};

/**
 * 门诊发退药记录分页DTO
 */
class OutpatientRecordPageDTO : public PageDTO<OutpatientRecordItemDTO::Wrapper>
{
	DTO_INIT(OutpatientRecordPageDTO, PageDTO<OutpatientRecordItemDTO::Wrapper>);
};

/**
 * 门诊发退药记录导出请求DTO
 */
class OutpatientRecordExportDTO : public oatpp::DTO
{
	DTO_INIT(OutpatientRecordExportDTO, DTO);
	// 开始日期
	DTO_FIELD(String, startDate);
	DTO_FIELD_INFO(startDate) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.startDate");
	}
	// 结束日期
	DTO_FIELD(String, endDate);
	DTO_FIELD_INFO(endDate) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.endDate");
	}
	// 业务类型筛选
	DTO_FIELD(String, businessType);
	DTO_FIELD_INFO(businessType) {
		info->description = ZH_WORDS_GETTER("dispense.outpatient-record.field.businessType");
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_OUTPATIENT_RECORD_DTO_
