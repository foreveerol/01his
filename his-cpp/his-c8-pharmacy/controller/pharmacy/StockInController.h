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
#ifndef _STOCKIN_CONTROLLER_
#define _STOCKIN_CONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/pharmacy/StockInVO.h"
#include "domain/query/pharmacy/StockInQuery.h"
#include "domain/dto/pharmacy/StockInDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("pharmacy.stockin.tag")

/**
 * Pharmacy stock-in document controller.
 * Provides full lifecycle management: list, detail, create, draft, submit, withdraw, approve, reject, remove.
 */
class StockInController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(StockInController);
public:
	// ---- list ----
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("pharmacy.stockin.list.summary"),
		queryStockInList,
		StockInQuery,
		StockInPageJsonVO::Wrapper,
		API_TAG
	);
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/pharmacy/stockin/list", queryStockInList,
		StockInQuery,
		execQueryStockInList(query));

	// ---- query one ----
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.stockin.query-one.summary"),
		queryStockInOne,
		StockInJsonVO::Wrapper,
		API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "orderNo", ZH_WORDS_GETTER("pharmacy.stockin.field.orderNo"), "RK202607190001", true);
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/pharmacy/stockin/query-one", queryStockInOne,
		QUERY(String, orderNo),
		execQueryStockInOne(orderNo));

	// ---- create blank ----
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.stockin.create.summary"),
		createStockIn,
		StringJsonVO::Wrapper,
		API_TAG
	);
	API_HANDLER_ENDPOINT_NOPARAM_AUTH(API_M_POST, "/pharmacy/stockin/create", createStockIn,
		execCreateStockIn());

	// ---- save draft ----
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.stockin.save-draft.summary"),
		saveStockInDraft,
		StringJsonVO::Wrapper,
		API_TAG
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/pharmacy/stockin/save-draft", saveStockInDraft,
		BODY_DTO(StockInSaveDTO::Wrapper, dto),
		execSaveStockInDraft(dto));

	// ---- save and submit ----
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.stockin.save-submit.summary"),
		saveAndSubmitStockIn,
		StringJsonVO::Wrapper,
		API_TAG
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/pharmacy/stockin/save-submit", saveAndSubmitStockIn,
		BODY_DTO(StockInSaveDTO::Wrapper, dto),
		execSaveAndSubmitStockIn(dto));

	// ---- submit to approval ----
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.stockin.submit.summary"),
		submitStockIn,
		StringJsonVO::Wrapper,
		API_TAG
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/pharmacy/stockin/submit", submitStockIn,
		BODY_DTO(StockInRemoveDTO::Wrapper, dto),
		execSubmitStockIn(dto));

	// ---- withdraw from approval ----
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.stockin.withdraw.summary"),
		withdrawStockIn,
		StringJsonVO::Wrapper,
		API_TAG
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/pharmacy/stockin/withdraw", withdrawStockIn,
		BODY_DTO(StockInRemoveDTO::Wrapper, dto),
		execWithdrawStockIn(dto));

	// ---- approve ----
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.stockin.approve.summary"),
		approveStockIn,
		StringJsonVO::Wrapper,
		API_TAG
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/pharmacy/stockin/approve", approveStockIn,
		BODY_DTO(StockInApprovalDTO::Wrapper, dto),
		execApproveStockIn(dto));

	// ---- reject ----
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.stockin.reject.summary"),
		rejectStockIn,
		StringJsonVO::Wrapper,
		API_TAG
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/pharmacy/stockin/reject", rejectStockIn,
		BODY_DTO(StockInApprovalDTO::Wrapper, dto),
		execRejectStockIn(dto));

	// ---- remove ----
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.stockin.remove.summary"),
		removeStockIn,
		StringJsonVO::Wrapper,
		API_TAG
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/pharmacy/stockin/remove", removeStockIn,
		BODY_DTO(StockInRemoveDTO::Wrapper, dto),
		execRemoveStockIn(dto));

private:
	StockInPageJsonVO::Wrapper execQueryStockInList(const StockInQuery::Wrapper& query);
	StockInJsonVO::Wrapper execQueryStockInOne(const String& orderNo);
	StringJsonVO::Wrapper execCreateStockIn();
	StringJsonVO::Wrapper execSaveStockInDraft(const StockInSaveDTO::Wrapper& dto);
	StringJsonVO::Wrapper execSaveAndSubmitStockIn(const StockInSaveDTO::Wrapper& dto);
	StringJsonVO::Wrapper execSubmitStockIn(const StockInRemoveDTO::Wrapper& dto);
	StringJsonVO::Wrapper execWithdrawStockIn(const StockInRemoveDTO::Wrapper& dto);
	StringJsonVO::Wrapper execApproveStockIn(const StockInApprovalDTO::Wrapper& dto);
	StringJsonVO::Wrapper execRejectStockIn(const StockInApprovalDTO::Wrapper& dto);
	StringJsonVO::Wrapper execRemoveStockIn(const StockInRemoveDTO::Wrapper& dto);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)
#endif // !_STOCKIN_CONTROLLER_
