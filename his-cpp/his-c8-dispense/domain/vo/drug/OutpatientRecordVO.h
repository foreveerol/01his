#pragma once
#ifndef _OUTPATIENT_RECORD_VO_
#define _OUTPATIENT_RECORD_VO_

#include "../../GlobalInclude.h"
#include "../../dto/drug/OutpatientRecordDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// Outpatient record page response JsonVO
class OutpatientRecordPageJsonVO : public JsonVO<OutpatientRecordPageDTO::Wrapper> {
	DTO_INIT(OutpatientRecordPageJsonVO, JsonVO<OutpatientRecordPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_OUTPATIENT_RECORD_VO_