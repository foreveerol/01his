#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: zjb517
 @Date: 2026/07/26 10:00:00

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
#ifndef _INVENTORYCHECKDO_H_
#define _INVENTORYCHECKDO_H_

#include "../DoInclude.h"

/**
 * 库存盘点数据库实体（wkf_supply_request 表）
 */
class InventoryCheckDO : public BaseDO
{
	// 通用审计字段
	MYSQL_SYNTHESIZE(long long, id, Id);
	MYSQL_SYNTHESIZE(long long, tenantId, TenantId);
	MYSQL_SYNTHESIZE(string, createdAt, CreatedAt);
	MYSQL_SYNTHESIZE(string, updatedAt, UpdatedAt);
	MYSQL_SYNTHESIZE(long long, createdBy, CreatedBy);
	MYSQL_SYNTHESIZE(long long, updatedBy, UpdatedBy);
	MYSQL_SYNTHESIZE(bool, isDeleted, IsDeleted);
	MYSQL_SYNTHESIZE(string, deletedAt, DeletedAt);
	MYSQL_SYNTHESIZE(long long, deletedBy, DeletedBy);
	MYSQL_SYNTHESIZE(int, version, Version);

	// 供应申请单据字段
	MYSQL_SYNTHESIZE(string, busNo, BusNo);
	MYSQL_SYNTHESIZE(string, originalBusNo, OriginalBusNo);
	MYSQL_SYNTHESIZE(string, typeEnum, TypeEnum);
	MYSQL_SYNTHESIZE(string, statusEnum, StatusEnum);
	MYSQL_SYNTHESIZE(string, intentEnum, IntentEnum);
	MYSQL_SYNTHESIZE(string, categoryEnum, CategoryEnum);
	MYSQL_SYNTHESIZE(string, priorityEnum, PriorityEnum);

	// 关联业务对象标识
	MYSQL_SYNTHESIZE(long long, summaryId, SummaryId);
	MYSQL_SYNTHESIZE(long long, deliverId, DeliverId);
	MYSQL_SYNTHESIZE(long long, patientId, PatientId);

	// 物品字段
	MYSQL_SYNTHESIZE(string, itemTable, ItemTable);
	MYSQL_SYNTHESIZE(double, itemQuantity, ItemQuantity);
	MYSQL_SYNTHESIZE(double, totalQuantity, TotalQuantity);
	MYSQL_SYNTHESIZE(long long, itemId, ItemId);
	MYSQL_SYNTHESIZE(string, unitCode, UnitCode);

	// 业务时间和人员字段
	MYSQL_SYNTHESIZE(string, occurrenceTime, OccurrenceTime);
	MYSQL_SYNTHESIZE(long long, practitionerId, PractitionerId);
	MYSQL_SYNTHESIZE(long long, supplierId, SupplierId);
	MYSQL_SYNTHESIZE(string, reason, Reason);

	// 来源与去向字段
	MYSQL_SYNTHESIZE(string, sourceTypeEnum, SourceTypeEnum);
	MYSQL_SYNTHESIZE(long long, sourceLocationId, SourceLocationId);
	MYSQL_SYNTHESIZE(string, purposeTypeEnum, PurposeTypeEnum);
	MYSQL_SYNTHESIZE(long long, purposeLocationId, PurposeLocationId);

	// 审批字段
	MYSQL_SYNTHESIZE(long long, approverId, ApproverId);
	MYSQL_SYNTHESIZE(string, approvalTime, ApprovalTime);
	MYSQL_SYNTHESIZE(long long, applicantId, ApplicantId);
	MYSQL_SYNTHESIZE(string, applyTime, ApplyTime);

	// 有效期和库存字段
	MYSQL_SYNTHESIZE(string, startTime, StartTime);
	MYSQL_SYNTHESIZE(string, endTime, EndTime);
	MYSQL_SYNTHESIZE(string, lotNumber, LotNumber);
	MYSQL_SYNTHESIZE(string, traceNo, TraceNo);
	MYSQL_SYNTHESIZE(double, price, Price);
	MYSQL_SYNTHESIZE(double, totalPrice, TotalPrice);
	MYSQL_SYNTHESIZE(string, remake, Remake);
	MYSQL_SYNTHESIZE(double, profitLossPrice, ProfitLossPrice);

public:
	InventoryCheckDO()
		: BaseDO("wkf_supply_request")
	{
		// 通用审计字段
		MYSQL_ADD_FIELD_PK("id", "ll", id);
		MYSQL_ADD_FIELD_NULLABLE("tenant_id", "ll", tenantId, true);
		MYSQL_ADD_FIELD_NULLABLE("created_at", "dt", createdAt, false);
		MYSQL_ADD_FIELD_NULLABLE("updated_at", "dt", updatedAt, true);
		MYSQL_ADD_FIELD_NULLABLE("created_by", "ll", createdBy, true);
		MYSQL_ADD_FIELD_NULLABLE("updated_by", "ll", updatedBy, true);
		MYSQL_ADD_FIELD_NULLABLE("is_deleted", "b", isDeleted, false);
		MYSQL_ADD_FIELD_NULLABLE("deleted_at", "dt", deletedAt, true);
		MYSQL_ADD_FIELD_NULLABLE("deleted_by", "ll", deletedBy, true);
		MYSQL_ADD_FIELD_NULLABLE("version", "i", version, false);

		// 供应申请单据字段
		MYSQL_ADD_FIELD_NULLABLE("bus_no", "s", busNo, false);
		MYSQL_ADD_FIELD_NULLABLE("original_bus_no", "s", originalBusNo, true);
		MYSQL_ADD_FIELD_NULLABLE("type_enum", "s", typeEnum, false);
		MYSQL_ADD_FIELD_NULLABLE("status_enum", "s", statusEnum, false);
		MYSQL_ADD_FIELD_NULLABLE("intent_enum", "s", intentEnum, true);
		MYSQL_ADD_FIELD_NULLABLE("category_enum", "s", categoryEnum, false);
		MYSQL_ADD_FIELD_NULLABLE("priority_enum", "s", priorityEnum, true);

		MYSQL_ADD_FIELD_NULLABLE("summary_id", "ll", summaryId, true);
		MYSQL_ADD_FIELD_NULLABLE("deliver_id", "ll", deliverId, true);
		MYSQL_ADD_FIELD_NULLABLE("patient_id", "ll", patientId, true);

		// 物品字段
		MYSQL_ADD_FIELD_NULLABLE("item_table", "s", itemTable, false);
		MYSQL_ADD_FIELD_NULLABLE("item_quantity", "d", itemQuantity, false);
		MYSQL_ADD_FIELD_NULLABLE("total_quantity", "d", totalQuantity, true);
		MYSQL_ADD_FIELD_NULLABLE("item_id", "ll", itemId, false);
		MYSQL_ADD_FIELD_NULLABLE("unit_code", "s", unitCode, false);

		// 业务时间和人员字段
		MYSQL_ADD_FIELD_NULLABLE("occurrence_time", "dt", occurrenceTime, true);
		MYSQL_ADD_FIELD_NULLABLE("practitioner_id", "ll", practitionerId, true);
		MYSQL_ADD_FIELD_NULLABLE("supplier_id", "ll", supplierId, true);
		MYSQL_ADD_FIELD_NULLABLE("reason", "s", reason, true);

		// 来源与去向字段
		MYSQL_ADD_FIELD_NULLABLE("source_type_enum", "s", sourceTypeEnum, true);
		MYSQL_ADD_FIELD_NULLABLE("source_location_id", "ll", sourceLocationId, true);
		MYSQL_ADD_FIELD_NULLABLE("purpose_type_enum", "s", purposeTypeEnum, true);
		MYSQL_ADD_FIELD_NULLABLE("purpose_location_id", "ll", purposeLocationId, true);

		// 审批字段
		MYSQL_ADD_FIELD_NULLABLE("approver_id", "ll", approverId, true);
		MYSQL_ADD_FIELD_NULLABLE("approval_time", "dt", approvalTime, true);
		MYSQL_ADD_FIELD_NULLABLE("applicant_id", "ll", applicantId, false);
		MYSQL_ADD_FIELD_NULLABLE("apply_time", "dt", applyTime, true);

		// 有效期和库存字段
		MYSQL_ADD_FIELD_NULLABLE("start_time", "dt", startTime, true);
		MYSQL_ADD_FIELD_NULLABLE("end_time", "dt", endTime, true);
		MYSQL_ADD_FIELD_NULLABLE("lot_number", "s", lotNumber, true);
		MYSQL_ADD_FIELD_NULLABLE("trace_no", "s", traceNo, true);
		MYSQL_ADD_FIELD_NULLABLE("price", "d", price, true);
		MYSQL_ADD_FIELD_NULLABLE("total_price", "d", totalPrice, true);
		MYSQL_ADD_FIELD_NULLABLE("remake", "s", remake, true);
		MYSQL_ADD_FIELD_NULLABLE("profit_loss_price", "d", profitLossPrice, true);
	}

	InventoryCheckDO(InventoryCheckDO&&) = default;
	InventoryCheckDO& operator=(InventoryCheckDO&&) = default;
};

typedef std::shared_ptr<InventoryCheckDO> PtrInventoryCheckDO;

#endif // !_INVENTORYCHECKDO_H_
