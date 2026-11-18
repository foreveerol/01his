/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/12/03 14:58:34

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
#include "Router.h"
#include "ApiHelper.h"

#include "drug/OutpatientDispenseController.h"
#include "drug/InpatientDispenseController.h"
#include "drug/DrugReturnController.h"
#include "drug/InpatientRecordController.h"
#include "drug/OutpatientRecordController.h"
#include "drug/OutpatientReturnController.h"

// If Swagger document is disabled
#ifdef CLOSE_SWAGGER_DOC
// Simplified controller binding macro
#define ROUTER_SIMPLE_BIND(__CLASS__) \
router->addController(__CLASS__::createShared())
#else
// Simplified controller binding macro (with Swagger support)
#define ROUTER_SIMPLE_BIND(__CLASS__) \
BIND_CONTROLLER(docEndpoints, router, __CLASS__)
#endif



Router::Router(Endpoints* docEndpoints, HttpRouter* router)
{
	this->docEndpoints = docEndpoints;
	this->router = router;
}

void Router::initRouter()
{
	// Outpatient dispense controller
	ROUTER_SIMPLE_BIND(OutpatientDispenseController);
	// Inpatient dispense controller
	ROUTER_SIMPLE_BIND(InpatientDispenseController);
	// Inpatient return controller
	ROUTER_SIMPLE_BIND(DrugReturnController);
	// Inpatient record controller
	ROUTER_SIMPLE_BIND(InpatientRecordController);
	// Outpatient record controller
	ROUTER_SIMPLE_BIND(OutpatientRecordController);
	// Outpatient return controller
	ROUTER_SIMPLE_BIND(OutpatientReturnController);
}
