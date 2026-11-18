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
 * @file PharmacyStockInApprovalService.cpp
 * @brief 药房入库审批业务服务实现。
 *
 * 负责实现药房入库单撤回、审批通过和驳回三个核心业务流程。
 *
 * Service 层主要负责：
 * 1. 接收 Controller 传递的 DTO；
 * 2. 校验业务参数；
 * 3. 调用 StockInOrderDAO 查询或更新入库单；
 * 4. 审批通过时调用 InventoryItemDAO 更新库存；
 * 5. 根据业务处理结果创建对应的 VO；
 * 6. 将业务处理结果返回给 Controller。
 */

#include "StockInApprovalService.hpp"

#include "dao/approval/StockInOrderDAO.hpp"
#include "dao/approval/InventoryItemDAO.hpp"

#include <jdbc/cppconn/connection.h>

#include <memory>
#include <string>


namespace
{

    /**
     * @brief 创建“入库单不存在”失败响应。
     *
     * 当 DAO 根据业务号查询不到对应入库单时，
     * Service 层通过该方法统一生成失败响应。
     *
     * @return 入库单不存在的失败结果 VO。
     */
    oatpp::Object<vo::StockInOperationResultVO>
        notFoundVO()
    {
        return makeFailVO(
            ZH_WORDS_GETTER(
                "stockin.error.not-found"
            )
        );
    }


    /**
     * @brief 创建“数据库操作失败”失败响应。
     *
     * 当 DAO 执行数据库更新操作失败时，
     * Service 层通过该方法统一生成失败响应。
     *
     * @return 数据库操作失败的结果 VO。
     */
    oatpp::Object<vo::StockInOperationResultVO>
        dbErrorVO()
    {
        return makeFailVO(
            ZH_WORDS_GETTER(
                "stockin.error.db-error"
            )
        );
    }

} // namespace


/**
 * @brief 撤回药房入库审批单。
 *
 * 业务流程：
 *
 * 1. 校验请求 DTO 及业务号 busNo；
 * 2. 根据 busNo 查询入库单；
 * 3. 判断入库单是否存在；
 * 4. 判断当前状态是否为 PENDING；
 * 5. 将入库单状态更新为 WITHDRAWN；
 * 6. 返回撤回成功或失败结果。
 *
 * @param dto 撤回入库单请求 DTO。
 *
 * @return 撤回操作结果 VO。
 */
oatpp::Object<vo::StockInOperationResultVO>
PharmacyStockInApprovalService::withdraw(
    const oatpp::Object<
    dto::StockInWithdrawDTO>& dto)
{
    // Controller 层已经进行过参数校验，
    // Service 层再次进行兜底校验，避免非法数据直接进入业务逻辑。
    if (!dto || !dto->busNo || dto->busNo->empty())
    {
        return makeFailVO(
            ZH_WORDS_GETTER(
                "stockin.error.busNo-empty"
            )
        );
    }


    std::string busNo = *dto->busNo;


    /*
     * 根据业务号查询入库单。
     *
     * DAO 负责具体 SQL 操作，
     * Service 只负责组织业务流程。
     */
     // TODO: 数据库连接应由项目统一的数据库连接管理模块提供。
    std::shared_ptr<sql::Connection> conn = nullptr;


    auto orderDO =
        StockInOrderDAO::queryByBusNo(
            conn,
            busNo
        );


    // 未查询到入库单。
    if (!orderDO)
    {
        return notFoundVO();
    }


    /*
     * 只有待审批状态的入库单才能执行撤回。
     *
     * 这里的状态值需要与数据库实际枚举定义保持一致。
     */
    if (!orderDO->statusEnum ||
        *orderDO->statusEnum != "PENDING")
    {
        return notPendingApprovalVO();
    }


    /*
     * 更新入库单状态。
     *
     * DAO 层通过 WHERE 条件再次限制：
     * status_enum = 'PENDING'
     *
     * 这样可以避免并发情况下已经被其他请求处理的单据
     * 被重复修改。
     */
    bool success =
        StockInOrderDAO::updateStatusToWithdrawn(
            conn,
            *orderDO->id,
            "system",  // updatedBy
            orderDO->version ? *orderDO->version : 0);


    if (!success)
    {
        return dbErrorVO();
    }


    // 返回撤回成功结果。
    return withdrawSuccessVO(
        dto->busNo
    );
}


/**
 * @brief 审批通过药房入库单。
 *
 * 业务流程：
 *
 * 1. 校验请求 DTO 及业务号 busNo；
 * 2. 查询入库单；
 * 3. 校验入库单是否存在；
 * 4. 校验当前状态是否为 PENDING；
 * 5. 更新入库单状态为 APPROVED；
 * 6. 记录审批人；
 * 7. 根据入库单中的药品和数量增加对应药房库存；
 * 8. 返回审批成功结果。
 *
 * @param dto 审批通过请求 DTO。
 *
 * @return 审批操作结果 VO。
 */
oatpp::Object<vo::StockInOperationResultVO>
PharmacyStockInApprovalService::approve(
    const oatpp::Object<
    dto::StockInApprovalDTO>& dto)
{
    // Service 层参数兜底校验。
    if (!dto || !dto->busNo || dto->busNo->empty())
    {
        return makeFailVO(
            ZH_WORDS_GETTER(
                "stockin.error.busNo-empty"
            )
        );
    }


    std::string busNo = *dto->busNo;


    // TODO: 数据库连接应由项目统一的数据库连接管理模块提供。
    std::shared_ptr<sql::Connection> conn = nullptr;


    /*
     * 查询待审批入库单。
     */
    auto orderDO =
        StockInOrderDAO::queryByBusNo(
            conn,
            busNo
        );


    // 入库单不存在。
    if (!orderDO)
    {
        return notFoundVO();
    }


    // 只有 PENDING 状态的入库单才能审批。
    if (!orderDO->statusEnum ||
        *orderDO->statusEnum != "PENDING")
    {
        return notPendingApprovalVO();
    }


    /*
     * 获取审批人。
     *
     * 实际项目中 approverId 应从当前登录用户的
     * Session、JWT 或统一用户上下文中获取。
     *
     * 当前阶段暂时从 DTO 中获取。
     */
    std::string approverId = "system";

    if (dto->approverId)
    {
        approverId = *dto->approverId;
    }


    /*
     * 更新入库单审批状态。
     *
     * DAO 层负责执行具体 UPDATE SQL。
     */
    bool success =
        StockInOrderDAO::updateStatusToApproved(
            conn,
            *orderDO->id,
            approverId,
            "system",  // updatedBy
            orderDO->version ? *orderDO->version : 0);


    if (!success)
    {
        return dbErrorVO();
    }


    /*
     * 审批通过后，根据入库单中的药品信息增加库存。
     *
     * itemId：
     *     药品标识。
     *
     * purposeLocationId：
     *     目的地点，即药房或药库。
     *
     * itemQuantity：
     *     本次入库数量。
     */
    if (orderDO->itemId &&
        orderDO->itemQuantity &&
        orderDO->purposeLocationId &&
        *orderDO->itemQuantity > 0)
    {
        bool inventorySuccess =
            InventoryItemDAO::increaseQuantity(
                conn,
                *orderDO->itemId,
                *orderDO->purposeLocationId,
                *orderDO->itemQuantity
            );


        /*
         * 库存更新失败时不能简单忽略。
         *
         * 正式业务中应当通过事务保证：
         *
         * 入库单审批状态更新
         *         +
         * 库存数量增加
         *
         * 两个操作要么全部成功，
         * 要么全部回滚。
         *
         * 当前阶段暂时返回数据库操作失败。
         */
        if (!inventorySuccess)
        {
            return dbErrorVO();
        }
    }


    // 返回审批通过成功结果。
    return approveSuccessVO(
        dto->busNo
    );
}


/**
 * @brief 驳回药房入库审批单。
 *
 * 业务流程：
 *
 * 1. 校验请求 DTO 及业务号 busNo；
 * 2. 校验驳回原因 rejectReason；
 * 3. 查询入库单；
 * 4. 校验入库单是否存在；
 * 5. 校验当前状态是否为 PENDING；
 * 6. 更新状态为 REJECTED；
 * 7. 记录驳回原因和审批人；
 * 8. 返回驳回成功结果。
 *
 * @param dto 驳回入库单请求 DTO。
 *
 * @return 驳回操作结果 VO。
 */
oatpp::Object<vo::StockInOperationResultVO>
PharmacyStockInApprovalService::reject(
    const oatpp::Object<
    dto::StockInRejectDTO>& dto)
{
    // 校验请求对象及业务号。
    if (!dto || !dto->busNo || dto->busNo->empty())
    {
        return makeFailVO(
            ZH_WORDS_GETTER(
                "stockin.error.busNo-empty"
            )
        );
    }


    // 驳回操作必须提供驳回原因。
    if (!dto->rejectReason ||
        dto->rejectReason->empty())
    {
        return rejectReasonEmptyVO();
    }


    std::string busNo =
        *dto->busNo;

    std::string reason =
        *dto->rejectReason;


    // TODO: 数据库连接应由项目统一的数据库连接管理模块提供。
    std::shared_ptr<sql::Connection> conn = nullptr;


    /*
     * 根据业务号查询入库单。
     */
    auto orderDO =
        StockInOrderDAO::queryByBusNo(
            conn,
            busNo
        );


    // 入库单不存在。
    if (!orderDO)
    {
        return notFoundVO();
    }


    // 只有 PENDING 状态的入库单才能被驳回。
    if (!orderDO->statusEnum ||
        *orderDO->statusEnum != "PENDING")
    {
        return notPendingApprovalVO();
    }


    /*
     * 获取审批人。
     *
     * 实际项目中应从当前登录用户上下文中获取。
     */
    std::string approverId = "system";

    if (dto->approverId)
    {
        approverId = *dto->approverId;
    }


    /*
     * 更新入库单状态为 REJECTED，
     * 同时记录驳回原因和审批人。
     */
    bool success =
        StockInOrderDAO::updateStatusToRejected(
            conn,
            *orderDO->id,
            reason,
            approverId,
            "system",  // updatedBy
            orderDO->version ? *orderDO->version : 0);


    if (!success)
    {
        return dbErrorVO();
    }


    // 返回驳回成功结果。
    return rejectSuccessVO(
        dto->busNo,
        dto->rejectReason
    );
}