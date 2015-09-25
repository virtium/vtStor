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

namespace vtStor
{

cBuffer::cBuffer( size_t SizeInBytes ) :
    m_SizeInBytes( SizeInBytes )
{
    assert( 0 != SizeInBytes );

    // Allocate enough memory to ensure cache alignment
    m_UnalignedBuffer = new U8[ m_SizeInBytes + CACHE_ALIGN_BYTES ];
    U16 currentAddress = ((U32)m_UnalignedBuffer & 0x0000FFFF);
    U16 nextAlignAddress = ((currentAddress | CACHE_ALIGN_BITMASK) + 1);
    m_AlignedBuffer = (m_UnalignedBuffer + (nextAlignAddress - currentAddress));
    m_OffsetBuffer = m_AlignedBuffer;

    m_SizeInSectors = m_SizeInBytes / STOR_API_SECTOR_SIZE;
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

void cBuffer::FillEntireBufferWithPattern(U8 Pattern)
{
    FillSectorsWithPattern(m_SizeInSectors, Pattern);
}

void cBuffer::FillSectorsWithPattern(U32 NumberOfSectors, U8 Pattern)
{
    memset(m_OffsetBuffer, Pattern, NumberOfSectors * STOR_API_SECTOR_SIZE);
}

bool cBuffer::CompareSector(std::shared_ptr<cBufferInterface> DataBuffer, U32 Sector)
{
    int result;

    if (Sector >= m_SizeInSectors)
    {
        return false;
    }

    int compareBytes = STOR_API_SECTOR_SIZE;
    U8* thisPointer = (m_OffsetBuffer + (Sector * STOR_API_SECTOR_SIZE));
    U8* comparePointer = (DataBuffer->ToDataBuffer() + (Sector * STOR_API_SECTOR_SIZE));

    int remainder = m_SizeInBytes % STOR_API_SECTOR_SIZE;

    if (((Sector + 1) == m_SizeInSectors) && (remainder > 0))
    {
        compareBytes = remainder;
    }

    result = memcmp(thisPointer, comparePointer, compareBytes);

    if (0 != result)
    {
        return false;
    }

    return true;
}

}