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

#include "ProtocolAsynIo.h"

void cAsynIo_GetProtocol(std::shared_ptr<vtStor::IProtocol>& Protocol)
{
    Protocol = std::shared_ptr<vtStor::IProtocol>(new vtStor::Protocol::cProtocolAsynIo());
}

namespace vtStor
{
    namespace Protocol
    {
        cProtocolAsynIo::~cProtocolAsynIo()
        {
        }

        eErrorCode cProtocolAsynIo::IssueCommand(const DeviceHandle& Handle, std::shared_ptr<const IBuffer> CommandDescriptor, std::shared_ptr<IBuffer> Data)
        {
            eErrorCode errorCode = eErrorCode::None;
            BOOL bResult;

            cAsynIoProtocolEssense commandDescriptorAsynIo = cAsynIoProtocolEssense::Reader(CommandDescriptor);

            sAsynchronousIoInputs& commandFields = commandDescriptorAsynIo.GetCommandFields();

            // Windows function: CreateEvent() , see more on msdn: https://msdn.microsoft.com/en-us/library/windows/desktop/ms682396(v=vs.85).aspx

            commandFields.OverlappedPtr->hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

            switch (commandFields.Command)
            {
            case READ_ASYNIO:
            {
                bResult = ReadFile(
                    Handle.Handle,
                    Data->ToDataBuffer(),
                    commandFields.m_DataTransferredInSectors,
                    NULL,
                    commandFields.OverlappedPtr);
            } break;

            case WRITE_ASYNIO:
            {
                bResult = WriteFile(
                    Handle.Handle,
                    Data->ToDataBuffer(),
                    commandFields.m_DataTransferredInSectors,
                    NULL,
                    commandFields.OverlappedPtr);
            } break;

            default:
                break;
            }

            // If bResult is true, this command is executed synchronously.
            if (true == bResult)
            {
                errorCode = eErrorCode::SyncIo;
            }
            else
            {
                U32 dwError = GetLastError();

                if (ERROR_IO_PENDING != dwError)
                {
                    errorCode = eErrorCode::Io;
                }
            }

            return (errorCode);
        }
    }
}