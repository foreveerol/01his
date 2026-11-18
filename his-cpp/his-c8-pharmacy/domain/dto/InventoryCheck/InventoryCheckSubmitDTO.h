#pragma once

#ifndef _INVENTORYCHECKDTO_H_
#define _INVENTORYCHECKDTO_H_
#include "../..//GlobalInclude.h"


#include OATPP_CODEGEN_BEGIN(DTO)

//药房盘点单中表格单行明细
class InventoryCheckSubmitItemDTO : public oatpp::DTO
{
    DTO_INIT(InventoryCheckSubmitItemDTO, DTO);

    // 明细ID
    API_DTO_FIELD_DEFAULT(String, detailId, ZH_WORDS_GETTER("pharmacy.inventory-check.field.detailId"));
    // 药品名称
    API_DTO_FIELD_REQUIRED(String, drugName, ZH_WORDS_GETTER("pharmacy.inventory-check.field.drugName"), true);
    // 规格
    API_DTO_FIELD_DEFAULT(String, specification, ZH_WORDS_GETTER("pharmacy.inventory-check.field.specification"));
    //厂家
    API_DTO_FIELD_DEFAULT(String, manufacturer, ZH_WORDS_GETTER("pharmacy.stockin.field.manufacturer"));
    // 批号
    API_DTO_FIELD_DEFAULT(String, batchNo, ZH_WORDS_GETTER("pharmacy.inventory-check.field.batchNo"));
    // 系统库存数（账面数量）
    API_DTO_FIELD_DEFAULT(Float64, systemQty, ZH_WORDS_GETTER("pharmacy.inventory-check.field.systemQty"));
    // 实盘数
    API_DTO_FIELD_REQUIRED(Float64, actualQty, ZH_WORDS_GETTER("pharmacy.inventory-check.field.actualQty"), true);
    // 差异数（盈亏数量）
    API_DTO_FIELD_DEFAULT(Float64, diffQty, ZH_WORDS_GETTER("pharmacy.inventory-check.field.diffQty"));
    // 药品单价
    API_DTO_FIELD_DEFAULT(Float64, drugPrice, ZH_WORDS_GETTER("pharmacy.inventory-check.field.drugPrice"));
    // 实盘金额
    API_DTO_FIELD_DEFAULT(String, actualPrice, ZH_WORDS_GETTER("pharmacy.inventory-check.field.actualPrice"));
    // 盈亏金额
    API_DTO_FIELD_DEFAULT(String, diffPrice, ZH_WORDS_GETTER("pharmacy.inventory-check.field.diffPrice"));
    //备注
    API_DTO_FIELD_DEFAULT(String, remark, ZH_WORDS_GETTER("pharmacy.inventory-check.field.remark"));
};

class InventoryCheckSubmitDTO : public oatpp::DTO
{
    DTO_INIT(InventoryCheckDTO, DTO);

    // 盘点单ID
    API_DTO_FIELD_DEFAULT(String, checkId, ZH_WORDS_GETTER("pharmacy.inventory-check.field.checkId"));
    // 盘点药房名称
    API_DTO_FIELD_REQUIRED(String, pharmacyId, ZH_WORDS_GETTER("pharmacy.inventory-check.field.pharmacyName"), false);
    // 项目类型（药品/耗材等）
    API_DTO_FIELD_REQUIRED(String, itemType, ZH_WORDS_GETTER("pharmacy.inventory-check.field.itemType"), false);
};



#include OATPP_CODEGEN_END(DTO)
#endif // _INVENTORYCHECKDTO_H_