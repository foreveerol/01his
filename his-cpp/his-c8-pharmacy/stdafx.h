// stdafx.h: 预编译头文件。
// 下列头文件只编译一次，可提升后续构建速度。
// 同时提升IntelliSense性能，包括代码补全和导航等功能。
// 但如果这些头文件在构建之间有任何修改，它们都将被重新编译。
// 请勿在此添加频繁变更的头文件，否则会降低性能收益。
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/24 23:00:54

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
#ifndef STDAFX_H
#define STDAFX_H

#ifndef LINUX
#include "OatppMacros.h"
// 导入在定义_HAS_STD_BYTE之前所需的类型头文件
#include "id/UuidFacade.h"

// 解决std::byte类型重定义问题
#ifdef _HAS_STD_BYTE
#undef _HAS_STD_BYTE
#endif
#define _HAS_STD_BYTE 0

// 在此添加需要预编译的头文件
#include "mysql/jdbc.h"
#include "SqlSession.h"
#include "yaml-cpp/yaml.h"
#include "sw/redis++/redis++.h"

#endif // !LINUX

#endif //STDAFX_H
