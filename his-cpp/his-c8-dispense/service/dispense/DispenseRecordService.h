#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:08:56

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
#ifndef _DISPENSE_RECORD_SERVICE_
#define _DISPENSE_RECORD_SERVICE_
#include "domain/do/dispense/DispenseRecordDO.h"
#include "domain/query/dispense/DispenseRecordQuery.h"
#include <list>

/**
 * 门诊发退药服务层
 */
class DispenseRecordService
{
public:
	// 按条件查询发退药记录
	std::list<DispenseRecordDO> listByCondition(const DispenseRecordQuery::Wrapper& query);
};

#endif // !_DISPENSE_RECORD_SERVICE_
