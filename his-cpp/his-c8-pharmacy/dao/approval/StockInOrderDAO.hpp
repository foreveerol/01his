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
 * @file StockInOrderDAO.h
 * @brief 药房入库单数据访问对象。
 *
 * 负责对 wkf_supply_request 表执行数据库访问操作，
 * 为药房入库单查询、撤回、审批通过以及驳回等业务提供数据访问能力。
 *
 * 主要功能：
 * 1. 条件分页查询入库单列表；
 * 2. 根据业务单号查询入库单详情；
 * 3. 更新入库单状态为 WITHDRAWN；
 * 4. 更新入库单状态为 APPROVED；
 * 5. 更新入库单状态为 REJECTED。
 *
 * 数据访问层只负责数据库操作，
 * 具体业务规则由 Service 层负责处理。
 *
 * SQL 查询遵循以下规范：
 * - 不使用 SELECT *，仅查询业务所需字段；
 * - 使用 PreparedStatement 参数化查询，避免 SQL 注入；
 * - 查询条件包含 is_deleted = 0，过滤已软删除数据；
 * - 状态更新增加原状态判断，避免重复审批；
 * - 使用 version 字段进行乐观锁控制。
 */

#pragma once

#include "domain/do/approval/WkfSupplyRequestDO.hpp"

#include <jdbc/cppconn/connection.h>
#include <memory>
#include <string>
#include <vector>


 /**
  * @brief 药房入库单数据访问对象。
  *
  * 负责 wkf_supply_request 表的数据访问操作。
  *
  * DAO 层不负责判断“当前用户是否有审批权限”等业务规则，
  * 只负责执行 Service 层要求的数据查询与数据库更新。
  */
class StockInOrderDAO
{
public:

    /**
     * @brief 条件分页查询药房入库单列表。
     *
     * 支持按照业务单号、供应状态、源药库以及目的药房
     * 对入库单进行条件过滤，并返回分页数据。
     *
     * 查询结果包含前端列表所需的主要信息：
     * - 入库单业务编号；
     * - 入库单状态；
     * - 供应类型；
     * - 制单人；
     * - 制单时间；
     * - 申请人；
     * - 药品 ID；
     * - 入库数量；
     * - 源药库 ID；
     * - 目的药房 ID；
     * - 单价及总金额；
     * - 追溯码；
     * - 审批人及审批时间。
     *
     * @param conn 数据库连接。
     * @param busNo 入库单业务编号，可为空。
     * @param statusEnum 入库单状态，可为空。
     * @param sourceLocationId 源药库 ID，可为空。
     * @param purposeLocationId 目的药房 ID，可为空。
     * @param offset 分页起始位置。
     * @param pageSize 每页数据条数。
     *
     * @return 当前分页范围内的入库单 DO 列表。
     */
    static std::vector<oatpp::Object<domain::WkfSupplyRequestDO>>
        queryPage(
            const std::shared_ptr<sql::Connection>& conn,
            const std::string& busNo,
            const std::string& statusEnum,
            const std::string& sourceLocationId,
            const std::string& purposeLocationId,
            int offset,
            int pageSize);


    /**
     * @brief 根据业务单号查询入库单详情。
     *
     * 用于获取单条入库单的完整业务数据，
     * 包括前端详情页面需要的制单信息、源药库、
     * 目的药房、追溯码、价格以及审批信息等。
     *
     * @param conn 数据库连接。
     * @param busNo 入库单业务编号。
     *
     * @return 入库单 DO。
     *         查询不到数据时返回 nullptr。
     */
    static oatpp::Object<domain::WkfSupplyRequestDO>
        queryDetailByBusNo(
            const std::shared_ptr<sql::Connection>& conn,
            const std::string& busNo);


    /**
     * @brief 根据业务单号查询入库单基础信息。
     *
     * 主要用于撤回、审批通过和驳回等审批操作，
     * 获取当前入库单的状态及业务数据。
     *
     * @param conn 数据库连接。
     * @param busNo 入库单业务编号。
     *
     * @return 入库单 DO。
     *         查询不到数据时返回 nullptr。
     */
    static oatpp::Object<domain::WkfSupplyRequestDO>
        queryByBusNo(
            const std::shared_ptr<sql::Connection>& conn,
            const std::string& busNo);


    /**
     * @brief 将入库单状态更新为 WITHDRAWN。
     *
     * 只有当前状态为 PENDING 的入库单才允许执行撤回。
     *
     * @param conn 数据库连接。
     * @param id 入库单主键。
     * @param updatedBy 执行撤回操作的用户 ID。
     * @param version 当前数据版本号。
     *
     * @return true 表示更新成功；
     *         false 表示更新失败或数据版本已发生变化。
     */
    static bool
        updateStatusToWithdrawn(
            const std::shared_ptr<sql::Connection>& conn,
            const std::string& id,
            const std::string& updatedBy,
            int version);


    /**
     * @brief 将入库单状态更新为 APPROVED。
     *
     * 审批通过后记录审批人和审批时间。
     * 只有当前状态为 PENDING 的入库单才允许审批通过。
     *
     * @param conn 数据库连接。
     * @param id 入库单主键。
     * @param approverId 审批人 ID。
     * @param updatedBy 最后修改人 ID。
     * @param version 当前数据版本号。
     *
     * @return true 表示更新成功；
     *         false 表示更新失败或数据版本已发生变化。
     */
    static bool
        updateStatusToApproved(
            const std::shared_ptr<sql::Connection>& conn,
            const std::string& id,
            const std::string& approverId,
            const std::string& updatedBy,
            int version);


    /**
     * @brief 将入库单状态更新为 REJECTED。
     *
     * 驳回后记录驳回原因、审批人以及审批时间。
     * 只有当前状态为 PENDING 的入库单才允许执行驳回。
     *
     * @param conn 数据库连接。
     * @param id 入库单主键。
     * @param reason 驳回原因。
     * @param approverId 审批人 ID。
     * @param updatedBy 最后修改人 ID。
     * @param version 当前数据版本号。
     *
     * @return true 表示更新成功；
     *         false 表示更新失败或数据版本已发生变化。
     */
    static bool
        updateStatusToRejected(
            const std::shared_ptr<sql::Connection>& conn,
            const std::string& id,
            const std::string& reason,
            const std::string& approverId,
            const std::string& updatedBy,
            int version);
};
