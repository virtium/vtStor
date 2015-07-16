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
#include "Buffer.h"
#include "ScsiCommandDescriptor.h"
#include "DriveScsiCommandExtensions.h"

namespace vtStor
{
    namespace Scsi
    {
        eErrorCode IssueCommand_Inquiry(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data)
        {
            std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>(cScsiCommandDescriptor::SIZE_IN_BYTES);
            cScsiCommandDescriptor commandDescriptorVersion1 = cScsiCommandDescriptor::Writer(commandDescriptor);

            StorageUtility::Scsi::sCdbFields& cdbFields = commandDescriptorVersion1.GetCdbFields();
            cdbFields.OpCode = SCSI_COMMAND_INQUIRY;
            cdbFields.TransferLen = 36;  // convert to allocation length, see specs

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_6;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Scsi::SECTOR_SIZE_IN_BYTES;

            Drive->IssueCommand(CommandType, commandDescriptor, Data);

            return(eErrorCode::None);
        }

        eErrorCode IssueCommand_Read6(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U16 Lba, U8 Count)
        {
            std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>(cScsiCommandDescriptor::SIZE_IN_BYTES);
            cScsiCommandDescriptor commandDescriptorVersion1 = cScsiCommandDescriptor::Writer(commandDescriptor);

            StorageUtility::Scsi::sCdbFields& cdbFields = commandDescriptorVersion1.GetCdbFields();
            cdbFields.OpCode = SCSI_COMMAND_READ06;
            cdbFields.Service = Lba >> 16;
            cdbFields.Lba = Lba & 0xFFFF;
            cdbFields.TransferLen = Count;

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_6;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = Count * StorageUtility::Scsi::SECTOR_SIZE_IN_BYTES;

            Drive->IssueCommand(CommandType, commandDescriptor, Data);

            return(eErrorCode::None);
        }

    eErrorCode IssueCommand_AtaIdentifyDevice(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data)
    {
        std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>(cScsiCommandDescriptor::SIZE_IN_BYTES);
        cScsiCommandDescriptor commandDescriptorVersion1 = cScsiCommandDescriptor::Writer(commandDescriptor);

        StorageUtility::Scsi::sCdbFields& cdbFields = commandDescriptorVersion1.GetCdbFields();
        cdbFields.OpCode = SCSI_COMMAND_ATA_PASS_THROUGH;
        cdbFields.Service = 0x09; // hardcode
        cdbFields.Lba = (U64)0x0B << 56; // hardcode
        cdbFields.TransferLen = 0;
        cdbFields.Group = ATA_SUBCOMMAND_IDENTIFY_DEVICE;

        StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
        commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_16;
        commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE;
        commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Scsi::SECTOR_SIZE_IN_BYTES;

        Drive->IssueCommand(CommandType, commandDescriptor, Data);

        return(eErrorCode::None);
    }
    /*
    eErrorCode IssueCommand_AtaReadDma(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U32 Lba, U8 Count)
    {
        std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>(cAtaPassThroughCommandDescriptor::SIZE_IN_BYTES);
        cAtaPassThroughCommandDescriptor commandDescriptorVersion1 = cAtaPassThroughCommandDescriptor::Writer(commandDescriptor);

        StorageUtility::Scsi::sCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
        commandFields.SubCommand = ATA_SUBCOMMAND_READ_DMA;
        commandFields.Count = Count;
        commandFields.Feature = 0;
        commandFields.Lba = Lba;
        commandFields.Device = 1 << 6;

        StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
        commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_16;
        commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE;
        commandCharacteristics.TransferMode = StorageUtility::Scsi::eTransferMode::DMA_PROTOCOL;
        commandCharacteristics.DataTransferLengthInBytes = Count * StorageUtility::Scsi::SECTOR_SIZE_IN_BYTES;

        Drive->IssueCommand(CommandType, commandDescriptor, Data);

        return(eErrorCode::None);
    }

    eErrorCode IssueCommand_AtaWriteDma(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U32 Lba, U8 Count)
    {
        std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>(cAtaPassThroughCommandDescriptor::SIZE_IN_BYTES);
        cAtaPassThroughCommandDescriptor commandDescriptorVersion1 = cAtaPassThroughCommandDescriptor::Writer(commandDescriptor);

        StorageUtility::Scsi::sCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
        commandFields.SubCommand = ATA_SUBCOMMAND_WRITE_DMA;
        commandFields.Count = Count;
        commandFields.Feature = 0;
        commandFields.Lba = Lba;
        commandFields.Device = 1 << 6;

        StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
        commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_16;
        commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::WRITE_TO_DEVICE;
        commandCharacteristics.TransferMode = StorageUtility::Scsi::eTransferMode::DMA_PROTOCOL;
        commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Scsi::SECTOR_SIZE_IN_BYTES;

        Drive->IssueCommand(CommandType, commandDescriptor, Data);

        return(eErrorCode::None);
    }

    eErrorCode IssueCommand_AtaReadBuffer(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data)
    {
        std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>(cAtaPassThroughCommandDescriptor::SIZE_IN_BYTES);
        cAtaPassThroughCommandDescriptor commandDescriptorVersion1 = cAtaPassThroughCommandDescriptor::Writer(commandDescriptor);

        StorageUtility::Scsi::sCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
        commandFields.SubCommand = ATA_SUBCOMMAND_READ_BUFFER;

        StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
        commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_16;
        commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE;
        commandCharacteristics.TransferMode = StorageUtility::Scsi::eTransferMode::PIO_PROTOCOL;
        commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Scsi::SECTOR_SIZE_IN_BYTES;

        Drive->IssueCommand(CommandType, commandDescriptor, Data);

        return(eErrorCode::None);
    }

    eErrorCode IssueCommand_AtaWriteBuffer(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data)
    {
        std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>(cAtaPassThroughCommandDescriptor::SIZE_IN_BYTES);
        cAtaPassThroughCommandDescriptor commandDescriptorVersion1 = cAtaPassThroughCommandDescriptor::Writer(commandDescriptor);

        StorageUtility::Scsi::sCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
        commandFields.SubCommand = ATA_SUBCOMMAND_WRITE_BUFFER;

        StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
        commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_16;
        commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::WRITE_TO_DEVICE;
        commandCharacteristics.TransferMode = StorageUtility::Scsi::eTransferMode::PIO_PROTOCOL;
        commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Scsi::SECTOR_SIZE_IN_BYTES;

        Drive->IssueCommand(CommandType, commandDescriptor, Data);

        return(eErrorCode::None);
    }

    eErrorCode IssueCommand_AtaSmart(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U8 SubCommand)
    {
        std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>(cAtaPassThroughCommandDescriptor::SIZE_IN_BYTES);
        cAtaPassThroughCommandDescriptor commandDescriptorVersion1 = cAtaPassThroughCommandDescriptor::Writer(commandDescriptor);

        StorageUtility::Scsi::sCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
        commandFields.SubCommand = ATA_SUBCOMMAND_SMART;
        commandFields.Feature = SubCommand;
        commandFields.Lba = 0xC24F00;
        commandFields.Device = 1 << 6;

        StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
        commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_16;
        commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE;
        commandCharacteristics.TransferMode = StorageUtility::Scsi::eTransferMode::PIO_PROTOCOL;
        commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Scsi::SECTOR_SIZE_IN_BYTES;

        Drive->IssueCommand(CommandType, commandDescriptor, Data);

        return(eErrorCode::None);
    }

    eErrorCode IssueCommand_AtaDownloadMicrocode(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U8 SubCommand, U16 BlockCount, U16 BufferOffset)
    {
        std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>(cAtaPassThroughCommandDescriptor::SIZE_IN_BYTES);
        cAtaPassThroughCommandDescriptor commandDescriptorVersion1 = cAtaPassThroughCommandDescriptor::Writer(commandDescriptor);

        StorageUtility::Scsi::sCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
        commandFields.SubCommand = ATA_SUBCOMMAND_DOWNLOADMICROCODE;
        commandFields.Feature = SubCommand;
        commandFields.Count = (BlockCount & 0xFF);
        U64 address = ((BlockCount >> 8) & 0xFF);
        address |= ((BufferOffset & 0xFF) << 8);
        address |= ((BufferOffset & 0xFF00) << 8);
        commandFields.Lba = address;
        
        StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
        commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_16;
        commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::WRITE_TO_DEVICE;
        commandCharacteristics.TransferMode = StorageUtility::Scsi::eTransferMode::PIO_PROTOCOL;
        commandCharacteristics.DataTransferLengthInBytes = (BlockCount & 0xFF) * StorageUtility::Scsi::SECTOR_SIZE_IN_BYTES;

        Drive->IssueCommand(CommandType, commandDescriptor, Data);

        return(eErrorCode::None);
    }
    */
}
}
