/*
<License>
Copyright 2016 Virtium Technology

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
#include "AsynIoProtocolEssense.h"
#include "StorageUtility.h"

namespace vtStor
{
    const size_t cAsynIoProtocolEssense::COMMAND_FIELDS_OFFSET = cProtocolEssense::DEVICE_HANDLE_OFFSET + sizeof(DeviceHandle);

    //! IMPORTANT NOTE: this must be updated to use the very last item
    const size_t cAsynIoProtocolEssense::SIZE_IN_BYTES = cAsynIoProtocolEssense::COMMAND_FIELDS_OFFSET + sizeof(sAsynchronousIoInputs);
    
    UUID cAsynIoProtocolEssense::FormatType;

    cAsynIoProtocolEssense cAsynIoProtocolEssense::Reader(std::shared_ptr<const IBuffer> Buffer)
    {
        return(cAsynIoProtocolEssense(Buffer));
    }

    cAsynIoProtocolEssense cAsynIoProtocolEssense::Writer(std::shared_ptr<IBuffer> Buffer)
    {
        CreateUUID(FormatType);
        return(cAsynIoProtocolEssense(Buffer, FormatType));
    }

    cAsynIoProtocolEssense::cAsynIoProtocolEssense(std::shared_ptr<IBuffer> Buffer) :
        cProtocolEssense(Buffer)
    {
    }

    cAsynIoProtocolEssense::cAsynIoProtocolEssense(std::shared_ptr<IBuffer> Buffer, const UUID& Format) :
        cProtocolEssense(Buffer, Format)
    {
    }

    cAsynIoProtocolEssense::cAsynIoProtocolEssense(std::shared_ptr<const IBuffer> Buffer) :
        cProtocolEssense(Buffer)
    {
    }

    sAsynchronousIoInputs& cAsynIoProtocolEssense::GetCommandFields()
    {
        U8* buffer = m_Buffer->ToDataBuffer();
        return((sAsynchronousIoInputs&)buffer[COMMAND_FIELDS_OFFSET]);
    }

    const sAsynchronousIoInputs& cAsynIoProtocolEssense::GetCommandFields() const
    {
        const U8* buffer = m_Buffer->ToDataBuffer();
        return((sAsynchronousIoInputs&)buffer[COMMAND_FIELDS_OFFSET]);
    }
}