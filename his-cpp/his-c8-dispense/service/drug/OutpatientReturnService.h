#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: zjb517
 @Date: 2026/07/26 10:00:00

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
#ifndef _OUTPATIENT_RETURN_SERVICE_
#define _OUTPATIENT_RETURN_SERVICE_

#include "../../domain/vo/drug/OutpatientReturnVO.h"
#include "../../domain/query/drug/OutpatientReturnQuery.h"
#include "../../domain/dto/drug/OutpatientReturnDTO.h"
#include "domain/vo/BaseJsonVO.h"

class OutpatientReturnService
{
public:
	OutpatientReturnQueuePageJsonVO::Wrapper listReturnQueue(const OutpatientReturnQuery::Wrapper& query);
	OutpatientReturnJsonVO::Wrapper getReturnDetail(const OutpatientReturnDrugDTO::Wrapper& dto);
	StringJsonVO::Wrapper confirmReturn(const OutpatientReturnConfirmDTO::Wrapper& dto);
	StringJsonVO::Wrapper rejectReturn(const OutpatientReturnRejectDTO::Wrapper& dto);
};

#endif // !_OUTPATIENT_RETURN_SERVICE_
