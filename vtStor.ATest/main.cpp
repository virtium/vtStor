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

#include "ErrorCodes.h"
#include "BusType.h"

#include "vtStor.h"
#include "Buffer.h"

#include "CommandHandlerAta.h"
#include "DriveAtaCommandExtensions.h"
#include "DriveEnumeratorAta.h"
#include "ProtocolAtaPassThrough.h"
#include "vtStorAta.h"

#include "CommandHandlerScsi.h"
#include "DriveScsiCommandExtensions.h"
#include "DriveEnumeratorScsi.h"
#include "ProtocolScsiPassThrough.h"
#include "vtStorScsi.h"

#include "Drive.h"

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

    driveManager->RegisterDriveEnumerator(std::make_unique<vtStor::cDriveEnumeratorAta>());
    driveManager->RegisterDriveEnumerator(std::make_unique<vtStor::cDriveEnumeratorScsi>());

    driveManager->EnumerateDrives( vtStor::eScanForHardwareChanges::No );

    vtStor::Vector_Drives drives = driveManager->GetDrives();
    // Create data buffer
    std::shared_ptr<vtStor::cBufferInterface> dataBuffer = std::make_shared<vtStor::cBuffer>(512);

    std::shared_ptr<vtStor::Protocol::cProtocolInterface> protocol = nullptr;
    std::shared_ptr<vtStor::cCommandHandlerInterface> commandHandler = nullptr;

    std::shared_ptr<vtStor::cDrive> drive = std::dynamic_pointer_cast<vtStor::cDrive>(drives[1]);
    tchar* devicePath;
    drive->DevicePath(devicePath);

    if (vtStor::eBusType::Ata == drives[1]->GetBusType())                         //!!! Warning: be careful with value 1 in drives[1]
    {
        protocol = std::make_shared<vtStor::Protocol::cAtaPassThrough>();
        commandHandler = std::make_shared<vtStor::cCommandHandlerAta>(protocol);

        // Register command handler
        drives[1]->RegisterCommandHandler(0, commandHandler);

        // Call command
        vtStor::Ata::IssueCommand_IdentifyDevice(drives[1], 0, dataBuffer);

    } else if (vtStor::eBusType::Scsi == drives[1]->GetBusType())
    {
        protocol = std::make_shared<vtStor::Protocol::cScsiPassThrough>();
        commandHandler = std::make_shared<vtStor::cCommandHandlerScsi>(protocol);

        // Register command handler
        drives[1]->RegisterCommandHandler(0, commandHandler);

        // Call command
        vtStor::Scsi::IssueCommand_AtaIdentifyDevice(drives[1], 0, dataBuffer);
    }

    vtStor::U8* data = dataBuffer->ToDataBuffer();

    // dump buffer
    for (int i = 0; i < 512; i++)
    {
        if (i % 16 == 15)
        {

            printf("%02X\n", *data);
            data++;
        }
        else
        {
            printf("%02X ", *data);
            data++;
        }
    }

    getchar();
}