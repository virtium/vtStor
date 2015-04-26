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
#ifndef __vtStorCommandHandlerAta_h__
#define __vtStorCommandHandlerAta_h__
#pragma once

#include "StorageUtility/Ata.h"
#include "CommandHandlerInterface.h"
#include "vtStorAtaPlatformDefines.h"

namespace vtStor
{

class VT_STOR_ATA_API cCommandHandlerAta : public cCommandHandlerInterface
{
public:
    cCommandHandlerAta( std::shared_ptr<Protocol::cProtocolInterface> Protocol );
    virtual ~cCommandHandlerAta();

public:
    virtual eErrorCode IssueCommand( std::shared_ptr<const cBufferInterface> CommandDescriptor, std::shared_ptr<cBufferInterface> Data ) override;

private:
    void cCommandHandlerAta::PrepareTaskFileRegisters( const StorageUtility::Ata::sCommandCharacteristic& AtaCommandCharacteristics, const StorageUtility::Ata::uCommandFields& CommandFields, StorageUtility::Ata::uTaskFileRegister& TaskFileRegister, StorageUtility::Ata::uTaskFileRegister& TaskFileRegisterExt );

};

}

#endif