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

#include "BufferFormatter.h"

namespace vtStor
{

const size_t cBufferFormatter::HEADER_OFFSET            = 0;
const size_t cBufferFormatter::HEADER_SIZE_IN_BYTES     = sizeof( cBufferFormatter::Header );
const size_t cBufferFormatter::DATA_OFFSET              = cBufferFormatter::HEADER_OFFSET + cBufferFormatter::HEADER_SIZE_IN_BYTES;

cBufferFormatter cBufferFormatter::Reader(std::shared_ptr<const cBufferInterface> Buffer)
{
    return(cBufferFormatter(Buffer));
}

cBufferFormatter::cBufferFormatter(std::shared_ptr<cBufferInterface> Buffer) :
m_Buffer(Buffer)
{

}

cBufferFormatter::cBufferFormatter( std::shared_ptr<cBufferInterface> Buffer, U32 Format ) :
m_Buffer( Buffer )
{
    Header& header = GetHeader();
    header.Format = Format;
}

cBufferFormatter::cBufferFormatter( std::shared_ptr<const cBufferInterface> Buffer ) :
m_Buffer( std::const_pointer_cast<cBufferInterface>(Buffer) )
{

}

cBufferFormatter::Header& cBufferFormatter::GetHeader()
{
    U8* buffer = m_Buffer->ToDataBuffer();
    return( (Header&)buffer[HEADER_OFFSET] );
}

const cBufferFormatter::Header& cBufferFormatter::GetHeader() const
{
    const U8* buffer = m_Buffer->ToDataBuffer();
    return( (Header&)buffer[HEADER_OFFSET] );
}

}