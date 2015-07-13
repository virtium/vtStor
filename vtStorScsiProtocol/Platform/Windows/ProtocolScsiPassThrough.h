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

#include <memory>

#include <Windows.h>
#include <Ntddscsi.h>

#include "ErrorCodes.h"
#include "BufferInterface.h"
#include "ProtocolInterface.h"

#include "StorageUtility/Scsi.h"

#include "vtStorScsiProtocolPlatformDefines.h"


namespace vtStor
{
namespace Protocol
{

class VT_STOR_SCSI_PROTOCOL_API cScsiPassThrough : public cProtocolInterface
{

public:
    virtual eErrorCode IssueCommand( std::shared_ptr<cBufferInterface> Essense, std::shared_ptr<cBufferInterface> DataBuffer ) override;

private:
    void InitializePassThroughDirect(
        const StorageUtility::Scsi::sCommandCharacteristics& CommandCharacteristics,
        const StorageUtility::Scsi::sTaskFileRegister& TaskFileRegister,
        std::shared_ptr<cBufferInterface> DataBuffer,
        U32 TimeoutValueInSeconds
        );

    //! Initialize the ATA flags in the ATA_PASS_THROUGH_DIRECT structure
    //!
    void InitializeFlags(const StorageUtility::Scsi::sCommandCharacteristics& ScsiCommandCharacteristics);

    //! Initialize the iCurrentTaskFile. and the PreviousTaskFile in the ATA_PASS_THROUGH_DIRECT structure
    //!
    void InitializeCdbRegister( const StorageUtility::Scsi::sTaskFileRegister& ScsiCommandField );

    eErrorCode IssuePassThroughDirectCommand( U32& BytesReturned );

private:
    HANDLE                  m_DeviceHandle;
    SCSI_PASS_THROUGH_DIRECT m_ScsiPassThrough;
};

}
}

extern "C"
{
    VT_STOR_SCSI_PROTOCOL_API void vtStorProtocolScsiPassThroughInit(std::shared_ptr<vtStor::Protocol::cProtocolInterface>& Protocol);
}