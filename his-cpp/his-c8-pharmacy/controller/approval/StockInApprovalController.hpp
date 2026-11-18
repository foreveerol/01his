/**
 * @file StockInApprovalController.hpp
 * @brief 药房入库审批接口控制器声明。
 * @Author: stellablack528
 */

#pragma once

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"

#include "domain/vo/approval/StockInOperationResultVO.hpp"
#include "domain/dto/approval/StockInWithdrawDTO.hpp"
#include "domain/dto/approval/StockInApprovalDTO.hpp"
#include "domain/dto/approval/StockInRejectDTO.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define APPROVAL_API_TAG ZH_WORDS_GETTER("pharmacy.stockin.tag")

/**
 * @brief 药房入库审批控制器。
 *
 * 提供撤回审批、审批通过、驳回审批接口。
 * 归属于「药房入库单」分组，与 list / save-draft 等接口共用同一个 API_TAG。
 */
class StockInApprovalController : public oatpp::web::server::api::ApiController {
	API_ACCESS_DECLARE(StockInApprovalController);

public:

	// ---- 撤回 ----
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.stockin.withdraw.summary"),
		withdrawStockIn,
		vo::StockInOperationResultVO::Wrapper,
		APPROVAL_API_TAG
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/pharmacy/stockin/withdraw", withdrawStockIn,
		BODY_DTO(Object<dto::StockInWithdrawDTO>, body),
		execWithdrawStockIn(body));

	// ---- 审批通过 ----
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.stockin.approve.summary"),
		approveStockIn,
		vo::StockInOperationResultVO::Wrapper,
		APPROVAL_API_TAG
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/pharmacy/stockin/approve", approveStockIn,
		BODY_DTO(Object<dto::StockInApprovalDTO>, body),
		execApproveStockIn(body));

	// ---- 驳回 ----
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.stockin.reject.summary"),
		rejectStockIn,
		vo::StockInOperationResultVO::Wrapper,
		APPROVAL_API_TAG
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/pharmacy/stockin/reject", rejectStockIn,
		BODY_DTO(Object<dto::StockInRejectDTO>, body),
		execRejectStockIn(body));

private:
	vo::StockInOperationResultVO::Wrapper execWithdrawStockIn(const oatpp::Object<dto::StockInWithdrawDTO>& body);
	vo::StockInOperationResultVO::Wrapper execApproveStockIn(const oatpp::Object<dto::StockInApprovalDTO>& body);
	vo::StockInOperationResultVO::Wrapper execRejectStockIn(const oatpp::Object<dto::StockInRejectDTO>& body);
};

#undef APPROVAL_API_TAG

#include OATPP_CODEGEN_END(ApiController)