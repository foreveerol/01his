#pragma once
#ifndef _INVENTORYCHECKREMOVEDTO_H_
#define _INVENTORYCHECKREMOVEDTO_H_

#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class InventoryCheckWithdrawDTO : public oatpp::DTO
{
    DTO_INIT(InventoryCheckWithdrawDTO, DTO);

    // 盘点单ID
    API_DTO_FIELD_DEFAULT(String, checkId, ZH_WORDS_GETTER("pharmacy.inventory-check.field.checkId"));
    //单据状态
    API_DTO_FIELD_DEFAULT(String, status, ZH_WORDS_GETTER("pharmacy.inventory-check.field.status"));
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_INVENTORYCHECKREMOVEDTO_H_