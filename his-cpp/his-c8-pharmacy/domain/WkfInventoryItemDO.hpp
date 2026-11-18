// domain/WkfInventoryItemDO.hpp
#pragma once
#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace domain {

#include OATPP_CODEGEN_BEGIN(DTO)

    class WkfInventoryItemDO : public oatpp::DTO {
        DTO_INIT(WkfInventoryItemDO, DTO)

            DTO_FIELD(Int64, id);
        DTO_FIELD(String, name);
        DTO_FIELD(Float64, quantity);
        DTO_FIELD(Int64, locationId);
        DTO_FIELD(Int64, itemId);
        DTO_FIELD(String, lotNumber);
    };

#include OATPP_CODEGEN_END(DTO)

}  // namespace domain