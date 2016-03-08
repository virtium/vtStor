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
            cCommandDescriptorScsi commandDescriptorScsi = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::uCommandInputFields& commandInputFields = commandDescriptorScsi.GetCommandInputFields();
            commandInputFields.Command6.OpCode = SCSI_COMMAND_INQUIRY;
            commandInputFields.Command6.Length = 36;

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorScsi.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_6;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cScsiCommandExtensions::IssueCommand_Read16(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Lba, U16 Count)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorScsi::SIZE_IN_BYTES);
            cCommandDescriptorScsi commandDescriptorScsi = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::uCommandInputFields& commandInputFields = commandDescriptorScsi.GetCommandInputFields();
            commandInputFields.Command16.OpCode = SCSI_COMMAND_READ16;
            commandInputFields.Command16.Lba = Lba;
            commandInputFields.Command16.Length = Count;

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorScsi.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_16;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = Count * StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cScsiCommandExtensions::IssueCommand_Read10(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Lba, U16 Count)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorScsi::SIZE_IN_BYTES);
            cCommandDescriptorScsi commandDescriptorScsi = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::uCommandInputFields& commandInputFields = commandDescriptorScsi.GetCommandInputFields();
            commandInputFields.Command10.OpCode = SCSI_COMMAND_READ10;
            commandInputFields.Command10.Lba = Lba;
            commandInputFields.Command10.Length = Count;

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorScsi.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_10;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = Count * StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cScsiCommandExtensions::IssueCommand_Write16(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Lba, U16 Count)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorScsi::SIZE_IN_BYTES);
            cCommandDescriptorScsi commandDescriptorScsi = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::uCommandInputFields& commandInputFields = commandDescriptorScsi.GetCommandInputFields();
            commandInputFields.Command16.OpCode = SCSI_COMMAND_WRITE16;
            commandInputFields.Command16.Lba = Lba;
            commandInputFields.Command16.Length = Count;

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorScsi.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_16;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::WRITE_TO_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = Count * StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cScsiCommandExtensions::IssueCommand_Write10(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Lba, U16 Count)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorScsi::SIZE_IN_BYTES);
            cCommandDescriptorScsi commandDescriptorScsi = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::uCommandInputFields& commandInputFields = commandDescriptorScsi.GetCommandInputFields();
            commandInputFields.Command10.OpCode = SCSI_COMMAND_WRITE10;
            commandInputFields.Command10.Lba = Lba;
            commandInputFields.Command10.Length = Count;

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorScsi.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::COMMAND_10;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::WRITE_TO_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = Count * StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cScsiCommandExtensions::IssueCommand_AtaIdentifyDevice(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorScsi::SIZE_IN_BYTES);
            commandDescriptor->Memset(0);
            cCommandDescriptorScsi commandDescriptorScsi = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::uCommandInputFields& commandInputFields = commandDescriptorScsi.GetCommandInputFields();
            commandInputFields.AtaPassThrough16.OpCode = SCSI_COMMAND_ATA_PASS_THROUGH;
            commandInputFields.AtaPassThrough16.Command = ATA_SUBCOMMAND_IDENTIFY_DEVICE;
            commandInputFields.AtaPassThrough16.Protocol = 0x04;            // PIO Data In
            commandInputFields.AtaPassThrough16.TDir = 0x01;                // Device to host
            commandInputFields.AtaPassThrough16.TLength = 0x03;             // Transfer length is specified in STPSIU

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorScsi.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::ATAPASSTHROUGH_16;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cScsiCommandExtensions::IssueCommand_AtaReadDma(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Lba, U16 Count)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorScsi::SIZE_IN_BYTES);
            commandDescriptor->Memset(0);
            cCommandDescriptorScsi commandDescriptorScsi = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::uCommandInputFields& commandInputFields = commandDescriptorScsi.GetCommandInputFields();
            commandInputFields.AtaPassThrough16.OpCode = SCSI_COMMAND_ATA_PASS_THROUGH;
            commandInputFields.AtaPassThrough16.Command = ATA_SUBCOMMAND_READ_DMA;
            commandInputFields.AtaPassThrough16.Protocol = 0x06;            // DMA
            commandInputFields.AtaPassThrough16.TDir = 0x01;                // Device to host
            commandInputFields.AtaPassThrough16.TLength = 0x03;             // Transfer length is specified in STPSIU
            commandInputFields.AtaPassThrough16.Features = 0x00;
            commandInputFields.AtaPassThrough16.Lba = Lba;
            commandInputFields.AtaPassThrough16.SectorCount = Count;
            commandInputFields.AtaPassThrough16.Device = 0x40;
            commandInputFields.AtaPassThrough16.Control = 0x00;

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorScsi.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::ATAPASSTHROUGH_16;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = Count * StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cScsiCommandExtensions::IssueCommand_AtaWriteDma(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Lba, U16 Count)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorScsi::SIZE_IN_BYTES);
            commandDescriptor->Memset(0);
            cCommandDescriptorScsi commandDescriptorScsi = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::uCommandInputFields& commandInputFields = commandDescriptorScsi.GetCommandInputFields();
            commandInputFields.AtaPassThrough16.OpCode = SCSI_COMMAND_ATA_PASS_THROUGH;
            commandInputFields.AtaPassThrough16.Command = ATA_SUBCOMMAND_WRITE_DMA;
            commandInputFields.AtaPassThrough16.Protocol = 0x06;            // DMA
            commandInputFields.AtaPassThrough16.TDir = 0x00;                // Host to Device
            commandInputFields.AtaPassThrough16.TLength = 0x03;             // Transfer length is specified in STPSIU
            commandInputFields.AtaPassThrough16.Features = 0x00;
            commandInputFields.AtaPassThrough16.Lba = Lba;
            commandInputFields.AtaPassThrough16.SectorCount = Count;
            commandInputFields.AtaPassThrough16.Device = 0x40;
            commandInputFields.AtaPassThrough16.Control = 0x00;

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorScsi.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::ATAPASSTHROUGH_16;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::WRITE_TO_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = Count * StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cScsiCommandExtensions::IssueCommand_AtaReadBuffer(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorScsi::SIZE_IN_BYTES);
            commandDescriptor->Memset(0);
            cCommandDescriptorScsi commandDescriptorScsi = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::uCommandInputFields& commandInputFields = commandDescriptorScsi.GetCommandInputFields();
            commandInputFields.AtaPassThrough16.OpCode = SCSI_COMMAND_ATA_PASS_THROUGH;
            commandInputFields.AtaPassThrough16.Command = ATA_SUBCOMMAND_READ_BUFFER;
            commandInputFields.AtaPassThrough16.Protocol = 0x04;            // PIO Data In
            commandInputFields.AtaPassThrough16.TDir = 0x01;                // Device to host
            commandInputFields.AtaPassThrough16.TLength = 0x03;             // Transfer length is specified in STPSIU
  
            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorScsi.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::ATAPASSTHROUGH_16;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cScsiCommandExtensions::IssueCommand_AtaWriteBuffer(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorScsi::SIZE_IN_BYTES);
            commandDescriptor->Memset(0);
            cCommandDescriptorScsi commandDescriptorScsi = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::uCommandInputFields& commandInputFields = commandDescriptorScsi.GetCommandInputFields();
            commandInputFields.AtaPassThrough16.OpCode = SCSI_COMMAND_ATA_PASS_THROUGH;
            commandInputFields.AtaPassThrough16.Command = ATA_SUBCOMMAND_WRITE_BUFFER;
            commandInputFields.AtaPassThrough16.Protocol = 0x05;            // PIO Data Out
            commandInputFields.AtaPassThrough16.TDir = 0x00;                // Host to device
            commandInputFields.AtaPassThrough16.TLength = 0x03;             // Transfer length is specified in STPSIU

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorScsi.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::ATAPASSTHROUGH_16;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::WRITE_TO_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cScsiCommandExtensions::IssueCommand_AtaSmart(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U8 SubCommand)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorScsi::SIZE_IN_BYTES);
            commandDescriptor->Memset(0);
            cCommandDescriptorScsi commandDescriptorScsi = cCommandDescriptorScsi::Writer(commandDescriptor);

            StorageUtility::Scsi::uCommandInputFields& commandInputFields = commandDescriptorScsi.GetCommandInputFields();
            commandInputFields.AtaPassThrough16.OpCode = SCSI_COMMAND_ATA_PASS_THROUGH;
            commandInputFields.AtaPassThrough16.Command = ATA_SUBCOMMAND_SMART;
            commandInputFields.AtaPassThrough16.Protocol = 0x04;            // PIO Data In
            commandInputFields.AtaPassThrough16.TDir = 0x01;                // Device to host
            commandInputFields.AtaPassThrough16.TLength = 0x03;             // Transfer length is specified in STPSIU
            commandInputFields.AtaPassThrough16.Features = SubCommand;
            commandInputFields.AtaPassThrough16.Lba = ATA_SUBSMART_IDENTIFIER;

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = commandDescriptorScsi.GetCommandCharacteristics();
            commandCharacteristics.FieldFormatting = StorageUtility::Scsi::eFieldFormatting::ATAPASSTHROUGH_16;
            commandCharacteristics.DataAccess = StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE;
            commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Scsi::SCSI_SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }
    }
}
