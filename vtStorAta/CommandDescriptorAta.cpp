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
#include "CommandDescriptorAta.h"

namespace vtStor
{
namespace Ata
{

const size_t cCommandDescriptorAta::COMMAND_FIELDS_OFFSET = cCommandDescriptor::DEVICE_HANDLE_OFFSET + sizeof(DeviceHandle);
const size_t cCommandDescriptorAta::COMMAND_CHARACTERISTICS_OFFSET = cCommandDescriptorAta::COMMAND_FIELDS_OFFSET + sizeof(StorageUtility::Ata::uCommandFields);

//! IMPORTANT NOTE: this must be updated to use the very last item
const size_t cCommandDescriptorAta::SIZE_IN_BYTES = COMMAND_CHARACTERISTICS_OFFSET + sizeof(StorageUtility::Ata::sCommandCharacteristic);

cCommandDescriptorAta cCommandDescriptorAta::Reader(std::shared_ptr<const IBuffer> Buffer)
{
    return(cCommandDescriptorAta(Buffer));
}

cCommandDescriptorAta cCommandDescriptorAta::Writer(std::shared_ptr<IBuffer> Buffer)
{
    return(cCommandDescriptorAta(Buffer, 1));
}

cCommandDescriptorAta cCommandDescriptorAta::Modifier(std::shared_ptr<IBuffer> Buffer)
{
    return(cCommandDescriptorAta(Buffer));
}

cCommandDescriptorAta::cCommandDescriptorAta(std::shared_ptr<IBuffer> Buffer) :
cCommandDescriptor(Buffer)
{

}

cCommandDescriptorAta::cCommandDescriptorAta(std::shared_ptr<IBuffer> Buffer, U32 Format) :
cCommandDescriptor(Buffer, Format)
{
    
}

cCommandDescriptorAta::cCommandDescriptorAta( std::shared_ptr<const IBuffer> Buffer ) :
cCommandDescriptor(Buffer)
{
    
}

StorageUtility::Ata::uCommandFields& cCommandDescriptorAta::GetCommandFields()
{
    U8* buffer = m_Buffer->ToDataBuffer();
    return( (StorageUtility::Ata::uCommandFields&)buffer[COMMAND_FIELDS_OFFSET] );
}

const StorageUtility::Ata::uCommandFields& cCommandDescriptorAta::GetCommandFields() const
{
    const U8* buffer = m_Buffer->ToDataBuffer();
    return((StorageUtility::Ata::uCommandFields&)buffer[COMMAND_FIELDS_OFFSET]);
}

StorageUtility::Ata::sCommandCharacteristic& cCommandDescriptorAta::GetCommandCharacteristics()
{
    U8* buffer = m_Buffer->ToDataBuffer();
    return( (StorageUtility::Ata::sCommandCharacteristic&)buffer[COMMAND_CHARACTERISTICS_OFFSET] );
}

const StorageUtility::Ata::sCommandCharacteristic& cCommandDescriptorAta::GetCommandCharacteristics() const
{
    const U8* buffer = m_Buffer->ToDataBuffer();
    return((StorageUtility::Ata::sCommandCharacteristic&)buffer[COMMAND_CHARACTERISTICS_OFFSET]);
}

}
}
