#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: tanqian
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
#ifndef _ENCOUNTER_DO_
#define _ENCOUNTER_DO_
#include "../DoInclude.h"

/**
 * Encounter database entity (adm_encounter table)
 * Represents a patient encounter/visit in the hospital information system
 */
class EncounterDO : public BaseDO
{
	// Common audit fields
	MYSQL_SYNTHESIZE(string, id, Id);
	MYSQL_SYNTHESIZE(string, tenant_id, TenantId);
	MYSQL_SYNTHESIZE(string, created_at, CreatedAt);
	MYSQL_SYNTHESIZE(string, updated_at, UpdatedAt);
	MYSQL_SYNTHESIZE(string, created_by, CreatedBy);
	MYSQL_SYNTHESIZE(string, updated_by, UpdatedBy);
	MYSQL_SYNTHESIZE(bool, is_deleted, IsDeleted);
	MYSQL_SYNTHESIZE(string, deleted_at, DeletedAt);
	MYSQL_SYNTHESIZE(string, deleted_by, DeletedBy);
	MYSQL_SYNTHESIZE(int, version, Version);

	// Business fields
	MYSQL_SYNTHESIZE(string, patient_id, PatientId);
	MYSQL_SYNTHESIZE(string, group_id, GroupId);
	MYSQL_SYNTHESIZE(string, bus_no, BusNo);
	MYSQL_SYNTHESIZE(string, status_enum, StatusEnum);
	MYSQL_SYNTHESIZE(string, class_enum, ClassEnum);
	MYSQL_SYNTHESIZE(string, yb_class_enum, YbClassEnum);
	MYSQL_SYNTHESIZE(string, yb_class_text, YbClassText);
	MYSQL_SYNTHESIZE(string, class_json, ClassJson);
	MYSQL_SYNTHESIZE(string, priority_enum, PriorityEnum);
	MYSQL_SYNTHESIZE(string, type_enum, TypeEnum);
	MYSQL_SYNTHESIZE(string, service_type_id, ServiceTypeId);
	MYSQL_SYNTHESIZE(string, subject_status_enum, SubjectStatusEnum);
	MYSQL_SYNTHESIZE(string, start_time, StartTime);
	MYSQL_SYNTHESIZE(string, end_time, EndTime);
	MYSQL_SYNTHESIZE(string, organization_id, OrganizationId);
	MYSQL_SYNTHESIZE(int, display_order, DisplayOrder);
	MYSQL_SYNTHESIZE(string, first_enum, FirstEnum);
	MYSQL_SYNTHESIZE(string, admit_source_code, AdmitSourceCode);
	MYSQL_SYNTHESIZE(string, in_way_code, InWayCode);
	MYSQL_SYNTHESIZE(string, reception_time, ReceptionTime);
	MYSQL_SYNTHESIZE(string, registrar_id, RegistrarId);
	MYSQL_SYNTHESIZE(string, amb_encounter_id, AmbEncounterId);
	MYSQL_SYNTHESIZE(string, out_way_code, OutWayCode);

public:
	EncounterDO()
		: BaseDO("adm_encounter")
	{
		// Common audit fields
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD_NULLABLE("tenant_id", "s", tenant_id, true);
		MYSQL_ADD_FIELD_NULLABLE("created_at", "dt", created_at, false);
		MYSQL_ADD_FIELD_NULLABLE("updated_at", "dt", updated_at, true);
		MYSQL_ADD_FIELD_NULLABLE("created_by", "s", created_by, true);
		MYSQL_ADD_FIELD_NULLABLE("updated_by", "s", updated_by, true);
		MYSQL_ADD_FIELD_NULLABLE("is_deleted", "b", is_deleted, false);
		MYSQL_ADD_FIELD_NULLABLE("deleted_at", "dt", deleted_at, true);
		MYSQL_ADD_FIELD_NULLABLE("deleted_by", "s", deleted_by, true);
		MYSQL_ADD_FIELD_NULLABLE("version", "i", version, false);

		// Business fields
		MYSQL_ADD_FIELD_NULLABLE("patient_id", "s", patient_id, false);
		MYSQL_ADD_FIELD_NULLABLE("group_id", "s", group_id, true);
		MYSQL_ADD_FIELD_NULLABLE("bus_no", "s", bus_no, false);
		MYSQL_ADD_FIELD_NULLABLE("status_enum", "s", status_enum, false);
		MYSQL_ADD_FIELD_NULLABLE("class_enum", "s", class_enum, false);
		MYSQL_ADD_FIELD_NULLABLE("yb_class_enum", "s", yb_class_enum, true);
		MYSQL_ADD_FIELD_NULLABLE("yb_class_text", "s", yb_class_text, true);
		MYSQL_ADD_FIELD_NULLABLE("class_json", "s", class_json, true);
		MYSQL_ADD_FIELD_NULLABLE("priority_enum", "s", priority_enum, true);
		MYSQL_ADD_FIELD_NULLABLE("type_enum", "s", type_enum, false);
		MYSQL_ADD_FIELD_NULLABLE("service_type_id", "s", service_type_id, true);
		MYSQL_ADD_FIELD_NULLABLE("subject_status_enum", "s", subject_status_enum, true);
		MYSQL_ADD_FIELD_NULLABLE("start_time", "dt", start_time, true);
		MYSQL_ADD_FIELD_NULLABLE("end_time", "dt", end_time, true);
		MYSQL_ADD_FIELD_NULLABLE("organization_id", "s", organization_id, false);
		MYSQL_ADD_FIELD_NULLABLE("display_order", "i", display_order, true);
		MYSQL_ADD_FIELD_NULLABLE("first_enum", "s", first_enum, true);
		MYSQL_ADD_FIELD_NULLABLE("admit_source_code", "s", admit_source_code, true);
		MYSQL_ADD_FIELD_NULLABLE("in_way_code", "s", in_way_code, true);
		MYSQL_ADD_FIELD_NULLABLE("reception_time", "dt", reception_time, true);
		MYSQL_ADD_FIELD_NULLABLE("registrar_id", "s", registrar_id, true);
		MYSQL_ADD_FIELD_NULLABLE("amb_encounter_id", "s", amb_encounter_id, true);
		MYSQL_ADD_FIELD_NULLABLE("out_way_code", "s", out_way_code, true);
	}

	EncounterDO(EncounterDO&&) = default;
	EncounterDO& operator=(EncounterDO&&) = default;
};

typedef std::shared_ptr<EncounterDO> PtrEncounterDO;

#endif // !_ENCOUNTER_DO_
