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
#ifndef __vtStorAtaProtocolEssense_h__
#define __vtStorAtaProtocolEssense_h__

#include <memory>

#include "IBuffer.h"
#include "Ata.h"

#include "ProtocolEssense.h"

namespace vtStor
{
namespace Protocol
{
class VT_STOR_ATA_PROTOCOL_API cEssenseAta1 : public cProtocolEssense
{
public:
    static const size_t SIZE_IN_BYTES;

public:
    static cEssenseAta1 Reader(std::shared_ptr<const IBuffer> Buffer);
    static cEssenseAta1 Writer(std::shared_ptr<IBuffer> Buffer);

protected:
    cEssenseAta1(std::shared_ptr<IBuffer> Buffer);
    cEssenseAta1(std::shared_ptr<IBuffer> Buffer, U32 Format);
    cEssenseAta1(std::shared_ptr<const IBuffer> Buffer);

public:

    StorageUtility::Ata::sCommandCharacteristic&       GetCommandCharacteristics();
    const StorageUtility::Ata::sCommandCharacteristic& GetCommandCharacteristics() const;

    StorageUtility::Ata::uTaskFileRegister&         GetTaskFile();
    const StorageUtility::Ata::uTaskFileRegister&   GetTaskFile() const;

    StorageUtility::Ata::uTaskFileRegister&         GetTaskFileExt();
    const StorageUtility::Ata::uTaskFileRegister&   GetTaskFileExt() const;

protected:
    static const size_t COMMAND_CHARACTERISTICS_OFFSET;
    static const size_t TASK_FILE_OFFSET;
    static const size_t TASK_FILE_EXT_OFFSET;
};
}
}

#endif
