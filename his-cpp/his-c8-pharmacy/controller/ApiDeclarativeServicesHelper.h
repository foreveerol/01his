#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2023/09/26 20:17:49

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
#ifndef _APIDECLARATIVESERVICESHELPER_H_
#define _APIDECLARATIVESERVICESHELPER_H_
/**
 * 声明式服务调用宏定义。
 * 此文件集中管理声明式服务类头文件的导入，便于统一管理和调用。
 */

 // 必须导入的头文件
#include "oatpp/core/data/mapping/ObjectMapper.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"
//////////////////////////////////////////////////////////////////////////
// #TIP: 在此导入项目ApiClient头文件



//////////////////////////////////////////////////////////////////////////

/**
 * 创建API客户端实例的宏。
 * @param _VAR_CLIENT_: 要创建的客户端变量名
 * @param _VAR_MAPPER_: 用于JSON序列化/反序列化的ObjectMapper变量名
 * @param _CLASS_CLIENT_: 客户端类名
 * @param _EXECUTOR_NAME_: HttpRequestExecutor组件名称（如"gateway"）
 */
#define API_CLIENT_CREATE(_VAR_CLIENT_, _VAR_MAPPER_, _CLASS_CLIENT_, _EXECUTOR_NAME_) \
OATPP_COMPONENT(std::shared_ptr<oatpp::web::client::HttpRequestExecutor>, requestExecutor, _EXECUTOR_NAME_); \
OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, _VAR_MAPPER_); \
auto _VAR_CLIENT_ = _CLASS_CLIENT_::createShared(requestExecutor, _VAR_MAPPER_)

#endif // !_APIDECLARATIVESERVICESHELPER_H_