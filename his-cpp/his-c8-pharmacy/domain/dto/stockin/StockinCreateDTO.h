#ifndef STOCKIN_CREATE_DTO_H
#define STOCKIN_CREATE_DTO_H

#include "domain/GlobalInclude.h"
#include "domain/DoInclude.h"

/* �½�����dto */
#include OATPP_CODEGEN_BEGIN(DTO)
class StockinCreateDTO : public oatpp::DTO
{
	DTO_INIT(StockinCreateDTO,DTO)
public:
	//API_DTO_FIRLF_REQUIRE(���ͣ����ƣ��������Ƿ������)
	//�Ƶ���
	API_DTO_FIELD_REQUIRE(String, preparedBy, ZH_WORDS_GETTER("stockin.data.prepared_by"), true);
	//ʱ��
	API_DTO_FIELD_REQUIRE(String, time, ZH_WORDS_GETTER("stockin.data.time"), true);
	//ԭҩ��
	API_DTO_FIELD_REQUIRE(String, sourceStoreroom, ZH_WORDS_GETTER("stockin.data.source_storeroom"), true);
	//Ŀ��ҩ��
	API_DTO_FIELD_REQUIRE(String, targetPharmacy, ZH_WORDS_GETTER("stockin.data.target_pharmacy"), true);
};
#include OATPP_CODEGEN_END(DTO)
#endif // !STOCKIN_CREATE_DTO_H
