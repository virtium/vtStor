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

VT_STOR_ATA_API eErrorCode IssueCommand_IdentifyDevice(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data);
VT_STOR_ATA_API eErrorCode IssueCommand_ReadDma(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U32 Lba, U8 Count);
VT_STOR_ATA_API eErrorCode IssueCommand_WriteDma(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U32 Lba, U8 Count);

}
}

#endif