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
#ifndef __vtStorAta_h__
#define __vtStorAta_h__
#pragma once

#include "BasicTypes.h"
#include "DriveEnumeratorInterface.h"
#include "vtStorAtaPlatformDefines.h"

namespace vtStor
{

class VT_STOR_ATA_API cAta
{
public:
    cAta() = delete;

public:
    static const U32 s_DefaultCommandHandlerAtaCommandType = 0;
};

}

extern "C"
{
    VT_STOR_ATA_API void vtStorAtaInit(std::shared_ptr<vtStor::cDriveEnumeratorInterface>& DriveEnumerator);
}

#endif