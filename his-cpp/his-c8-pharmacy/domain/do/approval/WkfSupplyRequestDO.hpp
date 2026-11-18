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
 * @file WkfSupplyRequestDO.hpp
 * @brief 供应请求及入库单主表 DO。
 *
 * 对应数据库 wkf_supply_request 表，用于映射药房入库审批业务中的
 * 入库申请、业务单号、药品信息、申请信息以及审批状态等核心数据。
 *
 * 在药房入库审批业务中：
 * - busNo 表示入库单业务编号，用于标识一组入库业务；
 * - statusEnum 表示当前审批状态，如 PENDING_APPROVAL、APPROVED、REJECTED、WITHDRAWN；
 * - applicantId 表示入库申请人；
 * - approverId 表示审批人；
 * - applyTime 表示提交审批时间；
 * - approvalTime 表示审批处理时间；
 * - sourceLocationId 表示来源地点，通常对应源药库；
 * - purposeLocationId 表示目的地点，通常对应目标药房；
 * - itemId 表示入库药品；
 * - itemQuantity 表示本次入库数量；
 * - traceNo 表示药品追溯码；
 * - reason 表示驳回等业务原因；
 * - createdBy 和 createdAt 可用于获取制单人和制单时间。
 *
 * 该 DO 主要用于数据库记录与 C++ 对象之间的数据映射，
 * 为 DAO 层进行数据库查询和更新，以及 Service 层执行业务逻辑提供数据模型支持。
 */

#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace domain {

#include OATPP_CODEGEN_BEGIN(DTO)

    /**
     * @brief 入库单主表数据对象。
     *
     * 一条记录表示 wkf_supply_request 表中的一条供应请求记录。
     * 同一 busNo 可以对应多条明细记录，共同组成一张业务入库单。
     */
    class WkfSupplyRequestDO : public oatpp::DTO
    {
        DTO_INIT(WkfSupplyRequestDO, DTO)

            // ==================== 基础公共字段 ====================

            // 主键
            DTO_FIELD(String, id);

        // 租户标识
        DTO_FIELD(String, tenantId);

        // 创建时间，可作为制单时间使用
        DTO_FIELD(String, createdAt);

        // 最后更新时间
        DTO_FIELD(String, updatedAt);

        // 创建人，可作为制单人使用
        DTO_FIELD(String, createdBy);

        // 最后更新人
        DTO_FIELD(String, updatedBy);

        // 软删除标记
        DTO_FIELD(Boolean, isDeleted);

        // 删除时间
        DTO_FIELD(String, deletedAt);

        // 删除人
        DTO_FIELD(String, deletedBy);

        // 乐观锁版本号
        DTO_FIELD(Int32, version);


        // ==================== 入库业务字段 ====================

        // 供应请求业务编号，同一 busNo 可聚合多条明细
        DTO_FIELD(String, busNo);

        // 来源业务单号，例如关联原始订货单
        DTO_FIELD(String, originalBusNo);

        // 供应类型持久化编码
        DTO_FIELD(String, typeEnum);

        // 当前供应请求状态
        DTO_FIELD(String, statusEnum);

        // 供应意图枚举值
        DTO_FIELD(String, intentEnum);

        // 供应类别持久化编码
        DTO_FIELD(String, categoryEnum);

        // 优先级枚举值
        DTO_FIELD(String, priorityEnum);

        // 汇总信息标识
        DTO_FIELD(String, summaryId);

        // 交付信息标识
        DTO_FIELD(String, deliverId);

        // 患者标识
        DTO_FIELD(String, patientId);

        // 明细表名称
        DTO_FIELD(String, itemTable);

        // 当前明细数量
        DTO_FIELD(Float64, itemQuantity);

        // 合计或实际数量
        DTO_FIELD(Float64, totalQuantity);

        // 药品目录项标识
        DTO_FIELD(String, itemId);

        // 计量单位编码
        DTO_FIELD(String, unitCode);

        // 业务发生时间
        DTO_FIELD(String, occurrenceTime);

        // 医护人员标识
        DTO_FIELD(String, practitionerId);

        // 供应商标识
        DTO_FIELD(String, supplierId);

        // 业务原因，例如驳回原因
        DTO_FIELD(String, reason);


        // ==================== 地点信息字段 ====================

        // 来源地点 ID，药房入库业务中通常对应源药库
        DTO_FIELD(String, sourceLocationId);

        // 来源地点类型
        DTO_FIELD(String, sourceTypeEnum);

        // 目的地点 ID，药房入库业务中通常对应目标药房
        DTO_FIELD(String, purposeLocationId);

        // 目的地点类型
        DTO_FIELD(String, purposeTypeEnum);


        // ==================== 审批信息字段 ====================

        // 审批人 ID
        DTO_FIELD(String, approverId);

        // 审批处理时间
        DTO_FIELD(String, approvalTime);

        // 申请人 ID
        DTO_FIELD(String, applicantId);

        // 提交审批时间
        DTO_FIELD(String, applyTime);


        // ==================== 药品及批次信息 ====================

        // 有效期起始时间
        DTO_FIELD(String, startTime);

        // 有效期结束时间
        DTO_FIELD(String, endTime);

        // 药品批号
        DTO_FIELD(String, lotNumber);

        // 药品追溯码
        DTO_FIELD(String, traceNo);


        // ==================== 价格及备注信息 ====================

        // 药品单价
        DTO_FIELD(Float64, price);

        // 入库明细合计价格
        DTO_FIELD(Float64, totalPrice);

        // 备注
        DTO_FIELD(String, remake);

        // 盘点盈亏金额
        DTO_FIELD(Float64, profitLossPrice);
    };

#include OATPP_CODEGEN_END(DTO)

} // namespace domain