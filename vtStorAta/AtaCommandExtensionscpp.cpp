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

#include "AtaCommandExtensions.h"
#include "Buffer.h"
#include "CommandDescriptorAta.h"
#include "TrimBufferFormatter.h"

void cAtaCommandExtensions_GetAtaCommandExtensions(std::unique_ptr<vtStor::IAtaCommandExtensions>& AtaCommandExtensions)
{
    AtaCommandExtensions = std::unique_ptr<vtStor::IAtaCommandExtensions>(new vtStor::Ata::cAtaCommandExtensions());
}

namespace vtStor
{
    namespace Ata
    {
        cAtaCommandExtensions::cAtaCommandExtensions()
        {
        }

        cAtaCommandExtensions::~cAtaCommandExtensions()
        {
        }

        eErrorCode cAtaCommandExtensions::IssueCommand_IdentifyDevice(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorAta::SIZE_IN_BYTES);
            cCommandDescriptorAta commandDescriptorVersion1 = cCommandDescriptorAta::Writer(commandDescriptor);

            StorageUtility::Ata::uCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
            commandFields.InputFields.Command = ATA_COMMAND_IDENTIFY_DEVICE;
            commandFields.InputFields.Count = 1;

            StorageUtility::Ata::sCommandCharacteristic& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();

            commandCharacteristics.DeviceReadyFlag = StorageUtility::Ata::eDeviceReadyFlag::DEVICE_READY_REQUIRED;
            commandCharacteristics.DataAccess = StorageUtility::Ata::eDataAccess::READ_FROM_DEVICE;
            commandCharacteristics.FieldFormatting = StorageUtility::Ata::eFieldFormatting::COMMAND_28_BIT;
            commandCharacteristics.TransferMode = StorageUtility::Ata::eTransferMode::PIO_PROTOCOL;
            commandCharacteristics.MultipleMode = StorageUtility::Ata::eMultipleMode::NOT_MULTIPLE_COMMAND;
            commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Ata::SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cAtaCommandExtensions::IssueCommand_ReadDma(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Lba, U16 Count)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorAta::SIZE_IN_BYTES);
            cCommandDescriptorAta commandDescriptorVersion1 = cCommandDescriptorAta::Writer(commandDescriptor);

            StorageUtility::Ata::uCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
            commandFields.InputFields.Command = ATA_COMMAND_READ_DMA;
            commandFields.InputFields.Lba = Lba;
            commandFields.InputFields.Count = Count;
            commandFields.InputFields.ChsMode = 0;

            StorageUtility::Ata::sCommandCharacteristic& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
            commandCharacteristics.DeviceReadyFlag = StorageUtility::Ata::eDeviceReadyFlag::DEVICE_READY_REQUIRED;
            commandCharacteristics.DataAccess = StorageUtility::Ata::eDataAccess::READ_FROM_DEVICE;
            commandCharacteristics.FieldFormatting = StorageUtility::Ata::eFieldFormatting::COMMAND_28_BIT;
            commandCharacteristics.TransferMode = StorageUtility::Ata::eTransferMode::DMA_PROTOCOL;
            commandCharacteristics.MultipleMode = StorageUtility::Ata::eMultipleMode::NOT_MULTIPLE_COMMAND;
            commandCharacteristics.DataTransferLengthInBytes = Count * StorageUtility::Ata::SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cAtaCommandExtensions::IssueCommand_WriteDma(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Lba, U16 Count)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorAta::SIZE_IN_BYTES);
            cCommandDescriptorAta commandDescriptorVersion1 = cCommandDescriptorAta::Writer(commandDescriptor);

            StorageUtility::Ata::uCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
            commandFields.InputFields.Command = ATA_COMMAND_WRITE_DMA;
            commandFields.InputFields.Lba = Lba;
            commandFields.InputFields.Count = Count;
            commandFields.InputFields.ChsMode = 0;

            StorageUtility::Ata::sCommandCharacteristic& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
            commandCharacteristics.DeviceReadyFlag = StorageUtility::Ata::eDeviceReadyFlag::DEVICE_READY_REQUIRED;
            commandCharacteristics.DataAccess = StorageUtility::Ata::eDataAccess::WRITE_TO_DEVICE;
            commandCharacteristics.FieldFormatting = StorageUtility::Ata::eFieldFormatting::COMMAND_28_BIT;
            commandCharacteristics.TransferMode = StorageUtility::Ata::eTransferMode::DMA_PROTOCOL;
            commandCharacteristics.MultipleMode = StorageUtility::Ata::eMultipleMode::NOT_MULTIPLE_COMMAND;
            commandCharacteristics.DataTransferLengthInBytes = Count * StorageUtility::Ata::SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cAtaCommandExtensions::IssueCommand_ReadBuffer(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorAta::SIZE_IN_BYTES);
            cCommandDescriptorAta commandDescriptorVersion1 = cCommandDescriptorAta::Writer(commandDescriptor);

            StorageUtility::Ata::uCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
            commandFields.InputFields.Command = ATA_COMMAND_READ_BUFFER;

            StorageUtility::Ata::sCommandCharacteristic& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
            commandCharacteristics.DeviceReadyFlag = StorageUtility::Ata::eDeviceReadyFlag::DEVICE_READY_REQUIRED;
            commandCharacteristics.DataAccess = StorageUtility::Ata::eDataAccess::READ_FROM_DEVICE;
            commandCharacteristics.FieldFormatting = StorageUtility::Ata::eFieldFormatting::COMMAND_28_BIT;
            commandCharacteristics.TransferMode = StorageUtility::Ata::eTransferMode::PIO_PROTOCOL;
            commandCharacteristics.MultipleMode = StorageUtility::Ata::eMultipleMode::NOT_MULTIPLE_COMMAND;
            commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Ata::SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cAtaCommandExtensions::IssueCommand_WriteBuffer(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorAta::SIZE_IN_BYTES);
            cCommandDescriptorAta commandDescriptorVersion1 = cCommandDescriptorAta::Writer(commandDescriptor);

            StorageUtility::Ata::uCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
            commandFields.InputFields.Command = ATA_COMMAND_WRITE_BUFFER;

            StorageUtility::Ata::sCommandCharacteristic& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
            commandCharacteristics.DeviceReadyFlag = StorageUtility::Ata::eDeviceReadyFlag::DEVICE_READY_REQUIRED;
            commandCharacteristics.DataAccess = StorageUtility::Ata::eDataAccess::WRITE_TO_DEVICE;
            commandCharacteristics.FieldFormatting = StorageUtility::Ata::eFieldFormatting::COMMAND_28_BIT;
            commandCharacteristics.TransferMode = StorageUtility::Ata::eTransferMode::PIO_PROTOCOL;
            commandCharacteristics.MultipleMode = StorageUtility::Ata::eMultipleMode::NOT_MULTIPLE_COMMAND;
            commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Ata::SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cAtaCommandExtensions::IssueCommand_Smart(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U8 SubCommand)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorAta::SIZE_IN_BYTES);
            cCommandDescriptorAta commandDescriptorVersion1 = cCommandDescriptorAta::Writer(commandDescriptor);

            StorageUtility::Ata::uCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
            commandFields.InputFields.Command = ATA_COMMAND_SMART;
            commandFields.InputFields.Feature = SubCommand;
            commandFields.InputFields.Lba = ATA_SMART_IDENTIFIER;

            StorageUtility::Ata::sCommandCharacteristic& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
            commandCharacteristics.DeviceReadyFlag = StorageUtility::Ata::eDeviceReadyFlag::DEVICE_READY_REQUIRED;
            commandCharacteristics.DataAccess = StorageUtility::Ata::eDataAccess::READ_FROM_DEVICE;
            commandCharacteristics.FieldFormatting = StorageUtility::Ata::eFieldFormatting::COMMAND_28_BIT;
            commandCharacteristics.TransferMode = StorageUtility::Ata::eTransferMode::PIO_PROTOCOL;
            commandCharacteristics.MultipleMode = StorageUtility::Ata::eMultipleMode::NOT_MULTIPLE_COMMAND;
            commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Ata::SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cAtaCommandExtensions::IssueCommand_DownloadMicrocode(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U8 SubCommand, U16 BlockCount, U16 BufferOffset)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorAta::SIZE_IN_BYTES);
            cCommandDescriptorAta commandDescriptorVersion1 = cCommandDescriptorAta::Writer(commandDescriptor);

            StorageUtility::Ata::uCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
            commandFields.InputFields.Command = ATA_COMMAND_DOWNLOADMICROCODE;
            commandFields.InputFields.Feature = SubCommand;
            commandFields.InputFields.Count = (BlockCount & 0xFF);
            U64 address = ((BlockCount >> 8) & 0xFF);
            address |= ((BufferOffset & 0xFF) << 8);
            address |= ((BufferOffset & 0xFF00) << 8);
            commandFields.InputFields.Lba = address;//(BlockCount >> 8) | (BufferOffset << 8);

            StorageUtility::Ata::sCommandCharacteristic& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
            commandCharacteristics.DeviceReadyFlag = StorageUtility::Ata::eDeviceReadyFlag::DEVICE_READY_REQUIRED;
            commandCharacteristics.DataAccess = StorageUtility::Ata::eDataAccess::WRITE_TO_DEVICE;
            commandCharacteristics.FieldFormatting = StorageUtility::Ata::eFieldFormatting::COMMAND_28_BIT;
            commandCharacteristics.TransferMode = StorageUtility::Ata::eTransferMode::PIO_PROTOCOL;
            commandCharacteristics.MultipleMode = StorageUtility::Ata::eMultipleMode::NOT_MULTIPLE_COMMAND;
            commandCharacteristics.DataTransferLengthInBytes = BlockCount * StorageUtility::Ata::SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cAtaCommandExtensions::IssueCommand_DownloadMicrocodeDma(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U8 SubCommand, U16 BlockCount, U16 BufferOffset)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorAta::SIZE_IN_BYTES);
            cCommandDescriptorAta commandDescriptorVersion1 = cCommandDescriptorAta::Writer(commandDescriptor);

            StorageUtility::Ata::uCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
            commandFields.InputFields.Command = ATA_COMMAND_DOWNLOADMICROCODE_DMA;
            commandFields.InputFields.Feature = SubCommand;
            commandFields.InputFields.Count = (BlockCount & 0xFF);
            commandFields.InputFields.Lba = (BlockCount >> 8) | (BufferOffset << 8);

            StorageUtility::Ata::sCommandCharacteristic& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
            commandCharacteristics.DeviceReadyFlag = StorageUtility::Ata::eDeviceReadyFlag::DEVICE_READY_REQUIRED;
            commandCharacteristics.DataAccess = StorageUtility::Ata::eDataAccess::WRITE_TO_DEVICE;
            commandCharacteristics.FieldFormatting = StorageUtility::Ata::eFieldFormatting::COMMAND_28_BIT;
            commandCharacteristics.TransferMode = StorageUtility::Ata::eTransferMode::DMA_PROTOCOL;
            commandCharacteristics.MultipleMode = StorageUtility::Ata::eMultipleMode::NOT_MULTIPLE_COMMAND;
            commandCharacteristics.DataTransferLengthInBytes = BlockCount * StorageUtility::Ata::SECTOR_SIZE_IN_BYTES;

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cAtaCommandExtensions::IssueCommand_Trim(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, const std::vector<StorageUtility::Ata::sLbaRangeEntry>& LbaRangeEntries)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptorAta::SIZE_IN_BYTES);
            cCommandDescriptorAta commandDescriptorVersion1 = cCommandDescriptorAta::Writer(commandDescriptor);
            U32 sectorCount = cTrimBufferFormatter::CalculateSectorCountInput(LbaRangeEntries);

            StorageUtility::Ata::uCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
            commandFields.InputFields.Command = ATA_COMMAND_TRIM;
            commandFields.InputFields.Count = sectorCount;
            commandFields.InputFields.ChsMode = 0;
            commandFields.InputFields.Feature = 1;

            StorageUtility::Ata::sCommandCharacteristic& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();

            commandCharacteristics.DeviceReadyFlag = StorageUtility::Ata::eDeviceReadyFlag::DEVICE_READY_REQUIRED;
            commandCharacteristics.DataAccess = StorageUtility::Ata::eDataAccess::WRITE_TO_DEVICE;
            commandCharacteristics.FieldFormatting = StorageUtility::Ata::eFieldFormatting::COMMAND_48_BIT;
            commandCharacteristics.TransferMode = StorageUtility::Ata::eTransferMode::DMA_PROTOCOL;
            commandCharacteristics.MultipleMode = StorageUtility::Ata::eMultipleMode::NOT_MULTIPLE_COMMAND;
            commandCharacteristics.DataTransferLengthInBytes = sectorCount * StorageUtility::Ata::SECTOR_SIZE_IN_BYTES;

            cTrimBufferFormatter::FillBufferWithLbaRangeEntries(Data, LbaRangeEntries);

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }
    }
}