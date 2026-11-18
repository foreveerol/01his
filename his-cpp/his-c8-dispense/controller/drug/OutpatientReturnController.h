#pragma once
#ifndef _OUTPATIENT_RETURN_CONTROLLER_
#define _OUTPATIENT_RETURN_CONTROLLER_

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/drug/OutpatientReturnQuery.h"
#include "domain/dto/drug/OutpatientReturnDTO.h"
#include "domain/vo/drug/OutpatientReturnVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("dispense.outpatient-return.tag")

class OutpatientReturnController : public oatpp::web::server::api::ApiController {
    API_ACCESS_DECLARE(OutpatientReturnController);

public:
    // Outpatient return queue - endpoint definition
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        ZH_WORDS_GETTER("dispense.outpatient-return.queue.summary"),
        getQueue,
        OutpatientReturnQuery,
        OutpatientReturnQueuePageJsonVO::Wrapper,
        API_TAG
    );
    // Outpatient return queue - endpoint binding
    API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/dispense/outpatient-return-queue", getQueue,
        OutpatientReturnQuery,
        execGetQueue(query));

    // Outpatient return detail - endpoint definition
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        ZH_WORDS_GETTER("dispense.outpatient-return.detail.summary"),
        getDetail,
        OutpatientReturnQuery,
        OutpatientReturnJsonVO::Wrapper,
        API_TAG
    );
    // Outpatient return detail - endpoint binding
    API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/dispense/outpatient-return-detail", getDetail,
        OutpatientReturnQuery,
        execGetDetail(query));

    // Confirm outpatient return - endpoint definition
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("dispense.outpatient-return.confirm.summary"),
        confirmReturn,
        StringJsonVO::Wrapper,
        API_TAG
    );
    // Confirm outpatient return - endpoint binding
    API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/dispense/outpatient-return-confirm", confirmReturn,
        BODY_DTO(Object<OutpatientReturnConfirmDTO>, dto),
        execConfirmReturn(dto));

    // Reject outpatient return - endpoint definition
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("dispense.outpatient-return.reject.summary"),
        rejectReturn,
        StringJsonVO::Wrapper,
        API_TAG
    );
    // Reject outpatient return - endpoint binding
    API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/dispense/outpatient-return-reject", rejectReturn,
        BODY_DTO(Object<OutpatientReturnRejectDTO>, dto),
        execRejectReturn(dto));

private:
    OutpatientReturnQueuePageJsonVO::Wrapper execGetQueue(const OutpatientReturnQuery::Wrapper& query);
    OutpatientReturnJsonVO::Wrapper execGetDetail(const OutpatientReturnQuery::Wrapper& query);
    StringJsonVO::Wrapper execConfirmReturn(const OutpatientReturnConfirmDTO::Wrapper& dto);
    StringJsonVO::Wrapper execRejectReturn(const OutpatientReturnRejectDTO::Wrapper& dto);
};
#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)
#endif
