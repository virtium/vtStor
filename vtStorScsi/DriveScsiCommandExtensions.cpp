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
    eErrorCode IssueCommand_AtaIdentifyDevice(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data)
    {
        std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>(cScsiCommandDescriptor::SIZE_IN_BYTES);
        cScsiCommandDescriptor commandDescriptorVersion1 = cScsiCommandDescriptor::Writer(commandDescriptor);

        StorageUtility::Scsi::sCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
        commandFields.InputFields.Command = SCSI_COMMAND_ATA_PASS_THROUGH;
        commandFields.InputFields.SubCommand = ATA_SUBCOMMAND_IDENTIFY_DEVICE;
        commandFields.InputFields.Count = 0;
        commandFields.InputFields.Feature = 0;
        commandFields.InputFields.Lba = 0;

        StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
        commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_16;
        commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE;
        commandCharacteristics.TransferMode = StorageUtility::Scsi::eTransferMode::PIO_PROTOCOL;
        commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Scsi::SECTOR_SIZE_IN_BYTES;

        Drive->IssueCommand(CommandType, commandDescriptor, Data);

        return(eErrorCode::None);
    }

    eErrorCode IssueCommand_AtaReadDma(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U32 Lba, U8 Count)
    {
        std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>(cScsiCommandDescriptor::SIZE_IN_BYTES);
        cScsiCommandDescriptor commandDescriptorVersion1 = cScsiCommandDescriptor::Writer(commandDescriptor);

        StorageUtility::Scsi::sCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
        commandFields.InputFields.Command = SCSI_COMMAND_ATA_PASS_THROUGH;
        commandFields.InputFields.SubCommand = ATA_SUBCOMMAND_READ_DMA;
        commandFields.InputFields.Count = Count;
        commandFields.InputFields.Feature = 0;
        commandFields.InputFields.Lba = Lba;
        commandFields.InputFields.Device = 1 << 6;

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
        std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>(cScsiCommandDescriptor::SIZE_IN_BYTES);
        cScsiCommandDescriptor commandDescriptorVersion1 = cScsiCommandDescriptor::Writer(commandDescriptor);

        StorageUtility::Scsi::sCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
        commandFields.InputFields.Command = SCSI_COMMAND_ATA_PASS_THROUGH;
        commandFields.InputFields.SubCommand = ATA_SUBCOMMAND_WRITE_DMA;
        commandFields.InputFields.Count = Count;
        commandFields.InputFields.Feature = 0;
        commandFields.InputFields.Lba = Lba;
        commandFields.InputFields.Device = 1 << 6;

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
        std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>(cScsiCommandDescriptor::SIZE_IN_BYTES);
        cScsiCommandDescriptor commandDescriptorVersion1 = cScsiCommandDescriptor::Writer(commandDescriptor);

        StorageUtility::Scsi::sCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
        commandFields.InputFields.Command = SCSI_COMMAND_ATA_PASS_THROUGH;
        commandFields.InputFields.SubCommand = ATA_SUBCOMMAND_READ_BUFFER;

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
        std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>(cScsiCommandDescriptor::SIZE_IN_BYTES);
        cScsiCommandDescriptor commandDescriptorVersion1 = cScsiCommandDescriptor::Writer(commandDescriptor);

        StorageUtility::Scsi::sCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
        commandFields.InputFields.Command = SCSI_COMMAND_ATA_PASS_THROUGH;
        commandFields.InputFields.SubCommand = ATA_SUBCOMMAND_WRITE_BUFFER;

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
        std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>(cScsiCommandDescriptor::SIZE_IN_BYTES);
        cScsiCommandDescriptor commandDescriptorVersion1 = cScsiCommandDescriptor::Writer(commandDescriptor);

        StorageUtility::Scsi::sCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
        commandFields.InputFields.Command = SCSI_COMMAND_ATA_PASS_THROUGH;
        commandFields.InputFields.SubCommand = ATA_SUBCOMMAND_SMART;
        commandFields.InputFields.Feature = SubCommand;
        commandFields.InputFields.Lba = 0xC24F00;
        commandFields.InputFields.Device = 1 << 6;

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
        std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>(cScsiCommandDescriptor::SIZE_IN_BYTES);
        cScsiCommandDescriptor commandDescriptorVersion1 = cScsiCommandDescriptor::Writer(commandDescriptor);

        StorageUtility::Scsi::sCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
        commandFields.InputFields.Command = SCSI_COMMAND_ATA_PASS_THROUGH;
        commandFields.InputFields.SubCommand = ATA_SUBCOMMAND_DOWNLOADMICROCODE;
        commandFields.InputFields.Feature = SubCommand;
        commandFields.InputFields.Count = (BlockCount & 0xFF);
        U64 address = ((BlockCount >> 8) & 0xFF);
        address |= ((BufferOffset & 0xFF) << 8);
        address |= ((BufferOffset & 0xFF00) << 8);
        commandFields.InputFields.Lba = address;
        
        StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
        commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_16;
        commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::WRITE_TO_DEVICE;
        commandCharacteristics.TransferMode = StorageUtility::Scsi::eTransferMode::PIO_PROTOCOL;
        commandCharacteristics.DataTransferLengthInBytes = (BlockCount & 0xFF) * StorageUtility::Scsi::SECTOR_SIZE_IN_BYTES;

        Drive->IssueCommand(CommandType, commandDescriptor, Data);

        return(eErrorCode::None);
    }
    
}
}
