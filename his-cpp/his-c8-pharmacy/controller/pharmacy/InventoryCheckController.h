#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: zjb517
 @Date: 2026/07/19 18:30:00

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
#ifndef _INVENTORY_CHECK_CONTROLLER_
#define _INVENTORY_CHECK_CONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/pharmacy/InventoryCheckVO.h"
#include "domain/query/pharmacy/InventoryCheckQuery.h"
#include "domain/dto/pharmacy/InventoryCheckDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("pharmacy.inventory-check.tag")

/**
 * Pharmacy inventory-check document controller.
 * Provides full lifecycle management: list, detail, create, draft, submit, withdraw, approve, reject, remove.
 */
class InventoryCheckController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(InventoryCheckController);
public:
	// ---- list ----
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("pharmacy.inventory-check.list.summary"),
		queryInventoryCheckList,
		InventoryCheckQuery,
		InventoryCheckPageJsonVO::Wrapper,
		API_TAG
	);
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/pharmacy/inventory-check/list", queryInventoryCheckList,
		InventoryCheckQuery,
		execQueryInventoryCheckList(query));

	// ---- query one ----
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.inventory-check.query-one.summary"),
		queryInventoryCheckOne,
		InventoryCheckJsonVO::Wrapper,
		API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "checkNo", ZH_WORDS_GETTER("pharmacy.inventory-check.field.checkNo"), "PD202607190001", true);
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/pharmacy/inventory-check/query-one", queryInventoryCheckOne,
		QUERY(String, checkNo),
		execQueryInventoryCheckOne(checkNo));

	// ---- create blank ----
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.inventory-check.create.summary"),
		createInventoryCheck,
		StringJsonVO::Wrapper,
		API_TAG
	);
	API_HANDLER_ENDPOINT_NOPARAM_AUTH(API_M_POST, "/pharmacy/inventory-check/create", createInventoryCheck,
		execCreateInventoryCheck());

	// ---- save draft ----
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.inventory-check.save-draft.summary"),
		saveInventoryCheckDraft,
		StringJsonVO::Wrapper,
		API_TAG
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/pharmacy/inventory-check/save-draft", saveInventoryCheckDraft,
		BODY_DTO(InventoryCheckSaveDTO::Wrapper, dto),
		execSaveInventoryCheckDraft(dto));

	// ---- save and submit ----
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.inventory-check.save-submit.summary"),
		saveAndSubmitInventoryCheck,
		StringJsonVO::Wrapper,
		API_TAG
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/pharmacy/inventory-check/save-submit", saveAndSubmitInventoryCheck,
		BODY_DTO(InventoryCheckSaveDTO::Wrapper, dto),
		execSaveAndSubmitInventoryCheck(dto));

	// ---- submit to approval ----
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.inventory-check.submit.summary"),
		submitInventoryCheck,
		StringJsonVO::Wrapper,
		API_TAG
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/pharmacy/inventory-check/submit", submitInventoryCheck,
		BODY_DTO(InventoryCheckRemoveDTO::Wrapper, dto),
		execSubmitInventoryCheck(dto));

	// ---- withdraw from approval ----
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.inventory-check.withdraw.summary"),
		withdrawInventoryCheck,
		StringJsonVO::Wrapper,
		API_TAG
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/pharmacy/inventory-check/withdraw", withdrawInventoryCheck,
		BODY_DTO(InventoryCheckRemoveDTO::Wrapper, dto),
		execWithdrawInventoryCheck(dto));

	// ---- approve ----
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.inventory-check.approve.summary"),
		approveInventoryCheck,
		StringJsonVO::Wrapper,
		API_TAG
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/pharmacy/inventory-check/approve", approveInventoryCheck,
		BODY_DTO(InventoryCheckApprovalDTO::Wrapper, dto),
		execApproveInventoryCheck(dto));

	// ---- reject ----
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.inventory-check.reject.summary"),
		rejectInventoryCheck,
		StringJsonVO::Wrapper,
		API_TAG
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/pharmacy/inventory-check/reject", rejectInventoryCheck,
		BODY_DTO(InventoryCheckApprovalDTO::Wrapper, dto),
		execRejectInventoryCheck(dto));

	// ---- remove ----
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.inventory-check.remove.summary"),
		removeInventoryCheck,
		StringJsonVO::Wrapper,
		API_TAG
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/pharmacy/inventory-check/remove", removeInventoryCheck,
		BODY_DTO(InventoryCheckRemoveDTO::Wrapper, dto),
		execRemoveInventoryCheck(dto));

private:
	InventoryCheckPageJsonVO::Wrapper execQueryInventoryCheckList(const InventoryCheckQuery::Wrapper& query);
	InventoryCheckJsonVO::Wrapper execQueryInventoryCheckOne(const String& checkNo);
	StringJsonVO::Wrapper execCreateInventoryCheck();
	StringJsonVO::Wrapper execSaveInventoryCheckDraft(const InventoryCheckSaveDTO::Wrapper& dto);
	StringJsonVO::Wrapper execSaveAndSubmitInventoryCheck(const InventoryCheckSaveDTO::Wrapper& dto);
	StringJsonVO::Wrapper execSubmitInventoryCheck(const InventoryCheckRemoveDTO::Wrapper& dto);
	StringJsonVO::Wrapper execWithdrawInventoryCheck(const InventoryCheckRemoveDTO::Wrapper& dto);
	StringJsonVO::Wrapper execApproveInventoryCheck(const InventoryCheckApprovalDTO::Wrapper& dto);
	StringJsonVO::Wrapper execRejectInventoryCheck(const InventoryCheckApprovalDTO::Wrapper& dto);
	StringJsonVO::Wrapper execRemoveInventoryCheck(const InventoryCheckRemoveDTO::Wrapper& dto);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)
#endif // !_INVENTORY_CHECK_CONTROLLER_
