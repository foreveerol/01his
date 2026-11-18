#pragma once

#ifndef _MEDICATIONDEFINITIONQUERY_H_
#define _MEDICATIONDEFINITIONQUERY_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class MedicationDefinitionQuery : public PageQuery
{
    DTO_INIT(MedicationDefinitionQuery, PageQuery);

    DTO_FIELD(String, keyword);
    DTO_FIELD(String, busNo);
    DTO_FIELD(String, categoryCode);
    DTO_FIELD(String, manufacturerText);
    DTO_FIELD(String, statusEnum);
    DTO_FIELD(Boolean, activeFlag) = true;
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_MEDICATIONDEFINITIONQUERY_H_