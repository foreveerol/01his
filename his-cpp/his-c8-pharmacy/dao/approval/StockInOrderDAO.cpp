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
#include "StockInOrderDAO.hpp"

#include <jdbc/cppconn/connection.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <jdbc/cppconn/resultset.h>

#include <iostream>
#include <memory>


namespace
{
    /**
     * @brief 将数据库结果集当前行映射为入库单 DO。
     *
     * 统一处理数据库字段到 WkfSupplyRequestDO 的映射，
     * 避免多个查询方法重复编写字段赋值代码。
     *
     * @param rs 数据库查询结果集。
     * @return 映射后的入库单 DO。
     */
    oatpp::Object<domain::WkfSupplyRequestDO>
        mapToDO(sql::ResultSet* rs)
    {
        auto result = domain::WkfSupplyRequestDO::createShared();

        result->id = rs->getString("id").c_str();
        result->tenantId = rs->getString("tenant_id").c_str();

        result->createdAt = rs->getString("created_at").c_str();
        result->updatedAt = rs->getString("updated_at").c_str();
        result->createdBy = rs->getString("created_by").c_str();
        result->updatedBy = rs->getString("updated_by").c_str();

        result->isDeleted = rs->getBoolean("is_deleted");
        result->version = rs->getInt("version");

        result->busNo = rs->getString("bus_no").c_str();
        result->originalBusNo = rs->getString("original_bus_no").c_str();

        result->typeEnum = rs->getString("type_enum").c_str();
        result->statusEnum = rs->getString("status_enum").c_str();
        result->intentEnum = rs->getString("intent_enum").c_str();
        result->categoryEnum = rs->getString("category_enum").c_str();
        result->priorityEnum = rs->getString("priority_enum").c_str();

        result->summaryId = rs->getString("summary_id").c_str();
        result->deliverId = rs->getString("deliver_id").c_str();
        result->patientId = rs->getString("patient_id").c_str();

        result->itemTable = rs->getString("item_table").c_str();
        result->itemQuantity = rs->getDouble("item_quantity");
        result->totalQuantity = rs->getDouble("total_quantity");

        result->itemId = rs->getString("item_id").c_str();
        result->unitCode = rs->getString("unit_code").c_str();

        result->occurrenceTime = rs->getString("occurrence_time").c_str();
        result->practitionerId = rs->getString("practitioner_id").c_str();
        result->supplierId = rs->getString("supplier_id").c_str();

        result->reason = rs->getString("reason").c_str();

        result->sourceTypeEnum =
            rs->getString("source_type_enum").c_str();

        result->sourceLocationId =
            rs->getString("source_location_id").c_str();

        result->purposeTypeEnum =
            rs->getString("purpose_type_enum").c_str();

        result->purposeLocationId =
            rs->getString("purpose_location_id").c_str();

        result->approverId =
            rs->getString("approver_id").c_str();

        result->approvalTime =
            rs->getString("approval_time").c_str();

        result->applicantId =
            rs->getString("applicant_id").c_str();

        result->applyTime =
            rs->getString("apply_time").c_str();

        result->startTime =
            rs->getString("start_time").c_str();

        result->endTime =
            rs->getString("end_time").c_str();

        result->lotNumber =
            rs->getString("lot_number").c_str();

        result->traceNo =
            rs->getString("trace_no").c_str();

        result->price =
            rs->getDouble("price");

        result->totalPrice =
            rs->getDouble("total_price");

        result->remake =
            rs->getString("remake").c_str();

        result->profitLossPrice =
            rs->getDouble("profit_loss_price");

        return result;
    }
}


/**
 * @brief 条件分页查询入库单列表。
 */
std::vector<oatpp::Object<domain::WkfSupplyRequestDO>>
StockInOrderDAO::queryPage(
    const std::shared_ptr<sql::Connection>& conn,
    const std::string& busNo,
    const std::string& statusEnum,
    const std::string& sourceLocationId,
    const std::string& purposeLocationId,
    int offset,
    int pageSize)
{
    std::vector<oatpp::Object<domain::WkfSupplyRequestDO>> result;

    if (!conn)
    {
        return result;
    }

    if (offset < 0)
    {
        offset = 0;
    }

    if (pageSize <= 0)
    {
        pageSize = 20;
    }

    if (pageSize > 100)
    {
        pageSize = 100;
    }

    const char* sql =
        "SELECT "
        "id, tenant_id, created_at, updated_at, "
        "created_by, updated_by, is_deleted, version, "
        "bus_no, original_bus_no, type_enum, status_enum, "
        "intent_enum, category_enum, priority_enum, "
        "summary_id, deliver_id, patient_id, item_table, "
        "item_quantity, total_quantity, item_id, unit_code, "
        "occurrence_time, practitioner_id, supplier_id, reason, "
        "source_type_enum, source_location_id, "
        "purpose_type_enum, purpose_location_id, "
        "approver_id, approval_time, applicant_id, apply_time, "
        "start_time, end_time, lot_number, trace_no, "
        "price, total_price, remake, profit_loss_price "
        "FROM wkf_supply_request "
        "WHERE is_deleted = 0 "
        "AND (? = '' OR bus_no LIKE CONCAT('%', ?, '%')) "
        "AND (? = '' OR status_enum = ?) "
        "AND (? = '' OR source_location_id = ?) "
        "AND (? = '' OR purpose_location_id = ?) "
        "ORDER BY created_at DESC "
        "LIMIT ? OFFSET ?";

    try
    {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement(sql));

        int index = 1;

        pstmt->setString(index++, busNo);
        pstmt->setString(index++, busNo);

        pstmt->setString(index++, statusEnum);
        pstmt->setString(index++, statusEnum);

        pstmt->setString(index++, sourceLocationId);
        pstmt->setString(index++, sourceLocationId);

        pstmt->setString(index++, purposeLocationId);
        pstmt->setString(index++, purposeLocationId);

        pstmt->setInt(index++, pageSize);
        pstmt->setInt(index++, offset);

        std::unique_ptr<sql::ResultSet> rs(
            pstmt->executeQuery());

        while (rs->next())
        {
            result.push_back(mapToDO(rs.get()));
        }
    }
    catch (const sql::SQLException& e)
    {
        std::cerr
            << "[StockInOrderDAO] queryPage failed: "
            << e.what()
            << std::endl;
    }

    return result;
}


/**
 * @brief 根据业务单号查询入库单详情。
 */
oatpp::Object<domain::WkfSupplyRequestDO>
StockInOrderDAO::queryDetailByBusNo(
    const std::shared_ptr<sql::Connection>& conn,
    const std::string& busNo)
{
    if (!conn || busNo.empty())
    {
        return nullptr;
    }

    const char* sql =
        "SELECT "
        "id, tenant_id, created_at, updated_at, "
        "created_by, updated_by, is_deleted, version, "
        "bus_no, original_bus_no, type_enum, status_enum, "
        "intent_enum, category_enum, priority_enum, "
        "summary_id, deliver_id, patient_id, item_table, "
        "item_quantity, total_quantity, item_id, unit_code, "
        "occurrence_time, practitioner_id, supplier_id, reason, "
        "source_type_enum, source_location_id, "
        "purpose_type_enum, purpose_location_id, "
        "approver_id, approval_time, applicant_id, apply_time, "
        "start_time, end_time, lot_number, trace_no, "
        "price, total_price, remake, profit_loss_price "
        "FROM wkf_supply_request "
        "WHERE bus_no = ? "
        "AND is_deleted = 0 "
        "ORDER BY created_at DESC "
        "LIMIT 1";

    try
    {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement(sql));

        pstmt->setString(1, busNo);

        std::unique_ptr<sql::ResultSet> rs(
            pstmt->executeQuery());

        if (!rs->next())
        {
            return nullptr;
        }

        return mapToDO(rs.get());
    }
    catch (const sql::SQLException& e)
    {
        std::cerr
            << "[StockInOrderDAO] queryDetailByBusNo failed: "
            << e.what()
            << std::endl;

        return nullptr;
    }
}


/**
 * @brief 根据业务单号查询入库单基础信息。
 */
oatpp::Object<domain::WkfSupplyRequestDO>
StockInOrderDAO::queryByBusNo(
    const std::shared_ptr<sql::Connection>& conn,
    const std::string& busNo)
{
    return queryDetailByBusNo(conn, busNo);
}


/**
 * @brief 更新入库单状态为 WITHDRAWN。
 */
bool StockInOrderDAO::updateStatusToWithdrawn(
    const std::shared_ptr<sql::Connection>& conn,
    const std::string& id,
    const std::string& updatedBy,
    int version)
{
    if (!conn || id.empty())
    {
        return false;
    }

    const char* sql =
        "UPDATE wkf_supply_request "
        "SET status_enum = 'WITHDRAWN', "
        "updated_at = NOW(), "
        "updated_by = ?, "
        "version = version + 1 "
        "WHERE id = ? "
        "AND is_deleted = 0 "
        "AND status_enum = 'PENDING' "
        "AND version = ?";

    try
    {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement(sql));

        pstmt->setString(1, updatedBy);
        pstmt->setString(2, id);
        pstmt->setInt(3, version);

        return pstmt->executeUpdate() > 0;
    }
    catch (const sql::SQLException& e)
    {
        std::cerr
            << "[StockInOrderDAO] updateStatusToWithdrawn failed: "
            << e.what()
            << std::endl;

        return false;
    }
}


/**
 * @brief 更新入库单状态为 APPROVED。
 */
bool StockInOrderDAO::updateStatusToApproved(
    const std::shared_ptr<sql::Connection>& conn,
    const std::string& id,
    const std::string& approverId,
    const std::string& updatedBy,
    int version)
{
    if (!conn || id.empty() || approverId.empty())
    {
        return false;
    }

    const char* sql =
        "UPDATE wkf_supply_request "
        "SET status_enum = 'APPROVED', "
        "approver_id = ?, "
        "approval_time = NOW(), "
        "updated_at = NOW(), "
        "updated_by = ?, "
        "version = version + 1 "
        "WHERE id = ? "
        "AND is_deleted = 0 "
        "AND status_enum = 'PENDING' "
        "AND version = ?";

    try
    {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement(sql));

        pstmt->setString(1, approverId);
        pstmt->setString(2, updatedBy);
        pstmt->setString(3, id);
        pstmt->setInt(4, version);

        return pstmt->executeUpdate() > 0;
    }
    catch (const sql::SQLException& e)
    {
        std::cerr
            << "[StockInOrderDAO] updateStatusToApproved failed: "
            << e.what()
            << std::endl;

        return false;
    }
}


/**
 * @brief 更新入库单状态为 REJECTED。
 */
bool StockInOrderDAO::updateStatusToRejected(
    const std::shared_ptr<sql::Connection>& conn,
    const std::string& id,
    const std::string& reason,
    const std::string& approverId,
    const std::string& updatedBy,
    int version)
{
    if (!conn || id.empty() ||
        reason.empty() || approverId.empty())
    {
        return false;
    }

    const char* sql =
        "UPDATE wkf_supply_request "
        "SET status_enum = 'REJECTED', "
        "reason = ?, "
        "approver_id = ?, "
        "approval_time = NOW(), "
        "updated_at = NOW(), "
        "updated_by = ?, "
        "version = version + 1 "
        "WHERE id = ? "
        "AND is_deleted = 0 "
        "AND status_enum = 'PENDING' "
        "AND version = ?";

    try
    {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement(sql));

        pstmt->setString(1, reason);
        pstmt->setString(2, approverId);
        pstmt->setString(3, updatedBy);
        pstmt->setString(4, id);
        pstmt->setInt(5, version);

        return pstmt->executeUpdate() > 0;
    }
    catch (const sql::SQLException& e)
    {
        std::cerr
            << "[StockInOrderDAO] updateStatusToRejected failed: "
            << e.what()
            << std::endl;

        return false;
    }
}