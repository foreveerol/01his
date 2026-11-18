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
#ifndef _DRUG_RETURN_DAO_
#define _DRUG_RETURN_DAO_

#include "BaseDAO.h"
#include "DrugReturnMapper.h"
#include "../../domain/query/drug/InpatientReturnQuery.h"
#include "../../domain/dto/drug/InpatientReturnDTO.h"

class DrugReturnDAO : public BaseDAO
{
public:
	std::list<InpatientReturnQueueDO> selectReturnQueue(const InpatientReturnQuery::Wrapper& query);
	uint64_t countReturnQueue(const InpatientReturnQuery::Wrapper& query);
	std::list<InpatientReturnDrugDO> selectReturnDrugs(const std::string& hospitalizationNo);
	std::list<InpatientReturnPatientDO> selectReturnPatient(const std::string& hospitalizationNo);
	int confirmReturn(const std::string& hospitalizationNo, const std::vector<std::string>& detailIds);
};

#endif // !_DRUG_RETURN_DAO_
