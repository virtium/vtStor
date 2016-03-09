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

int main()
{
    //The drive manager allows us to enumerate drives
    std::unique_ptr<vtStor::IDriveManager> driveManager;
    cDriveManager_GetDriveManager(driveManager);

    //Here we indicate the type of drives we want to enumerate by registering drive enumerators
    driveManager->RegisterDriveEnumerator(std::make_shared<vtStor::cDriveEnumeratorAta>());
    driveManager->RegisterDriveEnumerator(std::make_shared<vtStor::cDriveEnumeratorScsi>());
    
    //Enumerate drives
    driveManager->EnumerateDrives(vtStor::eScanForHardwareChanges::No);
    //Get all the drives enumerated
    vtStor::Vector_Drives drives = driveManager->GetDrives();

    //Now let's select a drive so we could do something fun
    //Be careful not to do anything destructive
    std::shared_ptr<vtStor::IDrive> selectedDrive = drives[0];

    //We can obtain some information about the drive
    std::shared_ptr<vtStor::sDriveProperties> driveProperties = selectedDrive->GetDriveProperties();
    vtStor::U32 physicalDiskNumber = driveProperties->PhysicalDiskNumber;
    tchar* devicePath = driveProperties->DevicePath;

    //Create a data buffer so we can use when sending commands to a drive
    std::shared_ptr<vtStor::IBuffer> dataBuffer = std::make_shared<vtStor::cBuffer>(512);

    //To send commands to a drive, we need to know several things
    //  What type of drive and protocol of the drive helps us determine which command set to use.
    std::shared_ptr<vtStor::IProtocol> protocol = nullptr;
    std::shared_ptr<vtStor::ICommandHandler> commandHandler = nullptr;
    
    //We can defind some default values for command types to represent different command handler
    const vtStor::U32 sDefaultCommandHandlerAtaCommandType = 0;
    const vtStor::U32 sDefaultCommandHandlerScsiCommandType = 1;

    //Command extensions help us to easily setup parameters for particular commands
    std::unique_ptr<vtStor::IAtaCommandExtensions> ataCommandExtensions(new vtStor::Ata::cAtaCommandExtensions);
    std::unique_ptr<vtStor::IScsiCommandExtensions> scsiCommandExtensions(new vtStor::Scsi::cScsiCommandExtensions);

    //Determine the bus type
    if (vtStor::eBusType::Ata == selectedDrive->GetBusType())
    {
        //Use ATA
        protocol = std::make_shared<vtStor::Protocol::cAtaPassThrough>();
        cCommandHandlerAta_GetCommandHandler(commandHandler, protocol);

        //Register command handler
        selectedDrive->RegisterCommandHandler(sDefaultCommandHandlerAtaCommandType, commandHandler);

        //Issue command
        ataCommandExtensions->IssueCommand_IdentifyDevice(selectedDrive, sDefaultCommandHandlerAtaCommandType, dataBuffer);

    }
    else if (vtStor::eBusType::Scsi == selectedDrive->GetBusType())
    {
        //Use SCSI
        protocol = std::make_shared<vtStor::Protocol::cScsiPassThrough>();
        cCommandHandlerScsi_GetCommandHandler(commandHandler, protocol);

        //Register command handler
        selectedDrive->RegisterCommandHandler(sDefaultCommandHandlerScsiCommandType, commandHandler);

        //Issue command
        scsiCommandExtensions->IssueCommand_AtaIdentifyDevice(selectedDrive, sDefaultCommandHandlerScsiCommandType, dataBuffer);
    }

    vtStor::U8* data = dataBuffer->ToDataBuffer();
    //Now have fun with the data

    return 0;
}
