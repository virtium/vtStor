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
#ifndef __vtStorIBuffer_h__
#define __vtStorIBuffer_h__

#include <memory>

#include "BasicTypes.h"
#include "PlatformDefines.h"

namespace vtStor
{
    struct IBuffer
    {
        virtual U8* ToDataBuffer() = 0;
        virtual void SetByteAt(U32 Index, U8 Value) = 0;
        virtual U8 GetByteAt(U32 Index) = 0;
        virtual U32 GetSizeInBytes() = 0;
    };
}

extern "C"
{
    VTSTOR_API void cBuffer_GetBuffer(std::shared_ptr<vtStor::IBuffer>& Buffer, vtStor::U32 SizeInByte);
}

typedef void (WINAPIV * GetBufferDelegate) (std::shared_ptr<vtStor::IBuffer>&, vtStor::U32);

#endif // end __vtStorIBuffer_h__