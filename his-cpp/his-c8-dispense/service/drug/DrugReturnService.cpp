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
#include "DrugReturnService.h"
#include "../../dao/drug/DrugReturnDAO.h"
#include <ctime>

InpatientReturnQueueJsonVO::Wrapper DrugReturnService::listReturnQueue(const InpatientReturnQuery::Wrapper& query)
{
	auto jvo = InpatientReturnQueueJsonVO::createShared();

	DrugReturnDAO dao;
	auto list = dao.selectReturnQueue(query);

	auto patientList = oatpp::List<InpatientReturnPatientDTO::Wrapper>::createShared();
	for (const auto& item : list) {
		auto dto = InpatientReturnPatientDTO::createShared();
		dto->name = item.getPatientName();
		dto->hospitalizationNo = item.getHospitalizationNo();
		dto->ward = item.getWard();
		dto->bedNo = item.getBedNo();
		dto->refundStatus = item.getRefundStatus();
		patientList->push_back(dto);
	}
	jvo->success(patientList);
	return jvo;
}

InpatientReturnJsonVO::Wrapper DrugReturnService::getReturnDetail(const std::string& hospitalizationNo)
{
	auto jvo = InpatientReturnJsonVO::createShared();

	if (hospitalizationNo.empty()) {
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	DrugReturnDAO dao;

	auto patientList = dao.selectReturnPatient(hospitalizationNo);
	if (!patientList.empty()) {
		auto& p = patientList.front();
		auto patientDTO = InpatientReturnPatientDTO::createShared();
		patientDTO->name = p.getName();
		patientDTO->gender = p.getGender();
		patientDTO->hospitalizationNo = p.getHospitalizationNo();
		patientDTO->ward = p.getWard();
		patientDTO->bedNo = p.getBedNo();
		patientDTO->refundStatus = p.getRefundStatus();

		std::string birthDate = p.getBirthDate();
		if (!birthDate.empty() && birthDate.length() >= 10) {
			try {
				int birthYear = std::stoi(birthDate.substr(0, 4));
				int birthMonth = std::stoi(birthDate.substr(5, 2));
				int birthDay = std::stoi(birthDate.substr(8, 2));
				std::time_t now = std::time(nullptr);
				std::tm ltm{};
				localtime_s(&ltm, &now);
				int currentYear = ltm.tm_year + 1900;
				int currentMonth = ltm.tm_mon + 1;
				int currentDay = ltm.tm_mday;
				int age = currentYear - birthYear;
				if (currentMonth < birthMonth || (currentMonth == birthMonth && currentDay < birthDay)) {
					age--;
				}
				patientDTO->age = Int32(age >= 0 ? age : 0);
			} catch (const std::exception&) {
				patientDTO->age = Int32(0);
			}
		}

		auto result = InpatientReturnDTO::createShared();
		result->patientInfo = patientDTO;

		auto drugList = oatpp::List<InpatientReturnDrugDTO::Wrapper>::createShared();
		auto list = dao.selectReturnDrugs(hospitalizationNo);
		for (const auto& item : list) {
			auto dto = InpatientReturnDrugDTO::createShared();
			dto->detailId = item.getDetailId();
			dto->serialNo = Int32(item.getSerialNo());
			dto->drugName = item.getDrugName();
			dto->quantity = item.getQuantity();
			dto->dispenseDate = item.getDispenseDate();
			drugList->push_back(dto);
		}
		result->drugList = drugList;
		jvo->success(result);
	} else {
		jvo->init(nullptr, RS_PARAMS_INVALID);
	}
	return jvo;
}

StringJsonVO::Wrapper DrugReturnService::confirmReturn(const InpatientReturnConfirmDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();

	if (!dto->hospitalizationNo || dto->hospitalizationNo->empty()) {
		jvo->init("hospitalizationNo is required.", RS_PARAMS_INVALID);
		return jvo;
	}
	if (!dto->refundDetailIds || dto->refundDetailIds->empty()) {
		jvo->init("refundDetailIds is required.", RS_PARAMS_INVALID);
		return jvo;
	}

	if (dto->refundDetailIds->size() > 500) {
		jvo->init("Too many detail IDs. Maximum allowed is 500.", RS_PARAMS_INVALID);
		return jvo;
	}

	std::vector<std::string> ids;
	for (const auto& id : *dto->refundDetailIds) {
		if (id && !id->empty()) {
			ids.push_back(id.getValue(""));
		}
	}

	if (ids.empty()) {
		jvo->init("No valid refund detail IDs provided.", RS_PARAMS_INVALID);
		return jvo;
	}

	DrugReturnDAO dao;
	int updated = dao.confirmReturn(dto->hospitalizationNo.getValue(""), ids);
	if (updated > 0) {
		jvo->success("Return confirmed successfully");
	} else {
		jvo->init("No records were updated.", RS_PARAMS_INVALID);
	}
	return jvo;
}
