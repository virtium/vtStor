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
                    essense.GetCdbRegister(),
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

    void cScsiPassThrough::InitializePassThroughDirect( const StorageUtility::Scsi::sCommandCharacteristics& CommandCharacteristics, const StorageUtility::Scsi::sCdbRegisters& CdbRegister, std::shared_ptr<IBuffer> DataBuffer, U32 TimeoutValueInSeconds )
    {
        m_ScsiPassThrough.Length = sizeof( SCSI_PASS_THROUGH_DIRECT );
        m_ScsiPassThrough.PathId = 0;
        m_ScsiPassThrough.TargetId = 1;
        m_ScsiPassThrough.Lun = 0;
        m_ScsiPassThrough.DataTransferLength = CommandCharacteristics.DataTransferLengthInBytes;
        m_ScsiPassThrough.TimeOutValue = TimeoutValueInSeconds;

        switch (CommandCharacteristics.FieldFormatting)
        {
        case StorageUtility::Scsi::eFieldFormatting::COMMAND_6:
            m_ScsiPassThrough.CdbLength = 6;
            break;
        case StorageUtility::Scsi::eFieldFormatting::COMMAND_10:
            m_ScsiPassThrough.CdbLength = 10;
            break;
        case StorageUtility::Scsi::eFieldFormatting::COMMAND_12:
            m_ScsiPassThrough.CdbLength = 12;
            break;
        case StorageUtility::Scsi::eFieldFormatting::COMMAND_16:
            m_ScsiPassThrough.CdbLength = 16;
            break;
        default:
            break;
        }
        
        switch (CommandCharacteristics.DataAccess)
        {
            case StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE:
                m_ScsiPassThrough.DataIn = SCSI_IOCTL_DATA_IN;
                break;
            case StorageUtility::Scsi::eDataAccess::WRITE_TO_DEVICE:
                m_ScsiPassThrough.DataIn = SCSI_IOCTL_DATA_OUT;
                break;
            default:
                break;
        }
        
        if (nullptr != DataBuffer)
        {
            m_ScsiPassThrough.DataBuffer = DataBuffer->ToDataBuffer();
        }

        InitializeCdbRegister( CdbRegister );
    }
    
    void cScsiPassThrough::InitializeCdbRegister( const StorageUtility::Scsi::sCdbRegisters& CdbRegister )
    {
        m_ScsiPassThrough.Cdb[0] = CdbRegister.Register0;
        m_ScsiPassThrough.Cdb[1] = CdbRegister.Register1;
        m_ScsiPassThrough.Cdb[2] = CdbRegister.Register2;
        m_ScsiPassThrough.Cdb[3] = CdbRegister.Register3;
        m_ScsiPassThrough.Cdb[4] = CdbRegister.Register4;
        m_ScsiPassThrough.Cdb[5] = CdbRegister.Register5;
        m_ScsiPassThrough.Cdb[6] = CdbRegister.Register6;
        m_ScsiPassThrough.Cdb[7] = CdbRegister.Register7;
        m_ScsiPassThrough.Cdb[8] = CdbRegister.Register8;
        m_ScsiPassThrough.Cdb[9] = CdbRegister.Register9;
        m_ScsiPassThrough.Cdb[10] = CdbRegister.Register10;
        m_ScsiPassThrough.Cdb[11] = CdbRegister.Register11;
        m_ScsiPassThrough.Cdb[12] = CdbRegister.Register12;
        m_ScsiPassThrough.Cdb[13] = CdbRegister.Register13;
        m_ScsiPassThrough.Cdb[14] = CdbRegister.Register14;
        m_ScsiPassThrough.Cdb[15] = CdbRegister.Register15;
    }

    eErrorCode cScsiPassThrough::IssuePassThroughDirectCommand( const DeviceHandle& Handle, U32& BytesReturned )
    {
        
        assert( INVALID_HANDLE_VALUE != Handle );

        eErrorCode error;
        error = eErrorCode::None;
        
        BOOL commandSuccessfulFlag;
        DWORD bytesReturned;
        commandSuccessfulFlag = DeviceIoControl
            (
            Handle,
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
