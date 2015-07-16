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
#ifndef __vtStorScsiCommandDescriptor_h__
#define __vtStorScsiCommandDescriptor_h__

#include <memory>

#include "BufferInterface.h"
#include "CommandDescriptor.h"

#include "StorageUtility/Scsi.h"
#include "vtStorScsiPlatformDefines.h"

namespace vtStor
{
namespace Scsi
{

const size_t COMMAND_DESCRIPTOR_VERSION_OFFSET = 0;
const size_t COMMAND_DESCRIPTOR_VERSION_SIZE_IN_BYTES = 2;
const size_t COMMAND_DESCRIPTOR_RESERVED0_OFFSET = COMMAND_DESCRIPTOR_VERSION_OFFSET + COMMAND_DESCRIPTOR_VERSION_SIZE_IN_BYTES;
const size_t COMMAND_DESCRIPTOR_RESERVED0_SIZE_IN_BYTES = 2;

class VT_STOR_SCSI_API cScsiCommandDescriptor : public cCommandDescriptor
{
public:
    static const size_t SIZE_IN_BYTES;

public:
    static cScsiCommandDescriptor Reader(std::shared_ptr<const cBufferInterface> Buffer);
    static cScsiCommandDescriptor Writer(std::shared_ptr<cBufferInterface> Buffer);
    static cScsiCommandDescriptor Modifier(std::shared_ptr<cBufferInterface> Buffer);

protected:
    cScsiCommandDescriptor(std::shared_ptr<cBufferInterface> Buffer);
    cScsiCommandDescriptor(std::shared_ptr<cBufferInterface> Buffer, U32 Format);
    cScsiCommandDescriptor(std::shared_ptr<const cBufferInterface> Buffer);

public:
    StorageUtility::Scsi::sCdbFields&               GetCdbFields();
    const StorageUtility::Scsi::sCdbFields&         GetCdbFields() const;
    StorageUtility::Scsi::sCommandCharacteristics&       GetCommandCharacteristics();
    const StorageUtility::Scsi::sCommandCharacteristics& GetCommandCharacteristics() const;

private:
    static const size_t CDB_FIELDS_OFFSET;
    static const size_t COMMAND_CHARACTERISTICS_OFFSET;
};

}
}

#endif
