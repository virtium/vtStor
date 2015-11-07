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

#include "AtaProtocolEssense1.h"

#include "ProtocolAtaPassThrough.h"

namespace vtStor
{
namespace Protocol
{

    const vtStor::U8 FEATURE_REGISTER_OFFSET = 0;
    const vtStor::U8 ERROR_REGISTER_OFFSET = 0;
    const vtStor::U8 COUNT_REGISTER_OFFSET = 1;
    const vtStor::U8 LBA_LOW_REGISTER_OFFSET = 2;
    const vtStor::U8 LBA_MID_REGISTER_OFFSET = 3;
    const vtStor::U8 LBA_HIGH_REGISTER_OFFSET = 4;
    const vtStor::U8 DEVICE_REGISTER_OFFSET = 5;
    const vtStor::U8 COMMAND_REGISTER_OFFSET = 6;
    const vtStor::U8 STATUS_REGISTER_OFFSET = 6;
    const vtStor::U8 RESERVED_REGISTER_OFFSET = 7;
    
   /* eErrorCode cAtaPassThrough::IssueCommand( const DeviceHandle& Handle, std::shared_ptr<const cBufferInterface> Essense, std::shared_ptr<cBufferInterface> DataBuffer )
    {
        eErrorCode errorCode = eErrorCode::None;

        cBufferFormatter bufferFormatter = cBufferFormatter::Reader(Essense);       
        
        switch (bufferFormatter.GetHeader().Format)
        {
            case 1:
            {
                cEssenseAta1 essense = cEssenseAta1::Reader(Essense);
                
                InitializePassThroughDirect(
                    essense.GetCommandCharacteristics(),
                    essense.GetTaskFileExt(),
                    essense.GetTaskFile(),
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
*/
   /* void cAtaPassThrough::InitializePassThroughDirect( const StorageUtility::Ata::sCommandCharacteristic& CommandCharacteristics, const StorageUtility::Ata::uTaskFileRegister& PreviousTaskFile, const StorageUtility::Ata::uTaskFileRegister& CurrentTaskFile, std::shared_ptr<cBufferInterface> DataBuffer, U32 TimeoutValueInSeconds )
    {
        m_AtaPassThrough.Length = sizeof( ATA_PASS_THROUGH_DIRECT );
        m_AtaPassThrough.DataTransferLength = CommandCharacteristics.DataTransferLengthInBytes;
        m_AtaPassThrough.TimeOutValue = TimeoutValueInSeconds;
        if (nullptr != DataBuffer)
        {
            m_AtaPassThrough.DataBuffer = DataBuffer->ToDataBuffer();
        }
        m_AtaPassThrough.ReservedAsUchar = 0;
        m_AtaPassThrough.ReservedAsUlong = 0;

        InitializeFlags( CommandCharacteristics );
        InitializeTaskFileInputRegisters( PreviousTaskFile, CurrentTaskFile );
    }

    void cAtaPassThrough::InitializeFlags( const StorageUtility::Ata::sCommandCharacteristic& AtaCommandCharacteristic )
    {
        // Clear all flags
        m_AtaPassThrough.AtaFlags = 0;

        if (StorageUtility::Ata::eDeviceReadyFlag::DEVICE_READY_REQUIRED == AtaCommandCharacteristic.DeviceReadyFlag)
        {
            m_AtaPassThrough.AtaFlags |= ATA_FLAGS_DRDY_REQUIRED;
        }

        switch (AtaCommandCharacteristic.DataAccess)
        {
        case StorageUtility::Ata::eDataAccess::READ_FROM_DEVICE:
        {
            m_AtaPassThrough.AtaFlags |= ATA_FLAGS_DATA_IN;
        } break;
        case StorageUtility::Ata::eDataAccess::WRITE_TO_DEVICE:
        {
            m_AtaPassThrough.AtaFlags |= ATA_FLAGS_DATA_OUT;
        } break;
        }

        if (StorageUtility::Ata::eFieldFormatting::COMMAND_48_BIT == AtaCommandCharacteristic.FieldFormatting)
        {
            m_AtaPassThrough.AtaFlags |= ATA_FLAGS_48BIT_COMMAND;
        }

        if (StorageUtility::Ata::eTransferMode::DMA_PROTOCOL == AtaCommandCharacteristic.TransferMode)
        {
            m_AtaPassThrough.AtaFlags |= ATA_FLAGS_USE_DMA;
        }

        if (StorageUtility::Ata::eMultipleMode::NOT_MULTIPLE_COMMAND == AtaCommandCharacteristic.MultipleMode)
        {
            m_AtaPassThrough.AtaFlags |= ATA_FLAGS_NO_MULTIPLE;
        }
    }

    void cAtaPassThrough::InitializeTaskFileInputRegisters( const StorageUtility::Ata::uTaskFileRegister& PreviousTaskFile, const StorageUtility::Ata::uTaskFileRegister& CurrentTaskFile )
    {
        m_AtaPassThrough.PreviousTaskFile[FEATURE_REGISTER_OFFSET] = PreviousTaskFile.InputRegister.Feature;
        m_AtaPassThrough.PreviousTaskFile[COUNT_REGISTER_OFFSET] = PreviousTaskFile.InputRegister.Count;
        m_AtaPassThrough.PreviousTaskFile[LBA_LOW_REGISTER_OFFSET] = PreviousTaskFile.InputRegister.LbaLow;
        m_AtaPassThrough.PreviousTaskFile[LBA_MID_REGISTER_OFFSET] = PreviousTaskFile.InputRegister.LbaMid;
        m_AtaPassThrough.PreviousTaskFile[LBA_HIGH_REGISTER_OFFSET] = PreviousTaskFile.InputRegister.LbaHigh;
        m_AtaPassThrough.PreviousTaskFile[DEVICE_REGISTER_OFFSET] = PreviousTaskFile.InputRegister.Device;
        m_AtaPassThrough.PreviousTaskFile[COMMAND_REGISTER_OFFSET] = PreviousTaskFile.InputRegister.Command;
        m_AtaPassThrough.PreviousTaskFile[RESERVED_REGISTER_OFFSET] = PreviousTaskFile.InputRegister.Reserved;

        m_AtaPassThrough.CurrentTaskFile[FEATURE_REGISTER_OFFSET] = CurrentTaskFile.InputRegister.Feature;
        m_AtaPassThrough.CurrentTaskFile[COUNT_REGISTER_OFFSET] = CurrentTaskFile.InputRegister.Count;
        m_AtaPassThrough.CurrentTaskFile[LBA_LOW_REGISTER_OFFSET] = CurrentTaskFile.InputRegister.LbaLow;
        m_AtaPassThrough.CurrentTaskFile[LBA_MID_REGISTER_OFFSET] = CurrentTaskFile.InputRegister.LbaMid;
        m_AtaPassThrough.CurrentTaskFile[LBA_HIGH_REGISTER_OFFSET] = CurrentTaskFile.InputRegister.LbaHigh;
        m_AtaPassThrough.CurrentTaskFile[DEVICE_REGISTER_OFFSET] = CurrentTaskFile.InputRegister.Device;
        m_AtaPassThrough.CurrentTaskFile[COMMAND_REGISTER_OFFSET] = CurrentTaskFile.InputRegister.Command;
        m_AtaPassThrough.CurrentTaskFile[RESERVED_REGISTER_OFFSET] = CurrentTaskFile.InputRegister.Reserved;
    }

    eErrorCode cAtaPassThrough::IssuePassThroughDirectCommand( const DeviceHandle& Handle, U32& BytesReturned )
    {
        
        assert( INVALID_HANDLE_VALUE != Handle );

        eErrorCode error;
        error = eErrorCode::None;
        
        BOOL commandSuccessfulFlag;
        DWORD bytesReturned;
        commandSuccessfulFlag = DeviceIoControl
            (
            Handle,
            IOCTL_ATA_PASS_THROUGH_DIRECT,
            &m_AtaPassThrough,
            m_AtaPassThrough.Length,
            &m_AtaPassThrough,
            m_AtaPassThrough.Length,
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
    }*/

}
}

VT_STOR_ATA_PROTOCOL_API void vtStorProtocolAtaPassThroughInit(std::shared_ptr<vtStor::Protocol::cProtocolInterface>& Protocol)
{
   // Protocol = std::make_shared<vtStor::Protocol::cAtaPassThrough>();
}
