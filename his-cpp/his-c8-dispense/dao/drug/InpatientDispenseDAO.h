/*
 Copyright Zero One Star. All rights reserved.

 @Author: juhao
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
#ifndef _INPATIENT_DISPENSE_DAO_
#define _INPATIENT_DISPENSE_DAO_

#include "BaseDAO.h"
#include "InpatientDispenseMapper.h"
#include "../../domain/query/drug/InpatientDispenseQuery.h"
#include "../../domain/dto/drug/InpatientDispenseDTO.h"

/**
 * 住院发药数据访问层
 * 处理住院发药业务的数据操作
 */
class InpatientDispenseDAO : public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const InpatientDispenseQuery::Wrapper& query, SqlParams& params);

public:
	std::list<InpatientSummaryDO> selectSummaryQueue(const InpatientDispenseQuery::Wrapper& query);
	uint64_t countSummaryQueue(const InpatientDispenseQuery::Wrapper& query);
	std::list<InpatientDrugItemDO> selectDrugDetail(const std::string& summaryNo);
	int verifyDispense(const std::string& summaryNo, const std::string& practitionerId);
	int rejectDispense(const std::string& summaryNo, const std::string& auditor, const std::string& reason);
};

#endif // !_INPATIENT_DISPENSE_DAO_