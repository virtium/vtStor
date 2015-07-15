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
#include "AtaPassThroughCommandDescriptor.h"

namespace vtStor
{
namespace Scsi
{

    const size_t cAtaPassThroughCommandDescriptor::COMMAND_FIELDS_OFFSET = cCommandDescriptor::DEVICE_HANDLE_OFFSET + sizeof(DeviceHandle);
    const size_t cAtaPassThroughCommandDescriptor::COMMAND_CHARACTERISTICS_OFFSET = cAtaPassThroughCommandDescriptor::COMMAND_FIELDS_OFFSET + sizeof(StorageUtility::Scsi::sCommandFields);

//! IMPORTANT NOTE: this must be updated to use the very last item
    const size_t cAtaPassThroughCommandDescriptor::SIZE_IN_BYTES = COMMAND_CHARACTERISTICS_OFFSET + sizeof(StorageUtility::Scsi::sCommandCharacteristics);

    cAtaPassThroughCommandDescriptor cAtaPassThroughCommandDescriptor::Reader(std::shared_ptr<const cBufferInterface> Buffer)
{
        return(cAtaPassThroughCommandDescriptor(Buffer));
}

    cAtaPassThroughCommandDescriptor cAtaPassThroughCommandDescriptor::Writer(std::shared_ptr<cBufferInterface> Buffer)
{
        return(cAtaPassThroughCommandDescriptor(Buffer, 1));
}

    cAtaPassThroughCommandDescriptor cAtaPassThroughCommandDescriptor::Modifier(std::shared_ptr<cBufferInterface> Buffer)
{
        return(cAtaPassThroughCommandDescriptor(Buffer));
}

    cAtaPassThroughCommandDescriptor::cAtaPassThroughCommandDescriptor(std::shared_ptr<cBufferInterface> Buffer) :
cCommandDescriptor(Buffer)
{

}

    cAtaPassThroughCommandDescriptor::cAtaPassThroughCommandDescriptor(std::shared_ptr<cBufferInterface> Buffer, U32 Format) :
cCommandDescriptor(Buffer, Format)
{
    
}

    cAtaPassThroughCommandDescriptor::cAtaPassThroughCommandDescriptor(std::shared_ptr<const cBufferInterface> Buffer) :
cCommandDescriptor(Buffer)
{
    
}

    StorageUtility::Scsi::sCommandFields& cAtaPassThroughCommandDescriptor::GetCommandFields()
{
    U8* buffer = m_Buffer->ToDataBuffer();
    return( (StorageUtility::Scsi::sCommandFields&)buffer[COMMAND_FIELDS_OFFSET] );
}

    const StorageUtility::Scsi::sCommandFields& cAtaPassThroughCommandDescriptor::GetCommandFields() const
{
    const U8* buffer = m_Buffer->ToDataBuffer();
    return((StorageUtility::Scsi::sCommandFields&)buffer[COMMAND_FIELDS_OFFSET]);
}

    StorageUtility::Scsi::sCommandCharacteristics& cAtaPassThroughCommandDescriptor::GetCommandCharacteristics()
{
    U8* buffer = m_Buffer->ToDataBuffer();
    return( (StorageUtility::Scsi::sCommandCharacteristics&)buffer[COMMAND_CHARACTERISTICS_OFFSET] );
}

    const StorageUtility::Scsi::sCommandCharacteristics& cAtaPassThroughCommandDescriptor::GetCommandCharacteristics() const
{
    const U8* buffer = m_Buffer->ToDataBuffer();
    return((StorageUtility::Scsi::sCommandCharacteristics&)buffer[COMMAND_CHARACTERISTICS_OFFSET]);
}

}
}
