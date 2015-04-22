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
#include "CommandDescriptorUtility.h"

namespace vtStor
{
namespace Ata
{

const U32 cCommandDescriptorVersion1::COMMAND_FIELD_OFFSET = COMMAND_DESCRIPTOR_RESERVED0_OFFSET + COMMAND_DESCRIPTOR_RESERVED0_SIZE_IN_BYTES;


cCommandDescriptorVersion1::cCommandDescriptorVersion1( std::shared_ptr<cBufferInterface> CommandDescriptor ) :
m_CommandDescriptor( CommandDescriptor )
{
    U8* commandDescriptorBuffer = CommandDescriptor->ToDataBuffer();

    const U32 VERSION = 1;
    commandDescriptorBuffer[COMMAND_DESCRIPTOR_VERSION_OFFSET] = (VERSION >> 8) & 0xff;
    commandDescriptorBuffer[COMMAND_DESCRIPTOR_VERSION_OFFSET + 1] = (VERSION)& 0xff;

    commandDescriptorBuffer[COMMAND_DESCRIPTOR_RESERVED0_OFFSET] = 0;
    commandDescriptorBuffer[COMMAND_DESCRIPTOR_RESERVED0_OFFSET + 1] = 0;
}

U16 cCommandDescriptorVersion1::GetVersion() const
{
    U8* commandDescriptorBuffer = m_CommandDescriptor->ToDataBuffer();
    U16 version = (commandDescriptorBuffer[COMMAND_DESCRIPTOR_VERSION_OFFSET] << 8) | (commandDescriptorBuffer[COMMAND_DESCRIPTOR_VERSION_OFFSET + 1]);
    return( version );
}

cAta::uCommandFields& cCommandDescriptorVersion1::GetCommandFields()
{
    U8* buffer = m_CommandDescriptor->ToDataBuffer();
    return( (cAta::uCommandFields&)buffer[COMMAND_FIELD_OFFSET] );
}

}
}
