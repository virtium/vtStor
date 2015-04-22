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
#ifndef __AtaPassThroughUtility_h__
#define __AtaPassThroughUtility_h__

#include <memory>

#include <Windows.h>
#include <Ntddscsi.h>

#include "ErrorCodes.h"
#include "BufferInterface.h"
#include "vtStorAta.h"

namespace vtStor
{
namespace AtaPassThroughUtility
{

eErrorCode IssueCommand( 
    HANDLE Handle,
    const cAta::sCommandCharacteristic CommandCharacteristics, 
    const cAta::uTaskFileRegister& PreviousTaskFile,
    const cAta::uTaskFileRegister& CurrentTaskFile,
    std::shared_ptr<cBufferInterface> DataBuffer
    );

//--    Private functions
void InitializePassThroughDirect(
    ATA_PASS_THROUGH_DIRECT& AtaPassThrough,
    const cAta::sCommandCharacteristic& CommandCharacteristics,
    const cAta::uTaskFileRegister& PreviousTaskFile,
    const cAta::uTaskFileRegister& CurrentTaskFile,
    std::shared_ptr<cBufferInterface> DataBuffer,
    U32 TimeoutValueInSeconds
    );

//! Initialize the ATA flags in the ATA_PASS_THROUGH_DIRECT structure
//!
void InitializeFlags(ATA_PASS_THROUGH_DIRECT& AtaPassThrough, const cAta::sCommandCharacteristic& AtaCommandCharacteristic);

//! Initialize the iCurrentTaskFile. and the PreviousTaskFile in the ATA_PASS_THROUGH_DIRECT structure
//!
void InitializeTaskFileInputRegisters( ATA_PASS_THROUGH_DIRECT& AtaPassThrough, const cAta::uTaskFileRegister& PreviousTaskFile, const cAta::uTaskFileRegister& CurrentTaskFile );

eErrorCode IssuePassThroughDirectCommand( HANDLE Handle, ATA_PASS_THROUGH_DIRECT& AtaPassThrough, U32& BytesReturned );

}
}

#endif
