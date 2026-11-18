#ifndef STOCKIN_SAVE_AND_SUMIT_H
#define STOCKIN_SAVE_AND_SUMIT_H
#include "domain/GlobalInclude.h"
#include "domain/DoInclude.h"
#include "domain/dto/stockin/StockinSaveDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)
class StockinSaveAndSubmit : public StockinSaveDTO
{
	DTO_INIT(StockinSaveAndSubmit, StockinSaveDTO);
	//API_DTO_FIRLF_REQUIRE(���ͣ����ƣ��������Ƿ������)
	//������ҩ���Ľ��
	API_DTO_FIELD_REQUIRE(Int32,sumPrice, ZH_WORDS_GETTER("stockin.sumprice"),true);
};
#include OATPP_CODEGEN_END(DTO)
#endif // !STOCKIN_SAVE_AND_SUMIT_H
