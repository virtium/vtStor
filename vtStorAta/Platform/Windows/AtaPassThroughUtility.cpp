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

#include "BasicTypes.h"
#include "AtaPassThroughUtility.h"

namespace vtStor
{
namespace AtaPassThroughUtility
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

eErrorCode IssueCommand(
    HANDLE Handle,
    const cAta::sCommandCharacteristic CommandCharacteristics,
    const cAta::uTaskFileRegister& PreviousTaskFile,
    const cAta::uTaskFileRegister& CurrentTaskFile,
    std::shared_ptr<cBufferInterface> DataBuffer
    )
{
    ATA_PASS_THROUGH_DIRECT ataPassThrough;
    InitializePassThroughDirect( ataPassThrough, CommandCharacteristics, PreviousTaskFile, CurrentTaskFile, DataBuffer, 60 );  //TODO: allow configurable timeout

    eErrorCode errorCode = eErrorCode::None;
    U32 bytesReturned = 0;
    errorCode = IssuePassThroughDirectCommand( Handle, ataPassThrough, bytesReturned );

    return( errorCode );
}

void InitializePassThroughDirect( ATA_PASS_THROUGH_DIRECT& AtaPassThrough, const cAta::sCommandCharacteristic& CommandCharacteristics, const cAta::uTaskFileRegister& PreviousTaskFile, const cAta::uTaskFileRegister& CurrentTaskFile, std::shared_ptr<cBufferInterface> DataBuffer, U32 TimeoutValueInSeconds )
{
    AtaPassThrough.Length = sizeof( ATA_PASS_THROUGH_DIRECT );
    AtaPassThrough.DataTransferLength = CommandCharacteristics.DataTransferLengthInBytes;
    AtaPassThrough.TimeOutValue = TimeoutValueInSeconds;
    if ( nullptr != DataBuffer )
    {
        AtaPassThrough.DataBuffer = DataBuffer->ToDataBuffer();
    }
    AtaPassThrough.ReservedAsUchar = 0;
    AtaPassThrough.ReservedAsUlong = 0;

    InitializeFlags( AtaPassThrough, CommandCharacteristics );
    InitializeTaskFileInputRegisters( AtaPassThrough, PreviousTaskFile, CurrentTaskFile );
}

void InitializeFlags( ATA_PASS_THROUGH_DIRECT& AtaPassThrough, const cAta::sCommandCharacteristic& AtaCommandCharacteristic )
{
    // Clear all flags
    AtaPassThrough.AtaFlags = 0;

    if (cAta::eDeviceReadyFlag::DEVICE_READY_REQUIRED == AtaCommandCharacteristic.DeviceReadyFlag)
    {
        AtaPassThrough.AtaFlags |= ATA_FLAGS_DRDY_REQUIRED;
    }

    switch (AtaCommandCharacteristic.DataAccess)
    {
    case cAta::eDataAccess::READ_FROM_DEVICE:
    {
        AtaPassThrough.AtaFlags |= ATA_FLAGS_DATA_IN;
    } break;
    case cAta::eDataAccess::WRITE_TO_DEVICE:
    {
        AtaPassThrough.AtaFlags |= ATA_FLAGS_DATA_OUT;
    } break;
    }

    if (cAta::eFieldFormatting::COMMAND_48_BIT == AtaCommandCharacteristic.FieldFormatting)
    {
        AtaPassThrough.AtaFlags |= ATA_FLAGS_48BIT_COMMAND;
    }

    if (cAta::eTransferMode::DMA_PROTOCOL == AtaCommandCharacteristic.TransferMode)
    {
        AtaPassThrough.AtaFlags |= ATA_FLAGS_USE_DMA;
    }

    if (cAta::eMultipleMode::NOT_MULTIPLE_COMMAND == AtaCommandCharacteristic.MultipleMode)
    {
        AtaPassThrough.AtaFlags |= ATA_FLAGS_NO_MULTIPLE;
    }
}

void InitializeTaskFileInputRegisters( ATA_PASS_THROUGH_DIRECT& AtaPassThrough, const cAta::uTaskFileRegister& PreviousTaskFile, const cAta::uTaskFileRegister& CurrentTaskFile )
{
    AtaPassThrough.PreviousTaskFile[FEATURE_REGISTER_OFFSET] = PreviousTaskFile.InputRegister.Feature;
    AtaPassThrough.PreviousTaskFile[COUNT_REGISTER_OFFSET] = PreviousTaskFile.InputRegister.Count;
    AtaPassThrough.PreviousTaskFile[LBA_LOW_REGISTER_OFFSET] = PreviousTaskFile.InputRegister.LbaLow;
    AtaPassThrough.PreviousTaskFile[LBA_MID_REGISTER_OFFSET] = PreviousTaskFile.InputRegister.LbaMid;
    AtaPassThrough.PreviousTaskFile[LBA_HIGH_REGISTER_OFFSET] = PreviousTaskFile.InputRegister.LbaHigh;
    AtaPassThrough.PreviousTaskFile[DEVICE_REGISTER_OFFSET] = PreviousTaskFile.InputRegister.Device;
    AtaPassThrough.PreviousTaskFile[COMMAND_REGISTER_OFFSET] = PreviousTaskFile.InputRegister.Command;
    AtaPassThrough.PreviousTaskFile[RESERVED_REGISTER_OFFSET] = PreviousTaskFile.InputRegister.Reserved;

    AtaPassThrough.CurrentTaskFile[FEATURE_REGISTER_OFFSET] = CurrentTaskFile.InputRegister.Feature;
    AtaPassThrough.CurrentTaskFile[COUNT_REGISTER_OFFSET] = CurrentTaskFile.InputRegister.Count;
    AtaPassThrough.CurrentTaskFile[LBA_LOW_REGISTER_OFFSET] = CurrentTaskFile.InputRegister.LbaLow;
    AtaPassThrough.CurrentTaskFile[LBA_MID_REGISTER_OFFSET] = CurrentTaskFile.InputRegister.LbaMid;
    AtaPassThrough.CurrentTaskFile[LBA_HIGH_REGISTER_OFFSET] = CurrentTaskFile.InputRegister.LbaHigh;
    AtaPassThrough.CurrentTaskFile[DEVICE_REGISTER_OFFSET] = CurrentTaskFile.InputRegister.Device;
    AtaPassThrough.CurrentTaskFile[COMMAND_REGISTER_OFFSET] = CurrentTaskFile.InputRegister.Command;
    AtaPassThrough.CurrentTaskFile[RESERVED_REGISTER_OFFSET] = CurrentTaskFile.InputRegister.Reserved;
}

eErrorCode IssuePassThroughDirectCommand( HANDLE Handle, ATA_PASS_THROUGH_DIRECT& AtaPassThrough, U32& BytesReturned )
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
        &AtaPassThrough,
        AtaPassThrough.Length,
        &AtaPassThrough,
        AtaPassThrough.Length,
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

    return( error );
}

}
}