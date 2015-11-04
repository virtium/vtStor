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
#include <assert.h>

#include "Buffer.h"
#include <inttypes.h>

namespace vtStor
{

cBuffer::cBuffer( size_t SizeInBytes ) :
    m_SizeInBytes( SizeInBytes )
{
    assert( 0 != SizeInBytes );

    // Allocate enough memory to ensure cache alignment
    m_UnalignedBuffer = new U8[ m_SizeInBytes + CACHE_ALIGN_BYTES ];
    U16 currentAddress = static_cast<U32>(reinterpret_cast<intptr_t>(m_UnalignedBuffer)) & 0x0000FFFF; // add int16_t to cast type by Minh Mai static_cast<int>(reinterpret_cast<intptr_t>(p))
    U16 nextAlignAddress = ((currentAddress | CACHE_ALIGN_BITMASK) + 1);
    m_AlignedBuffer = (m_UnalignedBuffer + (nextAlignAddress - currentAddress));
}

cBuffer::~cBuffer()
{
    if ( nullptr != m_UnalignedBuffer )
    {
        delete[] m_UnalignedBuffer;
    }
}

U8* cBuffer::ToDataBuffer()
{
    return( m_AlignedBuffer );
}

void cBuffer::SetByteAt( U32 Index, U8 Value )
{
    assert( Index < m_SizeInBytes );
    m_AlignedBuffer[ Index ] = Value;
}

U8 cBuffer::GetByteAt( U32 Index )
{
    assert( Index < m_SizeInBytes );
    return( m_AlignedBuffer[ Index ] );
}

U32 cBuffer::GetSizeInBytes()
{
    return( m_SizeInBytes );
}

}
