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
#include "CommandDescriptorScsi.h"

namespace vtStor
{
namespace Scsi
{

    const size_t cCommandDescriptorScsi::CDB_FIELDS_OFFSET = cCommandDescriptor::DATA_OFFSET;
    const size_t cCommandDescriptorScsi::COMMAND_CHARACTERISTICS_OFFSET = cCommandDescriptorScsi::CDB_FIELDS_OFFSET + sizeof(StorageUtility::Scsi::sCdbFields);

//! IMPORTANT NOTE: this must be updated to use the very last item
    const size_t cCommandDescriptorScsi::SIZE_IN_BYTES = COMMAND_CHARACTERISTICS_OFFSET + sizeof(StorageUtility::Scsi::sCommandCharacteristics);

    cCommandDescriptorScsi cCommandDescriptorScsi::Reader(std::shared_ptr<const cBufferInterface> Buffer)
{
        return(cCommandDescriptorScsi(Buffer));
}

    cCommandDescriptorScsi cCommandDescriptorScsi::Writer(std::shared_ptr<cBufferInterface> Buffer)
{
        return(cCommandDescriptorScsi(Buffer, 1));
}

    cCommandDescriptorScsi cCommandDescriptorScsi::Modifier(std::shared_ptr<cBufferInterface> Buffer)
{
        return(cCommandDescriptorScsi(Buffer));
}

    cCommandDescriptorScsi::cCommandDescriptorScsi(std::shared_ptr<cBufferInterface> Buffer) :
cCommandDescriptor(Buffer)
{

}

    cCommandDescriptorScsi::cCommandDescriptorScsi(std::shared_ptr<cBufferInterface> Buffer, U32 Format) :
cCommandDescriptor(Buffer, Format)
{
    
}

    cCommandDescriptorScsi::cCommandDescriptorScsi(std::shared_ptr<const cBufferInterface> Buffer) :
cCommandDescriptor(Buffer)
{
    
}

    StorageUtility::Scsi::sCdbFields& cCommandDescriptorScsi::GetCdbFields()
{
    U8* buffer = m_Buffer->ToDataBuffer();
    return( (StorageUtility::Scsi::sCdbFields&)buffer[CDB_FIELDS_OFFSET] );
}

    const StorageUtility::Scsi::sCdbFields& cCommandDescriptorScsi::GetCdbFields() const
{
    const U8* buffer = m_Buffer->ToDataBuffer();
    return((StorageUtility::Scsi::sCdbFields&)buffer[CDB_FIELDS_OFFSET]);
}

    StorageUtility::Scsi::sCommandCharacteristics& cCommandDescriptorScsi::GetCommandCharacteristics()
{
    U8* buffer = m_Buffer->ToDataBuffer();
    return( (StorageUtility::Scsi::sCommandCharacteristics&)buffer[COMMAND_CHARACTERISTICS_OFFSET] );
}

    const StorageUtility::Scsi::sCommandCharacteristics& cCommandDescriptorScsi::GetCommandCharacteristics() const
{
    const U8* buffer = m_Buffer->ToDataBuffer();
    return((StorageUtility::Scsi::sCommandCharacteristics&)buffer[COMMAND_CHARACTERISTICS_OFFSET]);
}

}
}
