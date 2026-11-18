#pragma once
#ifndef _INPATIENT_DISPENSE_QUERY_
#define _INPATIENT_DISPENSE_QUERY_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 住院发药汇总队列查询参数
class InpatientDispenseQuery : public PageQuery
{
	DTO_INIT(InpatientDispenseQuery, PageQuery);
	// 发药状态
	DTO_FIELD(String, dispenseStatus) = "";
	DTO_FIELD_INFO(dispenseStatus) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.dispenseStatus");
	}
	// 开始日期
	DTO_FIELD(String, startDate) = "";
	DTO_FIELD_INFO(startDate) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.startDate");
	}
	// 结束日期
	DTO_FIELD(String, endDate) = "";
	DTO_FIELD_INFO(endDate) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.endDate");
	}
	// 汇总单号
	DTO_FIELD(String, summaryNo) = "";
	DTO_FIELD_INFO(summaryNo) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.summaryNo");
	}
};

// 住院患者药品明细查询参数
class InpatientDrugDetailQuery : public oatpp::DTO
{
	DTO_INIT(InpatientDrugDetailQuery, DTO);
	// 汇总单号（必填）
	DTO_FIELD(String, summaryNo) = "";
	DTO_FIELD_INFO(summaryNo) {
		info->description = ZH_WORDS_GETTER("dispense.inpatient-dispense.field.summaryNo");
		info->required = true;
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_INPATIENT_DISPENSE_QUERY_