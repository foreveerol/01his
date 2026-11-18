#pragma once
#ifndef _MEDICATIONDEFINITIONDTO_H_
#define _MEDICATIONDEFINITIONDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class MedicationOptionDTO : public oatpp::DTO
{
    DTO_INIT(MedicationOptionDTO, DTO);

    DTO_FIELD(Int64, id);
    DTO_FIELD(String, busNo);
    DTO_FIELD(String, name);
    DTO_FIELD(String, nameEn);
    DTO_FIELD(String, pyStr);
    DTO_FIELD(String, wbStr);
    DTO_FIELD(String, merchandiseName);
    DTO_FIELD(String, specification);
    DTO_FIELD(String, manufacturerText);
    DTO_FIELD(String, purchaseUnitCode);
    DTO_FIELD(String, splitUnitCode);
    DTO_FIELD(String, stockUnitCode);
    DTO_FIELD(String, packageUnitCode);
    DTO_FIELD(String, statusEnum);
};

class MedicationDefinitionPageDTO
    : public PageDTO<MedicationOptionDTO::Wrapper>
{
    DTO_INIT(
        MedicationDefinitionPageDTO,
        PageDTO<MedicationOptionDTO::Wrapper>
    );
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_MEDICATIONDEFINITIONDTO_H_