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
#ifndef _DRUG_RETURN_CONTROLLER_
#define _DRUG_RETURN_CONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/drug/InpatientReturnVO.h"
#include "domain/query/drug/InpatientReturnQuery.h"
#include "domain/dto/drug/InpatientReturnDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("dispense.return.tag")

/**
 * Inpatient drug return controller
 * Provides inpatient drug return queue query, return details query, and confirm return interfaces
 */
class DrugReturnController : public oatpp::web::server::api::ApiController
{
	// 2 Declare access macro
	API_ACCESS_DECLARE(DrugReturnController);
public:
	// 3.1 Fetch inpatient return queue - endpoint definition
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("dispense.return.queue.summary"),
		queryInpatientReturnQueue,
		InpatientReturnQuery,
		InpatientReturnQueueJsonVO::Wrapper,
		API_TAG
	);
	// 3.2 Fetch inpatient return queue - endpoint binding
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/dispense/inpatient-return-queue", queryInpatientReturnQueue,
		InpatientReturnQuery,
		execQueryInpatientReturnQueue(query));

	// 3.1 Fetch patient return details - endpoint definition
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("dispense.return.query.summary"),
		queryInpatientReturn,
		InpatientReturnJsonVO::Wrapper,
		API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "hospitalizationNo", ZH_WORDS_GETTER("dispense.return.field.hospitalizationNo"), "ZY2026-07-020001", true);
	);
	// 3.2 Fetch patient return details - endpoint binding
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/dispense/inpatient-return-query", queryInpatientReturn,
		QUERY(String, hospitalizationNo),
		execQueryInpatientReturn(hospitalizationNo));

	// 3.1 Confirm return - endpoint definition
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("dispense.return.confirm.summary"),
		confirmInpatientReturn,
		StringJsonVO::Wrapper,
		API_TAG
	);
	// 3.2 Confirm return - endpoint binding
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/dispense/inpatient-return-confirm", confirmInpatientReturn,
		BODY_DTO(InpatientReturnConfirmDTO::Wrapper, dto),
		execConfirmInpatientReturn(dto));

private:
	// 3.3 Execute query for inpatient return queue
	InpatientReturnQueueJsonVO::Wrapper execQueryInpatientReturnQueue(const InpatientReturnQuery::Wrapper& query);
	// 3.3 Execute query for patient return details
	InpatientReturnJsonVO::Wrapper execQueryInpatientReturn(const String& hospitalizationNo);
	// 3.3 Execute confirm return (perform return and replenish inventory)
	StringJsonVO::Wrapper execConfirmInpatientReturn(const InpatientReturnConfirmDTO::Wrapper& dto);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)

#endif // _DRUG_RETURN_CONTROLLER_
