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
#ifndef __vtStorIProtocol_h__
#define __vtStorIProtocol_h__

#include <memory>

#include "ErrorCodes.h"
#include "PlatformDefines.h"
#include "IBuffer.h"

namespace vtStor
{
    struct IProtocol
    {
        virtual ~IProtocol() {}
        virtual eErrorCode IssueCommand(const DeviceHandle& Handle, std::shared_ptr<const IBuffer> Essense, std::shared_ptr<IBuffer> DataBuffer) = 0;
    };
}

extern "C"
{
    VT_STOR_ATA_PROTOCOL_API void cAtaPassThrough_GetProtocol(std::shared_ptr<vtStor::IProtocol>& Protocol);
    VT_STOR_SCSI_PROTOCOL_API void cScsiPassThrough_GetProtocol(std::shared_ptr<vtStor::IProtocol>& Protocol);
}

typedef void (WINAPIV * GetProtocolDelegate) (std::shared_ptr<vtStor::IProtocol>&);

#endif // end __vtStorIProtocol_h__