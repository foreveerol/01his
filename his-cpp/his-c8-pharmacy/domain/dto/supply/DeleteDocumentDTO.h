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
#ifndef _DELETE_DOCUMENT_DTO_
#define _DELETE_DOCUMENT_DTO_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Delete document request DTO
 */
class DeleteDocumentDTO : public oatpp::DTO
{
	DTO_INIT(DeleteDocumentDTO, DTO);
	// Document ID
	DTO_FIELD(String, requestId);
	DTO_FIELD_INFO(requestId) {
		info->description = ZH_WORDS_GETTER("supply.field.requestId");
	}

	// Payload data object
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_DELETE_DOCUMENT_DTO_
