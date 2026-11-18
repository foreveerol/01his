#pragma once
#ifndef _OUTPATIENT_RETURN_DTO_
#define _OUTPATIENT_RETURN_DTO_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 1. 门诊退药队列列表项 DTO 
class OutpatientReturnQueueItemDTO : public oatpp::DTO {
    DTO_INIT(OutpatientReturnQueueItemDTO, DTO);

    DTO_FIELD(String, id);
    DTO_FIELD_INFO(id) { info->description = ZH_WORDS_GETTER("dispense.outpatient.return.id"); }

    // awei 补充：响应前端实际需求增加的业务字段
    DTO_FIELD(String, patientName, "patient_name");
    DTO_FIELD(String, returnDate, "return_date");
    DTO_FIELD(Int32, drugCount, "drug_count");
    DTO_FIELD(String, returnStatus, "return_status");
};

// 2. 门诊退药主表信息 DTO 
class OutpatientReturnDTO : public oatpp::DTO {
    DTO_INIT(OutpatientReturnDTO, DTO);
    DTO_FIELD(String, returnId);
    DTO_FIELD_INFO(returnId) { info->description = ZH_WORDS_GETTER("dispense.outpatient.return.returnId"); }
};

// 3. 门诊退药药品明细 DTO 
class OutpatientReturnDrugDTO : public oatpp::DTO {
    DTO_INIT(OutpatientReturnDrugDTO, DTO);

    DTO_FIELD(String, drugId);
    DTO_FIELD_INFO(drugId) { info->description = ZH_WORDS_GETTER("dispense.outpatient.return.drugId"); }

    // awei 补充：药品明细详情字段
    DTO_FIELD(String, drugName, "drug_name");
    DTO_FIELD(Int32, quantity);
    DTO_FIELD(String, dispenseDate, "dispense_date");
};

// 4. 确认退药请求参数 DTO
class OutpatientReturnConfirmDTO : public oatpp::DTO {
    DTO_INIT(OutpatientReturnConfirmDTO, DTO);
    DTO_FIELD(String, returnId);
    DTO_FIELD_INFO(returnId) {
        info->required = true;
        info->description = ZH_WORDS_GETTER("dispense.outpatient.return.returnId");
    }
};

// 5. 拒绝退药请求参数 DTO 
class OutpatientReturnRejectDTO : public oatpp::DTO {
    DTO_INIT(OutpatientReturnRejectDTO, DTO);
    DTO_FIELD(String, returnId);
    DTO_FIELD_INFO(returnId) {
        info->required = true;
        info->description = ZH_WORDS_GETTER("dispense.outpatient-return.returnId");
    }

    // awei 补充：必须传入拒绝原因
    DTO_FIELD(String, reason);
    DTO_FIELD_INFO(reason) {
        info->required = true;
        info->description = "拒绝退药原因";
    }
};

#include OATPP_CODEGEN_END(DTO)

#endif // _OUTPATIENT_RETURN_DTO_