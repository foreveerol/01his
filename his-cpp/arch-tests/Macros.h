#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2024/04/09 15:41:46

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
#ifndef _MACROS_
#define _MACROS_

#ifndef TEST_NS_ADDR
#define TEST_NS_ADDR "192.168.16.130:8848"
#endif

#ifndef TEST_NS_NAMESPACE
#define TEST_NS_NAMESPACE "project-dev"
#endif

//////////////////////////////////////////////////////////////////////////

#include "YamlHelper.h"

// �������Ĵʵ�
YAML::Node zhDictNode = YAML::LoadFile("zh-dict.yaml");

// ����һ����ȡ�����ֻ�ȡ��
#define ZH_WORDS_GETTER(_KEY_) \
YamlHelper().getString(&zhDictNode, _KEY_)

//////////////////////////////////////////////////////////////////////////

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

// RocketMQ�첽����������Ϣ������Ὣ����ת����JSON�ַ���
#define RC_PUBLISH_OBJ_MSG_ASYNC(__ROCKET_CLIENT__, __TOPIC__, __DATA_OBJ__, __CB_OBJ__) \
[&] { \
	auto mapper = oatpp::parser::json::mapping::ObjectMapper::createShared(); \
	auto jobj = mapper->writeToString(__DATA_OBJ__); \
	__ROCKET_CLIENT__->productMsgAsync(__TOPIC__, jobj.getValue(""), __CB_OBJ__); \
}()

// RocketMQͬ������������Ϣ������Ὣ����ת����JSON�ַ���
#define RC_PUBLISH_OBJ_MSG_SYNC(__RETURN_VAR_NAME__, __ROCKET_CLIENT__, __TOPIC__, __DATA_OBJ__) \
rocketmq::SendStatus __RETURN_VAR_NAME__; \
[&] { \
	auto mapper = oatpp::parser::json::mapping::ObjectMapper::createShared(); \
	auto jobj = mapper->writeToString(__DATA_OBJ__); \
	__RETURN_VAR_NAME__ = __ROCKET_CLIENT__->productMsgSync(__TOPIC__, jobj.getValue("")); \
}()

// RocketMQ������Ϣ����JSON�ַ���ת���ɶ���
#define RC_RECEIVER_MSG_CONVERT(__RETURN_VAR_NAME__, __DATA__TYPE__, __PAYLOAD__) \
oatpp::Object<__DATA__TYPE__> __RETURN_VAR_NAME__; \
[&] { \
	auto mapper = oatpp::parser::json::mapping::ObjectMapper::createShared(); \
	__RETURN_VAR_NAME__ = mapper->readFromString<oatpp::Object<__DATA__TYPE__>>(__PAYLOAD__); \
}()

//////////////////////////////////////////////////////////////////////////

#endif // !_MACROS_