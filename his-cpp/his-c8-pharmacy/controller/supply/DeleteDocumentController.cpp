/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 10:58:42

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
#include "stdafx.h"
#include "DeleteDocumentController.h"
#include "../../service/supply/SupplyDeleteService.h"

DeleteDocumentResultVO::Wrapper DeleteDocumentController::execDeleteDocument(
	const DeleteDocumentDTO::Wrapper& dto, const PayloadDTO& payload)
{
	// Define return data object
	auto jvo = DeleteDocumentResultVO::createShared();

	// Parameter validation
	if (!dto->requestId || dto->requestId->empty())
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// Set payload
	dto->setPayload(&payload);

	// Execute delete document business logic
	std::string errmsg = SupplyDeleteService().deleteDocument(dto);
	if (errmsg.empty())
	{
		// Success: return document ID
		jvo->success(dto->requestId);
	}
	else
	{
		// Failure: return error message
		jvo->fail(errmsg);
	}

	// Response result
	return jvo;
}
