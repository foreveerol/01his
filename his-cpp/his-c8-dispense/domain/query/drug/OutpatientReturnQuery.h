#pragma once
#ifndef _OUTPATIENT_RETURN_QUERY_
#define _OUTPATIENT_RETURN_QUERY_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

// 继承分页查询模型
class OutpatientReturnQuery : public PageQuery {
    DTO_INIT(OutpatientReturnQuery, PageQuery);

    // 预留查询条件：比如患者姓名关键字
    DTO_FIELD(String, keyword);
    DTO_FIELD_INFO(keyword) {
        info->description = ZH_WORDS_GETTER("dispense.outpatient.return.keyword");
    }
};

#include OATPP_CODEGEN_END(DTO)
#endif