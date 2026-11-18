/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 10:58:42

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
#include "DispenseRecordController.h"
#include "../../service/dispense/DispenseRecordService.h"
#include "ExcelComponent.h"
#include "SimpleDateTimeFormat.h"

std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse>
DispenseRecordController::execExportDispenseRecord(const DispenseRecordQuery::Wrapper& query)
{
	// 查询发退药记录
	auto result = DispenseRecordService().listByCondition(query);

	// 将数据写入Excel
	auto buff = ExcelComponent().writeVectorToBuff("dispense-record",
		[&result](ExcelComponent* ex) {
			// 写入表头
			ex->addHeader({
				ZH_WORDS_GETTER("dispense.field.busNo"),
				ZH_WORDS_GETTER("dispense.field.statusEnum"),
				ZH_WORDS_GETTER("dispense.field.dispenseTime"),
				ZH_WORDS_GETTER("dispense.field.patientName"),
				ZH_WORDS_GETTER("dispense.field.idCard"),
				ZH_WORDS_GETTER("dispense.field.encounterBusNo"),
				ZH_WORDS_GETTER("dispense.field.medicationName"),
				ZH_WORDS_GETTER("dispense.field.totalVolume"),
				ZH_WORDS_GETTER("dispense.field.doseFormCode"),
				ZH_WORDS_GETTER("dispense.field.quantity"),
				ZH_WORDS_GETTER("dispense.field.dispenseQuantity"),
				ZH_WORDS_GETTER("dispense.field.unitCode"),
				ZH_WORDS_GETTER("dispense.field.lotNumber"),
				ZH_WORDS_GETTER("dispense.field.practitionerName"),
				ZH_WORDS_GETTER("dispense.field.locationName"),
				ZH_WORDS_GETTER("dispense.field.prescriptionNo"),
				ZH_WORDS_GETTER("dispense.field.requesterId"),
				ZH_WORDS_GETTER("dispense.field.createdAt")
				});
			// 写入数据
			int row = 2;
			for (auto& item : result) {
				int col = 1;
				ex->setCellValue(row, col++, item.getBusNo());
				ex->setCellValue(row, col++, item.getStatusEnum());
				ex->setCellValue(row, col++, item.getDispenseTime());
				ex->setCellValue(row, col++, item.getPatientName());
				ex->setCellValue(row, col++, item.getIdCard());
				ex->setCellValue(row, col++, item.getEncounterBusNo());
				ex->setCellValue(row, col++, item.getMedicationName());
				ex->setCellValue(row, col++, item.getTotalVolume());
				ex->setCellValue(row, col++, item.getDoseFormCode());
				ex->setCellValue(row, col++, item.getQuantity());
				ex->setCellValue(row, col++, item.getDispenseQuantity());
				ex->setCellValue(row, col++, item.getUnitCode());
				ex->setCellValue(row, col++, item.getLotNumber());
				ex->setCellValue(row, col++, item.getPractitionerName());
				ex->setCellValue(row, col++, item.getLocationName());
				ex->setCellValue(row, col++, item.getPrescriptionNo());
				ex->setCellValue(row, col++, item.getRequesterId());
				ex->setCellValue(row, col++, item.getCreatedAt());
				ex->setRowProperties(row++);
			}
		});

	// 封装二进制数据
	const char* charData = reinterpret_cast<const char*>(buff.data());
	auto fstring = String(charData, buff.size());

	// 构建响应
	auto response = createResponse(Status::CODE_200, fstring);

	// 设置响应头
	std::string filename = "dispense-record-" + SimpleDateTimeFormat::format() + ".xlsx";
	response->putHeader("Content-Disposition", "attachment; filename=" + filename);
	response->putHeader(Header::CONTENT_TYPE,
		" application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");

	// 返回文件流
	return response;
}
