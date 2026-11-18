#pragma once

 
#ifndef _Outpatient_Dispense_DO_
#define _Outpatient_Dispense_DO_
#include "../DoInclude.h"


 //Outpatient dispense/return record database view entity (multi-table join result)
 
class OutpatientDispenseDo : public BaseDO
{
    
    
    // d.status_enum 发药状态
    MYSQL_SYNTHESIZE(string, status_enum, statusEnum);
    // d.quantity 药品数量
    MYSQL_SYNTHESIZE(string, med_quantity, medQuantity);
    // d.dispense_quantity 发药药品数量
    MYSQL_SYNTHESIZE(string, dispense_quantity, dispenseQuantity);
    // d.lot_number //药品批号
    MYSQL_SYNTHESIZE(string, lot_number, lotNumber);
    //req.prescription_no 处方号
    MYSQL_SYNTHESIZE(string, prescription_no, prescriptionNo);
    // m.name 药品名称
    MYSQL_SYNTHESIZE(string, med_name, medName);
    // m.total_volume 药品规格
    MYSQL_SYNTHESIZE(string, total_volume, totalVolume);
    //m.manufacturer_text 生产厂家
    MYSQL_SYNTHESIZE(string, manufacturer_text, manufacturerText);
    // p.name
    MYSQL_SYNTHESIZE(string, patient_name, patientName);
    // p.gender_enum
    MYSQL_SYNTHESIZE(string, patient_gender_enum, patientGender);
    //p.patient_id 患者id
    MYSQL_SYNTHESIZE(string, patient_id, patientId);
    // e.bus_no 患者就诊号
    MYSQL_SYNTHESIZE(string, bus_no, busNo);
    //org.name 科室名称
    MYSQL_SYNTHESIZE(string, org_name, orgName);
	//d.status_enum 发药状态
    MYSQL_SYNTHESIZE(string, dispense_status, dispenseStatus);
	//e.class_enum 就诊类型
    MYSQL_SYNTHESIZE(string, class_enum, classEnum);
	//loc.name 药房名称
    MYSQL_SYNTHESIZE(string, loc_name, locName);
    
  
public:
    OutpatientDispenseDo() : BaseDO("med_medication_dispense")
    {
    }
    OutpatientDispenseDo(OutpatientDispenseDo&&) = default;
    OutpatientDispenseDo& operator=(OutpatientDispenseDo&&) = default;
};

typedef std::shared_ptr<OutpatientDispenseDo> PtrOutpatientDispenseDO;
#endif 
