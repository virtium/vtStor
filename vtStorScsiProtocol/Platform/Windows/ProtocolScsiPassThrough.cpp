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

#include <assert.h>

#include "ScsiProtocolEssense1.h"

#include "ProtocolScsiPassThrough.h"

void cScsiPassThrough_GetProtocol(std::shared_ptr<vtStor::IProtocol>& Protocol)
{
    Protocol = std::shared_ptr<vtStor::IProtocol>(new vtStor::Protocol::cScsiPassThrough());
}

namespace vtStor
{
    namespace Protocol
    {
        eErrorCode cScsiPassThrough::IssueCommand(const DeviceHandle& Handle, std::shared_ptr<const IBuffer> Essense, std::shared_ptr<IBuffer> DataBuffer)
        {
            eErrorCode errorCode = eErrorCode::None;

            cBufferFormatter bufferFormatter = cBufferFormatter::Reader(Essense);

            switch (bufferFormatter.GetHeader().Format)
            {
            case 1:
            {
                cEssenseScsi1 essense = cEssenseScsi1::Reader(Essense);

                ZeroMemory(&m_ScsiPassThrough, sizeof(SCSI_PASS_THROUGH_DIRECT));

                InitializePassThroughDirect(
                    essense.GetCommandCharacteristics(),
                    essense.GetCdbRegisters(),
                    DataBuffer,
                    60 //TODO: allow configurable timeout
                    );


                U32 bytesReturned = 0;
                errorCode = IssuePassThroughDirectCommand(Handle, bytesReturned);
            } break;

            default:
                errorCode = eErrorCode::FormatNotSupported;
                break;
            }

            return(errorCode);
        }

        void cScsiPassThrough::InitializePassThroughDirect(const StorageUtility::Scsi::sCommandCharacteristics& CommandCharacteristics, const StorageUtility::Scsi::uCdb& CdbRegister, std::shared_ptr<IBuffer> DataBuffer, U32 TimeoutValueInSeconds)
        {
            m_ScsiPassThrough.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
            m_ScsiPassThrough.PathId = 0;
            m_ScsiPassThrough.TargetId = 1;
            m_ScsiPassThrough.Lun = 0;
            m_ScsiPassThrough.DataTransferLength = CommandCharacteristics.DataTransferLengthInBytes;
            m_ScsiPassThrough.TimeOutValue = TimeoutValueInSeconds;

            switch (CommandCharacteristics.FieldFormatting)
            {
            case StorageUtility::Scsi::eFieldFormatting::COMMAND_6:
            {
                m_ScsiPassThrough.CdbLength = 6;
            } break;

            case StorageUtility::Scsi::eFieldFormatting::COMMAND_10:
            {
                m_ScsiPassThrough.CdbLength = 10;
            } break;

            case StorageUtility::Scsi::eFieldFormatting::COMMAND_12:
            {
                m_ScsiPassThrough.CdbLength = 12;
            } break;

            case StorageUtility::Scsi::eFieldFormatting::COMMAND_16:
            {
                m_ScsiPassThrough.CdbLength = 16;
            } break;

            case StorageUtility::Scsi::eFieldFormatting::ATAPASSTHROUGH_16:
            {
                m_ScsiPassThrough.CdbLength = 16;
            } break;

            default:
            {
                // Do nothing
            } break;
            }

            switch (CommandCharacteristics.DataAccess)
            {
            case StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE:
            {
                m_ScsiPassThrough.DataIn = SCSI_IOCTL_DATA_IN;
            } break;

            case StorageUtility::Scsi::eDataAccess::WRITE_TO_DEVICE:
            {
                m_ScsiPassThrough.DataIn = SCSI_IOCTL_DATA_OUT;
            } break;

            default:
            {
                // Do nothing
            } break;
            }

            if (nullptr != DataBuffer)
            {
                m_ScsiPassThrough.DataBuffer = DataBuffer->ToDataBuffer();
            }

            InitializeCdbRegister(CdbRegister);
        }

        void cScsiPassThrough::InitializeCdbRegister(const StorageUtility::Scsi::uCdb& CdbRegister)
        {
            memcpy(m_ScsiPassThrough.Cdb, CdbRegister.Cdb_16.Bytes, 16);
        }

        eErrorCode cScsiPassThrough::IssuePassThroughDirectCommand(const DeviceHandle& Handle, U32& BytesReturned)
        {
            if (INVALID_HANDLE_VALUE == Handle.Handle)
            {
                return eErrorCode::Invalid;
            }

            eErrorCode error;
            error = eErrorCode::None;

            BOOL commandSuccessfulFlag;
            DWORD bytesReturned;
            commandSuccessfulFlag = DeviceIoControl
                (
                    Handle.Handle,
                    IOCTL_SCSI_PASS_THROUGH_DIRECT,
                    &m_ScsiPassThrough,
                    m_ScsiPassThrough.Length,
                    &m_ScsiPassThrough,
                    m_ScsiPassThrough.Length,
                    &bytesReturned,
                    NULL
                    );

            // If the operation was not successful:
            if (FALSE == commandSuccessfulFlag)
            {
                error = eErrorCode::Io;

                //TODO: report extended error
                //fprintf( stderr, "\nDeviceIoControl was not successful. Error Code: %d", GetLastError() );
            }

            BytesReturned = bytesReturned;

            return(error);
        }

    }
}
