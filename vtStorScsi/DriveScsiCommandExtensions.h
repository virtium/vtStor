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
#ifndef __vtStorDriveScsiCommandExtensions_h__
#define __vtStorDriveScsiCommandExtensions_h__
#pragma once

#include <memory>

#include "ErrorCodes.h"
#include "DriveInterface.h"
#include "vtStorScsiPlatformDefines.h"

//! These are like "extension methods"

namespace vtStor
{
namespace Scsi
{
    const U8 SCSI_COMMAND_INQUIRY = 0x12;
    const U8 SCSI_COMMAND_READ16 = 0x88;
    const U8 SCSI_COMMAND_READ10 = 0x28;
    const U8 SCSI_COMMAND_WRITE10 = 0x2a;
    const U8 SCSI_COMMAND_WRITE16 = 0x8a;
    const U8 SCSI_COMMAND_ATA_PASS_THROUGH = 0x85;
    const U8 ATA_SUBCOMMAND_IDENTIFY_DEVICE = 0xec;
    const U8 ATA_SUBCOMMAND_READ_DMA = 0xc8;
    const U8 ATA_SUBCOMMAND_WRITE_DMA = 0xca;
    const U8 ATA_SUBCOMMAND_READ_BUFFER = 0xe4;
    const U8 ATA_SUBCOMMAND_WRITE_BUFFER = 0xe8;
    const U8 ATA_SUBCOMMAND_SMART = 0xb0;
    const U32 ATA_SUBSMART_IDENTIFIER = 0xC24F00;
    const U8 ATA_SUBCOMMAND_DOWNLOADMICROCODE = 0x92;
    const U8 ATA_SUBCOMMAND_DOWNLOADMICROCODE_DMA = 0x93;

    VT_STOR_SCSI_API eErrorCode IssueCommand_AtaIdentifyDevice(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data);
    VT_STOR_SCSI_API eErrorCode IssueCommand_AtaReadDma(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U32 Lba, U8 Count);
    VT_STOR_SCSI_API eErrorCode IssueCommand_AtaWriteDma(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U32 Lba, U8 Count);
    VT_STOR_SCSI_API eErrorCode IssueCommand_AtaReadBuffer(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data);
    VT_STOR_SCSI_API eErrorCode IssueCommand_AtaWriteBuffer(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data);
    VT_STOR_SCSI_API eErrorCode IssueCommand_AtaSmart(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U8 SubCommand);
    VT_STOR_SCSI_API eErrorCode IssueCommand_AtaDownloadMicrocode(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U8 SubCommand, U16 BlockCount, U16 BufferOffset);

    VT_STOR_SCSI_API eErrorCode IssueCommand_Inquiry(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data);
    VT_STOR_SCSI_API eErrorCode IssueCommand_Read10(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U32 Lba, U8 Count);
    VT_STOR_SCSI_API eErrorCode IssueCommand_Read16(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U32 Lba, U8 Count);
    VT_STOR_SCSI_API eErrorCode IssueCommand_Write10(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U32 Lba, U8 Count);
    VT_STOR_SCSI_API eErrorCode IssueCommand_Write16(std::shared_ptr<cDriveInterface> Drive, U32 CommandType, std::shared_ptr<cBufferInterface> Data, U32 Lba, U8 Count);
}
}

#endif