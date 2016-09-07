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

#include <cstring>
#include <sys/ioctl.h>

#include "ProtocolScsiPassThrough.h"
#include "ScsiProtocolEssense1.h"
#include "StorageUtility.h"

namespace vtStor
{
    namespace Protocol
    {

        eErrorCode cScsiPassThrough::IssueCommand(const DeviceHandle& Handle, std::shared_ptr<const IBuffer> Essense, std::shared_ptr<IBuffer> DataBuffer)
        {
            eErrorCode errorCode = eErrorCode::None;

            cBufferFormatter bufferFormatter = cBufferFormatter::Reader(Essense);

            if (true == vtStor::CompareUUID(bufferFormatter.GetHeader().Format, cEssenseScsi1::FormatType))
            {
                cEssenseScsi1 essense = cEssenseScsi1::Reader(Essense);

                memset(&m_ScsiPassThrough, 0, sizeof(m_ScsiPassThrough));

                InitializePassThroughDirect(
                    essense.GetCommandCharacteristics(),
                    essense.GetCdbRegisters(),
                    DataBuffer,
                    60 //TODO: allow configurable timeout
                    );
                errorCode = IssuePassThroughDirectCommand(Handle.Handle);
            }
            else
            {
                errorCode = eErrorCode::FormatNotSupported;
            }

            return(errorCode);
        }

        eErrorCode cScsiPassThrough::IssuePassThroughDirectCommand(const U32& FileDescriptor)
        {
            if (INVALID_FILE_DESCRIPTOR == FileDescriptor)
            {
                return eErrorCode::Invalid;
            }

            U32 commandSuccessfulFlag = ioctl(FileDescriptor, SG_IO, &m_ScsiPassThrough);

            delete(m_ScsiPassThrough.cmdp);
            if (IOCTL_SG_IO_ERROR == commandSuccessfulFlag)
            {
                //! ERROR: IOCTL SG_IO was not successful
                return(eErrorCode::Io);
            }

            return(eErrorCode::None);
        }

        void cScsiPassThrough::InitializePassThroughDirect(const StorageUtility::Scsi::sCommandCharacteristics& CommandCharacteristics, const StorageUtility::Scsi::uCdb& CdbRegister, std::shared_ptr<IBuffer> DataBuffer, U32 TimeoutValueInSeconds)
        {
            //! TODO: Set up for Sense Data

            m_ScsiPassThrough.interface_id = static_cast<U32>(eSgScsi::SgInterfaceId);
            m_ScsiPassThrough.mx_sb_len = static_cast<U8>(eSgScsi::MaxSenseDataLength);
            m_ScsiPassThrough.dxfer_len = CommandCharacteristics.DataTransferLengthInBytes;
            m_ScsiPassThrough.timeout = TimeoutValueInSeconds;

            switch (CommandCharacteristics.FieldFormatting)
            {
            case StorageUtility::Scsi::eFieldFormatting::COMMAND_6:
            {
                m_ScsiPassThrough.cmd_len = 6;
            } break;

            case StorageUtility::Scsi::eFieldFormatting::COMMAND_10:
            {
                m_ScsiPassThrough.cmd_len = 10;
            } break;

            case StorageUtility::Scsi::eFieldFormatting::COMMAND_12:
            {
                m_ScsiPassThrough.cmd_len = 12;
            } break;

            case StorageUtility::Scsi::eFieldFormatting::COMMAND_16:
            case StorageUtility::Scsi::eFieldFormatting::ATAPASSTHROUGH_16:
            {
                m_ScsiPassThrough.cmd_len = 16;
            } break;

            default:
            {
                // Do nothing
            } break;
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

        void cScsiPassThrough::InitializeCdbRegister(const StorageUtility::Scsi::uCdb& CdbRegister)
        {
            memcpy(m_ScsiPassThrough.cmdp, CdbRegister.Cdb_16.Bytes, 16);
        }

    }
}
