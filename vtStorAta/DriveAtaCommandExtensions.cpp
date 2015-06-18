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
#include "vtStorAta.h"
#include "Buffer.h"
#include "CommandDescriptorUtility.h"
#include "DriveAtaCommandExtensions.h"

namespace vtStor
{
namespace Ata
{

eErrorCode IssueCommand_IdentifyDevice( std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data )
{
    
    std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>( cCommandDescriptor1::SIZE_IN_BYTES );
    cCommandDescriptor1 commandDescriptorVersion1( commandDescriptor );

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
    
    Drive->IssueCommand( CommandType, commandDescriptor, Data );

    return( eErrorCode::None );
}


eErrorCode IssueCommand_ReadDma(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U32 Lba, U8 Count)
{
    std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptor1::SIZE_IN_BYTES);
    cCommandDescriptor1 commandDescriptorVersion1(commandDescriptor);

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

    Drive->IssueCommand(CommandType, commandDescriptor, Data);

    return(eErrorCode::None);
}

eErrorCode IssueCommand_WriteDma(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U32 Lba, U8 Count)
{
    std::shared_ptr<cBufferInterface> commmandDescriptor = std::make_shared<cBuffer>(cCommandDescriptor1::SIZE_IN_BYTES);
    cCommandDescriptor1 commandDescriptorVersion1(commmandDescriptor);

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

    Drive->IssueCommand(CommandType, commmandDescriptor, Data);

    return(eErrorCode::None);
}

eErrorCode IssueCommand_ReadBuffer(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data)
{
    std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptor1::SIZE_IN_BYTES);
    cCommandDescriptor1 commandDescriptorVersion1(commandDescriptor);

    StorageUtility::Ata::uCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
    commandFields.InputFields.Command = ATA_COMMAND_READ_BUFFER;

    StorageUtility::Ata::sCommandCharacteristic& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
    commandCharacteristics.DeviceReadyFlag = StorageUtility::Ata::eDeviceReadyFlag::DEVICE_READY_REQUIRED;
    commandCharacteristics.DataAccess = StorageUtility::Ata::eDataAccess::READ_FROM_DEVICE;
    commandCharacteristics.FieldFormatting = StorageUtility::Ata::eFieldFormatting::COMMAND_28_BIT;
    commandCharacteristics.TransferMode = StorageUtility::Ata::eTransferMode::PIO_PROTOCOL;
    commandCharacteristics.MultipleMode = StorageUtility::Ata::eMultipleMode::NOT_MULTIPLE_COMMAND;
    commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Ata::SECTOR_SIZE_IN_BYTES;

    Drive->IssueCommand(CommandType, commandDescriptor, Data);

    return(eErrorCode::None);
}

eErrorCode IssueCommand_WriteBuffer(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data)
{
    std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptor1::SIZE_IN_BYTES);
    cCommandDescriptor1 commandDescriptorVersion1(commandDescriptor);

    StorageUtility::Ata::uCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
    commandFields.InputFields.Command = ATA_COMMAND_WRITE_BUFFER;

    StorageUtility::Ata::sCommandCharacteristic& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
    commandCharacteristics.DeviceReadyFlag = StorageUtility::Ata::eDeviceReadyFlag::DEVICE_READY_REQUIRED;
    commandCharacteristics.DataAccess = StorageUtility::Ata::eDataAccess::WRITE_TO_DEVICE;
    commandCharacteristics.FieldFormatting = StorageUtility::Ata::eFieldFormatting::COMMAND_28_BIT;
    commandCharacteristics.TransferMode = StorageUtility::Ata::eTransferMode::PIO_PROTOCOL;
    commandCharacteristics.MultipleMode = StorageUtility::Ata::eMultipleMode::NOT_MULTIPLE_COMMAND;
    commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Ata::SECTOR_SIZE_IN_BYTES;

    Drive->IssueCommand(CommandType, commandDescriptor, Data);

    return(eErrorCode::None);
}

eErrorCode IssueCommand_Smart(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U8 SubCommand)
{
    std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptor1::SIZE_IN_BYTES);
    cCommandDescriptor1 commandDescriptorVersion1(commandDescriptor);

    StorageUtility::Ata::uCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
    commandFields.InputFields.Command = ATA_COMMAND_SMART;
    commandFields.InputFields.Feature = SubCommand;

    StorageUtility::Ata::sCommandCharacteristic& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
    commandCharacteristics.DeviceReadyFlag = StorageUtility::Ata::eDeviceReadyFlag::DEVICE_READY_REQUIRED;
    commandCharacteristics.DataAccess = StorageUtility::Ata::eDataAccess::READ_FROM_DEVICE;
    commandCharacteristics.FieldFormatting = StorageUtility::Ata::eFieldFormatting::COMMAND_28_BIT;
    commandCharacteristics.TransferMode = StorageUtility::Ata::eTransferMode::PIO_PROTOCOL;
    commandCharacteristics.MultipleMode = StorageUtility::Ata::eMultipleMode::NOT_MULTIPLE_COMMAND;
    commandCharacteristics.DataTransferLengthInBytes = StorageUtility::Ata::SECTOR_SIZE_IN_BYTES;

    Drive->IssueCommand(CommandType, commandDescriptor, Data);

    return(eErrorCode::None);
}

eErrorCode IssueCommand_DownloadMicrocode(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U8 SubCommand, U16 BlockCount, U16 BufferOffset)
{
    std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptor1::SIZE_IN_BYTES);
    cCommandDescriptor1 commandDescriptorVersion1(commandDescriptor);

    StorageUtility::Ata::uCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
    commandFields.InputFields.Command = ATA_COMMAND_DOWNLOADMICROCODE;
    commandFields.InputFields.Feature = SubCommand;
    commandFields.InputFields.Count = (BlockCount & 0xFF);
    commandFields.InputFields.Lba = (BlockCount >> 8) | (BufferOffset << 8);

    StorageUtility::Ata::sCommandCharacteristic& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
    commandCharacteristics.DeviceReadyFlag = StorageUtility::Ata::eDeviceReadyFlag::DEVICE_READY_REQUIRED;
    commandCharacteristics.DataAccess = StorageUtility::Ata::eDataAccess::WRITE_TO_DEVICE;
    commandCharacteristics.FieldFormatting = StorageUtility::Ata::eFieldFormatting::COMMAND_28_BIT;
    commandCharacteristics.TransferMode = StorageUtility::Ata::eTransferMode::PIO_PROTOCOL;
    commandCharacteristics.MultipleMode = StorageUtility::Ata::eMultipleMode::NOT_MULTIPLE_COMMAND;
    commandCharacteristics.DataTransferLengthInBytes = BlockCount * StorageUtility::Ata::SECTOR_SIZE_IN_BYTES;

    Drive->IssueCommand(CommandType, commandDescriptor, Data);

    return(eErrorCode::None);
}

eErrorCode IssueCommand_DownloadMicrocodeDma(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U8 SubCommand, U16 BlockCount, U16 BufferOffset)
{
    std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>(cCommandDescriptor1::SIZE_IN_BYTES);
    cCommandDescriptor1 commandDescriptorVersion1(commandDescriptor);

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

    Drive->IssueCommand(CommandType, commandDescriptor, Data);

    return(eErrorCode::None);
}

}
}
