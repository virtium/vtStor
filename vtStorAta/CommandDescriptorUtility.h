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
#ifndef __vtStorAtaCommandDescriptorUtility_h__
#define __vtStorAtaCommandDescriptorUtility_h__

#include <memory>

#include "IBuffer.h"
#include "CommandDescriptor.h"

#include "Ata.h"

namespace vtStor
{
namespace Ata
{

const size_t COMMAND_DESCRIPTOR_VERSION_OFFSET = 0;
const size_t COMMAND_DESCRIPTOR_VERSION_SIZE_IN_BYTES = 2;
const size_t COMMAND_DESCRIPTOR_RESERVED0_OFFSET = COMMAND_DESCRIPTOR_VERSION_OFFSET + COMMAND_DESCRIPTOR_VERSION_SIZE_IN_BYTES;
const size_t COMMAND_DESCRIPTOR_RESERVED0_SIZE_IN_BYTES = 2;

class VT_STOR_ATA_API cCommandDescriptor1 : public cCommandDescriptor
{
public:
    static const size_t SIZE_IN_BYTES;

public:
    static cCommandDescriptor1 Reader(std::shared_ptr<const IBuffer> Buffer);
    static cCommandDescriptor1 Writer(std::shared_ptr<IBuffer> Buffer);
    static cCommandDescriptor1 Modifier(std::shared_ptr<IBuffer> Buffer);

protected:
    cCommandDescriptor1(std::shared_ptr<IBuffer> Buffer);
    cCommandDescriptor1(std::shared_ptr<IBuffer> Buffer, U32 Format);
    cCommandDescriptor1(std::shared_ptr<const IBuffer> Buffer);

public:
    StorageUtility::Ata::uCommandFields&               GetCommandFields();
    const StorageUtility::Ata::uCommandFields&         GetCommandFields() const;
    StorageUtility::Ata::sCommandCharacteristic&       GetCommandCharacteristics();
    const StorageUtility::Ata::sCommandCharacteristic& GetCommandCharacteristics() const;

private:
    static const size_t COMMAND_FIELDS_OFFSET;
    static const size_t COMMAND_CHARACTERISTICS_OFFSET;
};

}
}

#endif
