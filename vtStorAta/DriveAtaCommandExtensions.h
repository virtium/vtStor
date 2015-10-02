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
#ifndef __vtStorDriveAtaCommandExtensions_h__
#define __vtStorDriveAtaCommandExtensions_h__
#pragma once

#include <memory>

#include "ErrorCodes.h"
#include "DriveInterface.h"
#include "vtStorAtaPlatformDefines.h"

//! These are like "extension methods"

namespace vtStor
{
namespace Ata
{

const U8 ATA_COMMAND_IDENTIFY_DEVICE = 0xec;
const U8 ATA_COMMAND_READ_DMA = 0xc8;
const U8 ATA_COMMAND_WRITE_DMA = 0xca;
const U8 ATA_COMMAND_READ_BUFFER = 0xe4;
const U8 ATA_COMMAND_WRITE_BUFFER = 0xe8;
const U8 ATA_COMMAND_SMART = 0xb0;
const U32 ATA_SMART_IDENTIFIER = 0xC24F00;
const U8 ATA_COMMAND_DOWNLOADMICROCODE = 0x92;
const U8 ATA_COMMAND_DOWNLOADMICROCODE_DMA = 0x93;

VT_STOR_ATA_API eErrorCode IssueCommand_IdentifyDevice(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data);
VT_STOR_ATA_API eErrorCode IssueCommand_ReadDma(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U32 Lba, U16 Count);
VT_STOR_ATA_API eErrorCode IssueCommand_WriteDma(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U32 Lba, U16 Count);
VT_STOR_ATA_API eErrorCode IssueCommand_ReadBuffer(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data);
VT_STOR_ATA_API eErrorCode IssueCommand_WriteBuffer(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data);
VT_STOR_ATA_API eErrorCode IssueCommand_Smart(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U8 SubCommand);
VT_STOR_ATA_API eErrorCode IssueCommand_DownloadMicrocode(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U8 SubCommand, U16 BlockCount, U16 BufferOffset);
VT_STOR_ATA_API eErrorCode IssueCommand_DownloadMicrocodeDma(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U8 SubCommand, U16 BlockCount, U16 BufferOffset);

}
}

#endif