/*
 Copyright Zero One Star. All rights reserved.

 @Author: stellablack528
 @Date: 2026/07/19 18:00:00

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
 * @brief 库存明细表 DO。
 *
 * 对应数据库 wkf_inventory_item 表，用于映射药品库存明细数据。
 *
 * 一条库存记录表示某个药品（itemId）在指定地点（locationId）
 * 的库存信息，可用于药房入库审批通过后的库存数量更新。
 */

#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace domain {

#include OATPP_CODEGEN_BEGIN(DTO)

    /**
     * @brief 库存明细数据对象。
     *
     * 用于完成数据库 wkf_inventory_item 表记录与 C++ 对象之间的数据映射。
     *
     * 主要业务用途：
     * 1. 根据 itemId 和 locationId 查询指定药品的库存记录；
     * 2. 获取当前药品库存数量；
     * 3. 在入库审批通过后，为库存数量更新提供数据模型支持。
     */
    class WkfInventoryItemDO : public oatpp::DTO {
        DTO_INIT(WkfInventoryItemDO, DTO)

            /**
             * @brief 库存记录主键。
             */
            DTO_FIELD(String, id);

        /**
         * @brief 药品名称。
         */
        DTO_FIELD(String, name);

        /**
         * @brief 当前库存数量。
         */
        DTO_FIELD(Float64, quantity);

        /**
         * @brief 库存所属地点ID。
         *
         * 用于关联药库或药房等库存地点。
         */
        DTO_FIELD(String, locationId);

        /**
         * @brief 药品ID。
         *
         * 用于标识当前库存记录对应的药品。
         */
        DTO_FIELD(String, itemId);

        /**
         * @brief 药品批号。
         *
         * 用于区分同一种药品的不同批次。
         */
        DTO_FIELD(String, lotNumber);

        /**
         * @brief 乐观锁版本号。
         *
         * 用于并发更新库存时进行版本控制。
         */
        DTO_FIELD(Int32, version);
    };

#include OATPP_CODEGEN_END(DTO)

} // namespace domain