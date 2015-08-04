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
#include <assert.h>

#include "Drive.h"

namespace vtStor
{

cDrive::cDrive(std::shared_ptr<String> DevicePath) : m_DevicePath(DevicePath)
{
    eErrorCode errorCode = GetStorageDeviceHandle(*m_DevicePath, m_DeviceHandle);
    //TODO: handle error
    assert(eErrorCode::None == errorCode);
}

cDrive::~cDrive()
{
    if (m_DeviceHandle)
    {
        CloseHandle(m_DeviceHandle);
    }
    
    m_CommandHandlers.clear();
}

void cDrive::RegisterCommandHandler(U32 CommandType, std::shared_ptr<cCommandHandlerInterface> CommandHandler)
{
    m_CommandHandlers.insert({ CommandType, CommandHandler });
}

eErrorCode cDrive::IssueCommand( U32 CommandType, std::shared_ptr<const cBufferInterface> CommandDescriptor, std::shared_ptr<cBufferInterface> Data )
{
    return( m_CommandHandlers[CommandType]->IssueCommand( m_DeviceHandle, CommandDescriptor, Data ) );
}

}