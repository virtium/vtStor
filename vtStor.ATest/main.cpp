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
#include <memory>

#include "AtaCommandExtensions.h"
#include "Buffer.h"
#include "BusType.h"
#include "CommandHandlerAta.h"
#include "CommandHandlerScsi.h"
#include "Drive.h"
#include "DriveEnumeratorAta.h"
#include "DriveEnumeratorScsi.h"
#include "DriveProperties.h"
#include "ErrorCodes.h"
#include "IDriveManager.h"
#include "ProtocolAtaPassThrough.h"
#include "ProtocolScsiPassThrough.h"
#include "ScsiCommandExtensions.h"

void main()
{
#if 0
    std::unique_ptr<vtStor::cDriveEnumeratorInterface> driveEnumeratorAta = std::make_unique<vtStor::cDriveEnumeratorAta>();
    vtStor::Vector_Drives drives;
    vtStor::U32 count;
    driveEnumeratorAta->EnumerateDrives( drives, count );
#endif

    const vtStor::U32 sDefaultCommandHandlerAtaCommandType = 0;
    const vtStor::U32 sDefaultCommandHandlerScsiCommandType = 1;

    std::unique_ptr<vtStor::IDriveManager> driveManager;
    std::unique_ptr<vtStor::IAtaCommandExtensions> ataCommandExtensions(new vtStor::Ata::cAtaCommandExtensions);
    std::unique_ptr<vtStor::IScsiCommandExtensions> scsiCommandExtensions(new vtStor::Scsi::cScsiCommandExtensions);
    cDriveManager_GetDriveManager(driveManager);

    driveManager->RegisterDriveEnumerator(std::make_shared<vtStor::cDriveEnumeratorAta>());
    driveManager->RegisterDriveEnumerator(std::make_shared<vtStor::cDriveEnumeratorScsi>());

    driveManager->EnumerateDrives( vtStor::eScanForHardwareChanges::No );

    vtStor::Vector_Drives drives = driveManager->GetDrives();
    std::shared_ptr<vtStor::IDrive> selectedDrive = drives[0];                         //!!! Warning: be careful with value 0 in drives[1]

    // Create data buffer
    std::shared_ptr<vtStor::IBuffer> dataBuffer = std::make_shared<vtStor::cBuffer>(512);

    std::shared_ptr<vtStor::IProtocol> protocol = nullptr;
    std::shared_ptr<vtStor::ICommandHandler> commandHandler = nullptr;

    std::shared_ptr<vtStor::sDriveProperties> driveProperties = selectedDrive->GetDriveProperties();
    vtStor::U32 physicalDiskNumber = driveProperties->PhysicalDiskNumber;
    tchar* devicePath = driveProperties->DevicePath;

    if (vtStor::eBusType::Ata == selectedDrive->GetBusType())
    {
        protocol = std::make_shared<vtStor::Protocol::cAtaPassThrough>();
        commandHandler = std::make_shared<vtStor::cCommandHandlerAta>(protocol);

        // Register command handler
        selectedDrive->RegisterCommandHandler(sDefaultCommandHandlerAtaCommandType, commandHandler);

        // Call command
        ataCommandExtensions->IssueCommand_IdentifyDevice(selectedDrive, sDefaultCommandHandlerAtaCommandType, dataBuffer);

    }
    else if (vtStor::eBusType::Scsi == selectedDrive->GetBusType())
    {
        protocol = std::make_shared<vtStor::Protocol::cScsiPassThrough>();
        commandHandler = std::make_shared<vtStor::cCommandHandlerScsi>(protocol);

        // Register command handler
        selectedDrive->RegisterCommandHandler(sDefaultCommandHandlerScsiCommandType, commandHandler);

        // Call command
        scsiCommandExtensions->IssueCommand_AtaIdentifyDevice(selectedDrive, sDefaultCommandHandlerScsiCommandType, dataBuffer);
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
