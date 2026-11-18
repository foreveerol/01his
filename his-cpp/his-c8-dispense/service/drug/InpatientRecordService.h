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
#ifndef _INPATIENT_RECORD_SERVICE_
#define _INPATIENT_RECORD_SERVICE_

#include "../../domain/vo/drug/InpatientRecordVO.h"
#include "../../domain/query/drug/InpatientRecordQuery.h"
#include "../../domain/dto/drug/InpatientRecordDTO.h"
#include "domain/vo/BaseJsonVO.h"

class InpatientRecordService
{
public:
	InpatientRecordPageJsonVO::Wrapper listByCondition(const InpatientRecordQuery::Wrapper& query);
	StringJsonVO::Wrapper exportRecords(const InpatientRecordExportDTO::Wrapper& dto);
};

#endif // !_INPATIENT_RECORD_SERVICE_
