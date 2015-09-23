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
#ifndef __vtStorBuffer_h__
#define __vtStorBuffer_h__
#pragma once

#include "BufferInterface.h"

namespace vtStor
{

class VTSTOR_API cBuffer : public cBufferInterface
{

    static const int STOR_API_SECTOR_SIZE = 512;

public:
    cBuffer( size_t SizeInBytes );
    virtual ~cBuffer();

public:
    virtual U8* ToDataBuffer() override;
    virtual void SetByteAt(U32 Index, U8 Value) override;
    virtual U8 GetByteAt(U32 Index) override;
    virtual U32 GetSizeInBytes() override;

public:
    virtual void FillEntireBufferWithPattern(U8 Pattern) override;
    virtual void FillSectorsWithPattern(U32 NumberOfSectors, U8 Pattern) override;
    virtual bool CompareSector(std::shared_ptr<vtStor::cBufferInterface> DataBuffer, U32 Sector) override;

protected:
    U8* m_AlignedBuffer;
    U8* m_UnalignedBuffer;
    U8* m_OffsetBuffer;
    size_t m_SizeInBytes;
    size_t m_SizeInSectors;

private:
    static const U8 CACHE_ALIGN_BYTES = 64;
    static const U16  CACHE_ALIGN_BITMASK = (CACHE_ALIGN_BYTES - 1);
};

}

#endif