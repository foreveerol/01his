#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/11/30 16:07:52

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
#ifndef _API_HELPER_
#define _API_HELPER_

#include <string>
// Oat++核心库头文件
#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
// 文件上传相关头文件
#include "oatpp/web/mime/multipart/InMemoryDataProvider.hpp"
#include "oatpp/web/mime/multipart/FileProvider.hpp"
#include "oatpp/web/mime/multipart/Reader.hpp"
#include "oatpp/web/mime/multipart/PartList.hpp"
#include "oatpp/web/protocol/http/outgoing/BufferBody.hpp"
// Swagger文档相关头文件
#include "oatpp-swagger/Types.hpp"
// 本模块封装相关头文件
#include "domain/vo/JsonVO.h"
#include "domain/dto/PageDTO.h"
#include "CustomerAuthorizeHandler.h"
#include "URIUtil.h"
using namespace std;
using namespace oatpp::web::protocol::http;

/**
 * 绑定控制器到文档和路由器
 * @param __DOC__: 文档对象指针
 * @param __ROUTER__: 路由器对象指针
 * @param __CLASS__: 控制器类名
 */
#define BIND_CONTROLLER(__DOC__, __ROUTER__, __CLASS__) \
__DOC__->append(__ROUTER__->addController(__CLASS__::createShared())->getEndpoints())

/**
 * 控制器访问声明宏，用于创建带授权处理器的控制器
 * @param __CLASS__: 控制器类名
 */
#define API_ACCESS_DECLARE(__CLASS__) \
public: \
__CLASS__(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) : oatpp::web::server::api::ApiController(objectMapper) { \
	setDefaultAuthorizationHandler(std::make_shared<CustomerAuthorizeHandler>()); \
} \
static std::shared_ptr<__CLASS__> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) { \
	return std::make_shared<__CLASS__>(objectMapper); \
}

// GET请求方式
#define API_M_GET  "GET"
// POST请求方式
#define API_M_POST "POST"
// PUT请求方式
#define API_M_PUT  "PUT"
// DELETE请求方式
#define API_M_DEL  "DELETE"
// Token在请求头中对应的键名
#define API_H_TOKEN "Authorization"
// WebSocket Token在请求头中对应的键名
#define API_H_WS_TOKEN "Sec-WebSocket-Protocol"

//////////////////////////////////////////////////////////////////////////

/**
 * API端点信息添加标题
 * @param _TITLE_: 接口标题
 */
#define API_DEF_ADD_TITLE(_TITLE_) info->summary = _TITLE_

// API端点信息添加安全认证
#define API_DEF_ADD_AUTH() info->addSecurityRequirement("bearer_auth")

/**
 * API端点信息添加标签
 * @param _TAG_: 标签名称
 */
#define API_DEF_ADD_TAG(_TAG_) info->addTag(_TAG_)

// API端点信息添加文件上传，用于流式文件上传
#define API_DEF_ADD_FILE_STREAM() info->addConsumes<oatpp::swagger::Binary>("application/octet-stream")

/**
 * API端点信息添加文件上传，用于表单方式上传文件（支持多文件上传）
 * @param _TYPE_: 数据体类型，如：xxxDTO::Wrapper
 */
#define API_DEF_ADD_FILE_FORM(_TYPE_) info->addConsumes<_TYPE_>("multipart/form-data")

/**
 * API端点信息添加响应体
 * @param __RESP_TYPE__: 响应体类型，如：xxxJsonVO::Wrapper
 */
#define API_DEF_ADD_RSP_JSON(__RESP_TYPE__) info->addResponse<__RESP_TYPE__>(Status::CODE_200, "application/json")

/**
 * API端点信息添加响应数据，由oatpp::Object包装后返回
 * @param __RESP_TYPE__: 响应体类型，如：xxxJsonVO
 */
#define API_DEF_ADD_RSP_JSON_WRAPPER(__RESP_TYPE__) API_DEF_ADD_RSP_JSON(oatpp::Object<__RESP_TYPE__>)

/**
 * API端点信息通用定义
 * @param _TITLE_: 接口标题
 * @param __RESP_TYPE__: 接口响应体类型，如："UserPageJsonVO::Wrapper"、"StringJsonVO::Wrapper"
 * @param __TAG__: 标签名称
 */
#define API_DEF_ADD_COMMON(_TITLE_, __RESP_TYPE__, __TAG__) \
API_DEF_ADD_TITLE(_TITLE_); \
API_DEF_ADD_TAG(__TAG__); \
API_DEF_ADD_RSP_JSON(__RESP_TYPE__)

/**
 * API端点信息通用定义，带授权认证
 * @param _TITLE_: 接口标题
 * @param __RESP_TYPE__: 接口响应体类型，如："UserPageJsonVO::Wrapper"、"StringJsonVO::Wrapper"
 * @param __TAG__: 标签名称
 */
#define API_DEF_ADD_COMMON_AUTH(_TITLE_, __RESP_TYPE__, __TAG__) \
API_DEF_ADD_AUTH(); \
API_DEF_ADD_COMMON(_TITLE_, __RESP_TYPE__, __TAG__)

// 跨平台分页参数描述信息
#ifndef LINUX
#define API_PAGE_INDEX_DESC u8"查询页码"
#define API_PAGE_SIZE_DESC u8"查询条数"
#else
#define API_PAGE_INDEX_DESC "page index"
#define API_PAGE_SIZE_DESC "page size"
#endif
// API端点信息添加分页参数说明
#define API_DEF_ADD_PAGE_PARAMS() \
info->queryParams.add<UInt64>("pageIndex").description = API_PAGE_INDEX_DESC;\
info->queryParams["pageIndex"].addExample("default", oatpp::UInt64(1)); \
info->queryParams.add<UInt64>("pageSize").description = API_PAGE_SIZE_DESC; \
info->queryParams["pageSize"].addExample("default", oatpp::UInt64(10))

/**
 * API端点信息添加查询参数说明
 * @param _TYPE_: 字段数据类型，如：String、UInt32
 * @param _FIELD_NAME_: 字段名称，如："age"、"sex"
 * @param _DESCRIPTION_: 字段描述
 * @param _EXAMPLE_VAL_: 示例值，如："li si"、123
 * @param _REQUIRE_: 是否必填，bool值，如：true、false
 */
#define API_DEF_ADD_QUERY_PARAMS(_TYPE_, _FIELD_NAME_, _DESCRIPTION_, _EXAMPLE_VAL_, _REQUIRE_) \
info->queryParams.add<_TYPE_>(_FIELD_NAME_).description = _DESCRIPTION_; \
info->queryParams[_FIELD_NAME_].addExample("default", _TYPE_(_EXAMPLE_VAL_)); \
info->queryParams[_FIELD_NAME_].required = _REQUIRE_

/**
 * API端点信息添加路径参数说明
 * @param _TYPE_: 字段数据类型，如：String、UInt32
 * @param _FIELD_NAME_: 字段名称，如："age"、"sex"
 * @param _DESCRIPTION_: 字段描述
 * @param _EXAMPLE_VAL_: 示例值，如："li si"、123
 * @param _REQUIRE_: 是否必填，bool值，如：true、false
 */
#define API_DEF_ADD_PATH_PARAMS(_TYPE_, _FIELD_NAME_, _DESCRIPTION_, _EXAMPLE_VAL_, _REQUIRE_) \
info->pathParams.add<_TYPE_>(_FIELD_NAME_).description = _DESCRIPTION_; \
info->pathParams[_FIELD_NAME_].addExample("default", _TYPE_(_EXAMPLE_VAL_)); \
info->pathParams[_FIELD_NAME_].required = _REQUIRE_

// 宏参数展开辅助，用于展开变参宏中的可变参数
#define API_DEF_EXPAND( x ) x
// 空参数占位符
#define API_DEF_NOTHING

/**
 * API端点信息定义
 * @param __TITLE__: Api端点标题
 * @param __ENDPOINT_FUN_NAME__: Api端点函数名称
 * @param __RESP_TYPE__: 响应体类型，如：XxxJsonVO::Wrapper
 * @param __TAG__: Api端点标签
 * @param ...: 扩展选项
 */
#define API_DEF_ENDPOINT_INFO(__TITLE__, __ENDPOINT_FUN_NAME__, __RESP_TYPE__, __TAG__, ...) \
ENDPOINT_INFO(__ENDPOINT_FUN_NAME__) { \
	API_DEF_ADD_COMMON(__TITLE__, __RESP_TYPE__, __TAG__); \
	API_DEF_EXPAND(API_DEF_NOTHING __VA_ARGS__) \
}

/**
 * API端点信息定义，带授权认证
 * @param __TITLE__: Api端点标题
 * @param __ENDPOINT_FUN_NAME__: Api端点函数名称
 * @param __RESP_TYPE__: 响应体类型，如：XxxJsonVO::Wrapper
 * @param __TAG__: Api端点标签
 * @param ...: 扩展选项
 */
#define API_DEF_ENDPOINT_INFO_AUTH(__TITLE__, __ENDPOINT_FUN_NAME__, __RESP_TYPE__, __TAG__, ...) \
ENDPOINT_INFO(__ENDPOINT_FUN_NAME__) { \
	API_DEF_ADD_COMMON_AUTH(__TITLE__, __RESP_TYPE__, __TAG__); \
	API_DEF_EXPAND(API_DEF_NOTHING __VA_ARGS__) \
}

/**
 * 根据Query类型自动构建Api查询参数文档信息
 * @param __QUERY_TYPE__: 查询对象类型，如：XxxQuery
*/
#define API_DEF_QUERY_PARAM_BUILD( __QUERY_TYPE__) \
auto tmp = __QUERY_TYPE__::createShared(); \
for (auto one : __QUERY_TYPE__::Wrapper::getPropertiesMap()) { \
	web::server::api::Endpoint::Info::Param* param = nullptr; \
	auto type = one.second->type; \
	if (type == oatpp::String::Class::getType()) \
		param = &(info->queryParams.add<oatpp::String>(one.first.c_str())); \
	else if (type == oatpp::Int32::Class::getType())\
		param = &(info->queryParams.add<oatpp::Int32>(one.first.c_str())); \
	else if (type == oatpp::UInt32::Class::getType())\
		param = &(info->queryParams.add<oatpp::UInt32>(one.first.c_str())); \
	else if (type == oatpp::Int64::Class::getType())\
		param = &(info->queryParams.add<oatpp::Int64>(one.first.c_str())); \
	else if (type == oatpp::UInt64::Class::getType())\
		param = &(info->queryParams.add<oatpp::UInt64>(one.first.c_str())); \
	else if (type == oatpp::Float32::Class::getType())\
		param = &(info->queryParams.add<oatpp::Float32>(one.first.c_str())); \
	else if (type == oatpp::Float64::Class::getType())\
		param = &(info->queryParams.add<oatpp::Float64>(one.first.c_str())); \
	else if (type == oatpp::Boolean::Class::getType())\
		param = &(info->queryParams.add<oatpp::Boolean>(one.first.c_str())); \
	if(param){ \
		param->description = one.second->info.description; \
		if(tmp[one.first]) \
			param->addExample("default", tmp[one.first]); \
		param->required = one.second->info.required; \
	} \
}

/**
 * API端点信息定义，用于查询接口
 * @param __TITLE__: Api端点标题
 * @param __ENDPOINT_FUN_NAME__: Api端点函数名称
 * @param __QUERY_TYPE__: 查询对象类型，如：XxxQuery
 * @param __RESP_TYPE__: 响应体类型，如：XxxJsonVO::Wrapper
 * @param __TAG__: Api端点标签
 */
#define API_DEF_ENDPOINT_INFO_QUERY(__TITLE__, __ENDPOINT_FUN_NAME__, __QUERY_TYPE__, __RESP_TYPE__, __TAG__) \
API_DEF_ENDPOINT_INFO(__TITLE__, __ENDPOINT_FUN_NAME__, __RESP_TYPE__, __TAG__, API_DEF_QUERY_PARAM_BUILD(__QUERY_TYPE__);)

/**
 * API端点信息定义，用于查询接口，带授权认证
 * @param __TITLE__: Api端点标题
 * @param __ENDPOINT_FUN_NAME__: Api端点函数名称
 * @param __QUERY_TYPE__: 查询对象类型，如：XxxQuery
 * @param  __RESP_TYPE__: 响应体类型，如：XxxJsonVO::Wrapper
 * @param __TAG__: Api端点标签
 */
#define API_DEF_ENDPOINT_INFO_QUERY_AUTH(__TITLE__, __ENDPOINT_FUN_NAME__, __QUERY_TYPE__, __RESP_TYPE__, __TAG__) \
API_DEF_ENDPOINT_INFO_AUTH(__TITLE__, __ENDPOINT_FUN_NAME__, __RESP_TYPE__, __TAG__, API_DEF_QUERY_PARAM_BUILD(__QUERY_TYPE__);)

/**
 * API端点信息定义，用于需要支持文件上传的接口信息定义
 * @param __TITLE__: Api端点标题
 * @param __ENDPOINT_FUN_NAME__: Api端点函数名称
 * @param __FORMDATA_TYPE__: 上传文件数据类型，如：XxxDTO::Wrapper
 * @param __RESP_TYPE__: 响应体类型，如：XxxJsonVO::Wrapper
 * @param __TAG__: Api端点标签
 */
#define API_DEF_ENDPOINT_INFO_FILE(__TITLE__, __ENDPOINT_FUN_NAME__, __FORMDATA_TYPE__, __RESP_TYPE__, __TAG__) \
API_DEF_ENDPOINT_INFO(__TITLE__, __ENDPOINT_FUN_NAME__, __RESP_TYPE__, __TAG__, API_DEF_ADD_FILE_FORM(__FORMDATA_TYPE__);)

/**
 * API端点信息定义，用于需要支持文件上传的接口信息定义，带授权认证
 * @param __TITLE__: Api端点标题
 * @param __ENDPOINT_FUN_NAME__: Api端点函数名称
 * @param __FORMDATA_TYPE__: 上传文件数据类型，如：XxxDTO::Wrapper
 * @param __RESP_TYPE__: 响应体类型，如：XxxJsonVO::Wrapper
 * @param __TAG__: Api端点标签
 */
#define API_DEF_ENDPOINT_INFO_FILE_AUTH(__TITLE__, __ENDPOINT_FUN_NAME__, __FORMDATA_TYPE__, __RESP_TYPE__, __TAG__) \
API_DEF_ENDPOINT_INFO_AUTH(__TITLE__, __ENDPOINT_FUN_NAME__, __RESP_TYPE__, __TAG__, API_DEF_ADD_FILE_FORM(__FORMDATA_TYPE__);)

//////////////////////////////////////////////////////////////////////////

// 接口处理器分页参数提取宏
#define API_HANDLER_PAGE_PARAME \
QUERY(UInt64, pageIndex), \
QUERY(UInt64, pageSize)

// 接口处理器授权参数提取宏
#define API_HANDLER_AUTH_PARAME \
AUTHORIZATION(std::shared_ptr<CustomerAuthorizeObject>, authObject)

// 授权请求头
#define API_HANDLER_AUTN_HEADER HEADER(oatpp::String, token, API_H_TOKEN)

/**
 * 接口处理器从查询参数构建查询对象
 * @param __VAR__: 转换后的变量名称，如：query
 * @param __TYPE__: 查询数据类型，如：XxxQuery
 * @param __PARAMS__: QueryParams的变量名称，如：QUERIES(QueryParams, queryParams)
 */
#define API_HANDLER_QUERY_PARAM(__VAR__, __TYPE__, __PARAMS__) \
auto __VAR__ = __TYPE__::createShared(); \
for (auto& param : __PARAMS__.getAll()) { \
	auto data = param.second.getMemoryHandle().get(); \
	auto typeval = __VAR__[param.first.toString()].getValueType(); \
	if (typeval == oatpp::String::Class::getType())\
		__VAR__[param.first.toString()] = oatpp::String(URIUtil::urlDecode(data->c_str())); \
	else if (typeval == oatpp::Int32::Class::getType())\
		__VAR__[param.first.toString()] = oatpp::Int32(stoi(*data)); \
	else if (typeval == oatpp::UInt32::Class::getType())\
		__VAR__[param.first.toString()] = oatpp::UInt32(stoi(*data)); \
	else if (typeval == oatpp::Int64::Class::getType())\
		__VAR__[param.first.toString()] = oatpp::Int64(stoll(*data)); \
	else if (typeval == oatpp::UInt64::Class::getType())\
		__VAR__[param.first.toString()] = oatpp::UInt64(stoull(*data)); \
	else if (typeval == oatpp::Float32::Class::getType())\
		__VAR__[param.first.toString()] = oatpp::Float32(stof(*data)); \
	else if (typeval == oatpp::Float64::Class::getType())\
		__VAR__[param.first.toString()] = oatpp::Float64(stod(*data)); \
	else if (typeval == oatpp::Boolean::Class::getType())\
		__VAR__[param.first.toString()] = oatpp::Boolean(*data == "true" || *data == "1"); \
}

/**
 * 接口处理器响应VO对象
 * @param __VO__: 响应数据对象
 */
#define API_HANDLER_RESP_VO(__VO__) return createDtoResponse(Status::CODE_200, __VO__)

/**
 * 接口处理器响应VO数据，由oatpp::Object包装后返回
 * @param __VO__: 响应数据对象
 */
#define API_HANDLER_RESP_VO_WRAPPER(__VO__) API_HANDLER_RESP_VO(oatpp::Object<__VO__>)

/**
 * API端点处理定义
 * @param _METHOD_: 请求方式，如：API_M_GET
 * @param _PATH_: 端点映射路径，如：/user/query-by-name
 * @param __ENDPOINT_FUN_NAME__: Api端点函数名称
 * @param _PARAM_MACRO_: 指定一个参数提取宏，如：BODY_DTO(SampleDTO::Wrapper, dto)
 * @param _EXECUTE_: 执行逻辑，如：execModifySample(dto)
 */
#define API_HANDLER_ENDPOINT(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _PARAM_MACRO_, _EXECUTE_) \
ENDPOINT(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _PARAM_MACRO_) { \
	API_HANDLER_RESP_VO(_EXECUTE_); \
}

/**
 * API端点处理定义，带授权认证
 * @param _METHOD_: 请求方式，如：API_M_GET
 * @param _PATH_: 端点映射路径，如：/user/query-by-name
 * @param __ENDPOINT_FUN_NAME__: Api端点函数名称
 * @param _PARAM_MACRO_: 指定一个参数提取宏，如：BODY_DTO(SampleDTO::Wrapper, dto)
 * @param _EXECUTE_: 执行逻辑，如：execModifySample(dto)
 */
#define API_HANDLER_ENDPOINT_AUTH(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _PARAM_MACRO_, _EXECUTE_) \
ENDPOINT(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _PARAM_MACRO_, API_HANDLER_AUTH_PARAME) { \
	API_HANDLER_RESP_VO(_EXECUTE_); \
}

/**
 * API端点处理定义，无参数版本
 * @param _METHOD_: 请求方式，如：API_M_GET
 * @param _PATH_: 端点映射路径，如：/user/query-by-name
 * @param __ENDPOINT_FUN_NAME__: Api端点函数名称
 * @param _EXECUTE_: 执行逻辑，如：execModifySample(dto)
 */
#define API_HANDLER_ENDPOINT_NOPARAM(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _EXECUTE_) \
ENDPOINT(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__) { \
	API_HANDLER_RESP_VO(_EXECUTE_); \
}

/**
 * API端点处理定义，无参数版本，带授权认证
 * @param _METHOD_: 请求方式，如：API_M_GET
 * @param _PATH_: 端点映射路径，如：/user/query-by-name
 * @param __ENDPOINT_FUN_NAME__: Api端点函数名称
 * @param _EXECUTE_: 执行逻辑，如：execModifySample(dto)
 */
#define API_HANDLER_ENDPOINT_NOPARAM_AUTH(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _EXECUTE_) \
ENDPOINT(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, API_HANDLER_AUTH_PARAME) { \
	API_HANDLER_RESP_VO(_EXECUTE_); \
}

/**
 * API端点处理定义，用于处理表单查询参数，查询参数的变量名固定为query
 * @param _METHOD_: 请求方式，如：API_M_GET
 * @param _PATH_: 端点映射路径，如：/user/query-by-name
 * @param __ENDPOINT_FUN_NAME__: Api端点函数名称
 * @param _QUERY_TYPE_: 查询参数类型，如：SampleQuery
 * @param _EXECUTE_: 执行逻辑，如：execQuerySample(query)
 */
#define API_HANDLER_ENDPOINT_QUERY(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _QUERY_TYPE_, _EXECUTE_) \
ENDPOINT(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, QUERIES(QueryParams, queryParams)) { \
	API_HANDLER_QUERY_PARAM(query, _QUERY_TYPE_, queryParams);\
	API_HANDLER_RESP_VO(_EXECUTE_); \
}

/**
 * API端点处理定义，用于处理表单查询参数，带授权认证
 * @param _METHOD_: 请求方式，如：API_M_GET
 * @param _PATH_: 端点映射路径，如：/user/query-by-name
 * @param __ENDPOINT_FUN_NAME__: Api端点函数名称
 * @param _QUERY_TYPE_: 查询参数类型，如：SampleQuery
 * @param _EXECUTE_: 执行逻辑，如：execQuerySample(query, authObject->getPayload())
 */
#define API_HANDLER_ENDPOINT_QUERY_AUTH(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _QUERY_TYPE_, _EXECUTE_) \
ENDPOINT(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) { \
	API_HANDLER_QUERY_PARAM(query, _QUERY_TYPE_, queryParams);\
	API_HANDLER_RESP_VO(_EXECUTE_); \
}

/**
 * API端点处理定义，自定义处理逻辑
 * @param _METHOD_: 请求方式，如：API_M_GET
 * @param _PATH_: 端点映射路径，如：/user/query-by-name
 * @param __ENDPOINT_FUN_NAME__: Api端点函数名称
 * @param _PARAM_MACRO_: 指定一个参数提取宏，如：BODY_DTO(SampleDTO::Wrapper, dto)
 * @param ...: 扩展自定义逻辑
 */
#define API_HANDLER_ENDPOINT_OPTION(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _PARAM_MACRO_, ...) \
ENDPOINT(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _PARAM_MACRO_) { \
	API_DEF_EXPAND(API_DEF_NOTHING __VA_ARGS__) \
}

/**
 * API端点处理定义，自定义处理逻辑，带授权认证
 * @param _METHOD_: 请求方式，如：API_M_GET
 * @param _PATH_: 端点映射路径，如：/user/query-by-name
 * @param __ENDPOINT_FUN_NAME__: Api端点函数名称
 * @param _PARAM_MACRO_: 指定一个参数提取宏，如：BODY_DTO(SampleDTO::Wrapper, dto)
 * @param ...: 扩展自定义逻辑，扩展逻辑需要自己编写响应逻辑，如：return createOkResponse(result);
 */
#define API_HANDLER_ENDPOINT_OPTION_AUTH(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _PARAM_MACRO_, ...) \
ENDPOINT(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _PARAM_MACRO_, API_HANDLER_AUTH_PARAME) { \
	API_DEF_EXPAND(API_DEF_NOTHING __VA_ARGS__) \
}

//////////////////////////////////////////////////////////////////////////

/**
 * DTO字段定义宏
 * @param _TYPE_: 字段类型，如：String、Int32、List<Int32>、List<SampleQuery::Wrapper>
 * @param _NAME_: 字段名称，如：name、sex
 * @param _DESCRIPTION_: 字段描述
 * @param _REQUIRE_: 是否必填，如：true、false
 * @param _DEFAULT_: 字段默认值，注意如果有默认值，如果字段值没有被赋值就会保持值为默认值，如："zhangsan"、123
 */
#define API_DTO_FIELD(_TYPE_, _NAME_, _DESCRIPTION_, _REQUIRE_, _DEFAULT_) \
DTO_FIELD(_TYPE_, _NAME_) = _DEFAULT_; \
DTO_FIELD_INFO(_NAME_) { \
	info->description = _DESCRIPTION_; \
	info->required = _REQUIRE_; \
}

/**
 * DTO字段定义宏，大部分成员使用系统默认值
 * @param _TYPE_: 字段类型，如：String、Int32、List<Int32>、List<SampleQuery::Wrapper>
 * @param _NAME_: 字段名称，如：name、sex
 * @param _DESCRIPTION_: 字段描述
 */
#define API_DTO_FIELD_DEFAULT(_TYPE_, _NAME_, _DESCRIPTION_) \
DTO_FIELD(_TYPE_, _NAME_); \
DTO_FIELD_INFO(_NAME_) { \
	info->description = _DESCRIPTION_; \
}

/**
 * DTO字段定义宏，支持自定义是否必填
 * @param _TYPE_: 字段类型，如：String、Int32、List<Int32>、List<SampleQuery::Wrapper>
 * @param _NAME_: 字段名称，如：name、sex
 * @param _DESCRIPTION_: 字段描述
 * @param _REQUIRE_: 是否必填，如：true、false
 */
#define API_DTO_FIELD_REQUIRE(_TYPE_, _NAME_, _DESCRIPTION_, _REQUIRE_) \
DTO_FIELD(_TYPE_, _NAME_); \
DTO_FIELD_INFO(_NAME_) { \
	info->description = _DESCRIPTION_; \
	info->required = _REQUIRE_; \
}

//////////////////////////////////////////////////////////////////////////

/**
 * 初始化multipart数据读取容器和读取器
 * @param _VAR_CONTAINER_: 容器变量名
 * @param _VAR_READER_: 读取器变量名
 */
#define API_MULTIPART_INIT(_VAR_CONTAINER_, _VAR_READER_) \
namespace multipart = oatpp::web::mime::multipart; \
/* 创建multipart容器 */ \
auto _VAR_CONTAINER_ = std::make_shared<multipart::PartList>(request->getHeaders()); \
/* 创建multipart读取器 */ \
multipart::Reader _VAR_READER_(_VAR_CONTAINER_.get())

/**
 * 设置读取器将值读入内存中
 * @param _READER_: 读取器
 * @param _FIELD_NAME_: 字段名称，如："nickname"
 * @param _MDS_: 最大读取数据大小，-1表示读取该字段全部数据
 */
#define API_MULTIPART_CONFIG_MEMO(_READER_, _FIELD_NAME_, _MDS_) \
_READER_.setPartReader(_FIELD_NAME_, multipart::createInMemoryPartReader(_MDS_))

/**
 * 设置读取器将值读入内存中，为没有单独设置读取大小的字段设置读取大小，默认读取到内存中
 * @param _READER_: 读取器
 * @param _MDS_: 最大读取数据大小，-1表示读取该字段全部数据
 */
#define API_MULTIPART_CONFIG_MEMO_DEFAULT(_READER_, _MDS_) \
_READER_.setDefaultPartReader(multipart::createInMemoryPartReader(_MDS_));

/**
 * 设置读取器将值写到文件中，一般用来直接保存文件到磁盘
 * @param _READER_: 读取器
 * @param _FIELD_NAME_: 字段名称，如："file"
 * @param _PATH_: 文件保存全路径，如："/tmp/zo/file.png"
 */
#define API_MULTIPART_CONFIG_FILE(_READER_, _FIELD_NAME_, _PATH_) \
_READER_.setPartReader(_FIELD_NAME_, multipart::createFilePartReader(_PATH_))

/**
 * 解析数值类型表单字段
 * @param _CONTAINER_: 读取容器
 * @param _FIELD_NAME_: 字段名称，如："age"
 * @param _TYPE_: 数据类型，如：Int32、UInt32、Float32等
 * @param _VAR_: 存储变量名称，如：age
 * @param _TYPE_TRANS_FUN_: 数值转换函数，如：stoi、stoll、stoull、stof、stod
 */
#define API_MULTIPART_PARSE_FORM_FIELD_NUM(_CONTAINER_, _FIELD_NAME_, _TYPE_, _VAR_, _TYPE_TRANS_FUN_) \
oatpp::_TYPE_ _VAR_ = nullptr; \
auto part##_VAR_ = _CONTAINER_->getNamedPart(_FIELD_NAME_); \
if(part##_VAR_){ \
	_VAR_ = oatpp::_TYPE_(_TYPE_TRANS_FUN_(part##_VAR_->getPayload()->getInMemoryData().getValue(""))); \
}

/**
 * 解析字符串类型表单字段
 * @param _CONTAINER_: 读取容器
 * @param _FIELD_NAME_: 字段名称，如："nickname"
 * @param _VAR_: 存储变量名称，如：nickname
 */
#define API_MULTIPART_PARSE_FORM_FIELD_STR(_CONTAINER_, _FIELD_NAME_, _VAR_) \
oatpp::String _VAR_ = nullptr; \
auto part##_VAR_ = _CONTAINER_->getNamedPart(_FIELD_NAME_); \
if(part##_VAR_){ \
	_VAR_ = part##_VAR_->getPayload()->getInMemoryData().getValue(""); \
}

/**
 * 解析布尔类型表单字段
 * @param _CONTAINER_: 读取容器
 * @param _FIELD_NAME_: 字段名称，如："isopen"
 * @param _VAR_: 存储变量名称，如：isopen
 */
#define API_MULTIPART_PARSE_FORM_FIELD_BOO(_CONTAINER_, _FIELD_NAME_, _VAR_) \
oatpp::Boolean _VAR_ = nullptr; \
auto part##_VAR_ = _CONTAINER_->getNamedPart(_FIELD_NAME_); \
if(part##_VAR_){ \
	std::string tmp = part##_VAR_->getPayload()->getInMemoryData().getValue(""); \
	_VAR_ = Boolean(tmp == "true" || tmp == "1"); \
}

/**
 * 解析文件数据，将临时存储在内存中的文件数据存入变量
 * @param _CONTAINER_: 读取容器
 * @param _FIELD_NAME_: 字段名称，如："head"
 * @param _VAR_: 存储变量名称，如：head
 */
#define API_MULTIPART_PARSE_FILE_FIELD(_CONTAINER_, _FIELD_NAME_, _VAR_) \
oatpp::String _VAR_ = nullptr; \
auto part##_VAR_ = _CONTAINER_->getNamedPart(_FIELD_NAME_); \
if(part##_VAR_){ \
	_VAR_ = part##_VAR_->getPayload()->getInMemoryData(); \
}

#endif // !_API_HELPER_
