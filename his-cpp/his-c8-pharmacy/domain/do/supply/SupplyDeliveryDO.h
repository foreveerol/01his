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
#ifndef _SUPPLY_DELIVERY_DO_
#define _SUPPLY_DELIVERY_DO_
#include "../DoInclude.h"

/**
 * 供应配送执行数据库实体（wkf_supply_delivery 表）
 */
class SupplyDeliveryDO : public BaseDO
{
	// 主键
	MYSQL_SYNTHESIZE(string, id, Id);
	// 关联供应申请
	MYSQL_SYNTHESIZE(string, request_id, RequestId);
	// 配送状态
	MYSQL_SYNTHESIZE(string, status_enum, StatusEnum);
	// 软删除标记
	MYSQL_SYNTHESIZE(int, is_deleted, IsDeleted);
	// 删除时间
	MYSQL_SYNTHESIZE(string, deleted_at, DeletedAt);
	// 删除操作人
	MYSQL_SYNTHESIZE(string, deleted_by, DeletedBy);
public:
	SupplyDeliveryDO() : BaseDO("wkf_supply_delivery")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("request_id", "s", request_id);
		MYSQL_ADD_FIELD("status_enum", "s", status_enum);
		MYSQL_ADD_FIELD("is_deleted", "i", is_deleted);
		MYSQL_ADD_FIELD("deleted_at", "s", deleted_at);
		MYSQL_ADD_FIELD("deleted_by", "s", deleted_by);
	}

	SupplyDeliveryDO(SupplyDeliveryDO&&) = default;
	SupplyDeliveryDO& operator=(SupplyDeliveryDO&&) = default;
};

typedef std::shared_ptr<SupplyDeliveryDO> PtrSupplyDeliveryDO;
#endif // !_SUPPLY_DELIVERY_DO_
