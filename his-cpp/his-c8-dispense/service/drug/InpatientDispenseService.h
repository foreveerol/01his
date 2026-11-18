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
#ifndef _INPATIENT_DISPENSE_SERVICE_
#define _INPATIENT_DISPENSE_SERVICE_

#include "../../domain/vo/drug/InpatientDispenseVO.h"
#include "../../domain/query/drug/InpatientDispenseQuery.h"
#include "../../domain/dto/drug/InpatientDispenseDTO.h"
#include "domain/vo/BaseJsonVO.h"

class InpatientDispenseService
{
public:
	InpatientDispenseSummaryPageJsonVO::Wrapper listSummaryQueue(const InpatientDispenseQuery::Wrapper& query);
	InpatientDrugDetailJsonVO::Wrapper getDrugDetail(const InpatientDrugDetailQuery::Wrapper& query);
	StringJsonVO::Wrapper verifyDispense(const InpatientDispenseVerifyDTO::Wrapper& dto);
	StringJsonVO::Wrapper rejectDispense(const InpatientDispenseRejectDTO::Wrapper& dto);
};

#endif // !_INPATIENT_DISPENSE_SERVICE_
