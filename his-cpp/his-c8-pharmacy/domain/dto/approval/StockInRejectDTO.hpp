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
 * @file StockInRejectDTO.hpp
 * @brief 药房入库驳回审批请求数据传输对象。
 *
 * 用于接收前端提交的入库单驳回请求。
 *
 * 驳回操作需要提供：
 * 1. 入库单业务编号 busNo；
 * 2. 驳回原因 rejectReason。
 *
 * Controller 层接收并校验请求参数后，
 * 将该 DTO 传递给 Service 层执行具体业务逻辑。
 */

#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include "Macros.h"
#include "ServerInfo.h"

namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

    /**
     * @brief 入库单驳回审批请求 DTO。
     *
     * 用于封装前端提交的入库单驳回请求参数。
     *
     * Service 层根据 busNo 查询对应入库单，
     * 校验当前单据状态后，
     * 使用 rejectReason 记录本次驳回原因。
     */
    class StockInRejectDTO : public oatpp::DTO {
        DTO_INIT(StockInRejectDTO, DTO)

            /**
             * @brief 入库单业务编号。
             *
             * 用于定位需要执行驳回操作的入库单。
             * 该字段为必填参数。
             *
             * Swagger 示例值仅用于接口文档展示，
             * 实际请求时由前端传入真实业务编号。
             */
            DTO_FIELD(String, busNo) = "RK20260720003";

        /**
         * @brief 入库单业务编号字段信息。
         */
        DTO_FIELD_INFO(busNo) {
            info->description = ZH_WORDS_GETTER(
                "pharmacy.stockin.field.busNo"
            );
            info->required = true;
        }


        /**
         * @brief 入库单驳回原因。
         *
         * 用于记录审批人员执行驳回操作时填写的具体原因。
         * 该字段为必填参数。
         *
         * Service 层需要对该字段进行非空校验，
         * 校验通过后传递给 DAO 层持久化到数据库。
         */
        DTO_FIELD(String, rejectReason)
            = "The specification of medicine does not match.";

        /**
         * @brief 驳回原因字段信息。
         */
        DTO_FIELD_INFO(rejectReason) {
            info->description = ZH_WORDS_GETTER(
                "pharmacy.stockin.field.rejectReason"
            );
            info->required = true;
        }

            /**
             * @brief 审批人ID。
             *
             * 用于标识执行驳回操作的审批人员。
             * 该字段为必填参数，用于记录审批操作的操作人。
             */
            DTO_FIELD(String, approverId) = "admin";

        /**
         * @brief 审批人ID字段信息。
         */
        DTO_FIELD_INFO(approverId) {
            info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.approverId");
            info->required = true;
        }

    };

#include OATPP_CODEGEN_END(DTO)

} // namespace dto