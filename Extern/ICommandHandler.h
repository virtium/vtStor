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
#ifndef __vtStorICommandHandler_h__
#define __vtStorICommandHandler_h__

#include <memory>

#include "ErrorCodes.h"
#include "PlatformDefines.h"
#include "IBuffer.h"
#include "IProtocol.h"

namespace vtStor
{
    class VTSTOR_API ICommandHandler
    {
    public:
        virtual ~ICommandHandler() {}
        virtual eErrorCode IssueCommand(const DeviceHandle& Handle, std::shared_ptr<const IBuffer> CommandDescriptor, std::shared_ptr<IBuffer> Data) = 0;
    };
}

extern "C"
{
    VT_STOR_ATA_API void cCommandHandlerAta_GetCommandHandler(std::shared_ptr<vtStor::ICommandHandler>& CommandHandler, std::shared_ptr<vtStor::IProtocol> Protocol);
    VT_STOR_SCSI_API void cCommandHandlerScsi_GetCommandHandler(std::shared_ptr<vtStor::ICommandHandler>& CommandHandler, std::shared_ptr<vtStor::IProtocol> Protocol);
}

typedef void (WINAPIV * GetCommandHandlerDelegate) (std::shared_ptr<vtStor::ICommandHandler>&, std::shared_ptr<vtStor::IProtocol>);

#endif // end __vtStorICommandHandler_h__