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
#ifndef _MEDICATION_DISPENSE_DO_
#define _MEDICATION_DISPENSE_DO_
#include "../DoInclude.h"

/**
 * Medication dispense record database entity (med_medication_dispense table)
 * Used for outpatient/inpatient dispensing and drug return CRUD operations
 */
class MedicationDispenseDO : public BaseDO
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
	MYSQL_SYNTHESIZE(string, status_enum, StatusEnum);
	MYSQL_SYNTHESIZE(string, not_performed_reason_enum, NotPerformedReasonEnum);
	MYSQL_SYNTHESIZE(string, status_changed_time, StatusChangedTime);
	MYSQL_SYNTHESIZE(string, dispense_enum, DispenseEnum);
	MYSQL_SYNTHESIZE(string, medication_id, MedicationId);
	MYSQL_SYNTHESIZE(string, patient_id, PatientId);
	MYSQL_SYNTHESIZE(string, encounter_id, EncounterId);
	MYSQL_SYNTHESIZE(string, location_id, LocationId);
	MYSQL_SYNTHESIZE(string, med_req_id, MedReqId);
	MYSQL_SYNTHESIZE(double, quantity, Quantity);
	MYSQL_SYNTHESIZE(string, unit_code, UnitCode);
	MYSQL_SYNTHESIZE(double, dispense_quantity, DispenseQuantity);
	MYSQL_SYNTHESIZE(string, lot_number, LotNumber);
	MYSQL_SYNTHESIZE(string, trace_no, TraceNo);
	MYSQL_SYNTHESIZE(string, preparer_id, PreparerId);
	MYSQL_SYNTHESIZE(string, prepare_time, PrepareTime);
	MYSQL_SYNTHESIZE(string, practitioner_id, PractitionerId);
	MYSQL_SYNTHESIZE(string, dispense_time, DispenseTime);
	MYSQL_SYNTHESIZE(string, limit_time, LimitTime);
	MYSQL_SYNTHESIZE(string, planned_dispense_time, PlannedDispenseTime);
	MYSQL_SYNTHESIZE(string, procedure_id, ProcedureId);
	MYSQL_SYNTHESIZE(string, summary_no, SummaryNo);
	MYSQL_SYNTHESIZE(string, des_location_id, DesLocationId);
	MYSQL_SYNTHESIZE(string, rec_practitioner_id, RecPractitionerId);
	MYSQL_SYNTHESIZE(string, dosage_instruction, DosageInstruction);
	MYSQL_SYNTHESIZE(string, method_code, MethodCode);
	MYSQL_SYNTHESIZE(string, frequency_code, FrequencyCode);
	MYSQL_SYNTHESIZE(double, dose, Dose);
	MYSQL_SYNTHESIZE(string, dose_unit_code, DoseUnitCode);

public:
	MedicationDispenseDO()
		: BaseDO("med_medication_dispense")
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
		MYSQL_ADD_FIELD_NULLABLE("status_enum", "s", status_enum, false);
		MYSQL_ADD_FIELD_NULLABLE("not_performed_reason_enum", "s", not_performed_reason_enum, true);
		MYSQL_ADD_FIELD_NULLABLE("status_changed_time", "dt", status_changed_time, true);
		MYSQL_ADD_FIELD_NULLABLE("dispense_enum", "s", dispense_enum, false);
		MYSQL_ADD_FIELD_NULLABLE("medication_id", "s", medication_id, false);
		MYSQL_ADD_FIELD_NULLABLE("patient_id", "s", patient_id, false);
		MYSQL_ADD_FIELD_NULLABLE("encounter_id", "s", encounter_id, false);
		MYSQL_ADD_FIELD_NULLABLE("location_id", "s", location_id, false);
		MYSQL_ADD_FIELD_NULLABLE("med_req_id", "s", med_req_id, false);
		MYSQL_ADD_FIELD_NULLABLE("quantity", "d", quantity, false);
		MYSQL_ADD_FIELD_NULLABLE("unit_code", "s", unit_code, false);
		MYSQL_ADD_FIELD_NULLABLE("dispense_quantity", "d", dispense_quantity, true);
		MYSQL_ADD_FIELD_NULLABLE("lot_number", "s", lot_number, true);
		MYSQL_ADD_FIELD_NULLABLE("trace_no", "s", trace_no, true);
		MYSQL_ADD_FIELD_NULLABLE("preparer_id", "s", preparer_id, true);
		MYSQL_ADD_FIELD_NULLABLE("prepare_time", "dt", prepare_time, true);
		MYSQL_ADD_FIELD_NULLABLE("practitioner_id", "s", practitioner_id, true);
		MYSQL_ADD_FIELD_NULLABLE("dispense_time", "dt", dispense_time, true);
		MYSQL_ADD_FIELD_NULLABLE("limit_time", "dt", limit_time, true);
		MYSQL_ADD_FIELD_NULLABLE("planned_dispense_time", "dt", planned_dispense_time, true);
		MYSQL_ADD_FIELD_NULLABLE("procedure_id", "s", procedure_id, true);
		MYSQL_ADD_FIELD_NULLABLE("summary_no", "s", summary_no, true);
		MYSQL_ADD_FIELD_NULLABLE("des_location_id", "s", des_location_id, true);
		MYSQL_ADD_FIELD_NULLABLE("rec_practitioner_id", "s", rec_practitioner_id, true);
		MYSQL_ADD_FIELD_NULLABLE("dosage_instruction", "s", dosage_instruction, true);
		MYSQL_ADD_FIELD_NULLABLE("method_code", "s", method_code, true);
		MYSQL_ADD_FIELD_NULLABLE("frequency_code", "s", frequency_code, true);
		MYSQL_ADD_FIELD_NULLABLE("dose", "d", dose, true);
		MYSQL_ADD_FIELD_NULLABLE("dose_unit_code", "s", dose_unit_code, true);
	}

	MedicationDispenseDO(MedicationDispenseDO&&) = default;
	MedicationDispenseDO& operator=(MedicationDispenseDO&&) = default;
};

typedef std::shared_ptr<MedicationDispenseDO> PtrMedicationDispenseDO;

#endif // !_MEDICATION_DISPENSE_DO_
