
//���ڱ���ݸ���ύ

#ifndef STOCK_IN_SAVE_DTO_H
#define STOCK_IN_SAVE_DTO_H

#include "domain/GlobalInclude.h"
#include "domain/DoInclude.h"
#include "domain/dto/stockin/StockinDrugItemDTO.h"

//���浥��
#include OATPP_CODEGEN_BEGIN(DTO)
class StockinSaveDTO : public oatpp::DTO
{
    DTO_INIT(StockinSaveDTO, DTO)

    //API_DTO_FIRLF_REQUIRE(���ͣ����ƣ��������Ƿ������)
    
	//�Ƶ���
	API_DTO_FIELD_REQUIRE(String, preparedBy, ZH_WORDS_GETTER("stockin.data.prepared_by"), true);
	//ʱ��
	API_DTO_FIELD_REQUIRE(String, time, ZH_WORDS_GETTER("stockin.data.time"), true);
	//ԭҩ��
	API_DTO_FIELD_REQUIRE(String, sourceStoreroom, ZH_WORDS_GETTER("stockin.data.source_storeroom"), true);
	//Ŀ��ҩ��
	API_DTO_FIELD_REQUIRE(String, targetPharmacy, ZH_WORDS_GETTER("stockin.data.target_pharmacy"), true);
	//����һ��ҩƷ��Ϣ
	API_DTO_FIELD_REQUIRE(List<Object<StockinDrugItemDTO>> ,drugItems,ZH_WORDS_GETTER("stockin.data.drug_items.at_least_one"), true);
};

#include OATPP_CODEGEN_END(DTO)

#endif