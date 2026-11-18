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
 * @file WkfInventoryItemDO.hpp
 * @brief Inventory item detail DO
 *
 * One row represents the on-hand quantity of a specific itemId at a given locationId.
 */
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
