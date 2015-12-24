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
#ifndef __vtStorIScsiCommandExtensions_h__
#define __vtStorIScsiCommandExtensions_h__

#include <memory>

#include "ErrorCodes.h"
#include "PlatformDefines.h"
#include "IDrive.h"

namespace vtStor
{
    struct IScsiCommandExtensions
    {
        virtual eErrorCode IssueCommand_AtaIdentifyDevice(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data) = 0;
        virtual eErrorCode IssueCommand_AtaReadDma(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Lba, U16 Count) = 0;
        virtual eErrorCode IssueCommand_AtaWriteDma(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Lba, U16 Count) = 0;
        virtual eErrorCode IssueCommand_AtaReadBuffer(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data) = 0;
        virtual eErrorCode IssueCommand_AtaWriteBuffer(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data) = 0;
        virtual eErrorCode IssueCommand_AtaSmart(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U8 SubCommand) = 0;
        virtual eErrorCode IssueCommand_AtaDownloadMicrocode(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U8 SubCommand, U16 BlockCount, U16 BufferOffset) = 0;

        virtual eErrorCode IssueCommand_Inquiry(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data) = 0;
        virtual eErrorCode IssueCommand_Read10(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Lba, U16 Count) = 0;
        virtual eErrorCode IssueCommand_Read16(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Lba, U16 Count) = 0;
        virtual eErrorCode IssueCommand_Write10(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Lba, U16 Count) = 0;
        virtual eErrorCode IssueCommand_Write16(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Lba, U16 Count) = 0;
    };
}

extern "C"
{
    VT_STOR_SCSI_API void cScsiCommandExtensions_GetScsiCommandExtensions(std::unique_ptr<vtStor::IScsiCommandExtensions>& AtaCommandExtensions);
}

typedef void (WINAPIV * GetScsiCommandExtensionsDelegate) (std::unique_ptr<vtStor::IScsiCommandExtensions>&);

#endif // end __vtStorIScsiCommandExtensions_h__