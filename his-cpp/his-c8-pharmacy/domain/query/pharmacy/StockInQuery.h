#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: zjb517
 @Date: 2026/07/19 18:00:00

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
#ifndef _STOCKIN_QUERY_
#define _STOCKIN_QUERY_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 药房入库单查询对象
 */
class StockInQuery : public PageQuery
{
	DTO_INIT(StockInQuery, PageQuery);
	// 入库单号
	DTO_FIELD(String, orderNo);
	DTO_FIELD_INFO(orderNo) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.orderNo");
	}
	// 供应商名称（模糊匹配）
	DTO_FIELD(String, supplierName);
	DTO_FIELD_INFO(supplierName) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.supplierName");
	}
	// 单据状态
	DTO_FIELD(String, status);
	DTO_FIELD_INFO(status) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.status");
	}
	// 开始日期
	DTO_FIELD(String, startDate);
	DTO_FIELD_INFO(startDate) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.startDate");
	}
	// 结束日期
	DTO_FIELD(String, endDate);
	DTO_FIELD_INFO(endDate) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.endDate");
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_STOCKIN_QUERY_
