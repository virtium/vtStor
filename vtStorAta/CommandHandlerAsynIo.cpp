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
#include "CommandHandlerAsynIo.h"

void cCommandHandlerAsynIo_GetCommandHandler(std::shared_ptr<vtStor::ICommandHandler>& CommandHandler, std::shared_ptr<vtStor::IProtocol> Protocol)
{
    CommandHandler = std::shared_ptr<vtStor::ICommandHandler>(new vtStor::cCommandHandlerAsynIo(Protocol));
}

namespace vtStor
{
    cCommandHandlerAsynIo::cCommandHandlerAsynIo(std::shared_ptr<IProtocol> Protocol) : m_Protocol(Protocol)
    {
    }

    cCommandHandlerAsynIo::~cCommandHandlerAsynIo()
    {
    }

    eErrorCode cCommandHandlerAsynIo::IssueCommand(const DeviceHandle& Handle, std::shared_ptr<const IBuffer> CommandDescriptor, std::shared_ptr<IBuffer> Data)
    {
        eErrorCode errorCode = eErrorCode::None;

        errorCode = m_Protocol->IssueCommand(Handle, CommandDescriptor, Data);

        return errorCode;
    }
}
