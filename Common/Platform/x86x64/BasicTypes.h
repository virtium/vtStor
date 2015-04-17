/*
<License>
Copyright 2015 Virtium Technology

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
#ifndef __BasicTypes_h__
#define __BasicTypes_h__

#include <cstdint>
#include "PlatformDefines.h"

namespace vtStor
{

using U8  = uint8_t;
using S8  = int8_t;
using U16 = uint16_t;
using S16 = int16_t;
using U32 = uint32_t;
using S32 = int32_t;
using U64 = uint64_t;
using S64 = int64_t;

using String = tstring;

}

#endif __BasicTypes_h__