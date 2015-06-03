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

#include "..\vtStorVsc\vtStorVsc.h"
#include "..\vtStorVsc\CommandHandlerVsc_1_0.h"
#include "..\vtStorVsc\CommandHandlerVsc_2_0.h"
#include "..\vtStorVsc\DriveVscCommandExtensions.h"

#include "DriveEnumeratorAta.h"
#include "vtStor.h"
#include "vtStorAta.h"
#include "Buffer.h"
#include "DriveAtaCommandExtensions.h"

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
    vtStor::cVsc::s_DefaultCommandHandlerCommandType_1_0 = 1;
    vtStor::cVsc::s_DefaultCommandHandlerCommandType_2_0 = 2;
    std::shared_ptr<vtStor::cDriveEnumeratorInterface> driveEnumeratorAta = std::make_unique<vtStor::cDriveEnumeratorAta>();
    driveManager->RegisterDriveEnumerator(driveEnumeratorAta);
    driveManager->EnumerateDrives( vtStor::cDriveManagerInterface::eScanForHardwareChanges::No );

    vtStor::Vector_Drives drives = driveManager->GetDrives();
    std::shared_ptr<vtStor::cBufferInterface> dataBuffer = std::make_shared<vtStor::cBuffer>(512);
    //vtStor::Ata::IssueCommand_IdentifyDevice(drives[1], vtStor::cAta::s_DefaultCommandHandlerCommandType, dataBuffer);
    std::shared_ptr<vtStor::cCommandHandlerVsc_1_0> commandHandlerVsc_1_0 = std::make_shared<vtStor::cCommandHandlerVsc_1_0>(drives[1]->m_Protocol);
    drives[1]->RegisterComandHandler(vtStor::cVsc::s_DefaultCommandHandlerCommandType_1_0, commandHandlerVsc_1_0);

    //vtStor::Vsc::IssueCommand_ReadFromMemory(drives[1], vtStor::cVsc::s_DefaultCommandHandlerCommandType_1_0, dataBuffer, 0, 1);
    //vtStor::Vsc::IssueCommand_GetDriveConfig(drives[1], vtStor::cVsc::s_DefaultCommandHandlerCommandType_1_0, dataBuffer);
    vtStor::Vsc::IssueCommand_GetEraseCountLogTableInfo(drives[1], vtStor::cVsc::s_DefaultCommandHandlerCommandType_1_0, dataBuffer);

    vtStor::U8* data = dataBuffer->ToDataBuffer();

    // dump buffer
    for (size_t i = 0; i < 512; i++)
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