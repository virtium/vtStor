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

const size_t cCommandDescriptor1::COMMAND_FIELDS_OFFSET = cCommandDescriptor::DEVICE_HANDLE_OFFSET + sizeof(DeviceHandle);
const size_t cCommandDescriptor1::COMMAND_CHARACTERISTICS_OFFSET = cCommandDescriptor1::COMMAND_FIELDS_OFFSET + sizeof(StorageUtility::Ata::uCommandFields);

//! IMPORTANT NOTE: this must be updated to use the very last item
const size_t cCommandDescriptor1::SIZE_IN_BYTES = COMMAND_CHARACTERISTICS_OFFSET + sizeof(StorageUtility::Ata::sCommandCharacteristic);

cCommandDescriptor1 cCommandDescriptor1::Reader(std::shared_ptr<const IBuffer> Buffer)
{
    return(cCommandDescriptor1(Buffer));
}

cCommandDescriptor1 cCommandDescriptor1::Writer(std::shared_ptr<IBuffer> Buffer)
{
    return(cCommandDescriptor1(Buffer, 1));
}

cCommandDescriptor1 cCommandDescriptor1::Modifier(std::shared_ptr<IBuffer> Buffer)
{
    return(cCommandDescriptor1(Buffer));
}

cCommandDescriptor1::cCommandDescriptor1(std::shared_ptr<IBuffer> Buffer) :
cCommandDescriptor(Buffer)
{

}

cCommandDescriptor1::cCommandDescriptor1(std::shared_ptr<IBuffer> Buffer, U32 Format) :
cCommandDescriptor(Buffer, Format)
{
    
}

cCommandDescriptor1::cCommandDescriptor1( std::shared_ptr<const IBuffer> Buffer ) :
cCommandDescriptor(Buffer)
{
    
}

StorageUtility::Ata::uCommandFields& cCommandDescriptor1::GetCommandFields()
{
    U8* buffer = m_Buffer->ToDataBuffer();
    return( (StorageUtility::Ata::uCommandFields&)buffer[COMMAND_FIELDS_OFFSET] );
}

const StorageUtility::Ata::uCommandFields& cCommandDescriptor1::GetCommandFields() const
{
    const U8* buffer = m_Buffer->ToDataBuffer();
    return((StorageUtility::Ata::uCommandFields&)buffer[COMMAND_FIELDS_OFFSET]);
}

StorageUtility::Ata::sCommandCharacteristic& cCommandDescriptor1::GetCommandCharacteristics()
{
    U8* buffer = m_Buffer->ToDataBuffer();
    return( (StorageUtility::Ata::sCommandCharacteristic&)buffer[COMMAND_CHARACTERISTICS_OFFSET] );
}

const StorageUtility::Ata::sCommandCharacteristic& cCommandDescriptor1::GetCommandCharacteristics() const
{
    const U8* buffer = m_Buffer->ToDataBuffer();
    return((StorageUtility::Ata::sCommandCharacteristic&)buffer[COMMAND_CHARACTERISTICS_OFFSET]);
}

}
}
