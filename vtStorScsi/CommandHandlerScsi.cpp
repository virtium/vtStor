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
#include "AtaPassThroughCommandDescriptor.h"

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

    eErrorCode cCommandHandlerScsi::IssueCommand(std::shared_ptr<const cBufferInterface> CommandDescriptor, std::shared_ptr<cBufferInterface> Data)
{
    eErrorCode errorCode = eErrorCode::None;

    cBufferFormatter bufferFormatter = cBufferFormatter::Reader(CommandDescriptor);
    switch (bufferFormatter.GetHeader().Format)
    {
        case 1:
        {
            Scsi::cAtaPassThroughCommandDescriptor commandDescriptor = Scsi::cAtaPassThroughCommandDescriptor::Reader(CommandDescriptor);
            const StorageUtility::Scsi::sCommandFields& commandFields = commandDescriptor.GetCommandFields();

            std::shared_ptr<cBufferInterface> buffer = std::make_shared<cBuffer>(vtStor::Protocol::cEssenseScsi1::SIZE_IN_BYTES);
            Protocol::cEssenseScsi1 essense = Protocol::cEssenseScsi1::Writer(buffer);
    
            DeviceHandle& deviceHandle = essense.GetDeviceHandle();
            deviceHandle = commandDescriptor.GetDeviceHandle();

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = essense.GetCommandCharacteristics();
            commandCharacteristics = commandDescriptor.GetCommandCharacteristics();

            StorageUtility::Scsi::cdbRegister& cdbRegister = essense.GetCdbRegister();
            PrepareAtaPassThroughCdbRegister(commandCharacteristics, commandFields, cdbRegister);

            errorCode = m_Protocol->IssueCommand( buffer, Data );

        } break;

        default:
        {
            errorCode = eErrorCode::FormatNotSupported;
        } break;
    }

    return(errorCode);
}

    void cCommandHandlerScsi::PrepareAtaPassThroughCdbRegister(const StorageUtility::Scsi::sCommandCharacteristics& ScsiCommandCharacteristics, const StorageUtility::Scsi::sCommandFields& CommandFields, StorageUtility::Scsi::cdbRegister& CdbRegister)
    {   
        switch (ScsiCommandCharacteristics.FieldFormatting)
        {
        case StorageUtility::Scsi::eFieldFormatting::COMMAND_12:
        {
            CdbRegister[0] = StorageUtility::Scsi::SCSI_COMMAND_ATA_PASS_THROUGH_12; 
            CdbRegister[3] = CommandFields.Feature;
            CdbRegister[4] = CommandFields.Count;
            CdbRegister[5] = ((CommandFields.Lba) & 0x000000FF);
            CdbRegister[6] = ((CommandFields.Lba >> 8) & 0x000000FF);
            CdbRegister[7] = ((CommandFields.Lba >> 16) & 0x000000FF);
            CdbRegister[8] = CommandFields.Device;
            CdbRegister[9] = CommandFields.SubCommand;
            CdbRegister[10] = 0;
            CdbRegister[11] = 0;
        } break;

        case StorageUtility::Scsi::eFieldFormatting::COMMAND_16:
        {
            CdbRegister[0] = StorageUtility::Scsi::SCSI_COMMAND_ATA_PASS_THROUGH_16; 
            CdbRegister[3] = (CommandFields.Feature >> 8) & 0xFF;
            CdbRegister[4] = CommandFields.Feature & 0xFF;
            CdbRegister[5] = (CommandFields.Count >> 8) & 0xFF;
            CdbRegister[6] = CommandFields.Count & 0xFF;
            CdbRegister[7] = (((CommandFields.Lba >> 16) & 0x0000FFFF) >> 8) & 0xFF;
            CdbRegister[8] = ((CommandFields.Lba) & 0x0000FFFF) & 0xFF;
            CdbRegister[9] = ((CommandFields.Lba >> 32) & 0x0000FFFF) & 0xFF;
            CdbRegister[10] = (((CommandFields.Lba) & 0x0000FFFF) >> 8) & 0xFF;
            CdbRegister[11] = (((CommandFields.Lba >> 32) & 0x0000FFFF) >> 8) & 0xFF;
            CdbRegister[12] = ((CommandFields.Lba >> 16) & 0x0000FFFF) & 0xFF;
            CdbRegister[13] = CommandFields.Device;
            CdbRegister[14] = CommandFields.SubCommand;
            CdbRegister[15] = 0;
        } break;

        default:
            break;
        }

        switch (ScsiCommandCharacteristics.TransferMode)
        {
        case StorageUtility::Scsi::eTransferMode::PIO_PROTOCOL:
        {
            if (ScsiCommandCharacteristics.DataAccess == StorageUtility::Scsi::eDataAccess::WRITE_TO_DEVICE)
            {
                CdbRegister[1] = 0x0B;                                                    // MULTIPLE_COUNT = 000, PROTOCOL = 0101b (PIO OUT), Extended = 1
            }
            else if (ScsiCommandCharacteristics.DataAccess == StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE)
            {
                CdbRegister[1] = 0x09;                                                    // MULTIPLE_COUNT = 000, PROTOCOL = 0100b (PIO IN), Extended = 1
            }
        } break;

        case StorageUtility::Scsi::eTransferMode::DMA_PROTOCOL:
        {
            CdbRegister[1] = 0x0D;                                                        // MULTIPLE_COUNT = 000, PROTOCOL = 0110b (DMA), Extended = 1
        } break;
        default:
        {
            printf("No supported!\n");
        } break;
        }

        switch (ScsiCommandCharacteristics.DataAccess)
        {
        case StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE:
        {
            CdbRegister[2] = 0x0B;                                                      // OFF_LINE = 0, CK_COND = 0, T_TYPE = 0, T_DIR = 1, BYT_BLOCK = 0, T_LENGTH = 11b
        } break;
        case StorageUtility::Scsi::eDataAccess::WRITE_TO_DEVICE:
        {
            CdbRegister[2] = 0x03;                                                      // OFF_LINE = 0, CK_COND = 0, T_TYPE = 0, T_DIR = 0, BYT_BLOCK = 0, T_LENGTH = 11b
        } break;
        }
    }
}

VT_STOR_SCSI_API void vtStorCommandHandlerScsiInit( std::shared_ptr<vtStor::cCommandHandlerInterface>& CommandHandler, std::shared_ptr<vtStor::Protocol::cProtocolInterface> Protocol )
{
    CommandHandler = std::make_shared<vtStor::cCommandHandlerScsi>( Protocol );
}