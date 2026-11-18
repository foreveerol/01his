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

#include "stdafx.h"
#include "InventoryItemDAO.hpp"

#include <jdbc/cppconn/connection.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <jdbc/cppconn/resultset.h>

#include <iostream>
#include <memory>


 /**
  * @brief 根据药品 ID 和地点 ID 查询库存记录。
  *
  * 查询指定药品在指定药房或药库中的库存信息。
  *
  * 注意：
  * 1. 不使用 SELECT *，只查询 DO 实际需要的字段；
  * 2. 使用 PreparedStatement 参数化查询，避免 SQL 注入；
  * 3. 使用 is_deleted = 0 排除软删除记录；
  * 4. LIMIT 1 保证只获取一条库存记录。
  */
oatpp::Object<domain::WkfInventoryItemDO>
InventoryItemDAO::selectByItemAndLocation(
    std::shared_ptr<sql::Connection> conn,
    const std::string& itemId,
    const std::string& locationId)
{
    // 数据库连接为空时无法执行查询。
    if (!conn)
    {
        return nullptr;
    }

    /*
     * 只查询 DO 中实际需要的字段。
     *
     * 不使用 SELECT *，避免读取数据库中不需要的数据，
     * 同时降低数据库与应用程序之间的数据传输量。
     */
    const char* sql =
        "SELECT id, name, quantity, location_id, item_id, lot_number "
        "FROM wkf_inventory_item "
        "WHERE item_id = ? "
        "  AND location_id = ? "
        "  AND is_deleted = 0 "
        "LIMIT 1";

    try
    {
        // 创建预编译 SQL。
        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement(sql));

        // 设置第一个参数：药品 ID。
        pstmt->setString(1, itemId);

        // 设置第二个参数：地点 ID。
        pstmt->setString(2, locationId);

        // 执行查询。
        std::unique_ptr<sql::ResultSet> rs(
            pstmt->executeQuery());

        // 没有查询到对应库存记录。
        if (!rs->next())
        {
            return nullptr;
        }

        /*
         * 创建库存 DO 对象。
         *
         * DAO 查询数据库后，
         * 将数据库查询结果映射成 C++ DO 对象，
         * 再交给 Service 层继续处理。
         */
        auto inventoryDO =
            domain::WkfInventoryItemDO::createShared();

        // 数据库字段 → DO 对象字段。
        inventoryDO->id =
            rs->getString("id").c_str();

        inventoryDO->name =
            rs->getString("name").c_str();

        inventoryDO->quantity =
            rs->getDouble("quantity");

        inventoryDO->locationId =
            rs->getString("location_id").c_str();

        inventoryDO->itemId =
            rs->getString("item_id").c_str();

        inventoryDO->lotNumber =
            rs->getString("lot_number").c_str();

        return inventoryDO;
    }
    catch (const sql::SQLException& e)
    {
        // 数据库异常记录日志，并向上层返回查询失败。
        std::cerr
            << "[InventoryItemDAO] "
            << "selectByItemAndLocation failed: "
            << e.what()
            << std::endl;

        return nullptr;
    }
}


/**
 * @brief 增加指定地点的药品库存数量。
 *
 * 主要用于药房入库审批通过后的库存更新。
 *
 * 直接执行：
 *
 * quantity = quantity + ?
 *
 * 由数据库完成原子累加，
 * 避免应用层执行「查询 → 计算 → 更新」带来的并发问题。
 */
bool InventoryItemDAO::increaseQuantity(
    std::shared_ptr<sql::Connection> conn,
    const std::string& itemId,
    const std::string& locationId,
    double quantity)
{
    // 数据库连接为空时无法执行更新。
    if (!conn)
    {
        return false;
    }

    /*
     * 直接在数据库中完成库存累加。
     *
     * 不使用 SELECT *。
     *
     * quantity = quantity + ?
     * 表示在原有库存数量的基础上增加本次入库数量。
     *
     * updated_at = NOW()
     * 更新最后修改时间。
     */
    const char* sql =
        "UPDATE wkf_inventory_item "
        "SET quantity = quantity + ?, "
        "    updated_at = NOW() "
        "WHERE item_id = ? "
        "  AND location_id = ? "
        "  AND is_deleted = 0";

    try
    {
        // 创建预编译 SQL。
        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement(sql));

        // 设置增加的库存数量。
        pstmt->setDouble(1, quantity);

        // 设置药品 ID。
        pstmt->setString(2, itemId);

        // 设置库存所属地点 ID。
        pstmt->setString(3, locationId);

        // 执行 UPDATE。
        int affectedRows =
            pstmt->executeUpdate();

        /*
         * affectedRows > 0：
         * 表示存在符合条件的库存记录，并成功执行更新。
         *
         * affectedRows == 0：
         * 表示没有找到符合条件的库存记录，
         * 或数据库没有产生更新。
         */
        return affectedRows > 0;
    }
    catch (const sql::SQLException& e)
    {
        // 数据库异常记录日志。
        std::cerr
            << "[InventoryItemDAO] "
            << "increaseQuantity failed: "
            << e.what()
            << std::endl;

        return false;
    }
}