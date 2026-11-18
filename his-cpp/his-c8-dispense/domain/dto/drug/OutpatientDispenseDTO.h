#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: zjb517
 @Date: 2026/07/19 17:02:00

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
#ifndef _OUTPATIENT_DISPENSE_DTO_
#define _OUTPATIENT_DISPENSE_DTO_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 发药药品明细DTO
 */
class OutpatientDrugDetailInfDTO : public oatpp::DTO
{
	DTO_INIT(OutpatientDrugDetailInfDTO, DTO);
	// 处方号
	API_DTO_FIELD_REQUIRE(String, prescriptionNo, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.prescriptionNo"), true);
	// 状态
	API_DTO_FIELD_REQUIRE(String, status, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.status"), true);
	//药名
	API_DTO_FIELD_REQUIRE(String, drug_name, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.drugName"), true);
	//数量
	API_DTO_FIELD_REQUIRE(String, num, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.quantity"), true);
	//药品规格
	API_DTO_FIELD_REQUIRE(String, drug_spe, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.specification"), true);
	//药品批次号
	API_DTO_FIELD_REQUIRE(String, lot_no, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.batchNum"), true);
	//金额
	API_DTO_FIELD_REQUIRE(Float32, money, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.money"), true);
	//发放库房
	API_DTO_FIELD_REQUIRE(String, issuing_warehouse, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.issuing_warehouse"), true);
	//追溯码
	API_DTO_FIELD_REQUIRE(String, trace_code, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.trace_code"), false);
	//厂家
	API_DTO_FIELD_REQUIRE(String, manufacturere, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.manufacturer"), true);
};

 // 患者待发药 DTO 
 
class OutpatientDispenseDTO : public oatpp::DTO
{
	DTO_INIT(OutpatientDispenseDTO, DTO);
	
	// 患者姓名
	API_DTO_FIELD_REQUIRE(String, patient_name, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.name"), true);
	// 患者id
	API_DTO_FIELD_REQUIRE(String, patient_id, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.id"), true);
	// 患者就诊号
	API_DTO_FIELD_REQUIRE(String, visit_no, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.visit_no"), true);
	// 患者所在科室
	API_DTO_FIELD_REQUIRE(String, department, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.department"), true);
	//患者医保类型
	API_DTO_FIELD_REQUIRE(String, insurance_type, ZH_WORDS_GETTER("dispense.outpatient-dispense.insurance_type"), true);
	//患者待发药状态
	API_DTO_FIELD_REQUIRE(String, dispenseStatus, ZH_WORDS_GETTER("dispense.outpatient-dispense.dispenseStatus"), true);
	//患者性别
	API_DTO_FIELD_REQUIRE(String, gender, ZH_WORDS_GETTER("dispense.outpatient-dispense.gender"), true);
	//患者门诊类型
	API_DTO_FIELD_REQUIRE(String, outpatient_type, ZH_WORDS_GETTER("dispense.outpatient-dispense.outpatient_type"), true);
};

 // 门诊处方主信息DTO
 
class OutpatientQueueItemDTO : public oatpp::DTO
{
	DTO_INIT(OutpatientQueueItemDTO, DTO);
	// ��������
	API_DTO_FIELD_REQUIRE(String, patient_name, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.name"), true);
	// �ŶӺ�
	API_DTO_FIELD_REQUIRE(String, queue_no, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.queue_no"), true);
	// ��������
	API_DTO_FIELD_REQUIRE(String, visit_date, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.visit_date"), true);
	
	
};

 // 发药操作参数DTO

class OutpatientBatchDispenseDTO : public oatpp::DTO
{
	DTO_INIT(OutpatientBatchDispenseDTO, DTO);
	// ����id
	API_DTO_FIELD_REQUIRE(Vector<String>, prescription_id_list, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.prescriptionNo"), true);
	// ����ҩʦid
	API_DTO_FIELD_REQUIRE(String, pharmacist_id, ZH_WORDS_GETTER("dispense.outpatient-dispense.field..pharmacist_id"), true);
	// ��ҩ����ʱ��
	API_DTO_FIELD_REQUIRE(String, dispense_time, ZH_WORDS_GETTER("dispense.outpatient-dispense.field.dispense_time"), true);
	
};

#include OATPP_CODEGEN_END(DTO)
#endif 
