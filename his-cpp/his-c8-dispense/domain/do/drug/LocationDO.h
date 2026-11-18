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
#ifndef _LOCATION_DO_
#define _LOCATION_DO_
#include "../DoInclude.h"

/**
 * Location database entity (adm_location table)
 * Represents a department/ward in the hospital information system
 */
class LocationDO : public BaseDO
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
	MYSQL_SYNTHESIZE(string, name, Name);
	MYSQL_SYNTHESIZE(string, bus_no, BusNo);
	MYSQL_SYNTHESIZE(string, status_enum, StatusEnum);
	MYSQL_SYNTHESIZE(string, operational_enum, OperationalEnum);
	MYSQL_SYNTHESIZE(string, form_enum, FormEnum);
	MYSQL_SYNTHESIZE(string, mode_enum, ModeEnum);
	MYSQL_SYNTHESIZE(string, type_json, TypeJson);
	MYSQL_SYNTHESIZE(string, organization_id, OrganizationId);
	MYSQL_SYNTHESIZE(int, display_order, DisplayOrder);
	MYSQL_SYNTHESIZE(string, py_str, PyStr);
	MYSQL_SYNTHESIZE(string, wb_str, WbStr);
	MYSQL_SYNTHESIZE(string, parent_id, ParentId);

public:
	LocationDO()
		: BaseDO("adm_location")
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
		MYSQL_ADD_FIELD_NULLABLE("name", "s", name, false);
		MYSQL_ADD_FIELD_NULLABLE("bus_no", "s", bus_no, false);
		MYSQL_ADD_FIELD_NULLABLE("status_enum", "s", status_enum, false);
		MYSQL_ADD_FIELD_NULLABLE("operational_enum", "s", operational_enum, true);
		MYSQL_ADD_FIELD_NULLABLE("form_enum", "s", form_enum, true);
		MYSQL_ADD_FIELD_NULLABLE("mode_enum", "s", mode_enum, true);
		MYSQL_ADD_FIELD_NULLABLE("type_json", "s", type_json, true);
		MYSQL_ADD_FIELD_NULLABLE("organization_id", "s", organization_id, false);
		MYSQL_ADD_FIELD_NULLABLE("display_order", "i", display_order, true);
		MYSQL_ADD_FIELD_NULLABLE("py_str", "s", py_str, true);
		MYSQL_ADD_FIELD_NULLABLE("wb_str", "s", wb_str, true);
		MYSQL_ADD_FIELD_NULLABLE("parent_id", "s", parent_id, true);
	}

	LocationDO(LocationDO&&) = default;
	LocationDO& operator=(LocationDO&&) = default;
};

typedef std::shared_ptr<LocationDO> PtrLocationDO;

#endif // !_LOCATION_DO_
