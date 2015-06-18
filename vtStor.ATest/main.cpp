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
#include <memory>

#include "DriveEnumeratorAta.h"
#include "vtStor.h"
#include "vtStorAta.h"
#include "CommandHandlerAta.h"
#include "Buffer.h"
#include "DriveAtaCommandExtensions.h"

#include "ProtocolAtaPassThrough.h"

void main()
{
#if 0
    std::unique_ptr<vtStor::cDriveEnumeratorInterface> driveEnumeratorAta = std::make_unique<vtStor::cDriveEnumeratorAta>();
    vtStor::Vector_Drives drives;
    vtStor::U32 count;
    driveEnumeratorAta->EnumerateDrives( drives, count );
#endif

    std::unique_ptr<vtStor::cDriveManagerInterface> driveManager;
    vtStorInit( driveManager );

    vtStor::cAta::s_DefaultCommandHandlerCommandType = 0;
    std::shared_ptr<vtStor::cDriveEnumeratorInterface> driveEnumeratorAta = std::make_unique<vtStor::cDriveEnumeratorAta>();
    driveManager->RegisterDriveEnumerator(driveEnumeratorAta);
    driveManager->EnumerateDrives( vtStor::cDriveManagerInterface::eScanForHardwareChanges::No );

    vtStor::Vector_Drives drives = driveManager->GetDrives();
    // Create data buffer
    std::shared_ptr<vtStor::cBufferInterface> dataBuffer = std::make_shared<vtStor::cBuffer>(512);
    // Create protocol
    std::shared_ptr<vtStor::Protocol::cProtocolInterface> protocol = std::make_shared<vtStor::Protocol::cAtaPassThrough>();
    // Create command handler
    std::shared_ptr<vtStor::cCommandHandlerInterface> commandHandlerAta = std::make_shared<vtStor::cCommandHandlerAta>(protocol);
    // Register command handler
    drives[1]->RegisterComandHandler(vtStor::cAta::s_DefaultCommandHandlerCommandType, commandHandlerAta);
    // Call command
    vtStor::Ata::IssueCommand_IdentifyDevice(drives[1], vtStor::cAta::s_DefaultCommandHandlerCommandType, dataBuffer);

    vtStor::U8* data = dataBuffer->ToDataBuffer();

    // dump buffer

    getchar();
}