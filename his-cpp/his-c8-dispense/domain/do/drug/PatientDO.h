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
#ifndef _PATIENT_DO_
#define _PATIENT_DO_
#include "../DoInclude.h"

/**
 * Patient database entity (adm_patient table)
 * Represents a patient in the hospital information system
 */
class PatientDO : public BaseDO
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
	MYSQL_SYNTHESIZE(string, bus_no, BusNo);
	MYSQL_SYNTHESIZE(string, name, Name);
	MYSQL_SYNTHESIZE(string, name_json, NameJson);
	MYSQL_SYNTHESIZE(string, gender_enum, GenderEnum);
	MYSQL_SYNTHESIZE(string, birth_date, BirthDate);
	MYSQL_SYNTHESIZE(string, status_enum, StatusEnum);
	MYSQL_SYNTHESIZE(int, active_flag, ActiveFlag);
	MYSQL_SYNTHESIZE(int, temp_flag, TempFlag);
	MYSQL_SYNTHESIZE(string, id_card, IdCard);
	MYSQL_SYNTHESIZE(string, marital_status_enum, MaritalStatusEnum);
	MYSQL_SYNTHESIZE(string, prfs_enum, PrfsEnum);
	MYSQL_SYNTHESIZE(string, phone, Phone);
	MYSQL_SYNTHESIZE(string, address, Address);
	MYSQL_SYNTHESIZE(string, address_province, AddressProvince);
	MYSQL_SYNTHESIZE(string, address_city, AddressCity);
	MYSQL_SYNTHESIZE(string, address_district, AddressDistrict);
	MYSQL_SYNTHESIZE(string, address_street, AddressStreet);
	MYSQL_SYNTHESIZE(string, address_extend_json, AddressExtendJson);
	MYSQL_SYNTHESIZE(string, nationality_code, NationalityCode);
	MYSQL_SYNTHESIZE(string, py_str, PyStr);
	MYSQL_SYNTHESIZE(string, wb_str, WbStr);
	MYSQL_SYNTHESIZE(int, blood_type_abo, BloodTypeAbo);
	MYSQL_SYNTHESIZE(int, blood_type_rh, BloodTypeRh);
	MYSQL_SYNTHESIZE(string, work_company, WorkCompany);
	MYSQL_SYNTHESIZE(string, native_place, NativePlace);
	MYSQL_SYNTHESIZE(string, country_code, CountryCode);
	MYSQL_SYNTHESIZE(string, link_name, LinkName);
	MYSQL_SYNTHESIZE(int, link_relation_code, LinkRelationCode);
	MYSQL_SYNTHESIZE(string, link_telcom, LinkTelcom);
	MYSQL_SYNTHESIZE(string, link_jsons, LinkJsons);
	MYSQL_SYNTHESIZE(string, deceased_date, DeceasedDate);
	MYSQL_SYNTHESIZE(string, deceased_reason, DeceasedReason);
	MYSQL_SYNTHESIZE(string, organization_id, OrganizationId);
	MYSQL_SYNTHESIZE(string, merged_target_patient_id, MergedTargetPatientId);
	MYSQL_SYNTHESIZE(string, merged_at, MergedAt);

public:
	PatientDO()
		: BaseDO("adm_patient")
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
		MYSQL_ADD_FIELD_NULLABLE("bus_no", "s", bus_no, false);
		MYSQL_ADD_FIELD_NULLABLE("name", "s", name, false);
		MYSQL_ADD_FIELD_NULLABLE("name_json", "s", name_json, true);
		MYSQL_ADD_FIELD_NULLABLE("gender_enum", "s", gender_enum, false);
		MYSQL_ADD_FIELD_NULLABLE("birth_date", "dt", birth_date, true);
		MYSQL_ADD_FIELD_NULLABLE("status_enum", "s", status_enum, false);
		MYSQL_ADD_FIELD_NULLABLE("active_flag", "i", active_flag, true);
		MYSQL_ADD_FIELD_NULLABLE("temp_flag", "i", temp_flag, true);
		MYSQL_ADD_FIELD_NULLABLE("id_card", "s", id_card, true);
		MYSQL_ADD_FIELD_NULLABLE("marital_status_enum", "s", marital_status_enum, true);
		MYSQL_ADD_FIELD_NULLABLE("prfs_enum", "s", prfs_enum, true);
		MYSQL_ADD_FIELD_NULLABLE("phone", "s", phone, true);
		MYSQL_ADD_FIELD_NULLABLE("address", "s", address, true);
		MYSQL_ADD_FIELD_NULLABLE("address_province", "s", address_province, true);
		MYSQL_ADD_FIELD_NULLABLE("address_city", "s", address_city, true);
		MYSQL_ADD_FIELD_NULLABLE("address_district", "s", address_district, true);
		MYSQL_ADD_FIELD_NULLABLE("address_street", "s", address_street, true);
		MYSQL_ADD_FIELD_NULLABLE("address_extend_json", "s", address_extend_json, true);
		MYSQL_ADD_FIELD_NULLABLE("nationality_code", "s", nationality_code, true);
		MYSQL_ADD_FIELD_NULLABLE("py_str", "s", py_str, true);
		MYSQL_ADD_FIELD_NULLABLE("wb_str", "s", wb_str, true);
		MYSQL_ADD_FIELD_NULLABLE("blood_type_abo", "i", blood_type_abo, true);
		MYSQL_ADD_FIELD_NULLABLE("blood_type_rh", "i", blood_type_rh, true);
		MYSQL_ADD_FIELD_NULLABLE("work_company", "s", work_company, true);
		MYSQL_ADD_FIELD_NULLABLE("native_place", "s", native_place, true);
		MYSQL_ADD_FIELD_NULLABLE("country_code", "s", country_code, true);
		MYSQL_ADD_FIELD_NULLABLE("link_name", "s", link_name, true);
		MYSQL_ADD_FIELD_NULLABLE("link_relation_code", "i", link_relation_code, true);
		MYSQL_ADD_FIELD_NULLABLE("link_telcom", "s", link_telcom, true);
		MYSQL_ADD_FIELD_NULLABLE("link_jsons", "s", link_jsons, true);
		MYSQL_ADD_FIELD_NULLABLE("deceased_date", "dt", deceased_date, true);
		MYSQL_ADD_FIELD_NULLABLE("deceased_reason", "s", deceased_reason, true);
		MYSQL_ADD_FIELD_NULLABLE("organization_id", "s", organization_id, false);
		MYSQL_ADD_FIELD_NULLABLE("merged_target_patient_id", "s", merged_target_patient_id, true);
		MYSQL_ADD_FIELD_NULLABLE("merged_at", "dt", merged_at, true);
	}

	PatientDO(PatientDO&&) = default;
	PatientDO& operator=(PatientDO&&) = default;
};

typedef std::shared_ptr<PatientDO> PtrPatientDO;

#endif // !_PATIENT_DO_
