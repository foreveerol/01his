
#pragma once
#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace domain {

#include OATPP_CODEGEN_BEGIN(DTO)

    class AdmLocationDO : public oatpp::DTO {
        DTO_INIT(AdmLocationDO, DTO)

            DTO_FIELD(Int64, id);
        DTO_FIELD(String, name);
        DTO_FIELD(String, busNo);
        DTO_FIELD(String, statusEnum);
        DTO_FIELD(String, formEnum);
        DTO_FIELD(Int64, parentId);
    };

#include OATPP_CODEGEN_END(DTO)

}  
