#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: zjb517
 @Date: 2026/07/19 18:00:00

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
#ifndef _INVENTORY_CHECK_DTO_
#define _INVENTORY_CHECK_DTO_
#include "../../GlobalInclude.h"
#include "domain/dto/PageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Pharmacy inventory check list item DTO
 */
class InventoryCheckListItemDTO : public oatpp::DTO
{
	DTO_INIT(InventoryCheckListItemDTO, DTO);
	// Check document number
	DTO_FIELD(String, checkNo);
	DTO_FIELD_INFO(checkNo) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.checkNo");
	}
	// Check type (full/sampling)
	DTO_FIELD(String, checkType);
	DTO_FIELD_INFO(checkType) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.checkType");
	}
	// Check date
	DTO_FIELD(String, checkDate);
	DTO_FIELD_INFO(checkDate) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.checkDate");
	}
	// Drug count
	DTO_FIELD(Int32, drugCount);
	DTO_FIELD_INFO(drugCount) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.drugCount");
	}
	// Status (draft/pending/approved/rejected)
	DTO_FIELD(String, status);
	DTO_FIELD_INFO(status) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.status");
	}
	// Checker name
	DTO_FIELD(String, checker);
	DTO_FIELD_INFO(checker) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.checker");
	}
public:
	InventoryCheckListItemDTO() { this->drugCount = Int32(0); }
};

/**
 * Pharmacy inventory check page DTO
 */
class InventoryCheckPageDTO : public PageDTO<InventoryCheckListItemDTO::Wrapper>
{
	DTO_INIT(InventoryCheckPageDTO, PageDTO<InventoryCheckListItemDTO::Wrapper>);
};

/**
 * Check drug detail item DTO
 */
class CheckDrugItemDTO : public oatpp::DTO
{
	DTO_INIT(CheckDrugItemDTO, DTO);
	// Detail ID
	DTO_FIELD(String, detailId);
	DTO_FIELD_INFO(detailId) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.detailId");
	}
	// Drug name
	DTO_FIELD(String, drugName);
	DTO_FIELD_INFO(drugName) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.drugName");
	}
	// Specification
	DTO_FIELD(String, specification);
	DTO_FIELD_INFO(specification) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.specification");
	}
	// Batch number
	DTO_FIELD(String, batchNo);
	DTO_FIELD_INFO(batchNo) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.batchNo");
	}
	// System quantity
	DTO_FIELD(Int32, systemQty);
	DTO_FIELD_INFO(systemQty) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.systemQty");
	}
	// Actual quantity
	DTO_FIELD(Int32, actualQty);
	DTO_FIELD_INFO(actualQty) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.actualQty");
	}
	// Difference quantity
	DTO_FIELD(Int32, diffQty);
	DTO_FIELD_INFO(diffQty) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.diffQty");
	}
	// Difference reason
	DTO_FIELD(String, diffReason);
	DTO_FIELD_INFO(diffReason) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.diffReason");
	}
public:
	CheckDrugItemDTO() { this->systemQty = Int32(0); this->actualQty = Int32(0); this->diffQty = Int32(0); }
};

/**
 * Inventory check detail DTO
 */
class InventoryCheckDTO : public oatpp::DTO
{
	DTO_INIT(InventoryCheckDTO, DTO);
	// Check document number
	DTO_FIELD(String, checkNo);
	DTO_FIELD_INFO(checkNo) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.checkNo");
	}
	// Check type
	DTO_FIELD(String, checkType);
	DTO_FIELD_INFO(checkType) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.checkType");
	}
	// Check date
	DTO_FIELD(String, checkDate);
	DTO_FIELD_INFO(checkDate) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.checkDate");
	}
	// Status
	DTO_FIELD(String, status);
	DTO_FIELD_INFO(status) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.status");
	}
	// Reject reason
	DTO_FIELD(String, rejectReason);
	DTO_FIELD_INFO(rejectReason) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.rejectReason");
	}
	// Remark
	DTO_FIELD(String, remark);
	DTO_FIELD_INFO(remark) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.remark");
	}
	// Drug detail list
	DTO_FIELD(oatpp::List<CheckDrugItemDTO::Wrapper>, drugList);
	DTO_FIELD_INFO(drugList) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.drugList");
	}
};

/**
 * Inventory check save request DTO
 */
class InventoryCheckSaveDTO : public oatpp::DTO
{
	DTO_INIT(InventoryCheckSaveDTO, DTO);
	// Check document number (empty for new, required for edit)
	DTO_FIELD(String, checkNo);
	DTO_FIELD_INFO(checkNo) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.checkNo");
	}
	// Check type
	DTO_FIELD(String, checkType);
	DTO_FIELD_INFO(checkType) {
		info->required = true;
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.checkType");
	}
	// Remark
	DTO_FIELD(String, remark);
	DTO_FIELD_INFO(remark) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.remark");
	}
	// Drug check list
	DTO_FIELD(oatpp::List<CheckDrugItemDTO::Wrapper>, drugList);
	DTO_FIELD_INFO(drugList) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.drugList");
	}
};

/**
 * Inventory check approval request DTO
 */
class InventoryCheckApprovalDTO : public oatpp::DTO
{
	DTO_INIT(InventoryCheckApprovalDTO, DTO);
	// Check document number
	DTO_FIELD(String, checkNo);
	DTO_FIELD_INFO(checkNo) {
		info->required = true;
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.checkNo");
	}
	// Approval comment
	DTO_FIELD(String, approvalComment);
	DTO_FIELD_INFO(approvalComment) {
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.approvalComment");
	}
};

/**
 * Inventory check remove request DTO
 */
class InventoryCheckRemoveDTO : public oatpp::DTO
{
	DTO_INIT(InventoryCheckRemoveDTO, DTO);
	// Check document number
	DTO_FIELD(String, checkNo);
	DTO_FIELD_INFO(checkNo) {
		info->required = true;
		info->description = ZH_WORDS_GETTER("pharmacy.inventory-check.field.checkNo");
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_INVENTORY_CHECK_DTO_
