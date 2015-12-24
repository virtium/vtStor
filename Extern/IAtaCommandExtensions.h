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
#ifndef __vtStorIAtaCommandExtensions_h__
#define __vtStorIAtaCommandExtensions_h__

#include <memory>

#include "ErrorCodes.h"
#include "PlatformDefines.h"
#include "IDrive.h"

namespace vtStor
{
    struct IAtaCommandExtensions
    {
        virtual eErrorCode IssueCommand_IdentifyDevice(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data) = 0;
        virtual eErrorCode IssueCommand_ReadDma(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Lba, U16 Count) = 0;
        virtual eErrorCode IssueCommand_WriteDma(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Lba, U16 Count) = 0;
        virtual eErrorCode IssueCommand_ReadBuffer(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data) = 0;
        virtual eErrorCode IssueCommand_WriteBuffer(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data) = 0;
        virtual eErrorCode IssueCommand_Smart(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U8 SubCommand) = 0;
        virtual eErrorCode IssueCommand_DownloadMicrocode(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U8 SubCommand, U16 BlockCount, U16 BufferOffset) = 0;
        virtual eErrorCode IssueCommand_DownloadMicrocodeDma(std::shared_ptr<IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U8 SubCommand, U16 BlockCount, U16 BufferOffset) = 0;
    };
}

extern "C"
{
    VT_STOR_ATA_API void cAtaCommandExtensions_GetAtaCommandExtensions(std::unique_ptr<vtStor::IAtaCommandExtensions>& AtaCommandExtensions);
}

typedef void (WINAPIV * GetAtaCommandExtensionsDelegate) (std::unique_ptr<vtStor::IAtaCommandExtensions>&);

#endif // end __vtStorIAtaCommandExtensions_h__