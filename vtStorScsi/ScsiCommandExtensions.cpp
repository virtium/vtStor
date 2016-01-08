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
#include "Buffer.h"
#include "CommandDescriptorScsi.h"
#include "ScsiCommandExtensions.h"

void cScsiCommandExtensions_GetScsiCommandExtensions(std::unique_ptr<vtStor::IScsiCommandExtensions>& ScsiCommandExtensions)
{
    ScsiCommandExtensions = std::unique_ptr<vtStor::IScsiCommandExtensions>(new vtStor::Scsi::cScsiCommandExtensions());
}

namespace vtStor
{
    namespace Scsi
    {
        cScsiCommandExtensions::cScsiCommandExtensions()
        {
        }

        cScsiCommandExtensions::~cScsiCommandExtensions()
        {
        }

        eErrorCode cScsiCommandExtensions::IssueCommand_Inquiry(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorScsi::SIZE_IN_BYTES);
            cCommandDescriptorScsi commandDescriptorVersion1 = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::sCdbFields& cdbFields = commandDescriptorVersion1.GetCdbFields();
            cdbFields.OpCode = SCSI_COMMAND_INQUIRY;
            cdbFields.TransferLen = 36;  // convert to allocation length, see specs

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_6;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cScsiCommandExtensions::IssueCommand_Read16(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Lba, U16 Count)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorScsi::SIZE_IN_BYTES);
            cCommandDescriptorScsi commandDescriptorVersion1 = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::sCdbFields& cdbFields = commandDescriptorVersion1.GetCdbFields();
            cdbFields.OpCode = SCSI_COMMAND_READ16;
            cdbFields.Lba = Lba;
            cdbFields.TransferLen = Count;

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_16;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = Count * StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cScsiCommandExtensions::IssueCommand_Read10(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Lba, U16 Count)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorScsi::SIZE_IN_BYTES);
            cCommandDescriptorScsi commandDescriptorVersion1 = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::sCdbFields& cdbFields = commandDescriptorVersion1.GetCdbFields();
            cdbFields.OpCode = SCSI_COMMAND_READ10;
            cdbFields.Lba = Lba;
            cdbFields.TransferLen = Count;

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_10;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = Count * StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cScsiCommandExtensions::IssueCommand_Write16(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Lba, U16 Count)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorScsi::SIZE_IN_BYTES);
            cCommandDescriptorScsi commandDescriptorVersion1 = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::sCdbFields& cdbFields = commandDescriptorVersion1.GetCdbFields();
            cdbFields.OpCode = SCSI_COMMAND_WRITE16;
            cdbFields.Lba = Lba;
            cdbFields.TransferLen = Count;

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_16;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::WRITE_TO_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = Count * StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cScsiCommandExtensions::IssueCommand_Write10(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Lba, U16 Count)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorScsi::SIZE_IN_BYTES);
            cCommandDescriptorScsi commandDescriptorVersion1 = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::sCdbFields& cdbFields = commandDescriptorVersion1.GetCdbFields();
            cdbFields.OpCode = SCSI_COMMAND_WRITE10;
            cdbFields.Lba = Lba;
            cdbFields.TransferLen = Count;

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_10;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::WRITE_TO_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = Count * StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cScsiCommandExtensions::IssueCommand_AtaIdentifyDevice(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorScsi::SIZE_IN_BYTES);
            cCommandDescriptorScsi commandDescriptorVersion1 = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::sCdbFields& cdbFields = commandDescriptorVersion1.GetCdbFields();
            cdbFields.OpCode = SCSI_COMMAND_ATA_PASS_THROUGH;
            cdbFields.Service = 0x09;
            cdbFields.Lba = (U64)0x0B << 56;
            cdbFields.TransferLen = 0;
            cdbFields.Group = ATA_SUBCOMMAND_IDENTIFY_DEVICE;

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_16;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cScsiCommandExtensions::IssueCommand_AtaReadDma(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Lba, U16 Count)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorScsi::SIZE_IN_BYTES);
            cCommandDescriptorScsi commandDescriptorVersion1 = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::sCdbFields& cdbFields = commandDescriptorVersion1.GetCdbFields();
            cdbFields.OpCode = SCSI_COMMAND_ATA_PASS_THROUGH;
            cdbFields.Service = 0x0D;
            cdbFields.Lba = ((U64)0x0B << 56) | ((U16)Count << 24) | (((U64)Lba & 0xFFFF) << 8) | (((U64)Lba >> 24) & 0xFF);
            U8 Device = 1 << 6;
            cdbFields.TransferLen = (Lba & 0xFF0000) | ((Lba & 0xFFFF00000000) >> 32) | Device;
            cdbFields.Group = ATA_SUBCOMMAND_READ_DMA;

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_16;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = Count * StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cScsiCommandExtensions::IssueCommand_AtaWriteDma(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Lba, U16 Count)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorScsi::SIZE_IN_BYTES);
            cCommandDescriptorScsi commandDescriptorVersion1 = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::sCdbFields& cdbFields = commandDescriptorVersion1.GetCdbFields();
            cdbFields.OpCode = SCSI_COMMAND_ATA_PASS_THROUGH;
            cdbFields.Service = 0x0D;
            cdbFields.Lba = ((U64)0x03 << 56) | ((U16)Count << 24) | (((U64)Lba & 0xFFFF) << 8) | (((U64)Lba >> 24) & 0xFF);
            U8 Device = 1 << 6;
            cdbFields.TransferLen = (Lba & 0xFF0000) | ((Lba & 0xFFFF00000000) >> 32) | Device;
            cdbFields.Group = ATA_SUBCOMMAND_WRITE_DMA;

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_16;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::WRITE_TO_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = Count * StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cScsiCommandExtensions::IssueCommand_AtaReadBuffer(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorScsi::SIZE_IN_BYTES);
            cCommandDescriptorScsi commandDescriptorVersion1 = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::sCdbFields& cdbFields = commandDescriptorVersion1.GetCdbFields();
            cdbFields.OpCode = SCSI_COMMAND_ATA_PASS_THROUGH;
            cdbFields.Service = 0x09;
            cdbFields.Lba = (U64)0x0B << 56;
            cdbFields.TransferLen = 0;
            cdbFields.Group = ATA_SUBCOMMAND_READ_BUFFER;

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_16;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cScsiCommandExtensions::IssueCommand_AtaWriteBuffer(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorScsi::SIZE_IN_BYTES);
            cCommandDescriptorScsi commandDescriptorVersion1 = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::sCdbFields& cdbFields = commandDescriptorVersion1.GetCdbFields();
            cdbFields.OpCode = SCSI_COMMAND_ATA_PASS_THROUGH;
            cdbFields.Service = 0x0B;
            cdbFields.Lba = ((U64)0x03 << 56);
            cdbFields.TransferLen = 0;
            cdbFields.Group = ATA_SUBCOMMAND_WRITE_BUFFER;

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_16;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::WRITE_TO_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cScsiCommandExtensions::IssueCommand_AtaSmart(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U8 SubCommand)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorScsi::SIZE_IN_BYTES);
            cCommandDescriptorScsi commandDescriptorVersion1 = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::sCdbFields& cdbFields = commandDescriptorVersion1.GetCdbFields();
            cdbFields.OpCode = SCSI_COMMAND_ATA_PASS_THROUGH;
            cdbFields.Service = 0x09;
            U64 Lba = 0xC2004F0000;
            U8 Device = 1 << 6;
            cdbFields.Lba = ((U64)0x0B << 56) | ((U64)SubCommand << 40) | (((U64)Lba & 0xFFFF) << 8) | (((U64)Lba >> 24) & 0xFF);
            cdbFields.TransferLen = (((Lba & 0xFF0000) | ((Lba & 0xFFFF00000000) >> 32)) << 8) | Device;
            cdbFields.Group = ATA_SUBCOMMAND_SMART;

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_16;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cScsiCommandExtensions::IssueCommand_AtaDownloadMicrocode(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U8 SubCommand, U16 BlockCount, U16 BufferOffset)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorScsi::SIZE_IN_BYTES);
            cCommandDescriptorScsi commandDescriptorVersion1 = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::sCdbFields& cdbFields = commandDescriptorVersion1.GetCdbFields();
            cdbFields.OpCode = SCSI_COMMAND_ATA_PASS_THROUGH;
            cdbFields.Service = 0x09;
            U8 Count = (BlockCount & 0xFF);
            U64 address = ((BlockCount >> 8) & 0xFF);
            address |= ((BufferOffset & 0xFF) << 8);
            address |= ((BufferOffset & 0xFF00) << 8);
            U64 Lba = address;
            cdbFields.Lba = ((U64)0x0B << 56) | ((U64)SubCommand << 40) | (((U64)Lba & 0xFFFF) << 8) | (((U64)Lba >> 24) & 0xFF);
            cdbFields.TransferLen = (Lba & 0xFF0000) | ((Lba & 0xFFFF00000000) >> 32);
            cdbFields.Group = ATA_SUBCOMMAND_DOWNLOADMICROCODE;

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_16;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::WRITE_TO_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = (BlockCount & 0xFF) * StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }
    }
}
