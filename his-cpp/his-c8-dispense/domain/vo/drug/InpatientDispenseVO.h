#pragma once
#ifndef _INPATIENT_DISPENSE_VO_
#define _INPATIENT_DISPENSE_VO_

#include "../../GlobalInclude.h"
#include "../../dto/drug/InpatientDispenseDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 住院发药汇总队列响应JsonVO
class InpatientDispenseSummaryPageJsonVO : public JsonVO<InpatientDispenseSummaryPageDTO::Wrapper> {
	DTO_INIT(InpatientDispenseSummaryPageJsonVO, JsonVO<InpatientDispenseSummaryPageDTO::Wrapper>);
};

// 住院患者药品明细响应JsonVO
class InpatientDrugDetailJsonVO : public JsonVO<InpatientDrugDetailDTO::Wrapper> {
	DTO_INIT(InpatientDrugDetailJsonVO, JsonVO<InpatientDrugDetailDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_INPATIENT_DISPENSE_VO_