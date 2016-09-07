/*
<License>
Copyright 2016 Virtium Technology

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http ://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
</License>
*/

#ifndef __VtStorATestDefine_h__
#define __VtStorATestDefine_h__
#pragma once

#include <iostream>

#ifdef _UNICODE
#define VtStorPrint std::wcout
#define VtStorPrintln std::wcout << std::endl
#else
#define VtStorMessage std::cout
#define VtStorPrintln std::cout << std::endl
#endif
#endif