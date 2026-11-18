#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/07/20 19:12:00

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
#ifndef _INPATIENT_DISPENSE_DTO_
#define _INPATIENT_DISPENSE_DTO_
#include "../../GlobalInclude.h"
#include "InpatientReturnDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 住院发药汇总单列表项DTO
class InpatientDispenseSummaryItemDTO : public oatpp::DTO
{
	DTO_INIT(InpatientDispenseSummaryItemDTO, DTO);
	// 汇总单ID
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.id");
	}
	// 汇总单号
	DTO_FIELD(String, summaryNo);
	DTO_FIELD_INFO(summaryNo) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.summaryNo");
	}
	// 汇总状态
    //状态示例为审核中
	DTO_FIELD(String, summaryStatus);
	DTO_FIELD_INFO(summaryStatus) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.summaryStatus");
	}
	// 创建时间
	DTO_FIELD(String, createTime);
	DTO_FIELD_INFO(createTime) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.createTime");
	}
	// 药房名称
	DTO_FIELD(String, pharmacy);
	DTO_FIELD_INFO(pharmacy) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.pharmacy");
	}
	// 申请人
	DTO_FIELD(String, applicant);
	DTO_FIELD_INFO(applicant) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.applicant");
	}
};

// 住院发药汇总队列分页响应DTO
class InpatientDispenseSummaryPageDTO : public oatpp::DTO
{
	DTO_INIT(InpatientDispenseSummaryPageDTO, DTO);
	// 总数
	DTO_FIELD(UInt64, total);
	DTO_FIELD_INFO(total) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.total");
	}
	// 汇总单列表
	DTO_FIELD(oatpp::List<InpatientDispenseSummaryItemDTO::Wrapper>, summaryList);
	DTO_FIELD_INFO(summaryList) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.summaryList");
	}
};

// 住院患者药品明细项DTO
class InpatientDrugItemDTO : public oatpp::DTO
{
	DTO_INIT(InpatientDrugItemDTO, DTO);
	// 明细ID
	DTO_FIELD(String, detailId);
	DTO_FIELD_INFO(detailId) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.detailId");
	}
	// 序号
	DTO_FIELD(Int32, serialNo);
	DTO_FIELD_INFO(serialNo) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.serialNo");
	}
	// 患者姓名
    // 前端界面没显示患者姓名
	//API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("dispense.inpatient-dispense.field.name"));
	// 住院号
    // 前端界面没显示住院号
	//API_DTO_FIELD_DEFAULT(String, hospitalizationNo, ZH_WORDS_GETTER("dispense.inpatient-dispense.field.hospitalizationNo"));
	// 药品名称
	DTO_FIELD(String, drugName);
	DTO_FIELD_INFO(drugName) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.drugName");
	}
    // 数量
	DTO_FIELD(String, quantity);
	DTO_FIELD_INFO(quantity) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.quantity");
	}	
	// 规格
	DTO_FIELD(String, specification);
	DTO_FIELD_INFO(specification) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.specification");
	}
};

// 住院患者药品明细响应DTO
class InpatientDrugDetailDTO : public oatpp::DTO
{
    DTO_INIT(InpatientDrugDetailDTO, DTO);
    // 汇总单号
    DTO_FIELD(String, summaryNo);
    DTO_FIELD_INFO(summaryNo) {
        info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.summaryNo");
    }
    // 所属病区
    DTO_FIELD(String, ward);
    DTO_FIELD_INFO(ward) {
        info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.ward");
    }
    // 创建时间
	DTO_FIELD(String, createTime);
	DTO_FIELD_INFO(createTime) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.createTime");
	}
    // 药房名称
    DTO_FIELD(String, pharmacy);
	DTO_FIELD_INFO(pharmacy) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.pharmacy");
	}
    // 申请人
    DTO_FIELD(String, applicant);
    DTO_FIELD_INFO(applicant) {
        info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.applicant");
    }
    // 药品明细列表
	DTO_FIELD(oatpp::List<InpatientDrugItemDTO::Wrapper>, drugList);
	DTO_FIELD_INFO(drugList) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.drugList");
	}
};

// 住院发药核对DTO
class InpatientDispenseVerifyDTO : public oatpp::DTO
{
    DTO_INIT(InpatientDispenseVerifyDTO,DTO);
    // 医保类型 0自费1医保2统筹
    DTO_FIELD(Int32, InsuranceType);
    DTO_FIELD_INFO(InsuranceType) {
        info->description = ZH_WORDS_GETTER("dispense.dispense.insurancetype");
    }
    // 发药药师
    DTO_FIELD(String, Pharmacist);
    DTO_FIELD_INFO(Pharmacist) {
        info->description = ZH_WORDS_GETTER("dispense.dispense.pharmacist");
    }
    // 领药人，患者本人/家属
    DTO_FIELD(String,Recipient);
    DTO_FIELD_INFO(Recipient) {
        info->description = ZH_WORDS_GETTER("dispense.dispense.recipient");
    }
    // 日期
    DTO_FIELD(String, Date);
    DTO_FIELD_INFO(Date) {
        info->description = ZH_WORDS_GETTER("dispense.dispense.date");
    }
    // 发药单ID，未发药为0
    DTO_FIELD(Int32, Dispenseld);
    DTO_FIELD_INFO(Dispenseld) {
        info->description = ZH_WORDS_GETTER("dispense.dispense.dispenseld");
    }
    // 病区
    DTO_FIELD(String, Ward);
    DTO_FIELD_INFO(Ward) {
        info->description = ZH_WORDS_GETTER("dispense.dispense.ward");
    }
    //// 发药药品明细
    //DTO_FIELD(oatpp::List<InpatientReturnDrugDTO::Wrapper>, senddrugList);
    //DTO_FIELD_INFO(senddrugList) {
    //    info->description = ZH_WORDS_GETTER("dispense.dispense.senddrugList");
    //}
    // 发药状态标识
    DTO_FIELD(String, dispenseStatus);
    DTO_FIELD_INFO(dispenseStatus) {
        info->description = ZH_WORDS_GETTER("dispense.dispense.dispenseStatus");
    }

public:
    InpatientDispenseVerifyDTO() {
        this->InsuranceType = Int32(0);
        this->Dispenseld = Int32(0);
    }
};

// 住院发药驳回DTO
class InpatientDispenseRejectDTO : public oatpp::DTO {
    DTO_INIT(InpatientDispenseRejectDTO, DTO)
    // 发药单ID
    DTO_FIELD(Int32, dispenseld);
    DTO_FIELD_INFO(dispenseld) {
        info->description = ZH_WORDS_GETTER("dispense.reject.field.dispenseld");
    }

    // 审核人
    DTO_FIELD(String, auditor);
    DTO_FIELD_INFO(auditor) {
        info->description = ZH_WORDS_GETTER("dispense.reject.field.auditor");
    }

    // 驳回原因
    DTO_FIELD(String, rejectReason);
    DTO_FIELD_INFO(rejectReason) {
        info->description = ZH_WORDS_GETTER("dispense.reject.field.rejectReason");
    }
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_INPATIENT_DISPENSE_DTO_
