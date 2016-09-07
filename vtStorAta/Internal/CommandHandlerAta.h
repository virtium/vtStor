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

#include "Ata.h"
#include "ICommandHandler.h"
#include "IProtocol.h"

namespace vtStor
{

class cCommandHandlerAta : public ICommandHandler
{
public:
    cCommandHandlerAta(std::shared_ptr<IProtocol> Protocol);
    virtual ~cCommandHandlerAta();

public:
    virtual eErrorCode IssueCommand(const DeviceHandle& Handle, std::shared_ptr<const IBuffer> CommandDescriptor, std::shared_ptr<IBuffer> Data) override;

private:
    void PrepareTaskFileRegisters(const StorageUtility::Ata::sCommandCharacteristic& AtaCommandCharacteristics, const StorageUtility::Ata::uCommandFields& CommandFields, StorageUtility::Ata::uTaskFileRegister& TaskFileRegister, StorageUtility::Ata::uTaskFileRegister& TaskFileRegisterExt);

private:
    std::shared_ptr<IProtocol> m_Protocol;
};

}

#endif