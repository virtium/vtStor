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
#ifndef __vtStorDrive_h__
#define __vtStorDrive_h__
#pragma once

#include <map>

#include "BasicTypes.h"
#include "CommandDescriptor.h"
#include "CommandHandlerInterface.h"
#include "DeviceInterface.h"
#include "DriveInterface.h"
#include "StorageUtility.h"

VTSTOR_API_EXPORT_IMPL template class VTSTOR_API std::map<vtStor::U32, std::shared_ptr<vtStor::cCommandHandlerInterface>>;

namespace vtStor
{

class VTSTOR_API cDrive : public cDriveInterface, cDeviceInterface
{
public:
    cDrive(std::shared_ptr<vtStor::cDeviceInterface> Device, DeviceHandle DeviceHandle);
    virtual ~cDrive();

public:
    virtual void RegisterCommandHandler(U32 CommandType, std::shared_ptr<cCommandHandlerInterface> CommandHandler) override;

public:
    virtual eErrorCode IssueCommand(U32 CommandType, std::shared_ptr<const cBufferInterface> CommandDescriptor, std::shared_ptr<cBufferInterface> Data) override;

public:
    virtual void Data(std::unordered_map<eDeviceDataType, void*>& Data) override;

    virtual DeviceHandle Handle() override;

protected:
    std::map<U32, std::shared_ptr<cCommandHandlerInterface>> m_CommandHandlers;

protected:
    std::shared_ptr<vtStor::cDeviceInterface> m_Device;
    DeviceHandle m_DeviceHandle;
};

}

#endif
