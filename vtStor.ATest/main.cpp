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

#include "vtStor.h"
#include "Buffer.h"

#include "DriveEnumeratorAta.h"
#include "vtStorAta.h"
#include "CommandHandlerAta.h"
#include "DriveAtaCommandExtensions.h"
#include "ProtocolAtaPassThrough.h"

#include "DriveEnumeratorScsi.h"
#include "vtStorScsi.h"
#include "CommandHandlerScsi.h"
#include "DriveScsiCommandExtensions.h"
#include "ProtocolScsiPassThrough.h"

#include "ErrorCodes.h"

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
    std::shared_ptr<vtStor::cDriveEnumeratorInterface> driveEnumeratorScsi = std::make_unique<vtStor::cDriveEnumeratorScsi>();
    driveManager->RegisterDriveEnumerator(driveEnumeratorScsi);

    driveManager->EnumerateDrives( vtStor::eScanForHardwareChanges::No );
        
    std::shared_ptr<vtStor::cBufferInterface> dataBuffer = std::make_shared<vtStor::cBuffer>(512);
    std::shared_ptr<vtStor::Protocol::cProtocolInterface> ataProtocol = std::make_shared<vtStor::Protocol::cAtaPassThrough>();
    std::shared_ptr<vtStor::cCommandHandlerInterface> commandHandlerAta = std::make_shared<vtStor::cCommandHandlerAta>(ataProtocol);

    std::shared_ptr<vtStor::Protocol::cProtocolInterface> scsiProtocol = std::make_shared<vtStor::Protocol::cScsiPassThrough>();
    std::shared_ptr<vtStor::cCommandHandlerInterface> commandHandlerScsi = std::make_shared<vtStor::cCommandHandlerScsi>(scsiProtocol);

    vtStor::Vector_Drives drives = driveManager->GetDrives();
    drives[1]->RegisterCommandHandler(vtStor::cAta::s_DefaultCommandHandlerCommandType, commandHandlerAta);
    drives[1]->RegisterCommandHandler(1, commandHandlerScsi);

    // Call command
    ZeroMemory(dataBuffer->ToDataBuffer(), dataBuffer->GetSizeInBytes());
    //memset(dataBuffer->ToDataBuffer(), 'G', dataBuffer->GetSizeInBytes());
    //vtStor::Scsi::IssueCommand_AtaIdentifyDevice(drives[1], 1, dataBuffer);    
    //vtStor::Scsi::IssueCommand_AtaReadDma(drives[1], 1, dataBuffer, 0, 1);
    //vtStor::Scsi::IssueCommand_AtaWriteDma(drives[1], 1, dataBuffer, 0, 1);
    //vtStor::Scsi::IssueCommand_AtaReadBuffer(drives[1], 1, dataBuffer);
    //vtStor::Scsi::IssueCommand_AtaWriteBuffer(drives[1], 1, dataBuffer);
    vtStor::Scsi::IssueCommand_AtaSmart(drives[1], 1, dataBuffer, 0xD0);

    //vtStor::Ata::IssueCommand_IdentifyDevice(drives[1], vtStor::cAta::s_DefaultCommandHandlerCommandType, dataBuffer);
    //vtStor::Ata::IssueCommand_ReadBuffer(drives[1], vtStor::cAta::s_DefaultCommandHandlerCommandType, dataBuffer);
    //vtStor::Ata::IssueCommand_Smart(drives[1], vtStor::cAta::s_DefaultCommandHandlerCommandType, dataBuffer, 208);
    
    vtStor::U8* data = dataBuffer->ToDataBuffer();
    
    // dump buffer
    for (int i = 0; i < 512; i++)
    {
        if (i % 16 == 15)
        {

            printf("%02x\n", *data);
            data++;
        }
        else
        {
            printf("%02x ", *data);
            data++;
        }
    }

    getchar();
}