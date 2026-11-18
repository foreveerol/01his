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
 * @file StockInOperationResultVO.hpp
 * @brief 药房入库审批操作结果响应数据对象。
 *
 * 用于封装药房入库单撤回、审批通过和驳回操作的处理结果，
 * 作为 Service 层向 Controller 层返回的统一响应数据对象。
 *
 * 主要包含：
 * 1. 操作是否成功；
 * 2. 操作结果消息；
 * 3. 入库单业务编号；
 * 4. 操作后的入库单状态；
 * 5. 驳回原因。
 *
 * Controller 层可将该 VO 转换为 HTTP 响应返回给前端。
 */

#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include "Macros.h"
#include "ServerInfo.h"

namespace vo {

#include OATPP_CODEGEN_BEGIN(DTO)

    /**
     * @brief 药房入库审批操作结果 VO。
     *
     * 用于统一返回药房入库单以下三类业务操作的处理结果：
     *
     * 1. 撤回：WITHDRAWN
     * 2. 审批通过：APPROVED
     * 3. 驳回：REJECTED
     *
     * 该 VO 由 Service 层创建并返回，
     * Controller 层负责将其作为接口响应返回给前端。
     */
    class StockInOperationResultVO : public oatpp::DTO
    {
        DTO_INIT(StockInOperationResultVO, DTO)

            /**
             * @brief 操作是否成功。
             *
             * true  表示业务操作执行成功；
             * false 表示业务操作执行失败。
             */
            DTO_FIELD(Boolean, success) = true;

        DTO_FIELD_INFO(success)
        {
            info->description =
                ZH_WORDS_GETTER(
                    "stockin.result.success"
                );
        }


        /**
         * @brief 操作结果消息。
         *
         * 用于向前端返回当前业务操作的处理结果描述。
         */
        DTO_FIELD(String, message) = "SUCCESS";

        DTO_FIELD_INFO(message)
        {
            info->description =
                ZH_WORDS_GETTER(
                    "stockin.result.message"
                );
        }


        /**
         * @brief 入库单业务编号。
         *
         * 用于标识本次操作对应的药房入库单。
         */
        DTO_FIELD(String, busNo) = "RK20260720001";

        DTO_FIELD_INFO(busNo)
        {
            info->description =
                ZH_WORDS_GETTER(
                    "stockin.result.busNo"
                );
        }


        /**
         * @brief 操作后的入库单状态。
         *
         * 可能的业务状态包括：
         *
         * WITHDRAWN：已撤回
         * APPROVED：已审批通过
         * REJECTED：已驳回
         */
        DTO_FIELD(String, statusEnum) = "WITHDRAWN";

        DTO_FIELD_INFO(statusEnum)
        {
            info->description =
                ZH_WORDS_GETTER(
                    "stockin.result.statusEnum"
                );
        }


        /**
         * @brief 入库单驳回原因。
         *
         * 当入库单执行驳回操作时，
         * 用于返回本次驳回操作对应的原因。
         *
         * 撤回和审批通过操作通常不需要该字段。
         */
        DTO_FIELD(String, rejectReason) = "SPECIFICATION_NOT_MATCH";

        DTO_FIELD_INFO(rejectReason)
        {
            info->description =
                ZH_WORDS_GETTER(
                    "stockin.result.rejectReason"
                );
        }


        /**
         * @brief 制单人。
         *
         * 入库单的创建者/制单人标识，
         * 用于记录是谁发起了本次入库申请。
         */
        DTO_FIELD(String, createdBy) = "";

        DTO_FIELD_INFO(createdBy)
        {
            info->description =
                ZH_WORDS_GETTER(
                    "stockin.result.createdBy"
                );
        }


        /**
         * @brief 制单时间。
         *
         * 入库单的创建时间，
         * 记录入库单据的生成时间戳。
         */
        DTO_FIELD(String, createdAt) = "";

        DTO_FIELD_INFO(createdAt)
        {
            info->description =
                ZH_WORDS_GETTER(
                    "stockin.result.createdAt"
                );
        }


        /**
         * @brief 追溯码。
         *
         * 入库单的唯一追溯码，
         * 用于全链路追踪和溯源管理。
         */
        DTO_FIELD(String, traceNo) = "";

        DTO_FIELD_INFO(traceNo)
        {
            info->description =
                ZH_WORDS_GETTER(
                    "stockin.result.traceNo"
                );
        }
    };


#include OATPP_CODEGEN_END(DTO)

} // namespace vo


/**
 * @brief 创建成功操作结果 VO。
 *
 * 用于统一构造业务操作成功时的响应结果。
 *
 * @param busNo 入库单业务编号。
 * @param status 操作完成后的入库单状态。
 * @param msg 操作结果消息。
 *
 * @return 封装成功结果的 VO 对象。
 */
inline oatpp::Object<vo::StockInOperationResultVO>
makeSuccessVO(
    const oatpp::String& busNo,
    const oatpp::String& status,
    const oatpp::String& msg)
{
    auto result =
        vo::StockInOperationResultVO::createShared();

    result->success = true;
    result->busNo = busNo;
    result->statusEnum = status;
    result->message = msg;

    return result;
}


/**
 * @brief 创建失败操作结果 VO。
 *
 * 用于统一构造业务操作失败时的响应结果。
 *
 * @param msg 操作失败原因或错误提示。
 *
 * @return 封装失败结果的 VO 对象。
 */
inline oatpp::Object<vo::StockInOperationResultVO>
makeFailVO(
    const oatpp::String& msg)
{
    auto result =
        vo::StockInOperationResultVO::createShared();

    result->success = false;
    result->message = msg;

    return result;
}


/**
 * @brief 创建入库单撤回成功结果 VO。
 *
 * 将入库单状态设置为 WITHDRAWN，
 * 并返回对应的撤回成功提示。
 *
 * @param busNo 入库单业务编号。
 *
 * @return 撤回成功结果 VO。
 */
inline oatpp::Object<vo::StockInOperationResultVO>
withdrawSuccessVO(
    const oatpp::String& busNo)
{
    return makeSuccessVO(
        busNo,
        "WITHDRAWN",
        ZH_WORDS_GETTER(
            "stockin.withdraw.success"
        )
    );
}


/**
 * @brief 创建入库单审批通过成功结果 VO。
 *
 * 将入库单状态设置为 APPROVED，
 * 并返回对应的审批成功提示。
 *
 * @param busNo 入库单业务编号。
 *
 * @return 审批通过成功结果 VO。
 */
inline oatpp::Object<vo::StockInOperationResultVO>
approveSuccessVO(
    const oatpp::String& busNo)
{
    return makeSuccessVO(
        busNo,
        "APPROVED",
        ZH_WORDS_GETTER(
            "stockin.approve.success"
        )
    );
}


/**
 * @brief 创建入库单驳回成功结果 VO。
 *
 * 将入库单状态设置为 REJECTED，
 * 并返回对应的驳回原因。
 *
 * @param busNo 入库单业务编号。
 * @param reason 入库单驳回原因。
 *
 * @return 驳回成功结果 VO。
 */
inline oatpp::Object<vo::StockInOperationResultVO>
rejectSuccessVO(
    const oatpp::String& busNo,
    const oatpp::String& reason)
{
    auto result =
        makeSuccessVO(
            busNo,
            "REJECTED",
            ZH_WORDS_GETTER(
                "stockin.reject.success"
            )
        );

    result->rejectReason = reason;

    return result;
}


/**
 * @brief 创建入库单状态不允许审批的失败结果 VO。
 *
 * 当入库单当前状态不是 PENDING 时，
 * 返回审批操作失败结果。
 *
 * @return 审批失败结果 VO。
 */
inline oatpp::Object<vo::StockInOperationResultVO>
notPendingApprovalVO()
{
    return makeFailVO(
        ZH_WORDS_GETTER(
            "stockin.error.not-pending"
        )
    );
}


/**
 * @brief 创建驳回原因为空的失败结果 VO。
 *
 * 当驳回入库单时未提供有效的驳回原因，
 * 返回参数校验失败结果。
 *
 * @return 驳回失败结果 VO。
 */
inline oatpp::Object<vo::StockInOperationResultVO>
rejectReasonEmptyVO()
{
    return makeFailVO(
        ZH_WORDS_GETTER(
            "stockin.error.reject-reason-empty"
        )
    );
}