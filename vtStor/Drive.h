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
#ifndef __vtStorDrive_h__
#define __vtStorDrive_h__
#pragma once

#include <map>

#include "BasicTypes.h"
#include "CommandDescriptor.h"
#include "StorageUtility.h"
#include "IBuffer.h"
#include "ICommandHandler.h"
#include "IDrive.h"

namespace vtStor
{

VTSTOR_API_EXPORT_IMPL template class VTSTOR_API std::map<vtStor::U32, std::shared_ptr<vtStor::ICommandHandler>>;

class VTSTOR_API cDrive : public IDrive
{
public:
    cDrive(std::shared_ptr<vtStor::IDevice> Device, DeviceHandle DeviceHandle, std::shared_ptr<vtStor::sDriveProperties> DriveProperties);
    virtual ~cDrive();

public:
    virtual void RegisterCommandHandler(U32 CommandType, std::shared_ptr<ICommandHandler> CommandHandler) override;

public:
    virtual eErrorCode IssueCommand(U32 CommandType, std::shared_ptr<const IBuffer> CommandDescriptor, std::shared_ptr<IBuffer> Data) override;

public:
    virtual void Data(std::unordered_map<eDeviceDataType, void*>& Data) override;

    virtual DeviceHandle Handle() override;

    virtual void DevicePath(tchar*& DevicePath) override;

public:
    virtual std::shared_ptr<vtStor::sDriveProperties> GetDriveProperties() override;

protected:
    std::map<U32, std::shared_ptr<ICommandHandler>> m_CommandHandlers;

protected:
    std::shared_ptr<vtStor::IDevice> m_Device;
    DeviceHandle m_DeviceHandle;
    std::shared_ptr<vtStor::sDriveProperties> m_DriveProperties;
};

}

#endif