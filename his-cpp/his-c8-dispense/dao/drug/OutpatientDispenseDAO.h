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
#ifndef _OUTPATIENT_DISPENSE_DAO_
#define _OUTPATIENT_DISPENSE_DAO_

#include "BaseDAO.h"
#include "OutpatientDispenseMapper.h"
#include "../../domain/query/drug/OutpatientDispenseQuery.h"
#include "../../domain/dto/drug/OutpatientDispenseDTO.h"

class OutpatientDispenseDAO : public BaseDAO
{
public:
	//查询门诊发药患者信息
	std::list<OutpatientDispenseDo> select_with_condition(const OutpatientDispenseQuery::Wrapper& query);
	//统计队列总条数
	int64_t count_with_condition(const OutpatientDispenseQuery::Wrapper& query);
	//根据处方号查询其药品明细
	std::list<OutpatientDispenseDo> select_drug_detail_with_condition(const OutpatientDrugDetailQuery::Wrapper& query);
};
#endif 
