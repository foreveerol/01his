#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:52:32

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
#ifndef _DISPENSE_RECORD_DO_
#define _DISPENSE_RECORD_DO_
#include "../DoInclude.h"

/**
 * Outpatient dispense/return record database view entity (multi-table join result)
 */
class DispenseRecordDO : public BaseDO
{
    // d.bus_no
    MYSQL_SYNTHESIZE(string, bus_no, BusNo);
    // d.status_enum
    MYSQL_SYNTHESIZE(string, status_enum, StatusEnum);
    // d.dispense_time
    MYSQL_SYNTHESIZE(string, dispense_time, DispenseTime);
    // p.name
    MYSQL_SYNTHESIZE(string, patient_name, PatientName);
    // p.id_card
    MYSQL_SYNTHESIZE(string, id_card, IdCard);
    // e.bus_no
    MYSQL_SYNTHESIZE(string, encounter_bus_no, EncounterBusNo);
    // m.name
    MYSQL_SYNTHESIZE(string, medication_name, MedicationName);
    // m.total_volume
    MYSQL_SYNTHESIZE(string, total_volume, TotalVolume);
    // m.dose_form_code
    MYSQL_SYNTHESIZE(string, dose_form_code, DoseFormCode);
    // d.quantity
    MYSQL_SYNTHESIZE(string, quantity, Quantity);
    // d.dispense_quantity
    MYSQL_SYNTHESIZE(string, dispense_quantity, DispenseQuantity);
    // d.unit_code
    MYSQL_SYNTHESIZE(string, unit_code, UnitCode);
    // d.lot_number
    MYSQL_SYNTHESIZE(string, lot_number, LotNumber);
    // pr.name
    MYSQL_SYNTHESIZE(string, practitioner_name, PractitionerName);
    // loc.name
    MYSQL_SYNTHESIZE(string, location_name, LocationName);
    // req.prescription_no
    MYSQL_SYNTHESIZE(string, prescription_no, PrescriptionNo);
    // req.requester_id
    MYSQL_SYNTHESIZE(string, requester_id, RequesterId);
    // d.created_at
    MYSQL_SYNTHESIZE(string, created_at, CreatedAt);
public:
    DispenseRecordDO() : BaseDO("med_medication_dispense")
    {
    }
    DispenseRecordDO(DispenseRecordDO&&) = default;
    DispenseRecordDO& operator=(DispenseRecordDO&&) = default;
};

typedef std::shared_ptr<DispenseRecordDO> PtrDispenseRecordDO;
#endif // !_DISPENSE_RECORD_DO_
