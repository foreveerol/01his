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
#ifndef _INPATIENT_RECORD_DTO_
#define _INPATIENT_RECORD_DTO_
#include "../../GlobalInclude.h"
#include "domain/dto/PageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Inpatient dispense/return record item DTO
 * Corresponds to one row in the detail list
 */
class InpatientRecordItemDTO : public oatpp::DTO
{
	DTO_INIT(InpatientRecordItemDTO, DTO);
	// Prescription number
	DTO_FIELD(String, prescriptionNo);
	DTO_FIELD_INFO(prescriptionNo) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.prescriptionNo");
	}
	// Record type (dispense/return)
	DTO_FIELD(String, recordType);
	DTO_FIELD_INFO(recordType) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.recordType");
	}
	// Patient name
	DTO_FIELD(String, patientName);
	DTO_FIELD_INFO(patientName) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.patientName");
	}
	// Hospitalization number
	DTO_FIELD(String, hospitalizationNo);
	DTO_FIELD_INFO(hospitalizationNo) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.hospitalizationNo");
	}
	// Ward
	DTO_FIELD(String, ward);
	DTO_FIELD_INFO(ward) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.ward");
	}
	// Bed number
	DTO_FIELD(String, bedNo);
	DTO_FIELD_INFO(bedNo) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.bedNo");
	}
	// Drug name
	DTO_FIELD(String, drugName);
	DTO_FIELD_INFO(drugName) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.drugName");
	}
	// Specification
	DTO_FIELD(String, specification);
	DTO_FIELD_INFO(specification) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.specification");
	}
	// Quantity
	DTO_FIELD(String, quantity);
	DTO_FIELD_INFO(quantity) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.quantity");
	}
	// Unit price
	DTO_FIELD(String, unitPrice);
	DTO_FIELD_INFO(unitPrice) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.unitPrice");
	}
	// Total amount
	DTO_FIELD(String, totalAmount);
	DTO_FIELD_INFO(totalAmount) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.totalAmount");
	}
	// Batch number
	DTO_FIELD(String, batchNo);
	DTO_FIELD_INFO(batchNo) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.batchNo");
	}
	// Trace code
	DTO_FIELD(String, traceCode);
	DTO_FIELD_INFO(traceCode) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.traceCode");
	}
	// Manufacturer
	DTO_FIELD(String, manufacturer);
	DTO_FIELD_INFO(manufacturer) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.manufacturer");
	}
	// Summary number
	DTO_FIELD(String, summaryNo);
	DTO_FIELD_INFO(summaryNo) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.summaryNo");
	}
	// Department name
	DTO_FIELD(String, deptName);
	DTO_FIELD_INFO(deptName) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.deptName");
	}
};

/**
 * Inpatient dispense/return record page DTO
 */
class InpatientRecordPageDTO : public PageDTO<InpatientRecordItemDTO::Wrapper>
{
	DTO_INIT(InpatientRecordPageDTO, PageDTO<InpatientRecordItemDTO::Wrapper>);
};

/**
 * Inpatient dispense/return record export request DTO
 * Contains all filter conditions (same as query, without pagination)
 */
class InpatientRecordExportDTO : public oatpp::DTO
{
	DTO_INIT(InpatientRecordExportDTO, DTO);
	// Drug name
	DTO_FIELD(String, drugName);
	DTO_FIELD_INFO(drugName) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.drugName");
	}
	// Record type
	DTO_FIELD(String, recordType);
	DTO_FIELD_INFO(recordType) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.recordType");
	}
	// Pharmacy
	DTO_FIELD(String, pharmacy);
	DTO_FIELD_INFO(pharmacy) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.pharmacy");
	}
	// Project type
	DTO_FIELD(String, projectType);
	DTO_FIELD_INFO(projectType) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.projectType");
	}
	// Dispenser name
	DTO_FIELD(String, dispenseName);
	DTO_FIELD_INFO(dispenseName) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.dispenseName");
	}
	// Patient name
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.name");
	}
	// Hospitalization number
	DTO_FIELD(String, hospitalizationNo);
	DTO_FIELD_INFO(hospitalizationNo) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.hospitalizationNo");
	}
	// Record number
	DTO_FIELD(String, recordNo);
	DTO_FIELD_INFO(recordNo) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.recordNo");
	}
	// Start date
	DTO_FIELD(String, startDate);
	DTO_FIELD_INFO(startDate) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.startDate");
	}
	// End date
	DTO_FIELD(String, endDate);
	DTO_FIELD_INFO(endDate) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-record.field.endDate");
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_INPATIENT_RECORD_DTO_
