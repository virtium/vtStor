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
#ifndef __vtStorBufferFormatter_h__
#define __vtStorBufferFormatter_h__
#pragma once

#include <memory>

#include "IBuffer.h"

namespace vtStor
{
VTSTOR_API_EXPORT_IMPL template class VTSTOR_API std::shared_ptr<IBuffer>;

class VTSTOR_API cBufferFormatter
{
public:
    struct Header
    {
        U32 Format;
    };

    static const size_t HEADER_SIZE_IN_BYTES;

public:
    static cBufferFormatter Reader(std::shared_ptr<const IBuffer> Buffer);

public:
    Header& GetHeader();
    const Header& GetHeader() const;

protected:
    cBufferFormatter(std::shared_ptr<IBuffer> Buffer);
    cBufferFormatter(std::shared_ptr<IBuffer> Buffer, U32 Format);
    cBufferFormatter(std::shared_ptr<const IBuffer> Buffer);

protected:
    static const size_t HEADER_OFFSET;
    static const size_t DATA_OFFSET;

protected:
    std::shared_ptr<IBuffer> m_Buffer;
};

}

#endif
