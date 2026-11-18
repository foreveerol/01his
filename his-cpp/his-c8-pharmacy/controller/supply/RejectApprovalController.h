#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 0:27:04

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
#ifndef _REJECT_APPROVAL_CONTROLLER_
#define _REJECT_APPROVAL_CONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/dto/supply/RejectApprovalDTO.h"
#include "domain/vo/supply/RejectApprovalVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("supply.tags.main")

/**
 * Pharmacy stocktake document reject approval controller
 */
class RejectApprovalController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(RejectApprovalController);
public:
	// Reject approval endpoint description
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("supply.reject-approval.summary"), rejectApproval, RejectApprovalResultVO::Wrapper, API_TAG);
	// Reject approval endpoint implementation
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/supply-request/reject-approval", rejectApproval,
		BODY_DTO(RejectApprovalDTO::Wrapper, dto),
		execRejectApproval(dto, authObject->getPayload()));

private:
	// Reject approval execution function
	RejectApprovalResultVO::Wrapper execRejectApproval(const RejectApprovalDTO::Wrapper& dto, const PayloadDTO& payload);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)
#endif // _REJECT_APPROVAL_CONTROLLER_
