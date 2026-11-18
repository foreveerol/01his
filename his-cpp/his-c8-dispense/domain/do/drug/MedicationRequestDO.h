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
#ifndef _MEDICATION_REQUEST_DO_
#define _MEDICATION_REQUEST_DO_
#include "../DoInclude.h"

/**
 * Medication request record entity (med_medication_request table)
 * Read-only DO, used for multi-table join queries
 */
class MedicationRequestDO : public BaseDO
{
	// req.bus_no
	MYSQL_SYNTHESIZE(string, bus_no, BusNo);
	// req.prescription_no
	MYSQL_SYNTHESIZE(string, prescription_no, PrescriptionNo);
	// req.status_enum
	MYSQL_SYNTHESIZE(string, status_enum, StatusEnum);
	// req.intent_enum
	MYSQL_SYNTHESIZE(string, intent_enum, IntentEnum);
	// req.category_enum
	MYSQL_SYNTHESIZE(string, category_enum, CategoryEnum);
	// req.medication_id
	MYSQL_SYNTHESIZE(string, medication_id, MedicationId);
	// req.patient_id
	MYSQL_SYNTHESIZE(string, patient_id, PatientId);
	// req.encounter_id
	MYSQL_SYNTHESIZE(string, encounter_id, EncounterId);
	// req.requester_id
	MYSQL_SYNTHESIZE(string, requester_id, RequesterId);
	// req.location_id
	MYSQL_SYNTHESIZE(string, location_id, LocationId);
	// req.quantity
	MYSQL_SYNTHESIZE(double, quantity, Quantity);
	// req.requester_id (as name)
	MYSQL_SYNTHESIZE(string, requester_name, RequesterName);
	// req.created_at
	MYSQL_SYNTHESIZE(string, created_at, CreatedAt);
	// req.req_authored_time
	MYSQL_SYNTHESIZE(string, req_authored_time, ReqAuthoredTime);
	// req.therapy_enum
	MYSQL_SYNTHESIZE(string, therapy_enum, TherapyEnum);

public:
	MedicationRequestDO() : BaseDO("med_medication_request")
	{
	}
	MedicationRequestDO(MedicationRequestDO&&) = default;
	MedicationRequestDO& operator=(MedicationRequestDO&&) = default;
};

typedef std::shared_ptr<MedicationRequestDO> PtrMedicationRequestDO;

#endif // !_MEDICATION_REQUEST_DO_
