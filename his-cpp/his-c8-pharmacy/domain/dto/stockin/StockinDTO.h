#ifndef STOCK_IN_DTO_H
#define STOCK_IN_DTO_H

#include "domain/GlobalInclude.h"
#include "domain/DoInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)


class StockinDTO : public oatpp::DTO
{
    DTO_INIT(StockinDTO, DTO)

    //API_DTO_FIRLF_REQUIRE(���ͣ����ƣ��������Ƿ������)
    //���ݺ�
    API_DTO_FIELD_REQUIRE(String, stockInDocNo, ZH_WORDS_GETTER("stockin.qurey.stockInDocNo"), true); 
	
};

#include OATPP_CODEGEN_END(DTO)

#endif