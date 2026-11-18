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
 * @file StockInApprovalDTO.hpp
 * @brief 药房入库审批通过请求数据传输对象。
 *
 * 用于接收前端提交的入库单审批通过请求。
 * Controller 层接收请求参数后，
 * 将该 DTO 传递至 Service 层执行具体业务逻辑。
 */

#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include "Macros.h"
#include "ServerInfo.h"

namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

    /**
     * @brief 入库单审批通过请求 DTO。
     *
     * 当前审批通过业务需要入库单业务编号 busNo
     * 和执行审批操作的审批人 ID。
     *
     * Service 层根据 busNo 查询对应入库单，
     * 校验当前单据状态后执行审批通过操作。
     */
    class StockInApprovalDTO : public oatpp::DTO {
        DTO_INIT(StockInApprovalDTO, DTO)

            /**
             * @brief 入库单业务编号。
             *
             * 用于定位需要审批的入库单。
             * 该字段为必填参数。
             *
             * 默认值仅用于 Swagger 接口文档生成时展示示例，
             * 实际请求时由前端传入真实业务编号。
             */
            DTO_FIELD(String, busNo) = "RK20260720002";

        /**
         * @brief 入库单业务编号字段信息。
         */
        DTO_FIELD_INFO(busNo) {
            info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.busNo");
            info->required = true;
        }

        /**
         * @brief 审批人 ID。
         *
         * 用于标识执行审批通过操作的审批人员。
         * 该字段为必填参数。
         */
        DTO_FIELD(String, approverId) = "admin";

        /**
         * @brief 审批人 ID 字段信息。
         */
        DTO_FIELD_INFO(approverId) {
            info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.approverId");
            info->required = true;
        }

    };

#include OATPP_CODEGEN_END(DTO)

} // namespace dto