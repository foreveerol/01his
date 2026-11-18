#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 0:27:04

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
#ifndef _DISPENSE_RECORD_CONTROLLER_
#define _DISPENSE_RECORD_CONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/dispense/DispenseRecordQuery.h"

// 0 导入API控制器宏
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

#define API_TAG ZH_WORDS_GETTER("dispense.tags.main")

/**
 * 门诊发退药记录导出控制器
 */
class DispenseRecordController : public oatpp::web::server::api::ApiController // 1 继承控制器
{
	// 2 定义控制器访问权限
	API_ACCESS_DECLARE(DispenseRecordController);
	// 3 定义接口
public:
	// 3.1 导出发退药记录接口描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("dispense.export.summary"), exportDispenseRecord, Void, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "startTime", ZH_WORDS_GETTER("dispense.field.startTime"), "", true);
		API_DEF_ADD_QUERY_PARAMS(String, "endTime", ZH_WORDS_GETTER("dispense.field.endTime"), "", true);
		API_DEF_ADD_QUERY_PARAMS(String, "statusList", ZH_WORDS_GETTER("dispense.field.statusList"), "", false);
		API_DEF_ADD_QUERY_PARAMS(String, "patientName", ZH_WORDS_GETTER("dispense.field.patientName"), "", false);
		API_DEF_ADD_QUERY_PARAMS(String, "medicationName", ZH_WORDS_GETTER("dispense.field.medicationName"), "", false);
		API_DEF_ADD_QUERY_PARAMS(String, "practitionerName", ZH_WORDS_GETTER("dispense.field.practitionerName"), "", false);
		API_DEF_ADD_QUERY_PARAMS(String, "locationId", ZH_WORDS_GETTER("dispense.field.locationId"), "", false);
	);
	// 3.2 导出发退药记录接口实现（返回Excel文件流）
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/dispense/export", exportDispenseRecord,
		QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, DispenseRecordQuery, queryParams);
		return execExportDispenseRecord(query););

private:
	// 3.3 导出执行函数
	std::shared_ptr<OutgoingResponse> execExportDispenseRecord(const DispenseRecordQuery::Wrapper& query);
};

#undef API_TAG

// 0 取消API控制器宏
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // _DISPENSE_RECORD_CONTROLLER_
