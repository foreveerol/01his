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
 * @file StockInWithdrawDTO.hpp
 * @brief 药房入库撤回审批请求数据传输对象。
 *
 * 用于定义撤回入库审批接口接收的请求参数。
 * 当前撤回操作通过入库单业务编号 busNo 定位需要撤回的入库单。
 */

#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include "Macros.h"
#include "ServerInfo.h"

namespace dto {

#include OATPP_CODEGEN_BEGIN(DTO)

    /**
     * @brief 入库单撤回审批请求 DTO。
     *
     * 用于接收前端提交的入库单撤回请求。
     *
     * 请求数据由 Controller 层接收后，
     * 传递至 Service 层执行撤回业务逻辑。
     *
     * 当前撤回业务仅需要入库单业务编号 busNo，
     * Service 层根据该编号查询入库单并校验其当前审批状态。
     */
    class StockInWithdrawDTO : public oatpp::DTO {
        DTO_INIT(StockInWithdrawDTO, DTO)

            /**
             * @brief 入库单业务编号。
             *
             * 用于唯一标识需要撤回处理的入库单。
             *
             * 该字段由前端请求传入。
             * Swagger 字段描述从 zh-dict.yaml 中文字典中读取。
             *
             * 默认值仅用于 Swagger 接口文档生成时展示示例，
             * 实际请求时由前端传入真实业务编号。
             */
            DTO_FIELD(String, busNo) = "RK20260720001";

        /**
         * @brief 入库单业务编号字段信息。
         *
         * required = true 表示该字段为必填字段。
         */
        DTO_FIELD_INFO(busNo) {
            info->description = ZH_WORDS_GETTER("pharmacy.stockin.field.busNo");
            info->required = true;
        }

    };

#include OATPP_CODEGEN_END(DTO)

} // namespace dto