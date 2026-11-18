#pragma once
#ifndef _INPATIENT_DISPENSE_CONTROLLER_H_
#define _INPATIENT_DISPENSE_CONTROLLER_H_

#include "../../domain/query/drug/InpatientDispenseQuery.h"
#include "../../domain/vo/drug/InpatientDispenseVO.h"
#include "domain/vo/BaseJsonVO.h"

using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG_INPATIENT_DISPENSE ZH_WORDS_GETTER("dispense.inpatient-dispense.tag")

// Inpatient drug dispensing controller
// Responsible for fetching summary queue and drug details (steps 1 & 2)
class InpatientDispenseController : public oatpp::web::server::api::ApiController {
    API_ACCESS_DECLARE(InpatientDispenseController);
public:
    // Fetch inpatient dispensing summary queue - endpoint definition
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("dispense.inpatient-dispense.queue.summary"),
                                      querySummaryQueue, InpatientDispenseQuery,
                                      InpatientDispenseSummaryPageJsonVO::Wrapper, API_TAG_INPATIENT_DISPENSE);
    // Fetch inpatient dispensing summary queue - endpoint binding
    API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/dispense/inpatient-summary-queue", querySummaryQueue,
                                    InpatientDispenseQuery, executeQuerySummaryQueue(query));

    // Fetch inpatient drug details - endpoint definition
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("dispense.inpatient-dispense.detail.summary"),
                                      queryDrugDetail, InpatientDrugDetailQuery,
                                      InpatientDrugDetailJsonVO::Wrapper, API_TAG_INPATIENT_DISPENSE);
    // Fetch inpatient drug details - endpoint binding
    API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/dispense/inpatient-drug-detail", queryDrugDetail,
                                    InpatientDrugDetailQuery, executeQueryDrugDetail(query));

    // Verify/approve dispensing - endpoint definition
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("dispense.inpatient-dispense.verify.summary"),
        verifyDispense, StringJsonVO::Wrapper, API_TAG_INPATIENT_DISPENSE);
    // Verify/approve dispensing - endpoint binding
    API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/dispense/inpatient-dispense-verify", verifyDispense,
        BODY_DTO(InpatientDispenseVerifyDTO::Wrapper, dto),
        executeVerifyDispense(dto));

    // Reject dispensing - endpoint definition
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("dispense.inpatient-dispense.reject.summary"),
        rejectDispense, StringJsonVO::Wrapper, API_TAG_INPATIENT_DISPENSE);
    // Reject dispensing - endpoint binding
    API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/dispense/inpatient-dispense-reject", rejectDispense,
        BODY_DTO(InpatientDispenseRejectDTO::Wrapper, dto),
        executeRejectDispense(dto));
private:
    // Validate query parameters for summary queue
    bool validateSummaryQueueQuery(const InpatientDispenseQuery::Wrapper& query, std::string& errMsg);
    // Validate query parameters for drug detail
    bool validateDrugDetailQuery(const InpatientDrugDetailQuery::Wrapper& query, std::string& errMsg);
    // Check if date string matches YYYY-MM-DD format
    bool isValidDateFormat(const std::string& dateStr);
    
    // Execute query for summary queue
    InpatientDispenseSummaryPageJsonVO::Wrapper executeQuerySummaryQueue(const InpatientDispenseQuery::Wrapper& query);
    // Execute query for drug details
    InpatientDrugDetailJsonVO::Wrapper executeQueryDrugDetail(const InpatientDrugDetailQuery::Wrapper& query);
    // Execute verify/approve dispensing
    StringJsonVO::Wrapper executeVerifyDispense(const InpatientDispenseVerifyDTO::Wrapper& dto);
    // Execute reject dispensing
    StringJsonVO::Wrapper executeRejectDispense(const InpatientDispenseRejectDTO::Wrapper& dto);
};

#undef API_TAG_INPATIENT_DISPENSE

#include OATPP_CODEGEN_END(ApiController)

#endif // !_INPATIENT_DISPENSE_CONTROLLER_H_
