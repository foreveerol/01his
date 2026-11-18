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
#include "stdafx.h"
#include "OutpatientDispenseService.h"
#include "../../dao/drug/OutpatientDispenseDAO.h"

OutpatientQueuePageJsonVO::Wrapper OutpatientDispenseService::listQueue(const OutpatientDispenseQuery::Wrapper& query)
{
	auto jvo = OutpatientQueuePageJsonVO::createShared();

	OutpatientDispenseDAO dao;
	auto list = dao.selectQueue(query);

	if (!list.empty()) {
		auto& item = list.front();
		auto dto = OutpatientQueueItemDTO::createShared();
		dto->patient_name = item.getPatientName();
		dto->queue_no = item.getQueueNo();
		dto->visit_date = item.getVisitDate();
		jvo->success(dto);
	} else {
		jvo->success(OutpatientQueueItemDTO::createShared());
	}
	return jvo;
}

OutpatientDispenseJsonVO::Wrapper OutpatientDispenseService::getDrugDetail(const OutpatientDrugDetailQuery::Wrapper& query)
{
	auto jvo = OutpatientDispenseJsonVO::createShared();

	if (!query->prescription_no || query->prescription_no->empty()) {
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	OutpatientDispenseDAO dao;
	auto list = dao.selectDrugDetails(query->prescription_no.getValue(""));

	if (!list.empty()) {
		auto& item = list.front();
		auto dto = OutpatientDrugDetailInfDTO::createShared();
		dto->drug_id = item.getDrugId();
		dto->status = item.getStatus();
		dto->drug_name = item.getDrugName();
		dto->num = Int32(item.getNum());
		jvo->success(dto);
	} else {
		jvo->success(OutpatientDrugDetailInfDTO::createShared());
	}
	return jvo;
}

StringJsonVO::Wrapper OutpatientDispenseService::batchDispense(const OutpatientBatchDispenseDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	if (!dto->prescription_id_list || dto->prescription_id_list->empty()) {
		jvo->init("prescription_id_list is required.", RS_PARAMS_INVALID);
		return jvo;
	}

	std::vector<std::string> ids;
	for (auto& id : *dto->prescription_id_list) {
		if (id && !id->empty()) {
			ids.push_back(id.getValue(""));
		}
	}

	if (ids.empty()) {
		jvo->init("No valid prescription IDs provided.", RS_PARAMS_INVALID);
		return jvo;
	}

	OutpatientDispenseDAO dao;
	int updated = dao.batchUpdateStatus(ids, "COMPLETED",
		dto->pharmacist_id.getValue(""),
		dto->dispense_time.getValue(""));

	if (updated > 0) {
		jvo->success("Batch dispense completed: " + std::to_string(updated) + " records updated");
	} else {
		jvo->init("No records were updated.", RS_PARAMS_INVALID);
	}
	return jvo;
}
