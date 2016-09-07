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

#ifndef __vtStorIAsynIoCommandExtensions_h__
#define __vtStorIAsynIoCommandExtensions_h__

#include <memory>

#include "ErrorCodes.h"
#include "IDrive.h"
#include "PlatformDefines.h"

namespace vtStor
{
    class VT_STOR_ATA_API IAsynIoCommandExtensions
    {
    public:
        virtual ~IAsynIoCommandExtensions() {}
        virtual eErrorCode IssueCommand_ReadAsynIo(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Count, U64 Lba, std::shared_ptr<OverlappedIo> OverlappedPtr) = 0;
        virtual eErrorCode IssueCommand_WriteAsynIo(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Count, U64 Lba, std::shared_ptr<OverlappedIo> OverlappedPtr) = 0;
    };
}

extern "C"
{
    VT_STOR_ATA_API void cAsynIoCommandExtensions_GetAsynIoCommandExtensions(std::unique_ptr<vtStor::IAsynIoCommandExtensions>& AsynIoCommandExtensions);
}

typedef void (OS_API * GetAsynIoCommandExtensionsDelegate) (std::unique_ptr<vtStor::IAsynIoCommandExtensions>&);

#endif // end __vtStorIAsynIoCommandExtensions_h__
