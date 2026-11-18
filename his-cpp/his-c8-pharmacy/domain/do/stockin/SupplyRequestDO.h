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
#ifndef _SUPPLY_REQUEST_DO_
#define _SUPPLY_REQUEST_DO_

#include "../DoInclude.h"

/**
 * 供应申请入库数据库实体（wkf_supply_request 表）
 * 入库场景下的完整申请字段视图
 */
class SupplyRequestDO : public BaseDO
{
	// 系统字段
	MYSQL_SYNTHESIZE(string, id, Id);
	MYSQL_SYNTHESIZE(string, tenantId, TenantId);
	MYSQL_SYNTHESIZE(string, createdAt, CreatedAt);
	MYSQL_SYNTHESIZE(string, updatedAt, UpdatedAt);
	MYSQL_SYNTHESIZE(string, createdBy, CreatedBy);
	MYSQL_SYNTHESIZE(string, updatedBy, UpdatedBy);
	MYSQL_SYNTHESIZE(int, isDeleted, IsDeleted);
	MYSQL_SYNTHESIZE(string, deletedAt, DeletedAt);
	MYSQL_SYNTHESIZE(string, deletedBy, DeletedBy);
	MYSQL_SYNTHESIZE(int, version, Version);

	// 业务字段
	MYSQL_SYNTHESIZE(string, busNo, BusNo);
	MYSQL_SYNTHESIZE(string, originalBusNo, OriginalBusNo);
	MYSQL_SYNTHESIZE(string, typeEnum, TypeEnum);
	MYSQL_SYNTHESIZE(string, statusEnum, StatusEnum);
	MYSQL_SYNTHESIZE(string, intentEnum, IntentEnum);
	MYSQL_SYNTHESIZE(string, categoryEnum, CategoryEnum);
	MYSQL_SYNTHESIZE(string, priorityEnum, PriorityEnum);

	MYSQL_SYNTHESIZE(string, summaryId, SummaryId);
	MYSQL_SYNTHESIZE(string, deliverId, DeliverId);
	MYSQL_SYNTHESIZE(string, patientId, PatientId);
	MYSQL_SYNTHESIZE(string, itemTable, ItemTable);

	MYSQL_SYNTHESIZE(double, itemQuantity, ItemQuantity);
	MYSQL_SYNTHESIZE(double, totalQuantity, TotalQuantity);

	MYSQL_SYNTHESIZE(string, itemId, ItemId);
	MYSQL_SYNTHESIZE(string, unitCode, UnitCode);
	MYSQL_SYNTHESIZE(string, occurrenceTime, OccurrenceTime);
	MYSQL_SYNTHESIZE(string, practitionerId, PractitionerId);
	MYSQL_SYNTHESIZE(string, supplierId, SupplierId);

	MYSQL_SYNTHESIZE(string, sourceLocationId, SourceLocationId);
	MYSQL_SYNTHESIZE(string, purposeLocationId, PurposeLocationId);
	MYSQL_SYNTHESIZE(string, approverId, ApproverId);
	MYSQL_SYNTHESIZE(string, approvalTime, ApprovalTime);
	MYSQL_SYNTHESIZE(string, applicantId, ApplicantId);
	MYSQL_SYNTHESIZE(string, applyTime, ApplyTime);

	MYSQL_SYNTHESIZE(string, lotNumber, LotNumber);
	MYSQL_SYNTHESIZE(string, traceNo, TraceNo);

	MYSQL_SYNTHESIZE(double, price, Price);
	MYSQL_SYNTHESIZE(double, totalPrice, TotalPrice);

	MYSQL_SYNTHESIZE(string, remake, Remake);

public:
	SupplyRequestDO()
		: BaseDO("wkf_supply_request")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD_NULLABLE("tenant_id", "s", tenantId, true);
		MYSQL_ADD_FIELD_NULLABLE("created_at", "s", createdAt, true);
		MYSQL_ADD_FIELD_NULLABLE("updated_at", "s", updatedAt, true);
		MYSQL_ADD_FIELD_NULLABLE("created_by", "s", createdBy, true);
		MYSQL_ADD_FIELD_NULLABLE("updated_by", "s", updatedBy, true);
		MYSQL_ADD_FIELD_NULLABLE("is_deleted", "i", isDeleted, true);
		MYSQL_ADD_FIELD_NULLABLE("deleted_at", "s", deletedAt, true);
		MYSQL_ADD_FIELD_NULLABLE("deleted_by", "s", deletedBy, true);
		MYSQL_ADD_FIELD_NULLABLE("version", "i", version, true);

		MYSQL_ADD_FIELD_NULLABLE("bus_no", "s", busNo, true);
		MYSQL_ADD_FIELD_NULLABLE("original_bus_no", "s", originalBusNo, true);
		MYSQL_ADD_FIELD_NULLABLE("type_enum", "s", typeEnum, true);
		MYSQL_ADD_FIELD_NULLABLE("status_enum", "s", statusEnum, true);
		MYSQL_ADD_FIELD_NULLABLE("intent_enum", "s", intentEnum, true);
		MYSQL_ADD_FIELD_NULLABLE("category_enum", "s", categoryEnum, true);
		MYSQL_ADD_FIELD_NULLABLE("priority_enum", "s", priorityEnum, true);

		MYSQL_ADD_FIELD_NULLABLE("summary_id", "s", summaryId, true);
		MYSQL_ADD_FIELD_NULLABLE("deliver_id", "s", deliverId, true);
		MYSQL_ADD_FIELD_NULLABLE("patient_id", "s", patientId, true);
		MYSQL_ADD_FIELD_NULLABLE("item_table", "s", itemTable, true);

		MYSQL_ADD_FIELD_NULLABLE("item_quantity", "d", itemQuantity, true);
		MYSQL_ADD_FIELD_NULLABLE("total_quantity", "d", totalQuantity, true);

		MYSQL_ADD_FIELD_NULLABLE("item_id", "s", itemId, true);
		MYSQL_ADD_FIELD_NULLABLE("unit_code", "s", unitCode, true);
		MYSQL_ADD_FIELD_NULLABLE("occurrence_time", "s", occurrenceTime, true);
		MYSQL_ADD_FIELD_NULLABLE("practitioner_id", "s", practitionerId, true);
		MYSQL_ADD_FIELD_NULLABLE("supplier_id", "s", supplierId, true);

		MYSQL_ADD_FIELD_NULLABLE("source_location_id", "s", sourceLocationId, true);
		MYSQL_ADD_FIELD_NULLABLE("purpose_location_id", "s", purposeLocationId, true);
		MYSQL_ADD_FIELD_NULLABLE("approver_id", "s", approverId, true);
		MYSQL_ADD_FIELD_NULLABLE("approval_time", "s", approvalTime, true);
		MYSQL_ADD_FIELD_NULLABLE("applicant_id", "s", applicantId, true);
		MYSQL_ADD_FIELD_NULLABLE("apply_time", "s", applyTime, true);

		MYSQL_ADD_FIELD_NULLABLE("lot_number", "s", lotNumber, true);
		MYSQL_ADD_FIELD_NULLABLE("trace_no", "s", traceNo, true);

		MYSQL_ADD_FIELD_NULLABLE("price", "d", price, true);
		MYSQL_ADD_FIELD_NULLABLE("total_price", "d", totalPrice, true);

		MYSQL_ADD_FIELD_NULLABLE("remake", "s", remake, true);
	}

	SupplyRequestDO(SupplyRequestDO&&) = default;
	SupplyRequestDO& operator=(SupplyRequestDO&&) = default;
};

typedef std::shared_ptr<SupplyRequestDO> PtrSupplyRequestDO;

#endif // !_SUPPLY_REQUEST_DO_
