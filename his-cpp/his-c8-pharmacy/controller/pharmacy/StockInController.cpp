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
#include "StockInController.h"
#include "../../service/pharmacy/StockInService.h"

StockInPageJsonVO::Wrapper StockInController::execQueryStockInList(const StockInQuery::Wrapper& query)
{
	return StockInService().listByCondition(query);
}

StockInJsonVO::Wrapper StockInController::execQueryStockInOne(const String& orderNo)
{
	return StockInService().queryOne(orderNo);
}

StringJsonVO::Wrapper StockInController::execCreateStockIn()
{
	return StockInService().create();
}

StringJsonVO::Wrapper StockInController::execSaveStockInDraft(const StockInSaveDTO::Wrapper& dto)
{
	return StockInService().saveDraft(dto);
}

StringJsonVO::Wrapper StockInController::execSaveAndSubmitStockIn(const StockInSaveDTO::Wrapper& dto)
{
	return StockInService().saveAndSubmit(dto);
}

StringJsonVO::Wrapper StockInController::execSubmitStockIn(const StockInRemoveDTO::Wrapper& dto)
{
	return StockInService().submit(dto);
}

StringJsonVO::Wrapper StockInController::execWithdrawStockIn(const StockInRemoveDTO::Wrapper& dto)
{
	return StockInService().withdraw(dto);
}

StringJsonVO::Wrapper StockInController::execApproveStockIn(const StockInApprovalDTO::Wrapper& dto)
{
	return StockInService().approve(dto);
}

StringJsonVO::Wrapper StockInController::execRejectStockIn(const StockInApprovalDTO::Wrapper& dto)
{
	return StockInService().reject(dto);
}

StringJsonVO::Wrapper StockInController::execRemoveStockIn(const StockInRemoveDTO::Wrapper& dto)
{
	return StockInService().remove(dto);
}
