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
#include <scsi/sg.h>

#include "IBuffer.h"
#include "ErrorCodes.h"
#include "IProtocol.h"
#include "Scsi.h"

namespace vtStor
{
namespace Protocol
{

//! Structure for sending Scsi command pass through SG drivers
enum class eSgScsi
{
    SgInterfaceId                   = 'S',  // 'S' for SCSI generic
    SgCommandDescBlockLengh         = 16,   // Command Descriptor Block length
    MaxSenseDataLength              = 32,   // Max of Sense Data Length
};

class VT_STOR_SCSI_PROTOCOL_API cScsiPassThrough : public IProtocol
{

public:
    virtual eErrorCode IssueCommand(const DeviceHandle& Handle, std::shared_ptr<const IBuffer> Essense, std::shared_ptr<IBuffer> DataBuffer) override;

private:
    void InitializePassThroughDirect(
            const StorageUtility::Scsi::sCommandCharacteristics& CommandCharacteristics,
            const StorageUtility::Scsi::sCdbRegisters& CdbRegister,
            std::shared_ptr<IBuffer> DataBuffer,
            U32 TimeoutValueInSeconds
            );

    void InitializeFlags(const vtStor::StorageUtility::Scsi::sCommandCharacteristics& CommandCharacteristic);

    void InitializeCdbRegister(const StorageUtility::Scsi::sCdbRegisters& CdbRegister);

    eErrorCode IssuePassThroughDirectCommand(const U32& FileDescriptor);

private:
    sg_io_hdr m_ScsiPassThrough;

};

}
}