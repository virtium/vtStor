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
    
    std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>( cCommandDescriptorVersion1::SIZE_IN_BYTES );
    cCommandDescriptorVersion1 commandDescriptorVersion1( commandDescriptor );

    cAta::uCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
    commandFields.InputFields.Command = ATA_COMMAND_IDENTIFY_DEVICE;
    commandFields.InputFields.Count = 1;

    cAta::sCommandCharacteristic& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();

    commandCharacteristics.DeviceReadyFlag = cAta::eDeviceReadyFlag::DEVICE_READY_REQUIRED;
    commandCharacteristics.DataAccess = cAta::eDataAccess::READ_FROM_DEVICE;
    commandCharacteristics.FieldFormatting = cAta::eFieldFormatting::COMMAND_28_BIT;
    commandCharacteristics.TransferMode = cAta::eTransferMode::PIO_PROTOCOL;
    commandCharacteristics.MultipleMode = cAta::eMultipleMode::NOT_MULTIPLE_COMMAND;
    commandCharacteristics.DataTransferLengthInBytes = cAta::SECTOR_SIZE_IN_BYTES;

    //TODO: populate required information for IssueCommand

    Drive->IssueCommand( CommandType, commandDescriptor, Data );

    return( eErrorCode::None );
}

}
}
