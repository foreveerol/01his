#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 10:59:38

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
#ifndef _DISPENSE_RECORD_DTO_
#define _DISPENSE_RECORD_DTO_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 门诊发退药记录数据传输对象
 */
class DispenseRecordDTO : public oatpp::DTO
{
	DTO_INIT(DispenseRecordDTO, DTO);
	// 发退药单号
	DTO_FIELD(String, busNo);
	DTO_FIELD_INFO(busNo) {
		info->description = ZH_WORDS_GETTER("dispense.field.busNo");
	}
	// 记录类型
	DTO_FIELD(String, statusEnum);
	DTO_FIELD_INFO(statusEnum) {
		info->description = ZH_WORDS_GETTER("dispense.field.statusEnum");
	}
	// 操作时间
	DTO_FIELD(String, dispenseTime);
	DTO_FIELD_INFO(dispenseTime) {
		info->description = ZH_WORDS_GETTER("dispense.field.dispenseTime");
	}
	// 患者姓名
	DTO_FIELD(String, patientName);
	DTO_FIELD_INFO(patientName) {
		info->description = ZH_WORDS_GETTER("dispense.field.patientName");
	}
	// 身份证号
	DTO_FIELD(String, idCard);
	DTO_FIELD_INFO(idCard) {
		info->description = ZH_WORDS_GETTER("dispense.field.idCard");
	}
	// 就诊号
	DTO_FIELD(String, encounterBusNo);
	DTO_FIELD_INFO(encounterBusNo) {
		info->description = ZH_WORDS_GETTER("dispense.field.encounterBusNo");
	}
	// 药品名称
	DTO_FIELD(String, medicationName);
	DTO_FIELD_INFO(medicationName) {
		info->description = ZH_WORDS_GETTER("dispense.field.medicationName");
	}
	// 规格
	DTO_FIELD(String, totalVolume);
	DTO_FIELD_INFO(totalVolume) {
		info->description = ZH_WORDS_GETTER("dispense.field.totalVolume");
	}
	// 剂型
	DTO_FIELD(String, doseFormCode);
	DTO_FIELD_INFO(doseFormCode) {
		info->description = ZH_WORDS_GETTER("dispense.field.doseFormCode");
	}
	// 申请数量
	DTO_FIELD(String, quantity);
	DTO_FIELD_INFO(quantity) {
		info->description = ZH_WORDS_GETTER("dispense.field.quantity");
	}
	// 实发/退数量
	DTO_FIELD(String, dispenseQuantity);
	DTO_FIELD_INFO(dispenseQuantity) {
		info->description = ZH_WORDS_GETTER("dispense.field.dispenseQuantity");
	}
	// 单位
	DTO_FIELD(String, unitCode);
	DTO_FIELD_INFO(unitCode) {
		info->description = ZH_WORDS_GETTER("dispense.field.unitCode");
	}
	// 批号
	DTO_FIELD(String, lotNumber);
	DTO_FIELD_INFO(lotNumber) {
		info->description = ZH_WORDS_GETTER("dispense.field.lotNumber");
	}
	// 操作人
	DTO_FIELD(String, practitionerName);
	DTO_FIELD_INFO(practitionerName) {
		info->description = ZH_WORDS_GETTER("dispense.field.practitionerName");
	}
	// 药房名称
	DTO_FIELD(String, locationName);
	DTO_FIELD_INFO(locationName) {
		info->description = ZH_WORDS_GETTER("dispense.field.locationName");
	}
	// 处方号
	DTO_FIELD(String, prescriptionNo);
	DTO_FIELD_INFO(prescriptionNo) {
		info->description = ZH_WORDS_GETTER("dispense.field.prescriptionNo");
	}
	// 开嘱医生ID
	DTO_FIELD(String, requesterId);
	DTO_FIELD_INFO(requesterId) {
		info->description = ZH_WORDS_GETTER("dispense.field.requesterId");
	}
	// 创建时间
	DTO_FIELD(String, createdAt);
	DTO_FIELD_INFO(createdAt) {
		info->description = ZH_WORDS_GETTER("dispense.field.createdAt");
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_DISPENSE_RECORD_DTO_
