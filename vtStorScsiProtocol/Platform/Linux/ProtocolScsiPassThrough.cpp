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

#include <assert.h>
#include <cstring>
#include <sys/ioctl.h>

#include "ProtocolScsiPassThrough.h"
#include "ScsiProtocolEssense1.h"

namespace vtStor
{
namespace Protocol
{

eErrorCode cScsiPassThrough::IssueCommand(const DeviceHandle& Handle, std::shared_ptr<const cBufferInterface> Essense, std::shared_ptr<cBufferInterface> DataBuffer)
{
    eErrorCode errorCode = eErrorCode::None;

    cBufferFormatter bufferFormatter = cBufferFormatter::Reader(Essense);

    switch (bufferFormatter.GetHeader().Format)
    {
    case 1:
    {
        cEssenseScsi1 essense = cEssenseScsi1::Reader(Essense);

        memset(&m_ScsiPassThrough, 0, sizeof(m_ScsiPassThrough));

        InitializePassThroughDirect(
                    essense.GetCommandCharacteristics(),
                    essense.GetCdbRegister(),
                    DataBuffer,
                    60 //TODO: allow configurable timeout
                    );
        errorCode = IssuePassThroughDirectCommand(Handle.Handle);
    } break;

    default:
    {
        errorCode = eErrorCode::FormatNotSupported;
    } break;
    }

    return(errorCode);
}

eErrorCode cScsiPassThrough::IssuePassThroughDirectCommand(const U32& FileDescriptor)
{
    assert(INVALID_FILE_DESCRIPTOR != FileDescriptor);

    U32 commandSuccessfulFlag = ioctl(FileDescriptor, SG_IO, &m_ScsiPassThrough);

    delete(m_ScsiPassThrough.cmdp);
    if (IOCTL_SG_IO_ERROR == commandSuccessfulFlag)
    {
        //! ERROR: IOCTL SG_IO was not successful
        return(eErrorCode::Io);
    }

    return(eErrorCode::None);
}

void cScsiPassThrough::InitializePassThroughDirect(const StorageUtility::Scsi::sCommandCharacteristics& CommandCharacteristics, const StorageUtility::Scsi::sCdbRegisters& CdbRegister, std::shared_ptr<cBufferInterface> DataBuffer, U32 TimeoutValueInSeconds)
{
    //! TODO: Set up for Sense Data

    m_ScsiPassThrough.interface_id       = static_cast<U32>(eSgScsi::SgInterfaceId);
    m_ScsiPassThrough.mx_sb_len          = static_cast<U8>(eSgScsi::MaxSenseDataLength);
    m_ScsiPassThrough.dxfer_len          = CommandCharacteristics.DataTransferLengthInBytes;
    m_ScsiPassThrough.timeout            = TimeoutValueInSeconds;

    switch (CommandCharacteristics.FieldFormatting)
    {
    case StorageUtility::Scsi::eFieldFormatting::COMMAND_6:
        m_ScsiPassThrough.cmd_len = 6;
        break;
    case StorageUtility::Scsi::eFieldFormatting::COMMAND_10:
        m_ScsiPassThrough.cmd_len = 10;
        break;
    case StorageUtility::Scsi::eFieldFormatting::COMMAND_12:
        m_ScsiPassThrough.cmd_len = 12;
        break;
    case StorageUtility::Scsi::eFieldFormatting::COMMAND_16:
        m_ScsiPassThrough.cmd_len = 16;
        break;
    default:
        break;
    }

    if (nullptr != DataBuffer)
    {
        m_ScsiPassThrough.dxferp = DataBuffer->ToDataBuffer();
    }

    m_ScsiPassThrough.cmdp = new U8[static_cast<U32>(eSgScsi::SgCommandDescBlockLengh)];
    memset(m_ScsiPassThrough.cmdp, 0, static_cast<U32>(eSgScsi::SgCommandDescBlockLengh) * sizeof(*m_ScsiPassThrough.cmdp)); // Set value of elements of Cdb to 0

    InitializeFlags(CommandCharacteristics);
    InitializeCdbRegister(CdbRegister);
}

void cScsiPassThrough::InitializeFlags(const StorageUtility::Scsi::sCommandCharacteristics& CommandCharacteristic)
{
    switch (CommandCharacteristic.DataAccess)
    {
    case StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE:
    {
        m_ScsiPassThrough.dxfer_direction = SG_DXFER_FROM_DEV;
    } break;

    case StorageUtility::Scsi::eDataAccess::WRITE_TO_DEVICE:
    {
        m_ScsiPassThrough.dxfer_direction = SG_DXFER_TO_DEV;

    } break;

    case StorageUtility::Scsi::eDataAccess::NONE:
    {
        m_ScsiPassThrough.dxfer_direction = SG_DXFER_NONE;
        m_ScsiPassThrough.dxfer_len = 0;
    } break;

    default:
    {
        throw std::runtime_error("Attributes of the access was not supported\n");
    } break;
    }
}

void cScsiPassThrough::InitializeCdbRegister(const StorageUtility::Scsi::sCdbRegisters& CdbRegister)
{
    m_ScsiPassThrough.cmdp[0] = CdbRegister.Register0;
    m_ScsiPassThrough.cmdp[1] = CdbRegister.Register1;
    m_ScsiPassThrough.cmdp[2] = CdbRegister.Register2;
    m_ScsiPassThrough.cmdp[3] = CdbRegister.Register3;
    m_ScsiPassThrough.cmdp[4] = CdbRegister.Register4;
    m_ScsiPassThrough.cmdp[5] = CdbRegister.Register5;
    m_ScsiPassThrough.cmdp[6] = CdbRegister.Register6;
    m_ScsiPassThrough.cmdp[7] = CdbRegister.Register7;
    m_ScsiPassThrough.cmdp[8] = CdbRegister.Register8;
    m_ScsiPassThrough.cmdp[9] = CdbRegister.Register9;
    m_ScsiPassThrough.cmdp[10] = CdbRegister.Register10;
    m_ScsiPassThrough.cmdp[11] = CdbRegister.Register11;
    m_ScsiPassThrough.cmdp[12] = CdbRegister.Register12;
    m_ScsiPassThrough.cmdp[13] = CdbRegister.Register13;
    m_ScsiPassThrough.cmdp[14] = CdbRegister.Register14;
    m_ScsiPassThrough.cmdp[15] = CdbRegister.Register15;
}

}
}

VT_STOR_SCSI_PROTOCOL_API void vtStorProtocolScsiPassThroughInit(std::shared_ptr<vtStor::Protocol::cProtocolInterface>& Protocol)
{
    Protocol = std::make_shared<vtStor::Protocol::cScsiPassThrough>();
}