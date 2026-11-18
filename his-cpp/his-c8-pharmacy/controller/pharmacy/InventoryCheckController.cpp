/*
 Copyright Zero One Star. All rights reserved.

 @Author: zjb517
 @Date: 2026/07/19 18:30:00

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
#include "stdafx.h"
#include "InventoryCheckController.h"
#include "../../service/pharmacy/InventoryCheckService.h"

InventoryCheckPageJsonVO::Wrapper InventoryCheckController::execQueryInventoryCheckList(const InventoryCheckQuery::Wrapper& query)
{
	return InventoryCheckService().listByCondition(query);
}

InventoryCheckJsonVO::Wrapper InventoryCheckController::execQueryInventoryCheckOne(const String& checkNo)
{
	return InventoryCheckService().queryOne(checkNo);
}

StringJsonVO::Wrapper InventoryCheckController::execCreateInventoryCheck()
{
	return InventoryCheckService().create();
}

StringJsonVO::Wrapper InventoryCheckController::execSaveInventoryCheckDraft(const InventoryCheckSaveDTO::Wrapper& dto)
{
	return InventoryCheckService().saveDraft(dto);
}

StringJsonVO::Wrapper InventoryCheckController::execSaveAndSubmitInventoryCheck(const InventoryCheckSaveDTO::Wrapper& dto)
{
	return InventoryCheckService().saveAndSubmit(dto);
}

StringJsonVO::Wrapper InventoryCheckController::execSubmitInventoryCheck(const InventoryCheckRemoveDTO::Wrapper& dto)
{
	return InventoryCheckService().submit(dto);
}

StringJsonVO::Wrapper InventoryCheckController::execWithdrawInventoryCheck(const InventoryCheckRemoveDTO::Wrapper& dto)
{
	return InventoryCheckService().withdraw(dto);
}

StringJsonVO::Wrapper InventoryCheckController::execApproveInventoryCheck(const InventoryCheckApprovalDTO::Wrapper& dto)
{
	return InventoryCheckService().approve(dto);
}

StringJsonVO::Wrapper InventoryCheckController::execRejectInventoryCheck(const InventoryCheckApprovalDTO::Wrapper& dto)
{
	return InventoryCheckService().reject(dto);
}

StringJsonVO::Wrapper InventoryCheckController::execRemoveInventoryCheck(const InventoryCheckRemoveDTO::Wrapper& dto)
{
	return InventoryCheckService().remove(dto);
}
