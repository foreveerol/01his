 /*
 * Copyright Zero One Star. All rights reserved.
 *
 * @Author: stellablack528
 * @Date: 2026/07/27 18:00:00
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file InventoryItemDAO.h
 * @brief 库存明细数据访问对象。
 *
 * 负责对 wkf_inventory_item 库存明细表进行数据库操作。
 *
 * 主要用于：
 * 1. 根据药品 ID 和地点 ID 查询库存记录；
 * 2. 在入库审批通过后增加指定地点的药品库存数量。
 *
 * DAO 层只负责数据库访问，不负责具体业务规则判断。
 * 例如「只有审批通过后才能增加库存」属于 Service 层业务逻辑。
 */

#pragma once

#include "domain/do/approval/WkfInventoryItemDO.hpp"

#include <memory>
#include <string>

#include <jdbc/cppconn/connection.h>

 /**
  * @brief 库存明细 DAO。
  *
  * 封装 wkf_inventory_item 表相关的数据访问操作，
  * 为 Service 层提供统一的库存数据访问接口。
  */
class InventoryItemDAO
{
public:

    /**
     * @brief 根据药品 ID 和地点 ID 查询库存记录。
     *
     * 用于确定指定药品在指定药房或药库中的库存信息。
     *
     * 查询条件：
     * - item_id：药品 ID
     * - location_id：库存所属地点 ID
     * - is_deleted = 0：排除已软删除的数据
     *
     * @param conn 数据库连接。
     * @param itemId 药品 ID。
     * @param locationId 药房或药库地点 ID。
     *
     * @return
     * 查询成功返回库存 DO 对象；
     * 未查询到记录或数据库操作失败时返回 nullptr。
     */
    static oatpp::Object<domain::WkfInventoryItemDO>
        selectByItemAndLocation(
            std::shared_ptr<sql::Connection> conn,
            const std::string& itemId,
            const std::string& locationId);

    /**
     * @brief 增加指定地点的药品库存数量。
     *
     * 主要用于药房入库审批通过后的库存更新。
     *
     * 使用：
     * quantity = quantity + ?
     *
     * 直接在数据库层完成数量累加，减少「先查询库存 → C++ 计算 → 再更新」
     * 所产生的并发风险。
     *
     * @param conn 数据库连接。
     * @param itemId 药品 ID。
     * @param locationId 药房或药库地点 ID。
     * @param quantity 本次需要增加的库存数量。
     *
     * @return
     * true 表示数据库成功更新库存；
     * false 表示更新失败或没有符合条件的库存记录。
     */
    static bool increaseQuantity(
        std::shared_ptr<sql::Connection> conn,
        const std::string& itemId,
        const std::string& locationId,
        double quantity);
};