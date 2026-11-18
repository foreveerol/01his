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
#ifndef _DELETE_DOCUMENT_CONTROLLER_
#define _DELETE_DOCUMENT_CONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/dto/supply/DeleteDocumentDTO.h"
#include "domain/vo/supply/DeleteDocumentVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("supply.tags.main")

/**
 * Pharmacy stocktake document delete controller
 */
class DeleteDocumentController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(DeleteDocumentController);
public:
	// Delete document endpoint description
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("supply.delete-document.summary"), deleteDocument, DeleteDocumentResultVO::Wrapper, API_TAG);
	// Delete document endpoint implementation
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/supply-request/delete-document", deleteDocument,
		BODY_DTO(DeleteDocumentDTO::Wrapper, dto),
		execDeleteDocument(dto, authObject->getPayload()));

private:
	// Delete document execution function
	DeleteDocumentResultVO::Wrapper execDeleteDocument(const DeleteDocumentDTO::Wrapper& dto, const PayloadDTO& payload);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)
#endif // _DELETE_DOCUMENT_CONTROLLER_
