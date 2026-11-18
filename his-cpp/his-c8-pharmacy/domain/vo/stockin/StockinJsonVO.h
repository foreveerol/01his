#ifndef STOCK_IN_JSON_VO_H
#define STOCK_IN_JSON_VO_H

#include "domain/GlobalInclude.h"
#include "domain/DoInclude.h"
#include "domain/dto/stockin/StockinDrugItemDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class StockinVO : public oatpp::DTO
{
    DTO_INIT(StockinVO, DTO)
    API_DTO_FIELD_REQUIRE(String, code, ZH_WORDS_GETTER(""), true);
    //���״̬
    API_DTO_FIELD_DEFAULT(String, statusEnum, ZH_WORDS_GETTER("statusEnum"),true);
    //���������
    API_DTO_FIELD_REQUIRE(String,reviewerName,ZH_WORDS_GETTER("stockin.vo.reviewer_name"),false);
    //ʱ��
    API_DTO_FIELD_REQUIRE(String, time, ZH_WORDS_GETTER("stockin.data.time"), true);
    //�Ƶ���
    API_DTO_FIELD_REQUIRE(String, preparedBy, ZH_WORDS_GETTER("stockin.data.prepared_by"), true);
    //Ŀ��ҩ��
    API_DTO_FIELD_REQUIRE(String, targetPharmacy, ZH_WORDS_GETTER("stockin.data.target_pharmacy"), true);
    //ԭҩ��
    API_DTO_FIELD_REQUIRE(String, sourceStoreroom, ZH_WORDS_GETTER("stockin.data.source_storeroom"), true);
    //������ҩ���Ľ��
    API_DTO_FIELD_REQUIRE(Float32, sumPrice, ZH_WORDS_GETTER("stockin.sumprice"),true);
    //ҩƷ��Ϣ�б�
    API_DTO_FIELD_REQUIRE(List<Object<StockinDrugItemDTO>>, druglist, "stockin.data.drug_items", true);
};
class StockinJsonVO :public JsonVO<StockinVO::Wrapper>
{
    DTO_INIT(StockinJsonVO, JsonVO<StockinVO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)

#endif