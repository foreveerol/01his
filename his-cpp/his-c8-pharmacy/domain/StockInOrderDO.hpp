// domain/StockInOrderDO.hpp
#pragma once
#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace domain {

#include OATPP_CODEGEN_BEGIN(DTO)

    class StockInOrderDO : public oatpp::DTO {
        DTO_INIT(StockInOrderDO, DTO)

            DTO_FIELD(Int64, id);
        DTO_FIELD(String, busNo);
        DTO_FIELD(String, statusEnum);
        DTO_FIELD(String, rejectReason);
        DTO_FIELD(Int64, handlerId);
        DTO_FIELD(String, handlerName);
        DTO_FIELD(Int64, sourceLocationId);
        DTO_FIELD(String, sourceLocationName);
        DTO_FIELD(Int64, targetLocationId);
        DTO_FIELD(String, targetLocationName);
        DTO_FIELD(Int64, createdAt);
        DTO_FIELD(Int64, updatedAt);
    };

#include OATPP_CODEGEN_END(DTO)

}  // namespace domain