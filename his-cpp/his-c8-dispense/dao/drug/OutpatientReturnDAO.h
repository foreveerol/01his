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


#pragma once
#ifndef _OUTPATIENT_RETURN_DAO_
#define _OUTPATIENT_RETURN_DAO_

#include "BaseDAO.h"
#include "OutpatientReturnMapper.h"
#include "../../domain/query/drug/OutpatientReturnQuery.h"
#include "../../domain/dto/drug/OutpatientReturnDTO.h"


class OutpatientReturnDAO : public BaseDAO
{
public:
	std::list<OutpatientReturnQueueDO> selectReturnQueue(const OutpatientReturnQuery::Wrapper& query);
	uint64_t countReturnQueue(const OutpatientReturnQuery::Wrapper& query);
	std::list<OutpatientReturnDetailDO> selectReturnDetail(const std::string& returnId);
	int confirmReturn(const std::string& returnId);
	int rejectReturn(const std::string& returnId, const std::string& reason);
};

#endif // !_OUTPATIENT_RETURN_DAO_