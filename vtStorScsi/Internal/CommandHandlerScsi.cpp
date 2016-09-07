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
#include "CommandDescriptorScsi.h"
#include "Buffer.h"
#include "BufferFormatter.h"
#include "ScsiProtocolEssense1.h"
#include "CommandHandlerScsi.h"
#include "StorageUtility.h"

void cCommandHandlerScsi_GetCommandHandler(std::shared_ptr<vtStor::ICommandHandler>& CommandHandler, std::shared_ptr<vtStor::IProtocol> Protocol)
{
    CommandHandler = std::shared_ptr<vtStor::ICommandHandler>(new vtStor::cCommandHandlerScsi(Protocol));
}

namespace vtStor
{
    cCommandHandlerScsi::cCommandHandlerScsi(std::shared_ptr<IProtocol> Protocol) : m_Protocol(Protocol)
    {
    }

    cCommandHandlerScsi::~cCommandHandlerScsi()
    {
    }

    eErrorCode cCommandHandlerScsi::IssueCommand(const DeviceHandle& Handle, std::shared_ptr<const IBuffer> CommandDescriptor, std::shared_ptr<IBuffer> Data)
    {
        eErrorCode errorCode = eErrorCode::None;

        cBufferFormatter bufferFormatter = cBufferFormatter::Reader(CommandDescriptor);

        if (true == vtStor::CompareUUID(bufferFormatter.GetHeader().Format, Scsi::cCommandDescriptorScsi::FormatType))
        {
            Scsi::cCommandDescriptorScsi commandDescriptor = Scsi::cCommandDescriptorScsi::Reader(CommandDescriptor);
            const StorageUtility::Scsi::uCommandInputFields& commandInputFields = commandDescriptor.GetCommandInputFields();

            std::shared_ptr<IBuffer> buffer = std::make_shared<cBuffer>(vtStor::Protocol::cEssenseScsi1::SIZE_IN_BYTES);
            Protocol::cEssenseScsi1 essense = Protocol::cEssenseScsi1::Writer(buffer);

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = essense.GetCommandCharacteristics();
            commandCharacteristics = commandDescriptor.GetCommandCharacteristics();

            StorageUtility::Scsi::uCdb& cdbRegister = essense.GetCdbRegisters();
            PrepareCdbRegister(commandCharacteristics, commandInputFields, cdbRegister);

            errorCode = m_Protocol->IssueCommand(Handle, buffer, Data);
        }

        else
        {
            errorCode = eErrorCode::FormatNotSupported;
        }

        return(errorCode);
    }

    void cCommandHandlerScsi::PrepareCdbRegister(const StorageUtility::Scsi::sCommandCharacteristics& ScsiCommandCharacteristics,
        const StorageUtility::Scsi::uCommandInputFields& InputFields, StorageUtility::Scsi::uCdb& CdbRegister)
    {
        switch (ScsiCommandCharacteristics.FieldFormatting)
        {
        case StorageUtility::Scsi::eFieldFormatting::COMMAND_6:
        {
            CdbRegister.Cdb_16.Registers.Register0 = InputFields.Command6.OpCode;
            CdbRegister.Cdb_16.Registers.Register1 = (InputFields.Command6.Service & 0xE0) | ((InputFields.Command6.Lba >> 16) & 0x1F);
            CdbRegister.Cdb_16.Registers.Register2 = ((InputFields.Command6.Lba >> 8) & 0xFF);
            CdbRegister.Cdb_16.Registers.Register3 = (InputFields.Command6.Lba & 0xFF);
            CdbRegister.Cdb_16.Registers.Register4 = (InputFields.Command6.Length & 0xFF);
            CdbRegister.Cdb_16.Registers.Register5 = InputFields.Command6.Control;
        } break;

        case StorageUtility::Scsi::eFieldFormatting::COMMAND_10:
        {
            CdbRegister.Cdb_16.Registers.Register0 = InputFields.Command10.OpCode;
            CdbRegister.Cdb_16.Registers.Register1 = InputFields.Command10.Service;
            CdbRegister.Cdb_16.Registers.Register2 = ((InputFields.Command10.Lba >> 24) & 0xFF);
            CdbRegister.Cdb_16.Registers.Register3 = ((InputFields.Command10.Lba >> 16) & 0xFF);
            CdbRegister.Cdb_16.Registers.Register4 = ((InputFields.Command10.Lba >> 8) & 0xFF);
            CdbRegister.Cdb_16.Registers.Register5 = (InputFields.Command10.Lba & 0xFF);
            CdbRegister.Cdb_16.Registers.Register6 = InputFields.Command10.MiscCdb;
            CdbRegister.Cdb_16.Registers.Register7 = (InputFields.Command10.Length >> 8) & 0xFF;
            CdbRegister.Cdb_16.Registers.Register8 = InputFields.Command10.Length & 0xFF;
            CdbRegister.Cdb_16.Registers.Register9 = InputFields.Command10.Control;
        } break;

        case StorageUtility::Scsi::eFieldFormatting::COMMAND_12:
        {
            CdbRegister.Cdb_16.Registers.Register0 = InputFields.Command12.OpCode;
            CdbRegister.Cdb_16.Registers.Register1 = InputFields.Command12.Service;
            CdbRegister.Cdb_16.Registers.Register2 = ((InputFields.Command12.Lba >> 24) & 0xFF);
            CdbRegister.Cdb_16.Registers.Register3 = ((InputFields.Command12.Lba >> 16) & 0xFF);
            CdbRegister.Cdb_16.Registers.Register4 = ((InputFields.Command12.Lba >> 8) & 0xFF);
            CdbRegister.Cdb_16.Registers.Register5 = (InputFields.Command12.Lba & 0xFF);
            CdbRegister.Cdb_16.Registers.Register6 = ((InputFields.Command12.Length >> 24) & 0xFF);
            CdbRegister.Cdb_16.Registers.Register7 = ((InputFields.Command12.Length >> 16) & 0xFF);
            CdbRegister.Cdb_16.Registers.Register8 = ((InputFields.Command12.Length >> 8) & 0xFF);
            CdbRegister.Cdb_16.Registers.Register9 = (InputFields.Command12.Length & 0xFF);
            CdbRegister.Cdb_16.Registers.Register10 = InputFields.Command12.MiscCdb;
            CdbRegister.Cdb_16.Registers.Register11 = InputFields.Command12.Control;
        } break;

        case StorageUtility::Scsi::eFieldFormatting::COMMAND_16:
        {
            CdbRegister.Cdb_16.Registers.Register0 = InputFields.Command16.OpCode;
            CdbRegister.Cdb_16.Registers.Register1 = InputFields.Command16.Service;
            CdbRegister.Cdb_16.Registers.Register2 = ((InputFields.Command16.Lba >> 56) & 0xFF);
            CdbRegister.Cdb_16.Registers.Register3 = ((InputFields.Command16.Lba >> 48) & 0xFF);
            CdbRegister.Cdb_16.Registers.Register4 = ((InputFields.Command16.Lba >> 40) & 0xFF);
            CdbRegister.Cdb_16.Registers.Register5 = ((InputFields.Command16.Lba >> 32) & 0xFF);
            CdbRegister.Cdb_16.Registers.Register6 = ((InputFields.Command16.Lba >> 24) & 0xFF);
            CdbRegister.Cdb_16.Registers.Register7 = ((InputFields.Command16.Lba >> 16) & 0xFF);
            CdbRegister.Cdb_16.Registers.Register8 = ((InputFields.Command16.Lba >> 8) & 0xFF);
            CdbRegister.Cdb_16.Registers.Register9 = (InputFields.Command16.Lba & 0xFF);
            CdbRegister.Cdb_16.Registers.Register10 = ((InputFields.Command16.Length >> 24) & 0xFF);
            CdbRegister.Cdb_16.Registers.Register11 = ((InputFields.Command16.Length >> 16) & 0xFF);
            CdbRegister.Cdb_16.Registers.Register12 = ((InputFields.Command16.Length >> 8) & 0xFF);
            CdbRegister.Cdb_16.Registers.Register13 = (InputFields.Command16.Length & 0xFF);
            CdbRegister.Cdb_16.Registers.Register14 = InputFields.Command16.MiscCdb;
            CdbRegister.Cdb_16.Registers.Register15 = InputFields.Command16.Control;
        } break;

        case StorageUtility::Scsi::eFieldFormatting::ATAPASSTHROUGH_16:
        {
            CdbRegister.Cdb_16.Registers.Register0 = InputFields.AtaPassThrough16.OpCode;
            //     7 6 5            4 3 2 1        0
            // MULTIPLE_COUNT       PROTOCOL     EXTEND
            CdbRegister.Cdb_16.Registers.Register1 = (((InputFields.AtaPassThrough16.MultipleCount << 5) & 0xE0)
                | ((InputFields.AtaPassThrough16.Protocol << 1) & 0x1E)
                | (InputFields.AtaPassThrough16.Extend & 0x01));
            //   7 6           5           4          3        2          1 0
            // OFF_LINE     CK_COND     Reserved    T_DIR   BYT_BLOK    T_LENGTH
            CdbRegister.Cdb_16.Registers.Register2 = (((InputFields.AtaPassThrough16.Offline << 6) & 0xC0)
                | ((InputFields.AtaPassThrough16.CkCond << 5) & 0x20)
                | ((InputFields.AtaPassThrough16.TDir << 3) & 0x08)
                | ((InputFields.AtaPassThrough16.ByteBlock << 2) & 0x04)
                | (InputFields.AtaPassThrough16.TLength & 0x03));
            CdbRegister.Cdb_16.Registers.Register3 = ((InputFields.AtaPassThrough16.Features >> 8) & 0xFF);
            CdbRegister.Cdb_16.Registers.Register4 = (InputFields.AtaPassThrough16.Features & 0xFF);
            CdbRegister.Cdb_16.Registers.Register13 = InputFields.AtaPassThrough16.Device;
            CdbRegister.Cdb_16.Registers.Register14 = InputFields.AtaPassThrough16.Command;
            CdbRegister.Cdb_16.Registers.Register15 = InputFields.AtaPassThrough16.Control;

            if (1 == InputFields.AtaPassThrough16.Extend)
            {
                // Byte 5, 7, 9, 11 are valid
                CdbRegister.Cdb_16.Registers.Register5 = ((InputFields.AtaPassThrough16.SectorCount >> 8) & 0xFF);
                CdbRegister.Cdb_16.Registers.Register6 = (InputFields.AtaPassThrough16.SectorCount & 0xFF);
                CdbRegister.Cdb_16.Registers.Register7 = ((InputFields.AtaPassThrough16.Lba >> 8) & 0xFF);
                CdbRegister.Cdb_16.Registers.Register8 = (InputFields.AtaPassThrough16.Lba & 0xFF);
                CdbRegister.Cdb_16.Registers.Register9 = ((InputFields.AtaPassThrough16.Lba >> 24) & 0xFF);
                CdbRegister.Cdb_16.Registers.Register10 = ((InputFields.AtaPassThrough16.Lba >> 16) & 0xFF);
                CdbRegister.Cdb_16.Registers.Register11 = ((InputFields.AtaPassThrough16.Lba >> 40) & 0xFF);
                CdbRegister.Cdb_16.Registers.Register12 = ((InputFields.AtaPassThrough16.Lba >> 32) & 0xFF);
            }
            else
            {
                // Byte 5, 7, 9, 11 are reserved
                CdbRegister.Cdb_16.Registers.Register6 = (InputFields.AtaPassThrough16.SectorCount & 0xFF);
                CdbRegister.Cdb_16.Registers.Register8 = (InputFields.AtaPassThrough16.Lba & 0xFF);
                CdbRegister.Cdb_16.Registers.Register10 = ((InputFields.AtaPassThrough16.Lba >> 8) & 0xFF);
                CdbRegister.Cdb_16.Registers.Register12 = ((InputFields.AtaPassThrough16.Lba >> 16) & 0xFF);
                CdbRegister.Cdb_16.Registers.Register5 = 0;
                CdbRegister.Cdb_16.Registers.Register7 = 0;
                CdbRegister.Cdb_16.Registers.Register9 = 0;
                CdbRegister.Cdb_16.Registers.Register11 = 0;
            }

            if (StorageUtility::Scsi::eDataAccess::NONE != ScsiCommandCharacteristics.DataAccess)
            {
                // Initialize the last 4 bits of the 28 bit LBA
                U8 last4BitInLBA;
                last4BitInLBA = (U8)((InputFields.AtaPassThrough16.Lba >> 24) & 0x0000000F);

                // 0xE0 is used instead of 0x40 to be safe and support legacy systems
                CdbRegister.Cdb_16.Registers.Register13 = (U8)(0xE0 | last4BitInLBA);
            }
        } break;

        default:
            break;
        }
    }
}
