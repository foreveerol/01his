/*
 Copyright Zero One Star. All rights reserved.

 @Author: juhao
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
#ifndef _INPATIENT_DISPENSE_MAPPER_
#define _INPATIENT_DISPENSE_MAPPER_

#include "Mapper.h"

/**
 * 住院发药汇总队列查询结果 DO（只读）
 * 用于展示汇总队列列表
 */
class InpatientSummaryDO : public BaseDO
{
	// 汇总单据ID（由 summary_no 映射）
	MYSQL_SYNTHESIZE(string, id, Id);
	// 汇总单据号
	MYSQL_SYNTHESIZE(string, summary_no, SummaryNo);
	// 汇总状态
	MYSQL_SYNTHESIZE(string, summary_status, SummaryStatus);
	// 创建时间（相关记录的最早创建时间）
	MYSQL_SYNTHESIZE(string, create_time, CreateTime);
	// 药房名称
	MYSQL_SYNTHESIZE(string, pharmacy, Pharmacy);
	// 申请人姓名
	MYSQL_SYNTHESIZE(string, applicant, Applicant);
public:
	InpatientSummaryDO() : BaseDO("med_medication_dispense") {}
	InpatientSummaryDO(InpatientSummaryDO&&) = default;
	InpatientSummaryDO& operator=(InpatientSummaryDO&&) = default;
};

/**
 * 住院汇总队列字段映射
 * SELECT 列顺序：
 * d.summary_no(1), d.summary_no(2), d.status_enum(3),
 * MIN(d.created_at)(4), COALESCE(loc.name,'')(5), COALESCE(pr.name,'')(6)
 */
class InpatientSummaryMapper : public Mapper<InpatientSummaryDO>
{
public:
	InpatientSummaryDO mapper(ResultSet* resultSet) const override
	{
		InpatientSummaryDO data;
		data.setId(resultSet->getString(2));
		data.setSummaryNo(resultSet->getString(2));
		data.setSummaryStatus(resultSet->getString(3));
		data.setCreateTime(resultSet->getString(4));
		data.setPharmacy(resultSet->getString(5));
		data.setApplicant(resultSet->getString(6));
		return data;
	}
};

/**
 * 住院药品明细查询结果 DO（只读）
 * 用于展示指定汇总单据的药品项目
 */
class InpatientDrugItemDO : public BaseDO
{
	// 明细项ID
	MYSQL_SYNTHESIZE(string, detail_id, DetailId);
	// 序号（自动生成）
	MYSQL_SYNTHESIZE(int, serial_no, SerialNo);
	// 药品名称
	MYSQL_SYNTHESIZE(string, drug_name, DrugName);
	// 发药数量
	MYSQL_SYNTHESIZE(string, quantity, Quantity);
	// 药品规格
	MYSQL_SYNTHESIZE(string, specification, Specification);
public:
	InpatientDrugItemDO() : BaseDO("med_medication_dispense") {}
	InpatientDrugItemDO(InpatientDrugItemDO&&) = default;
	InpatientDrugItemDO& operator=(InpatientDrugItemDO&&) = default;
};

/**
 * 住院药品明细字段映射
 * SELECT 列顺序：
 * d.id(1), ROW_NUMBER()(2), m.name(3), CAST(d.dispense_quantity AS CHAR)(4), m.total_volume(5)
 */
class InpatientDrugItemMapper : public Mapper<InpatientDrugItemDO>
{
public:
	InpatientDrugItemDO mapper(ResultSet* resultSet) const override
	{
		InpatientDrugItemDO data;
		data.setDetailId(resultSet->getString(1));
		data.setSerialNo(resultSet->getInt(2));
		data.setDrugName(resultSet->getString(3));
		data.setQuantity(resultSet->getString(4));
		data.setSpecification(resultSet->getString(5));
		return data;
	}
};

#endif // !_INPATIENT_DISPENSE_MAPPER_