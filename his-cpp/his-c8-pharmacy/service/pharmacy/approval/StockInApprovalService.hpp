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
 * @file PharmacyStockInApprovalService.h
 * @brief 药房入库审批业务服务声明。
 *
 * 负责处理药房入库单审批流程相关的核心业务逻辑，
 * 包括入库单撤回、审批通过以及驳回操作。
 *
 * Service 层负责接收 Controller 层传递的 DTO 请求数据，
 * 根据业务规则组织 DAO 层的数据访问操作，
 * 并将业务处理结果封装为 VO 返回给 Controller 层。
 */

#pragma once

#include "oatpp/core/Types.hpp"

#include "domain/dto/approval/StockInWithdrawDTO.hpp"
#include "domain/dto/approval/StockInApprovalDTO.hpp"
#include "domain/dto/approval/StockInRejectDTO.hpp"

#include "domain/vo/approval/StockInOperationResultVO.hpp"


 /**
  * @brief 药房入库审批业务服务。
  *
  * 负责实现药房入库单审批流程中的核心业务操作：
  *
  * 1. 撤回入库单；
  * 2. 审批通过入库单；
  * 3. 驳回入库单。
  *
  * Service 层位于 Controller 与 DAO 之间：
  *
  * Controller
  *     ↓ DTO
  * PharmacyStockInApprovalService
  *     ↓ DAO
  * Database
  *
  * 业务处理完成后：
  *
  * Database
  *     ↓
  * PharmacyStockInApprovalService
  *     ↓ VO
  * Controller
  *
  * 通过 Service 层统一组织业务流程，
  * 避免 Controller 直接处理数据库操作，
  * 保持各层职责清晰。
  */
class PharmacyStockInApprovalService
{
public:

    /**
     * @brief 撤回已提交审批的入库单。
     *
     * 根据前端传入的撤回请求，
     * 查询并校验入库单当前状态，
     * 在满足业务规则的情况下将入库单状态更新为 WITHDRAWN。
     *
     * @param dto 撤回入库单请求参数。
     *
     * @return 撤回操作结果 VO。
     */
    oatpp::Object<vo::StockInOperationResultVO>
        withdraw(
            const oatpp::Object<
            dto::StockInWithdrawDTO>& dto);


    /**
     * @brief 审批通过入库单。
     *
     * 根据前端传入的审批请求，
     * 校验入库单是否满足审批条件，
     * 更新入库单审批状态，
     * 并根据业务流程完成对应的库存数据处理。
     *
     * @param dto 入库单审批请求参数。
     *
     * @return 审批操作结果 VO。
     */
    oatpp::Object<vo::StockInOperationResultVO>
        approve(
            const oatpp::Object<
            dto::StockInApprovalDTO>& dto);


    /**
     * @brief 驳回入库审批单。
     *
     * 根据前端传入的驳回请求，
     * 校验驳回原因及入库单当前状态，
     * 在满足业务规则的情况下将入库单状态更新为 REJECTED。
     *
     * @param dto 入库单驳回请求参数。
     *
     * @return 驳回操作结果 VO。
     */
    oatpp::Object<vo::StockInOperationResultVO>
        reject(
            const oatpp::Object<
            dto::StockInRejectDTO>& dto);
};