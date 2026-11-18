#pragma once
#ifndef _OUTPATIENT_RETURN_VO_
#define _OUTPATIENT_RETURN_VO_

#include "../../GlobalInclude.h"
#include "../../dto/drug/OutpatientReturnDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

// 1. 获取患者队列的分页响应 VO
class OutpatientReturnQueuePageJsonVO : public JsonVO<PageDTO<OutpatientReturnQueueItemDTO::Wrapper>::Wrapper> {
    DTO_INIT(OutpatientReturnQueuePageJsonVO, JsonVO<PageDTO<OutpatientReturnQueueItemDTO::Wrapper>::Wrapper>);
};

// 2. 获取患者退药明细的响应 VO
class OutpatientReturnJsonVO : public JsonVO<OutpatientReturnDTO::Wrapper> {
    DTO_INIT(OutpatientReturnJsonVO, JsonVO<OutpatientReturnDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif