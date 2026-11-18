#include "stdafx.h"
#include "service/dispense/OutpatientReturnService.h"
#include "dao/drug/OutpatientReturnDAO.h" 

PageDTO<OutpatientReturnQueueItemDTO::Wrapper>::Wrapper OutpatientReturnService::listReturnQueue(const OutpatientReturnQuery::Wrapper& query)
{
	OutpatientReturnDAO dao;

	auto page = PageDTO<OutpatientReturnQueueItemDTO::Wrapper>::createShared();
	page->pageIndex = query->pageIndex ? query->pageIndex : 1;
	page->pageSize = query->pageSize ? query->pageSize : 10;

	// 1. 查总条数
	uint64_t totalCount = dao.countReturnQueue(query);
	page->total = totalCount;

	// 2. 查具体数据并进行 DO -> DTO 转换
	auto dtoItems = oatpp::List<OutpatientReturnQueueItemDTO::Wrapper>::createShared();
	if (totalCount > 0) {
		auto doList = dao.selectReturnQueue(query);

		for (const auto& doItem : doList) {
			auto dto = OutpatientReturnQueueItemDTO::createShared();
			dto->id = doItem.getId();
			dto->patientName = doItem.getPatientName();
			dto->returnDate = doItem.getReturnDate();
			dto->drugCount = doItem.getDrugCount();
			dto->returnStatus = doItem.getReturnStatus();
			dtoItems->push_back(dto);
		}
	}

	page->rows = dtoItems;
	return page;
}

oatpp::List<OutpatientReturnDrugDTO::Wrapper> OutpatientReturnService::listReturnDetail(const std::string& returnId)
{
	OutpatientReturnDAO dao;
	auto dtoItems = oatpp::List<OutpatientReturnDrugDTO::Wrapper>::createShared();

	auto doList = dao.selectReturnDetail(returnId);

	for (const auto& doItem : doList) {
		auto dto = OutpatientReturnDrugDTO::createShared();
		dto->drugId = doItem.getDrugId();
		dto->drugName = doItem.getDrugName();
		dto->quantity = doItem.getQuantity();
		dto->dispenseDate = doItem.getDispenseDate();
		dtoItems->push_back(dto);
	}

	return dtoItems;
}

bool OutpatientReturnService::modifyConfirmReturn(const OutpatientReturnConfirmDTO::Wrapper& dto)
{
	if (!dto || !dto->returnId) return false;

	OutpatientReturnDAO dao;
	int affectedRows = dao.confirmReturn(dto->returnId);
	return affectedRows > 0;
}

bool OutpatientReturnService::modifyRejectReturn(const OutpatientReturnRejectDTO::Wrapper& dto)
{
	if (!dto || !dto->returnId || !dto->reason) return false;

	OutpatientReturnDAO dao;
	int affectedRows = dao.rejectReturn(dto->returnId, dto->reason);
	return affectedRows > 0;
}