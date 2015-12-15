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
#include "vtStorScsi.h"
#include "CommandDescriptorScsi.h"

#include "CommandHandlerScsi.h"
#include "Buffer.h"
#include "BufferFormatter.h"

#include "vtStorScsiProtocol/ScsiProtocolEssense1.h"

namespace vtStor
{

    cCommandHandlerScsi::cCommandHandlerScsi(std::shared_ptr<Protocol::cProtocolInterface> Protocol) :
    cCommandHandlerInterface( Protocol )
{
}


    cCommandHandlerScsi::~cCommandHandlerScsi()
{
}

    eErrorCode cCommandHandlerScsi::IssueCommand(const DeviceHandle& Handle, std::shared_ptr<const cBufferInterface> CommandDescriptor, std::shared_ptr<cBufferInterface> Data)
{
    eErrorCode errorCode = eErrorCode::None;

    cBufferFormatter bufferFormatter = cBufferFormatter::Reader(CommandDescriptor);
    switch (bufferFormatter.GetHeader().Format)
    {
        case 1:
        {
            Scsi::cCommandDescriptorScsi commandDescriptor = Scsi::cCommandDescriptorScsi::Reader(CommandDescriptor);
            const StorageUtility::Scsi::sCdbFields& cdbFields = commandDescriptor.GetCdbFields();

            std::shared_ptr<cBufferInterface> buffer = std::make_shared<cBuffer>(vtStor::Protocol::cEssenseScsi1::SIZE_IN_BYTES);
            Protocol::cEssenseScsi1 essense = Protocol::cEssenseScsi1::Writer(buffer);

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = essense.GetCommandCharacteristics();
            commandCharacteristics = commandDescriptor.GetCommandCharacteristics();

            StorageUtility::Scsi::sCdbRegisters& cdbRegister = essense.GetCdbRegister();
            PrepareCdbRegister(commandCharacteristics, cdbFields, cdbRegister);

            errorCode = m_Protocol->IssueCommand( Handle, buffer, Data );

        } break;

        default:
        {
            errorCode = eErrorCode::FormatNotSupported;
        } break;
    }

    return(errorCode);
}

    void cCommandHandlerScsi::PrepareCdbRegister(const StorageUtility::Scsi::sCommandCharacteristics& ScsiCommandCharacteristics,
        const StorageUtility::Scsi::sCdbFields& CdbFields, StorageUtility::Scsi::sCdbRegisters& CdbRegister)
    {   
        switch (ScsiCommandCharacteristics.FieldFormatting)
        {
        case StorageUtility::Scsi::eFieldFormatting::COMMAND_6:
        {
            CdbRegister.Register0 = CdbFields.OpCode;
            CdbRegister.Register1 = CdbFields.Service;
            CdbRegister.Register2 = (CdbFields.Lba >> 8) & 0xFF;
            CdbRegister.Register3 = CdbFields.Lba & 0xFF;
            CdbRegister.Register4 = CdbFields.TransferLen & 0xFF;
            CdbRegister.Register5 = CdbFields.Control;
        } break;

        case StorageUtility::Scsi::eFieldFormatting::COMMAND_10:
        {
            CdbRegister.Register0 = CdbFields.OpCode;
            CdbRegister.Register1 = CdbFields.Service;
            CdbRegister.Register2 = (CdbFields.Lba >> 24) & 0xFF;
            CdbRegister.Register3 = (CdbFields.Lba >> 16) & 0xFF;
            CdbRegister.Register4 = (CdbFields.Lba >> 8) & 0xFF;
            CdbRegister.Register5 = CdbFields.Lba & 0xFF;
            CdbRegister.Register6 = CdbFields.Group;
            CdbRegister.Register7 = (CdbFields.TransferLen >> 8) & 0xFF;
            CdbRegister.Register8 = CdbFields.TransferLen & 0xFF;
            CdbRegister.Register9 = CdbFields.Control;
        } break;

        case StorageUtility::Scsi::eFieldFormatting::COMMAND_12:
        {
            CdbRegister.Register0 = CdbFields.OpCode; 
            CdbRegister.Register1 = CdbFields.Service;
            CdbRegister.Register2 = (CdbFields.Lba >> 24) & 0xFF;
            CdbRegister.Register3 = (CdbFields.Lba >> 16) & 0xFF;
            CdbRegister.Register4 = (CdbFields.Lba >> 8) & 0xFF;
            CdbRegister.Register5 = CdbFields.Lba & 0xFF;
            CdbRegister.Register6 = (CdbFields.TransferLen >> 24) & 0xFF;
            CdbRegister.Register7 = (CdbFields.TransferLen >> 16) & 0xFF;
            CdbRegister.Register8 = (CdbFields.TransferLen >> 8) & 0xFF;
            CdbRegister.Register9 = CdbFields.TransferLen & 0xFF;
            CdbRegister.Register10 = CdbFields.Group;
            CdbRegister.Register11 = CdbFields.Control;
        } break;

        case StorageUtility::Scsi::eFieldFormatting::COMMAND_16:
        {
            CdbRegister.Register0 = CdbFields.OpCode;
            CdbRegister.Register1 = CdbFields.Service;
            CdbRegister.Register2 = (CdbFields.Lba >> 56) & 0xFF;
            CdbRegister.Register3 = (CdbFields.Lba >> 48) & 0xFF;
            CdbRegister.Register4 = (CdbFields.Lba >> 48) & 0xFF;
            CdbRegister.Register5 = (CdbFields.Lba >> 32) & 0xFF;
            CdbRegister.Register6 = (CdbFields.Lba >> 24) & 0xFF;
            CdbRegister.Register7 = (CdbFields.Lba >> 16) & 0xFF;
            CdbRegister.Register8 = (CdbFields.Lba >> 8) & 0xFF;
            CdbRegister.Register9 = CdbFields.Lba & 0xFF;
            CdbRegister.Register10 = (CdbFields.TransferLen >> 24) & 0xFF;
            CdbRegister.Register11 = (CdbFields.TransferLen >> 16) & 0xFF;
            CdbRegister.Register12 = (CdbFields.TransferLen >> 8) & 0xFF;
            CdbRegister.Register13 = CdbFields.TransferLen & 0xFF;
            CdbRegister.Register14 = CdbFields.Group;
            CdbRegister.Register15 = CdbFields.Control;
        } break;

        default:
            break;
        }
    }
}

VT_STOR_SCSI_API void vtStorCommandHandlerScsiInit( std::shared_ptr<vtStor::cCommandHandlerInterface>& CommandHandler, std::shared_ptr<vtStor::Protocol::cProtocolInterface> Protocol )
{
    CommandHandler = std::make_shared<vtStor::cCommandHandlerScsi>( Protocol );
}