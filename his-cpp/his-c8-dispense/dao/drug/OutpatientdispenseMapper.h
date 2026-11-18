#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 14:21:55

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
#ifndef _OUTPATIENT_DISPENSE_MAPPER_
#define _OUTPATIENT_DISPENSE_MAPPER_

#include "Mapper.h"
#include "../../domain/do/drug/OutpatientDispenseDo.h"

//d.status_enum(1), d.quantity(2), d.dispense_quantity(3), "
//"d.lot_number(4), req.prescription_no(5, "
//"m.name(6,m.total_volume(7,m.manufacturer_text(8,p.name(9,p.gender_enum(10,e.bus_no(11,loc.name(12
class OutpatientdispenseMapper : public Mapper<OutpatientDispenseDo>
{
public:
	OutpatientDispenseDo mapper(ResultSet* resultSet) const override
	{
		OutpatientDispenseDo data;
		data.setstatusEnum(resultSet->getString(1));
		data.setmedQuantity(resultSet->getString(2));
		data.setdispenseQuantity(resultSet->getString(3));
		data.setlotNumber (resultSet->getString(4));
		data.setprescriptionNo(resultSet->getString(5));
		data.setmedName(resultSet->getString(6));
		data.settotalVolume(resultSet->getString(7));
		data.setmanufacturerText(resultSet->getString(8));
		data.setpatientName(resultSet->getString(9));
		data.setpatientGender(resultSet->getString(10));
		data.setbusNo(resultSet->getString(11));
		data.setlocName(resultSet->getString(12));
		
		return data;
    }
};
#endif

