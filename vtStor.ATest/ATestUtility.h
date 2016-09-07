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

#ifndef __ATestUtility_h__
#define __ATestUtility_h__
#pragma once

#include <memory>

#include "IBuffer.h"
#include "IDrive.h"

namespace vtStorATest
{
    class ATestUtility
    {
    public:
        // Utility functions
        static vtStor::U8 CalculateChecksum(vtStor::U8* DataBuffer);
        static vtStor::U32 MakeRandomValue(vtStor::U32 MaxUserLba);
        static vtStor::U64 GetValueOfBuffer(vtStor::U32 IdWord, vtStor::U32 WordCount, std::shared_ptr<vtStor::IBuffer> IdentifyBuffer);
        static vtStor::String ConvertErrorCodeToString(vtStor::eErrorCode Error);
        static vtStor::String GetModelString(std::shared_ptr<vtStor::IBuffer>& IdentifyBuffer);
        static vtStor::Vector_Drives ScanForDrives();
        static bool CompareBuffers(const std::shared_ptr<vtStor::IBuffer>& SrcBuffer, const std::shared_ptr<vtStor::IBuffer>& DestBuffer, vtStor::U32 SectorCount);
    };
}

#endif