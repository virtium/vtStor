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

#include "StorageUtility.h"
#include "BasicTypes.h"
#include "DriveInterface.h"
#include "CommandHandlerInterface.h"

VTSTOR_API_EXPORT_IMPL template class VTSTOR_API std::map<vtStor::U32, std::shared_ptr<vtStor::cCommandHandlerInterface>>;
VTSTOR_API_EXPORT_IMPL template class VTSTOR_API std::shared_ptr<vtStor::String>;

namespace vtStor
{

class VTSTOR_API cDrive : public cDriveInterface
{
public:
    cDrive(std::shared_ptr<String> DevicePath);
    virtual ~cDrive();

public:
    virtual void RegisterComandHandler( U32 CommandType, std::shared_ptr<cCommandHandlerInterface> CommandHandler ) override;

public:
    virtual eErrorCode IssueCommand(U32 CommandType, std::shared_ptr<const cBufferInterface> CommandDescriptor, std::shared_ptr<cBufferInterface> Data) override;
  
protected:
    std::map<U32, std::shared_ptr<cCommandHandlerInterface>> m_CommandHandlers;

protected:
    //! This is a work around to by pass the need to export template for "String" type.
    //! Apparently exporting from within shared_ptr will cover it.
    std::shared_ptr<String> m_DevicePath;
    DeviceHandle m_DeviceHandle;
};

}

#endif