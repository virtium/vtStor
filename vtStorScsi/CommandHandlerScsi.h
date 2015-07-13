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
#ifndef __vtStorCommandHandlerScsi_h__
#define __vtStorCommandHandlerScsi_h__
#pragma once

#include "StorageUtility/Scsi.h"
#include "CommandHandlerInterface.h"
#include "vtStorScsiPlatformDefines.h"

namespace vtStor
{
    class VT_STOR_SCSI_API cCommandHandlerScsi : public cCommandHandlerInterface
{
public:
    cCommandHandlerScsi(std::shared_ptr<Protocol::cProtocolInterface> Protocol);
    virtual ~cCommandHandlerScsi();

public:
    virtual eErrorCode IssueCommand( std::shared_ptr<const cBufferInterface> CommandDescriptor, std::shared_ptr<cBufferInterface> Data ) override;

private:
    void cCommandHandlerScsi::PrepareTaskFileRegister(const StorageUtility::Scsi::sCommandCharacteristics& ScsiCommandCharacteristics, const StorageUtility::Scsi::sCommandFields& CommandFields, StorageUtility::Scsi::sTaskFileRegister& Cdb);

};

}

extern "C"
{
    VT_STOR_SCSI_API void vtStorCommandHandlerScsiInit( std::shared_ptr<vtStor::cCommandHandlerInterface>& CommandHandler, std::shared_ptr<vtStor::Protocol::cProtocolInterface> Protocol );
}

#endif