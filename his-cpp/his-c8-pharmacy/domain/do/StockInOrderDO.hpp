/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/07/21 00:00:00

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
/**
 * @file StockInOrderDO.hpp
 * @brief Stock-in order header DO
 *
 * Field names follow the database column convention (snake_case exposed as camelCase).
 */
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
