/*
 Copyright Zero One Star. All rights reserved.

 @Author: zjb517
 @Date: 2026/07/26 10:00:00

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#include "stdafx.h"
#include "InpatientRecordService.h"
#include "../../dao/drug/InpatientRecordDAO.h"
#include <sstream>
#include <iomanip>

namespace {
	// Format double as fixed 2-decimal string for currency display
	std::string formatCurrency(double value) {
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(2) << value;
		return oss.str();
	}
}

InpatientRecordPageJsonVO::Wrapper InpatientRecordService::listByCondition(const InpatientRecordQuery::Wrapper& query)
{
	auto jvo = InpatientRecordPageJsonVO::createShared();
	auto pageDTO = InpatientRecordPageDTO::createShared();
	pageDTO->pageIndex = query->pageIndex;
	pageDTO->pageSize = query->pageSize;

	InpatientRecordDAO dao;
	auto list = dao.selectWithCondition(query);
	uint64_t total = dao.countWithCondition(query);

	pageDTO->total = Int64(total);
	pageDTO->calcPages();

	auto rows = oatpp::List<InpatientRecordItemDTO::Wrapper>::createShared();
	for (auto& item : list) {
		auto dto = InpatientRecordItemDTO::createShared();
		dto->prescriptionNo = item.getPrescriptionNo();
		dto->recordType = item.getRecordType();
		dto->patientName = item.getPatientName();
		dto->hospitalizationNo = item.getHospitalizationNo();
		dto->ward = item.getWard();
		dto->bedNo = item.getBedNo();
		dto->drugName = item.getDrugName();
		dto->specification = item.getSpecification();
		dto->quantity = item.getQuantity();
		dto->unitPrice = formatCurrency(item.getUnitPrice());
		dto->totalAmount = formatCurrency(item.getTotalAmount());
		dto->batchNo = item.getBatchNo();
		dto->traceCode = item.getTraceCode();
		dto->manufacturer = item.getManufacturer();
		dto->summaryNo = item.getSummaryNo();
		dto->deptName = item.getDeptName();
		rows->push_back(dto);
	}
	pageDTO->rows = rows;
	jvo->success(pageDTO);
	return jvo;
}

StringJsonVO::Wrapper InpatientRecordService::exportRecords(const InpatientRecordExportDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	// Build query from export DTO filter conditions
	auto query = InpatientRecordQuery::createShared();
	if (dto->drugName)       query->drugName = dto->drugName;
	if (dto->recordType)     query->recordType = dto->recordType;
	if (dto->pharmacy)       query->pharmacy = dto->pharmacy;
	if (dto->projectType)    query->projectType = dto->projectType;
	if (dto->dispenseName)   query->dispenseName = dto->dispenseName;
	if (dto->name)            query->name = dto->name;
	if (dto->hospitalizationNo) query->hospitalizationNo = dto->hospitalizationNo;
	if (dto->recordNo)       query->recordNo = dto->recordNo;
	if (dto->startDate)      query->startDate = dto->startDate;
	if (dto->endDate)        query->endDate = dto->endDate;
	// Export all records, set large page size
	query->pageIndex = UInt64(1);
	query->pageSize = UInt64(10000);

	InpatientRecordDAO dao;
	auto list = dao.selectWithCondition(query);
	uint64_t total = dao.countWithCondition(query);

	if (total == 0) {
		jvo->success("No records found for export.");
		return jvo;
	}

	// TODO: Generate Excel file using xlnt library and upload to FastDFS
	// For now, return the record count to confirm data is available
	std::ostringstream msg;
	msg << "Export ready: " << total << " record(s) found, "
		<< list.size() << " record(s) loaded.";
	jvo->success(msg.str());
	return jvo;
}
