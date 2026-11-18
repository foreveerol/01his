#include "stdafx.h"
#include "OutpatientDispenseController.h"
#include "../../service/drug/OutpatientDispenseService.h"

OutpatientQueuePageJsonVO::Wrapper OutpatientDispenseController::executeQuerySummaryQueue(const OutpatientDispenseQuery::Wrapper& query)
{
	if (!query) {
		auto jvo = OutpatientQueuePageJsonVO::createShared();
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	try {
		return OutpatientDispenseService().listQueue(query);
	} catch (const std::exception&) {
		auto jvo = OutpatientQueuePageJsonVO::createShared();
		jvo->init(nullptr, RS_FAIL);
		return jvo;
	}
}

OutpatientDispenseJsonVO::Wrapper OutpatientDispenseController::executeDrugSummaryQueue(const OutpatientDrugDetailQuery::Wrapper& query)
{
	if (!query) {
		auto jvo = OutpatientDispenseJsonVO::createShared();
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	if (!query->prescription_no || query->prescription_no->empty()) {
		auto jvo = OutpatientDispenseJsonVO::createShared();
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	try {
		return OutpatientDispenseService().getDrugDetail(query);
	} catch (const std::exception&) {
		auto jvo = OutpatientDispenseJsonVO::createShared();
		jvo->init(nullptr, RS_FAIL);
		return jvo;
	}
}

OutpatientBatchDispenseDTO::Wrapper OutpatientDispenseController::execbatchDispense(const OutpatientBatchDispenseDTO::Wrapper& dto, const PayloadDTO& payload)
{
	if (!dto) {
		auto jvo = OutpatientBatchDispenseDTO::createShared();
		return jvo;
	}
	if (!dto->prescription_id_list || dto->prescription_id_list->empty()) {
		auto jvo = OutpatientBatchDispenseDTO::createShared();
		return jvo;
	}
	try {
		OutpatientDispenseService().batchDispense(dto);
	} catch (const std::exception&) {}
	auto jvo = OutpatientBatchDispenseDTO::createShared();
	return jvo;
}
