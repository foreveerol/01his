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
#ifndef _DRUG_RETURN_SERVICE_
#define _DRUG_RETURN_SERVICE_

#include "../../domain/vo/drug/InpatientReturnVO.h"
#include "../../domain/query/drug/InpatientReturnQuery.h"
#include "../../domain/dto/drug/InpatientReturnDTO.h"
#include "domain/vo/BaseJsonVO.h"

class DrugReturnService
{
public:
	InpatientReturnQueueJsonVO::Wrapper listReturnQueue(const InpatientReturnQuery::Wrapper& query);
	InpatientReturnJsonVO::Wrapper getReturnDetail(const std::string& hospitalizationNo);
	StringJsonVO::Wrapper confirmReturn(const InpatientReturnConfirmDTO::Wrapper& dto);
};

#endif // !_DRUG_RETURN_SERVICE_
