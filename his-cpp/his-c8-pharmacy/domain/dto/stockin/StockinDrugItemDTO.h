#ifndef STOCK_IN_DETAIL_DTO_H
#define STOCK_IN_DETAIL_DTO_H

#include "domain/GlobalInclude.h"
#include "domain/DoInclude.h"

/* �����ϸdto */
#include OATPP_CODEGEN_BEGIN(DTO)
class StockinDrugItemDTO : public oatpp::DTO
{
    DTO_INIT(StockinDrugItemDTO, DTO)

    //API_DTO_FIRLD_REQUIRE(���ͣ����ƣ��������Ƿ������)
        
    //��Ŀ����,
    API_DTO_FIELD_REQUIRE(String, code, ZH_WORDS_GETTER("stockin.drugdata.code"), true);
    //��Ŀ����
    API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("stockin.drugdata.name"), true);
    //����
    API_DTO_FIELD_REQUIRE(String, manufacturer, ZH_WORDS_GETTER("manufacturer"), true);
    //����
    API_DTO_FIELD_REQUIRE(Int32, drugNumber, ZH_WORDS_GETTER("stockin.drugdata.number"), true);
    //��װ��λ
    API_DTO_FIELD_REQUIRE(String, drugPackUnit, ZH_WORDS_GETTER("stockin.drugdata.packUnit"), true);
    //��С��λ
    API_DTO_FIELD_REQUIRE(String, drugMinunit, ZH_WORDS_GETTER("stockin.drugdata.minunit"), true);
    // ������
    API_DTO_FIELD_REQUIRE(Float32, drugpurchasePricePerPack, ZH_WORDS_GETTER("stockin.drugdata.purchase_price_per_pack"), true);
    //���ۼ�
    API_DTO_FIELD_REQUIRE(Float32, drugretailPricePerPack, ZH_WORDS_GETTER("stockin.drugdata.retail_price_per_pack"), true);
    //���
    API_DTO_FIELD_REQUIRE(String, specification, ZH_WORDS_GETTER("stockin.drugdata.specification"), true);
    //�ⷿ����
    API_DTO_FIELD_REQUIRE(Int32, packStorageQuantity, ZH_WORDS_GETTER("stockin.drugdata.pack_storage_quantity"), true);
    //�ܼ�
    API_DTO_FIELD_REQUIRE(Int32, drugsumPrice, ZH_WORDS_GETTER("stockin.drugdata.pack_storage_quantity"), true);
    //����
    API_DTO_FIELD_REQUIRE(String, batchNo, ZH_WORDS_GETTER("stockin.drugdata.batch_no"), true);
    //׷����
    API_DTO_FIELD_REQUIRE(String, drugTraceCode, ZH_WORDS_GETTER("stockin.drugdata.drug_trace_code"), false);
    //��ע
    API_DTO_FIELD_REQUIRE(String, remark, ZH_WORDS_GETTER("stockin.drugdata.remark"), false);
};

#include OATPP_CODEGEN_END(DTO)

#endif