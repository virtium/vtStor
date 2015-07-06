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

#include "BufferInterface.h"
#include "StorageUtility/Ata.h"
#include "vtStorProtocolPlatformDefines.h"
#include "BufferFormatter.h"

namespace vtStor
{
namespace Protocol
{

class VT_STOR_PROTOCOL_API cEssenseAta1 : public cBufferFormatter
{
public:
    static const size_t SIZE_IN_BYTES;

public:
    cEssenseAta1( std::shared_ptr<cBufferInterface> Buffer );
    cEssenseAta1( std::shared_ptr<const cBufferInterface> Buffer );

public:
    DeviceHandle&                                      GetDeviceHandle();
    const DeviceHandle&                                GetDeviceHandle() const;

    StorageUtility::Ata::sCommandCharacteristic&       GetCommandCharacteristics();
    const StorageUtility::Ata::sCommandCharacteristic& GetCommandCharacteristics() const;

    StorageUtility::Ata::uTaskFileRegister&         GetTaskFile();
    const StorageUtility::Ata::uTaskFileRegister&   GetTaskFile() const;

    StorageUtility::Ata::uTaskFileRegister&         GetTaskFileExt();
    const StorageUtility::Ata::uTaskFileRegister&   GetTaskFileExt() const;

protected:
    static const size_t DEVICE_HANDLE_OFFSET;
    static const size_t COMMAND_CHARACTERISTICS_OFFSET;
    static const size_t TASK_FILE_OFFSET;
    static const size_t TASK_FILE_EXT_OFFSET;
};

}
}

#endif
