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

#include "AtaProtocolEssense1.h"
#include "ProtocolAtaPassThrough.h"

namespace vtStor
{
namespace Protocol
{

eErrorCode cAtaPassThrough::IssueCommand(const DeviceHandle& Handle, std::shared_ptr<const IBuffer> Essense, std::shared_ptr<IBuffer> DataBuffer)
{
    eErrorCode errorCode = eErrorCode::None;

    cBufferFormatter bufferFormatter = cBufferFormatter::Reader(Essense);

    switch (bufferFormatter.GetHeader().Format)
    {
    case 1:
    {
        cEssenseAta1 essense = cEssenseAta1::Reader(Essense);

        //! TODO: magic code 60
        InitializePassThroughDirect(essense.GetCommandCharacteristics(), essense.GetTaskFileExt(), essense.GetTaskFile(), DataBuffer, 60);

        errorCode = IssuePassThroughDirectCommand(Handle.Handle);
    } break;

    default:
    {
        errorCode = eErrorCode::FormatNotSupported;
    } break;
    }

    return(errorCode);
}

eErrorCode cAtaPassThrough::IssuePassThroughDirectCommand(const U32& FileDescriptor)
{
    assert(INVALID_FILE_DESCRIPTOR != FileDescriptor);

    U32 commandSuccessfulFlag = ioctl(FileDescriptor, SG_IO, &m_ATAPassThrough);
    if (IOCTL_SG_IO_ERROR == commandSuccessfulFlag)
    {
        //! ERROR: IOCTL SG_IO was not successful
        return(eErrorCode::Io);
    }

    return(eErrorCode::None);
}

void cAtaPassThrough::InitializePassThroughDirect(const StorageUtility::Ata::sCommandCharacteristic& CommandCharacteristics,
        const StorageUtility::Ata::uTaskFileRegister& PreviousTaskFile,
        const StorageUtility::Ata::uTaskFileRegister& CurrentTaskFile,
        std::shared_ptr<IBuffer> DataBuffer,
        U32 TimeoutValueInSeconds)
{
    memset(&m_ATAPassThrough, 0, sizeof(m_ATAPassThrough));

    //! TODO: Set up for Sense Data

    m_ATAPassThrough.interface_id       = static_cast<U32>(eSgAtaPassThough16::SgInterfaceId);
    m_ATAPassThrough.mx_sb_len          = static_cast<U8>(eSgAtaPassThough16::MaxSenseDataLength);
    m_ATAPassThrough.cmd_len            = static_cast<U8>(eSgAtaPassThough16::SgCdbLengh);
    m_ATAPassThrough.dxfer_len          = CommandCharacteristics.DataTransferLengthInBytes;
    m_ATAPassThrough.timeout            = TimeoutValueInSeconds;

    if (nullptr != DataBuffer)
    {
        m_ATAPassThrough.dxferp = DataBuffer->ToDataBuffer();
    }

    InitializeFlags(CommandCharacteristics);
    InitializeCommandDescBlock16Flags(CommandCharacteristics);
    InitializeCommandDescBlock16Registers(PreviousTaskFile, CurrentTaskFile);

    m_ATAPassThrough.cmdp = (U8*)&m_CommandDescBlock16;
}

void cAtaPassThrough::InitializeCommandDescBlock16Flags(const StorageUtility::Ata::sCommandCharacteristic& AtaCommandCharacteristic)
{
    if (StorageUtility::Ata::eFieldFormatting::COMMAND_48_BIT == AtaCommandCharacteristic.FieldFormatting)
    {
        m_CommandDescBlock16.ExtendProtocol.Extend = SG_ATA_LBA48;
    }
    if (StorageUtility::Ata::eDataAccess::NONE != AtaCommandCharacteristic.DataAccess)
    {
        m_CommandDescBlock16.Param.TLength = static_cast<U8>(eTransferLenghValue::SpecInSectorCount);
        m_CommandDescBlock16.Param.BytBlock = static_cast<U8>(eByteBlockBit::TransferSectorMode);

        if (StorageUtility::Ata::eTransferMode::DMA_PROTOCOL == AtaCommandCharacteristic.TransferMode)
        {
            m_CommandDescBlock16.ExtendProtocol.Protocol = static_cast<U8>(eATAProtocolField::DMA);
        }
        else
        {
            if (StorageUtility::Ata::eDataAccess::WRITE_TO_DEVICE == AtaCommandCharacteristic.DataAccess)
            {
                m_CommandDescBlock16.ExtendProtocol.Protocol = static_cast<U8>(eATAProtocolField::PIO_Data_Out);
                m_CommandDescBlock16.Param.TDir = static_cast<U8>(eTransferDirection::TransferToDevice);
            }
            else
            {
                //! Read to device
                m_CommandDescBlock16.ExtendProtocol.Protocol = static_cast<U8>(eATAProtocolField::PIO_Data_In);
                m_CommandDescBlock16.Param.TDir = static_cast<U8>(eTransferDirection::TransferFromDevice);
            }
        }
        //! TODO: Support other protocols
    }
    else
    {
        m_CommandDescBlock16.ExtendProtocol.Protocol = static_cast<U8>(eATAProtocolField::NonData);
        m_CommandDescBlock16.Param.CheckCondition = static_cast<U8>(eCheckCondition::CommonTerminate);
    }
}

void cAtaPassThrough::InitializeFlags(const StorageUtility::Ata::sCommandCharacteristic& AtaCommandCharacteristic)
{
    switch (AtaCommandCharacteristic.DataAccess)
    {
    case StorageUtility::Ata::eDataAccess::READ_FROM_DEVICE:
    {
        m_ATAPassThrough.dxfer_direction = SG_DXFER_FROM_DEV;
    } break;

    case StorageUtility::Ata::eDataAccess::WRITE_TO_DEVICE:
    {
        m_ATAPassThrough.dxfer_direction = SG_DXFER_TO_DEV;

    } break;

    case StorageUtility::Ata::eDataAccess::NONE:
    {
        m_ATAPassThrough.dxfer_direction = SG_DXFER_NONE;
        m_ATAPassThrough.dxfer_len = 0;
    } break;

    default:
    {
        throw std::runtime_error("Attributes of the access was not supported\n");
    } break;
    }
}


void cAtaPassThrough::InitializeCommandDescBlock16Registers(const StorageUtility::Ata::uTaskFileRegister& PreviousTaskFile, const StorageUtility::Ata::uTaskFileRegister& CurrentTaskFile)
{
    m_CommandDescBlock16.Opcode                 = static_cast<U8>(eSgAtaPassThough16::SgAtaPassThough);
    m_CommandDescBlock16.LowDevice              = CurrentTaskFile.InputRegister.Device;

    m_CommandDescBlock16.LowCommand             = CurrentTaskFile.InputRegister.Command;
    m_CommandDescBlock16.LowFeature             = CurrentTaskFile.InputRegister.Feature;
    m_CommandDescBlock16.LowSectorCount         = CurrentTaskFile.InputRegister.Count;
    m_CommandDescBlock16.LowObLbaLow            = CurrentTaskFile.InputRegister.LbaLow;
    m_CommandDescBlock16.LowObLbaMid            = CurrentTaskFile.InputRegister.LbaMid;
    m_CommandDescBlock16.LowObLbaHigh           = CurrentTaskFile.InputRegister.LbaHigh;

    m_CommandDescBlock16.HighFeature            = PreviousTaskFile.InputRegister.Feature;
    m_CommandDescBlock16.HighSectorCount        = PreviousTaskFile.InputRegister.Count;
    m_CommandDescBlock16.HighObLbaLow           = PreviousTaskFile.InputRegister.LbaLow;
    m_CommandDescBlock16.HighObLbaMid           = PreviousTaskFile.InputRegister.LbaMid;
    m_CommandDescBlock16.HighObLbaHigh          = PreviousTaskFile.InputRegister.LbaHigh;
}

}
}