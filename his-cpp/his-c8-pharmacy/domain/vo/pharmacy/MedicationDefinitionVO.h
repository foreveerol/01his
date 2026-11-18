#pragma once
#ifndef _MEDICATIONDEFINITIONVO_H_
#define _MEDICATIONDEFINITIONVO_H_

#include "../../GlobalInclude.h"
#include "../../dto/pharmacy/MedicationDefinitionDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class MedicationDefinitionPageJsonVO
    : public JsonVO<MedicationDefinitionPageDTO::Wrapper>
{
    DTO_INIT(
        MedicationDefinitionPageJsonVO,
        JsonVO<MedicationDefinitionPageDTO::Wrapper>
    );
};



#include OATPP_CODEGEN_END(DTO)

#endif // !_MEDICATIONDEFINITIONVO_H_