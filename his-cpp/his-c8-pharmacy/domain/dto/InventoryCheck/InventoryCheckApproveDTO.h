#pragma once
#ifndef _INVENTORYCHECKREMOVEDTO_H_
#define _INVENTORYCHECKREMOVEDTO_H_

#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class InventoryCheckApproveDTO : public oatpp::DTO
{
    DTO_INIT(InventoryCheckApproveDTO, DTO);

    // 盘点单ID
    API_DTO_FIELD_DEFAULT(String, checkId, ZH_WORDS_GETTER("pharmacy.inventory-check.field.checkId"));
    //单据状态
    API_DTO_FIELD_DEFAULT(String, status, ZH_WORDS_GETTER("pharmacy.inventory-check.field.status"));
    // 明细ID
    API_DTO_FIELD_DEFAULT(String, detailId, ZH_WORDS_GETTER("pharmacy.inventory-check.field.detailId"));
    // 药品名称
    API_DTO_FIELD_DEFAULT(String, drugName, ZH_WORDS_GETTER("pharmacy.inventory-check.field.drugName"), true);
    // 规格
    API_DTO_FIELD_DEFAULT(String, specification, ZH_WORDS_GETTER("pharmacy.inventory-check.field.specification"));
    // 药品单价
    API_DTO_FIELD_DEFAULT(Float64, diffQty, ZH_WORDS_GETTER("pharmacy.inventory-check.field.drugPrice"));
    // 实盘金额
    API_DTO_FIELD_DEFAULT(String, diffReason, ZH_WORDS_GETTER("pharmacy.inventory-check.field.actualPrice"));
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_INVENTORYCHECKREMOVEDTO_H_
