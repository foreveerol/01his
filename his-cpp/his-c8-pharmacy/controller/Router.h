#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/24 23:02:34

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
#ifndef _ROUTER_
#define _ROUTER_
#include "oatpp/web/server/api/Endpoint.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
using namespace oatpp::web::server;
using namespace oatpp::web::server::api;

// Pharmacy module route registration function
void registerPharmacyRouter(Endpoints* docEndpoints, HttpRouter* router);

/**
 * Server frontend route binding.
 * Defines the mapping between frontend access paths and backend API endpoints.
 * Swagger UI is accessible at: http://localhost:8090/swagger/ui
 */
class Router
{
private:
	// Document access endpoints
	Endpoints* docEndpoints;
	// Router instance
	HttpRouter* router;
public:
	// Constructor
	Router(Endpoints* docEndpoints, HttpRouter* router);
	// Initialize routes
	void initRouter();
};

#endif // !_ROUTER_