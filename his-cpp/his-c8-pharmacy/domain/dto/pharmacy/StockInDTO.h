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
#ifndef _STOCKIN_DTO_
#define _STOCKIN_DTO_
#include "../../GlobalInclude.h"
#include "domain/dto/PageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 药房入库单列表项DTO
 */
class StockInListItemDTO : public oatpp::DTO
{
	DTO_INIT(StockInListItemDTO, DTO);
	// 入库单号
	DTO_FIELD(String, orderNo);
	DTO_FIELD_INFO(orderNo) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.orderNo");
	}
	// 供应商名称
	DTO_FIELD(String, supplierName);
	DTO_FIELD_INFO(supplierName) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.supplierName");
	}
	// 入库日期
	DTO_FIELD(String, stockInDate);
	DTO_FIELD_INFO(stockInDate) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.stockInDate");
	}
	// 药品总数
	DTO_FIELD(Int32, drugCount);
	DTO_FIELD_INFO(drugCount) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.drugCount");
	}
	// 总金额
	DTO_FIELD(Float64, totalAmount);
	DTO_FIELD_INFO(totalAmount) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.totalAmount");
	}
	// 单据状态（草稿/审批中/已入库/已驳回）
	DTO_FIELD(String, status);
	DTO_FIELD_INFO(status) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.status");
	}
	// 制单人
	DTO_FIELD(String, creator);
	DTO_FIELD_INFO(creator) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.creator");
	}
public:
	StockInListItemDTO() { this->drugCount = Int32(0); this->totalAmount = Float64(0.0); }
};

/**
 * 药房入库单分页DTO
 */
class StockInPageDTO : public PageDTO<StockInListItemDTO::Wrapper>
{
	DTO_INIT(StockInPageDTO, PageDTO<StockInListItemDTO::Wrapper>);
};

/**
 * 入库单药品明细DTO
 */
class StockInDrugItemDTO : public oatpp::DTO
{
	DTO_INIT(StockInDrugItemDTO, DTO);
	// 明细ID
	DTO_FIELD(String, detailId);
	DTO_FIELD_INFO(detailId) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.detailId");
	}
	// 药品名称
	DTO_FIELD(String, drugName);
	DTO_FIELD_INFO(drugName) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.drugName");
	}
	// 规格
	DTO_FIELD(String, specification);
	DTO_FIELD_INFO(specification) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.specification");
	}
	// 生产厂家
	DTO_FIELD(String, manufacturer);
	DTO_FIELD_INFO(manufacturer) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.manufacturer");
	}
	// 批号
	DTO_FIELD(String, batchNo);
	DTO_FIELD_INFO(batchNo) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.batchNo");
	}
	// 有效期
	DTO_FIELD(String, expiryDate);
	DTO_FIELD_INFO(expiryDate) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.expiryDate");
	}
	// 单位
	DTO_FIELD(String, unit);
	DTO_FIELD_INFO(unit) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.unit");
	}
	// 数量
	DTO_FIELD(Int32, quantity);
	DTO_FIELD_INFO(quantity) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.quantity");
	}
	// 单价
	DTO_FIELD(Float64, unitPrice);
	DTO_FIELD_INFO(unitPrice) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.unitPrice");
	}
public:
	StockInDrugItemDTO() { this->quantity = Int32(0); this->unitPrice = Float64(0.0); }
};

/**
 * 入库单详情DTO
 */
class StockInDTO : public oatpp::DTO
{
	DTO_INIT(StockInDTO, DTO);
	// 入库单号
	DTO_FIELD(String, orderNo);
	DTO_FIELD_INFO(orderNo) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.orderNo");
	}
	// 供应商名称
	DTO_FIELD(String, supplierName);
	DTO_FIELD_INFO(supplierName) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.supplierName");
	}
	// 入库类型
	DTO_FIELD(String, stockInType);
	DTO_FIELD_INFO(stockInType) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.stockInType");
	}
	// 入库日期
	DTO_FIELD(String, stockInDate);
	DTO_FIELD_INFO(stockInDate) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.stockInDate");
	}
	// 单据状态
	DTO_FIELD(String, status);
	DTO_FIELD_INFO(status) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.status");
	}
	// 驳回原因
	DTO_FIELD(String, rejectReason);
	DTO_FIELD_INFO(rejectReason) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.rejectReason");
	}
	// 备注
	DTO_FIELD(String, remark);
	DTO_FIELD_INFO(remark) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.remark");
	}
	// 药品明细列表
	DTO_FIELD(oatpp::List<StockInDrugItemDTO::Wrapper>, drugList);
	DTO_FIELD_INFO(drugList) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.drugList");
	}
};

/**
 * 入库单保存请求DTO
 */
class StockInSaveDTO : public oatpp::DTO
{
	DTO_INIT(StockInSaveDTO, DTO);
	// 入库单号（新增时为空，修改时必填）
	DTO_FIELD(String, orderNo);
	DTO_FIELD_INFO(orderNo) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.orderNo");
	}
	// 供应商名称
	DTO_FIELD(String, supplierName);
	DTO_FIELD_INFO(supplierName) {
		info->required = true;
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.supplierName");
	}
	// 入库类型
	DTO_FIELD(String, stockInType);
	DTO_FIELD_INFO(stockInType) {
		info->required = true;
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.stockInType");
	}
	// 备注
	DTO_FIELD(String, remark);
	DTO_FIELD_INFO(remark) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.remark");
	}
	// 药品明细列表
	DTO_FIELD(oatpp::List<StockInDrugItemDTO::Wrapper>, drugList);
	DTO_FIELD_INFO(drugList) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.drugList");
	}
};

/**
 * 入库单审批操作请求DTO
 */
class StockInApprovalDTO : public oatpp::DTO
{
	DTO_INIT(StockInApprovalDTO, DTO);
	// 入库单号
	DTO_FIELD(String, orderNo);
	DTO_FIELD_INFO(orderNo) {
		info->required = true;
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.orderNo");
	}
	// 审批意见
	DTO_FIELD(String, approvalComment);
	DTO_FIELD_INFO(approvalComment) {
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.approvalComment");
	}
};

/**
 * 入库单删除请求DTO
 */
class StockInRemoveDTO : public oatpp::DTO
{
	DTO_INIT(StockInRemoveDTO, DTO);
	// 入库单号
	DTO_FIELD(String, orderNo);
	DTO_FIELD_INFO(orderNo) {
		info->required = true;
		info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.orderNo");
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_STOCKIN_DTO_
