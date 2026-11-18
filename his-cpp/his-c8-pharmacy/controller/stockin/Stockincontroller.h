#ifndef STOCK_IN_CONTROLLER_H
#define STOCK_IN_CONTROLLER_H

#include"domain/vo/stockin/StockinJsonVO.h"
#include"domain/dto/stockin/StockinDTO.h"
#include"domain/dto/stockin/StockinCreateDTO.h"
#include"domain/dto/stockin/StockinSaveDTO.h"
#include"domain/dto/stockin/StockinSaveAndSubmit.h"
#include"ApiHelper.h"
#define API_TAG ZH_WORDS_GETTER("pharmacy.stockin.tag")

#include OATPP_CODEGEN_BEGIN(ApiController)
class Stockincontroller : public oatpp::web::server::api::ApiController
{
private:
	StockinDTO::Wrapper execQueryStockInOne(const String& queryParams);
	NoDataJsonVO::Wrapper execCreateStockIn(const StockinCreateDTO::Wrapper& dto);
	NoDataJsonVO::Wrapper exeSaveStockIn(const StockinSaveDTO::Wrapper& dto);
	NoDataJsonVO::Wrapper exesaveAndSumitStockIn(const StockinSaveAndSubmit::Wrapper& queryParams);

	//������������ʽӿ�
	API_ACCESS_DECLARE(Stockincontroller);
public://����ӿ�

	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("pharmacy.stockin.query-one.summary"),
		queryStockInOne,
		StockinJsonVO::Wrapper, 
		API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, 
		"/pharmacy/stockin/query-one", 
		queryStockInOne, QUERY(String, orderNo),
		execQueryStockInOne(orderNo));
	
	//�½�����POST /pharmacy/stockin/create
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("pharmacy.stockin.create.summary"),
		createStockIn, 
		NoDataJsonVO::Wrapper,
		API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST,
		"/pharmacy/stockin/create", 
		createStockIn, 
		BODY_DTO(Object<StockinCreateDTO>,dto), 
		execCreateStockIn(dto));
	
	//��ʱ���浥��POST /pharmacy/stockin/save-draft
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.stockin.save-draft.summary"),
		saveStockIn, 
		NoDataJsonVO::Wrapper, 
		API_TAG);
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,
		"/pharmacy/stockin/save-draft",
		saveStockIn, 
		BODY_DTO(Object<StockinSaveDTO>,dto), 
		exeSaveStockIn(dto));
	
	//���浥�ݲ��ύPOST /pharmacy/stockin/save-submit
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("pharmacy.stockin.save-submit.summary"),
		saveAndSumitStockIn,
		NoDataJsonVO::Wrapper,
		API_TAG);

	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,
		"/pharmacy/stockin/save-submit",
		saveAndSumitStockIn,
		BODY_DTO(Object<StockinSaveAndSubmit>, dto),
		exesaveAndSumitStockIn(dto)
	);
};

#include OATPP_CODEGEN_END(ApiController)


#endif // !STOCK_IN_CONTROLLER_H