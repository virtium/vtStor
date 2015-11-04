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
#include "CommandDescriptor.h"

namespace vtStor
{
    const size_t cCommandDescriptor::DEVICE_HANDLE_OFFSET = cBufferFormatter::DATA_OFFSET;

    cCommandDescriptor cCommandDescriptor::Reader(std::shared_ptr<const cBufferInterface> Buffer)
    {
        return(cCommandDescriptor(Buffer));
    }

    cCommandDescriptor cCommandDescriptor::Modifier(std::shared_ptr<cBufferInterface> Buffer)
    {
        return(cCommandDescriptor(Buffer));
    }

    cCommandDescriptor::cCommandDescriptor(std::shared_ptr<cBufferInterface> Buffer) :
        cBufferFormatter(Buffer)
    {

    }

    cCommandDescriptor::cCommandDescriptor(std::shared_ptr<cBufferInterface> Buffer, U32 Format) :
        cBufferFormatter(Buffer, Format)
    {

    }

    cCommandDescriptor::cCommandDescriptor(std::shared_ptr<const cBufferInterface> Buffer) :
        cBufferFormatter(Buffer)
    {

    }
    // comment by Minh Mai
    
    DeviceHandle& cCommandDescriptor::GetDeviceHandle()
    {
        U8* buffer = m_Buffer->ToDataBuffer();
        return((DeviceHandle&)buffer[DEVICE_HANDLE_OFFSET]);
    }

    const DeviceHandle& cCommandDescriptor::GetDeviceHandle() const
    {
        const U8* buffer = m_Buffer->ToDataBuffer();
        return((DeviceHandle&)buffer[DEVICE_HANDLE_OFFSET]);
    }
}
