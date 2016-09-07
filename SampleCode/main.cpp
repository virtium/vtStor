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
#include <iostream>
#include <memory>
#include <string>

#include "ScsiCommandExtensions.h"
#include "AtaCommandExtensions.h"
#include "Buffer.h"
#include "BusType.h"
#include "DriveEnumeratorAta.h"
#include "ErrorCodes.h"
#include "IDriveManager.h"
#include "ProtocolScsiPassThrough.h"
#include "ProtocolAtaPassThrough.h"
#include "DriveEnumerator.h"
#include "DriveEnumeratorAta.h"
#include "DriveEnumeratorScsi.h"
#include "IDriveManager.h"

int WORD_SIZE_IN_BYTE = 2;
int MODEL_NUMBER_SIZE_IN_BYTE = 40;

// ID words
int MODEL_NUMBER_ID_WORD = 27;

std::string GetATAString(int idWord, int stringSizeInByte, std::shared_ptr<vtStor::IBuffer> dataBuffer)
{
        vtStor::String modelNumber;
        vtStor::U32 byteOffset = WORD_SIZE_IN_BYTE  * idWord;
        for (vtStor::U32 i = 0; i < stringSizeInByte; i += 2)
        {
            modelNumber += ((vtStor::U8)dataBuffer->GetByteAt(byteOffset + i + 1));
            modelNumber += ((vtStor::U8)dataBuffer->GetByteAt(byteOffset + i));
        }
        return modelNumber;
}

int main()
{
    std::unique_ptr<vtStor::IDriveManager> driveManager;
    std::shared_ptr<vtStor::IDriveEnumerator> driveEnumerator;

    // Enumerate drive
    cDriveManager_GetDriveManager(driveManager);
    driveEnumerator = std::make_shared<vtStor::cDriveEnumerator>();
    driveEnumerator = std::make_shared<vtStor::cDriveEnumeratorAta>(driveEnumerator);
    driveEnumerator = std::make_shared<vtStor::cDriveEnumeratorScsi>(driveEnumerator);
    driveManager->RegisterDriveEnumerator(driveEnumerator);
    driveManager->EnumerateDrives(vtStor::eScanForHardwareChanges::No);

    // Get all the drives enumerated
    vtStor::Vector_Drives drives = driveManager->GetDrives();

    // Create a data buffer so we can use when sending commands to a drive
    std::shared_ptr<vtStor::IBuffer> dataBuffer = std::make_shared<vtStor::cBuffer>(512);
    dataBuffer->Memset(0);
    
    // To send commands to a drive, we need to know several things
    // What type of drive and protocol of the drive helps us determine which command set to use.
    std::shared_ptr<vtStor::IProtocol> protocol = nullptr;
    std::shared_ptr<vtStor::ICommandHandler> commandHandler = nullptr;
        
    // We can defind some default values for command types to represent different command handler
    const vtStor::U32 sDefaultCommandHandlerAtaCommandType = 0;

    // Command extensions help us to easily setup parameters for particular commands
    std::unique_ptr<vtStor::IAtaCommandExtensions> ataCommandExtensions = std::make_unique<vtStor::Ata::cAtaCommandExtensions>();
	
    // Use ATA
    protocol = std::make_shared<vtStor::Protocol::cAtaPassThrough>();
	
    printf("List drives' model numbers attached to OS:\n");
    
    for ( auto drive : drives )
    {
        // Determine the bus type
        if (vtStor::eBusType::Ata == drive->GetBusType())
        {
            cCommandHandlerAta_GetCommandHandler(commandHandler, protocol);
	
            // Register command handler
            drive->RegisterCommandHandler(sDefaultCommandHandlerAtaCommandType, commandHandler);

            // Issue command
            vtStor::eErrorCode issueCode = vtStor::eErrorCode::None;
            issueCode = ataCommandExtensions->IssueCommand_IdentifyDevice(drive, sDefaultCommandHandlerAtaCommandType, dataBuffer);

            if(vtStor::eErrorCode::None != issueCode)
            {
                printf("Error when identify device %d %d\n", issueCode, drive->Handle().Handle);
            }

            // Now have fun with the data
            printf("--------------------------\n");
            std::string modelNumber = GetATAString(MODEL_NUMBER_ID_WORD, MODEL_NUMBER_SIZE_IN_BYTE, dataBuffer);
            std::cout<<modelNumber<<"\n";
            printf("--------------------------\n");
        }
    }

    getchar();

    return 0;
}
