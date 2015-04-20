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
    //TODO: populate parameters and call IssueCommand
    cAta::uCommandFields commandFields;
    commandFields.InputFields.Command = ATA_COMMAND_IDENTIFY_DEVICE;
    commandFields.InputFields.Count = 1;

    //TODO: allocate size appropriately
    std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>( 128 );
    cCommandDescriptorVersion1::InitializeBuffer( commandDescriptor, commandFields );

    Drive->IssueCommand( CommandType, commandDescriptor, Data );

    return( eErrorCode::None );
}

}
}
