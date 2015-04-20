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

#include "BufferInterface.h"
#include "vtStorAta.h"

namespace vtStor
{
namespace Ata
{

const U32 COMMAND_DESCRIPTOR_VERSION_OFFSET             = 0;
const U32 COMMAND_DESCRIPTOR_VERSION_SIZE_IN_BYTES      = 2;
const U32 COMMAND_DESCRIPTOR_RESERVED0_OFFSET           = COMMAND_DESCRIPTOR_VERSION_OFFSET + COMMAND_DESCRIPTOR_VERSION_SIZE_IN_BYTES;
const U32 COMMAND_DESCRIPTOR_RESERVED0_SIZE_IN_BYTES    = 2;

class cCommandDescriptorVersion1
{
public:
    static void InitializeBuffer( std::shared_ptr<cBufferInterface> CommandDescriptor, const cAta::uCommandFields& CommandFields );

private:
    static const U32 COMMAND_FIELD_OFFSET;

};

}

}

#endif
