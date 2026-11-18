#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: zjb517
 @Date: 2026/07/19 17:02:00

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
#ifndef _INPATIENT_RETURN_DTO_
#define _INPATIENT_RETURN_DTO_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 患者基础信息DTO，展示在退药明细页面上方
 */
class InpatientReturnPatientDTO : public oatpp::DTO
{
	DTO_INIT(InpatientReturnPatientDTO, DTO);
	// 患者姓名
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("dispense.return.field.name");
	}
	// 性别
	DTO_FIELD(String, gender);
	DTO_FIELD_INFO(gender) {
		info->description = ZH_WORDS_GETTER("dispense.return.field.gender");
	}
	// 年龄
	DTO_FIELD(Int32, age);
	DTO_FIELD_INFO(age) {
		info->description = ZH_WORDS_GETTER("dispense.return.field.age");
	}
	// 住院号
	DTO_FIELD(String, hospitalizationNo);
	DTO_FIELD_INFO(hospitalizationNo) {
		info->description = ZH_WORDS_GETTER("dispense.return.field.hospitalizationNo");
	}
	// 所属病区
	DTO_FIELD(String, ward);
	DTO_FIELD_INFO(ward) {
		info->description = ZH_WORDS_GETTER("dispense.return.field.ward");
	}
	// 床位号
	DTO_FIELD(String, bedNo);
	DTO_FIELD_INFO(bedNo) {
		info->description = ZH_WORDS_GETTER("dispense.return.field.bedNo");
	}
	// 退药状态标签
	DTO_FIELD(String, refundStatus);
	DTO_FIELD_INFO(refundStatus) {
		info->description = ZH_WORDS_GETTER("dispense.return.field.refundStatus");
	}
public:
	InpatientReturnPatientDTO() {
		this->age = Int32(0);
	}
};

/**
 * 退药药品明细项DTO，对应表格中每一行药品数据
 */
class InpatientReturnDrugDTO : public oatpp::DTO
{
	DTO_INIT(InpatientReturnDrugDTO, DTO);
	// 退药明细唯一ID
	DTO_FIELD(String, detailId);
	DTO_FIELD_INFO(detailId) {
		info->description = ZH_WORDS_GETTER("dispense.return.field.detailId");
	}
	// 表格序号
	DTO_FIELD(Int32, serialNo);
	DTO_FIELD_INFO(serialNo) {
		info->description = ZH_WORDS_GETTER("dispense.return.field.serialNo");
	}
	// 药品名称
	DTO_FIELD(String, drugName);
	DTO_FIELD_INFO(drugName) {
		info->description = ZH_WORDS_GETTER("dispense.return.field.drugName");
	}
	// quantity
	DTO_FIELD(String, quantity);
	DTO_FIELD_INFO(quantity) {
		info->description = ZH_WORDS_GETTER("dispense.return.field.quantity");
	}
	// dispense date
	DTO_FIELD(String, dispenseDate);
	DTO_FIELD_INFO(dispenseDate) {
		info->description = ZH_WORDS_GETTER("dispense.return.field.dispenseDate");
	}
public:
	InpatientReturnDrugDTO() {
		this->serialNo = Int32(0);
	}
};

/**
 * 退药明细综合响应DTO，包含患者信息和药品列表
 */
class InpatientReturnDTO : public oatpp::DTO
{
	DTO_INIT(InpatientReturnDTO, DTO);
	// 患者基础信息
	DTO_FIELD(Object<InpatientReturnPatientDTO>, patientInfo);
	DTO_FIELD_INFO(patientInfo) {
		info->description = ZH_WORDS_GETTER("dispense.return.field.patientInfo");
	}
	// 待退药品列表
	DTO_FIELD(oatpp::List<InpatientReturnDrugDTO::Wrapper>, drugList);
	DTO_FIELD_INFO(drugList) {
		info->description = ZH_WORDS_GETTER("dispense.return.field.drugList");
	}
};

/**
 * 确认退药请求体DTO
 */
class InpatientReturnConfirmDTO : public oatpp::DTO
{
	DTO_INIT(InpatientReturnConfirmDTO, DTO);
	// 住院号
	DTO_FIELD(String, hospitalizationNo);
	DTO_FIELD_INFO(hospitalizationNo) {
		info->required = true;
		info->description = ZH_WORDS_GETTER("dispense.return.field.hospitalizationNo");
	}
	// 待退药的明细ID列表（对应勾选的药品行）
	DTO_FIELD(oatpp::List<String>, refundDetailIds);
	DTO_FIELD_INFO(refundDetailIds) {
		info->required = true;
		info->description = ZH_WORDS_GETTER("dispense.return.field.refundDetailIds");
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_INPATIENT_RETURN_DTO_
