#pragma once
#ifndef _OUTPATIENT_RETURN_DO_AWEI_H_
#define _OUTPATIENT_RETURN_DO_AWEI_H_

#include "../DoInclude.h"

class OutpatientReturnQueueDO : public BaseDO
{
	// 退药记录 ID
	MYSQL_SYNTHESIZE(string, id, Id);
	// 患者姓名
	MYSQL_SYNTHESIZE(string, patient_name, PatientName);
	// 退药申请时间
	MYSQL_SYNTHESIZE(string, return_date, ReturnDate);
	// 包含的药品种类/数量
	MYSQL_SYNTHESIZE(int, drug_count, DrugCount);
	// 当前退药状态 (RETURN, REFUNDED, RETURN_REJECTED等)
	MYSQL_SYNTHESIZE(string, return_status, ReturnStatus);

public:
	OutpatientReturnQueueDO() : BaseDO("med_medication_dispense") {}
	OutpatientReturnQueueDO(OutpatientReturnQueueDO&&) = default;
	OutpatientReturnQueueDO& operator=(OutpatientReturnQueueDO&&) = default;
};
class OutpatientReturnDetailDO : public BaseDO
{
	// 药品 ID
	MYSQL_SYNTHESIZE(string, drug_id, DrugId);
	// 药品名称
	MYSQL_SYNTHESIZE(string, drug_name, DrugName);
	// 退药数量
	MYSQL_SYNTHESIZE(int, quantity, Quantity);
	// 原始发药时间
	MYSQL_SYNTHESIZE(string, dispense_date, DispenseDate);

public:
	OutpatientReturnDetailDO() : BaseDO("med_medication_dispense") {}
	OutpatientReturnDetailDO(OutpatientReturnDetailDO&&) = default;
	OutpatientReturnDetailDO& operator=(OutpatientReturnDetailDO&&) = default;
};

#endif 