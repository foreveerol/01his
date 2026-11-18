 /*
 * Copyright Zero One Star. All rights reserved.
 *
 * @Author: stellablack528
 * @Date: 2026/07/27 19:00:00
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
 * @file AdmLocationDO.hpp
 * @brief 地点信息表 DO。
 *
 * 对应数据库 adm_location 表，用于映射药库、药房等业务地点信息。
 *
 * 在药房入库审批业务中：
 * - sourceLocationId 表示入库药品的来源地点，通常对应药库；
 * - purposeLocationId 表示入库药品的目的地点，通常对应药房；
 * - formEnum 用于区分地点类型，如 WAREHOUSE（药库）、PHARMACY（药房）；
 * - parentId 用于表示地点之间的层级关系。
 *
 * 该 DO 主要用于数据库记录与 C++ 对象之间的数据映射，
 * 为 DAO 层查询地点信息以及 Service 层处理业务逻辑提供数据模型支持。
 */

#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace domain {

#include OATPP_CODEGEN_BEGIN(DTO)

    /**
     * @brief 地点信息数据对象。
     *
     * 一条记录表示一个具体的业务地点，例如药库或药房。
     */
    class AdmLocationDO : public oatpp::DTO
    {
        DTO_INIT(AdmLocationDO, DTO)

            // 地点主键
            DTO_FIELD(String, id);

        // 地点名称，例如：中心药库、第一药房
        DTO_FIELD(String, name);

        // 地点业务编号
        DTO_FIELD(String, busNo);

        // 地点状态
        DTO_FIELD(String, statusEnum);

        // 地点类型：WAREHOUSE（药库）/ PHARMACY（药房）
        DTO_FIELD(String, formEnum);

        // 父级地点 ID，用于表示地点层级关系
        DTO_FIELD(String, parentId);
    };

#include OATPP_CODEGEN_END(DTO)

} // namespace domain