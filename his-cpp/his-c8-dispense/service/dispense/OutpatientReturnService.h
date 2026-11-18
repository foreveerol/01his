#pragma once
#ifndef _OUTPATIENT_RETURN_SERVICE_
#define _OUTPATIENT_RETURN_SERVICE_

#include "domain/query/drug/OutpatientReturnQuery.h"
#include "domain/dto/drug/OutpatientReturnDTO.h"
#include "domain/dto/PageDTO.h" 

/**
 * 门诊退药服务层 
 */
class OutpatientReturnService
{
public:
	// 1. 分页查询门诊退药队列
	PageDTO<OutpatientReturnQueueItemDTO::Wrapper>::Wrapper listReturnQueue(const OutpatientReturnQuery::Wrapper& query);

	// 2. 查询门诊退药明细
	oatpp::List<OutpatientReturnDrugDTO::Wrapper> listReturnDetail(const std::string& returnId);

	// 3. 确认退药
	bool modifyConfirmReturn(const OutpatientReturnConfirmDTO::Wrapper& dto);

	// 4. 拒绝退药
	bool modifyRejectReturn(const OutpatientReturnRejectDTO::Wrapper& dto);
};

#endif // !_OUTPATIENT_RETURN_SERVICE_