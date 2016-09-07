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

#ifndef __vtStorDriveAtaCommandExtensionManaged_h__
#define __vtStorDriveAtaCommandExtensionManaged_h__
#pragma once

#include "DataCommandStructureManaged.h"
#include "IAtaCommandExtensions.h"
#include "UniquePtrManaged.h"

using namespace System::Collections::Generic;

namespace vtStor
{
    namespace Ata
    {
        namespace Managed
        {
            public ref class cAtaCommandExtensions
            {
            public:
                cAtaCommandExtensions(vtStor::Managed::IRunTimeDll^ RunTimeDll);

            protected:
                ~cAtaCommandExtensions();

            protected:
                !cAtaCommandExtensions();

            public:
                vtStor::Managed::eErrorCode IssueCommand_IdentifyDevice(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data);
                vtStor::Managed::eErrorCode IssueCommand_ReadDma(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U32 Lba, U8 Count);
                vtStor::Managed::eErrorCode IssueCommand_WriteDma(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U32 Lba, U8 Count);
                vtStor::Managed::eErrorCode IssueCommand_ReadBuffer(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data);
                vtStor::Managed::eErrorCode IssueCommand_WriteBuffer(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data);
                vtStor::Managed::eErrorCode IssueCommand_Smart(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U8 SubCommand);
                vtStor::Managed::eErrorCode IssueCommand_DownloadMicrocode(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U8 SubCommand, U16 BlockCount, U16 BufferOffset);
                vtStor::Managed::eErrorCode IssueCommand_DownloadMicrocodeDma(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U8 SubCommand, U16 BlockCount, U16 BufferOffset);
                vtStor::Managed::eErrorCode IssueCommand_Trim(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, List<vtStor::Managed::sLbaRangeEntryManaged^>^ LbaRangeEntries);
                vtStor::Managed::eErrorCode IssueCommand_ReadDmaExt(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U64 Lba, U32 Count);
                vtStor::Managed::eErrorCode IssueCommand_WriteDmaExt(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U64 Lba, U32 Count);
                vtStor::Managed::eErrorCode IssueCommand_ReadSector(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U32 Lba, U32 Count);
                vtStor::Managed::eErrorCode IssueCommand_WriteSector(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U32 Lba, U32 Count);
                vtStor::Managed::eErrorCode IssueCommand_ReadSectorExt(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U64 Lba, U32 Count);
                vtStor::Managed::eErrorCode IssueCommand_WriteSectorExt(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U64 Lba, U32 Count);

            private:
                vtStor::Managed::cUniquePtr<vtStor::IAtaCommandExtensions> m_AtaCommandExtensions;
            };
        }
    }
}

#endif