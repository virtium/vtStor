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

namespace vtStor
{
namespace Protocol
{

    cScsiPassThrough::cScsiPassThrough()
    {
        ProtocolType = 1;
    }

    cScsiPassThrough::~cScsiPassThrough()
    {
    
    }

    U8 cScsiPassThrough::GetProtocolType()
    {
        return ( ProtocolType );
    }

    eErrorCode cScsiPassThrough::IssueCommand( std::shared_ptr<cBufferInterface> Essense, std::shared_ptr<cBufferInterface> DataBuffer )
    {
        eErrorCode errorCode = eErrorCode::None;

        cBufferFormatter bufferFormatter = cBufferFormatter::Reader(Essense);

        switch (bufferFormatter.GetHeader().Format)
        {
            case 1:
            {
                cEssenseScsi1 essense = cEssenseScsi1::Reader(Essense);
                m_DeviceHandle = essense.GetDeviceHandle();

                ZeroMemory(&m_ScsiPassThrough, sizeof(SCSI_PASS_THROUGH_DIRECT));

                InitializePassThroughDirect(
                    essense.GetCommandCharacteristics(),
                    essense.GetTaskFileRegister(),
                    DataBuffer,
                    60 //TODO: allow configurable timeout
                    );

                  
                U32 bytesReturned = 0;
                errorCode = IssuePassThroughDirectCommand(bytesReturned);
            } break;

            default:
                errorCode = eErrorCode::FormatNotSupported;
                break; 
        }        

        return(errorCode);
    }

    void cScsiPassThrough::InitializePassThroughDirect( const StorageUtility::Scsi::sCommandCharacteristics& CommandCharacteristics, const StorageUtility::Scsi::sTaskFileRegister& TaskFileRegister, std::shared_ptr<cBufferInterface> DataBuffer, U32 TimeoutValueInSeconds )
    {
        m_ScsiPassThrough.Length = sizeof( SCSI_PASS_THROUGH_DIRECT );
        m_ScsiPassThrough.PathId = 0;
        m_ScsiPassThrough.TargetId = 1;
        m_ScsiPassThrough.Lun = 0;
        m_ScsiPassThrough.DataTransferLength = CommandCharacteristics.DataTransferLengthInBytes;
        m_ScsiPassThrough.TimeOutValue = TimeoutValueInSeconds;
        switch (CommandCharacteristics.FieldFormatting)
        {
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

        switch (CommandCharacteristics.TransferMode)
        {
            case StorageUtility::Scsi::eTransferMode::PIO_PROTOCOL:
            {
                if (CommandCharacteristics.DataAccess == StorageUtility::Scsi::eDataAccess::WRITE_TO_DEVICE)
                {
                    m_ScsiPassThrough.Cdb[1] = 0x0B;                                                    // MULTIPLE_COUNT = 000, PROTOCOL = 0101b (PIO OUT), Extended = 1
                }
                else if (CommandCharacteristics.DataAccess == StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE)
                {
                    m_ScsiPassThrough.Cdb[1] = 0x09;                                                    // MULTIPLE_COUNT = 000, PROTOCOL = 0100b (PIO IN), Extended = 1
                }
            } break;

            case StorageUtility::Scsi::eTransferMode::DMA_PROTOCOL:
            {
                m_ScsiPassThrough.Cdb[1] = 0x0D;                                                        // MULTIPLE_COUNT = 000, PROTOCOL = 0110b (DMA), Extended = 1
            } break;
            default:
            {
                printf("No supported!\n");
            } break;
        }

        switch (CommandCharacteristics.DataAccess)
        {
            case StorageUtility::Scsi::eDataAccess::READ_FROM_DEVICE:
            {
                m_ScsiPassThrough.Cdb[2] = 0x0B;                                                      // OFF_LINE = 0, CK_COND = 0, T_TYPE = 0, T_DIR = 1, BYT_BLOCK = 0, T_LENGTH = 11b
            } break;
            case StorageUtility::Scsi::eDataAccess::WRITE_TO_DEVICE:
            {
                m_ScsiPassThrough.Cdb[2] = 0x03;                                                      // OFF_LINE = 0, CK_COND = 0, T_TYPE = 0, T_DIR = 0, BYT_BLOCK = 0, T_LENGTH = 11b
            } break;
        }

        if (nullptr != DataBuffer)
        {
            m_ScsiPassThrough.DataBuffer = DataBuffer->ToDataBuffer();
        }

        InitializeCdbRegister( TaskFileRegister );
    }
    
    void cScsiPassThrough::InitializeCdbRegister( const StorageUtility::Scsi::sTaskFileRegister& TaskFileRegister )
    {
        m_ScsiPassThrough.Cdb[0] = TaskFileRegister.Command;   
        m_ScsiPassThrough.Cdb[3] = (TaskFileRegister.Feature >> 8) & 0xFF;
        m_ScsiPassThrough.Cdb[4] = TaskFileRegister.Feature & 0xFF;
        m_ScsiPassThrough.Cdb[5] = (TaskFileRegister.Count >> 8) & 0xFF;
        m_ScsiPassThrough.Cdb[6] = TaskFileRegister.Count & 0xFF;
        m_ScsiPassThrough.Cdb[7] = (TaskFileRegister.LbaMid >> 8) & 0xFF;
        m_ScsiPassThrough.Cdb[8] = TaskFileRegister.LbaLow & 0xFF;                                   // low lba
        m_ScsiPassThrough.Cdb[9] = TaskFileRegister.LbaHigh & 0xFF;
        m_ScsiPassThrough.Cdb[10] = (TaskFileRegister.LbaLow >> 8) & 0xFF;                                   // middle lba
        m_ScsiPassThrough.Cdb[11] = (TaskFileRegister.LbaHigh >> 8) & 0xFF;
        m_ScsiPassThrough.Cdb[12] = TaskFileRegister.LbaMid & 0xFF;                                  // high lba
        m_ScsiPassThrough.Cdb[13] = TaskFileRegister.Device;                                                        // CommandFields.InputFields.Device;
        m_ScsiPassThrough.Cdb[14] = TaskFileRegister.SubCommand;
        m_ScsiPassThrough.Cdb[15] = 0;
    }

    eErrorCode cScsiPassThrough::IssuePassThroughDirectCommand( U32& BytesReturned )
    {
        
        assert( INVALID_HANDLE_VALUE != m_DeviceHandle );

        eErrorCode error;
        error = eErrorCode::None;
        
        BOOL commandSuccessfulFlag;
        DWORD bytesReturned;
        commandSuccessfulFlag = DeviceIoControl
            (
            m_DeviceHandle,
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

VT_STOR_SCSI_PROTOCOL_API void vtStorProtocolScsiPassThroughInit(std::shared_ptr<vtStor::Protocol::cProtocolInterface>& Protocol)
{
    Protocol = std::make_shared<vtStor::Protocol::cScsiPassThrough>();
}