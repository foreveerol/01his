#pragma once
#ifndef _OUTPATIENT_DISPENSE_CONTROLLER_
#define _OUTPATIENT_DISPENSE_CONTROLLER_

#include "ApiHelper.h"
#include "../../domain/query/drug/OutpatientDispenseQuery.h"
#include "../../domain/vo/drug/OutpatientDispenseVO.h"
#include "domain/vo/BaseJsonVO.h"
#include OATPP_CODEGEN_BEGIN(ApiController)


#define API_TAG ZH_WORDS_GETTER("dispense.outpatient-dispense.tag")

using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(ApiController)

class OutpatientDispenseController : public oatpp::web::server::api::ApiController {
	    API_ACCESS_DECLARE(OutpatientDispenseController);
	public:
	    // Outpatient dispense queue endpoint
	    API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("dispense.outpatient-dispense.queue.summary"),
	        patientQueue, OutpatientDispenseQuery, OutpatientQueuePageJsonVO::Wrapper, API_TAG);
	    API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/dispense/outpatient-queue", patientQueue,
	        OutpatientDispenseQuery, executeQuerySummaryQueue(query));
	    // Outpatient drug detail endpoint
	    API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("dispense.outpatient-dispense.detail.summary"),
	        patientdrugQueue, OutpatientDrugDetailQuery, OutpatientDispenseJsonVO::Wrapper, API_TAG);
	    API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/dispense/outpatient-drug-detail", patientdrugQueue,
	        OutpatientDrugDetailQuery, executeDrugSummaryQueue(query));
	    // Outpatient batch dispense endpoint
	    API_DEF_ENDPOINT_INFO_FILE_AUTH(ZH_WORDS_GETTER("dispense.outpatient-dispense.batch.summary"),
	        drugdispenseDto, OutpatientBatchDispenseDTO::Wrapper, StringJsonVO::Wrapper, API_TAG);
	    API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/dispense/outpatient-batch-dispense", drugdispenseDto,
	        BODY_DTO(OutpatientBatchDispenseDTO::Wrapper, dto), execbatchDispense(dto, authObject->getPayload()));

	private:
	    OutpatientQueuePageJsonVO::Wrapper executeQuerySummaryQueue(const OutpatientDispenseQuery::Wrapper& query);
	    OutpatientDispenseJsonVO::Wrapper executeDrugSummaryQueue(const OutpatientDrugDetailQuery::Wrapper& query);
	    OutpatientBatchDispenseDTO::Wrapper execbatchDispense(const OutpatientBatchDispenseDTO::Wrapper& dto, const PayloadDTO& payload);
	};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)
#endif
