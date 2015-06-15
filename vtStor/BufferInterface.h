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
#ifndef __vtStorBufferInterface_h__
#define __vtStorBufferInterface_h__

#include <memory>

#include "BasicTypes.h"
#include "vtStorPlatformDefines.h"

namespace vtStor
{
    
class VTSTOR_API cBufferInterface
{
public:
    static std::shared_ptr<vtStor::cBufferInterface> ToSharedPtr( void* Object );
    static void* ToVoidPointer( std::shared_ptr<vtStor::cBufferInterface>& Object );

public:
    cBufferInterface();
    virtual ~cBufferInterface();

public:
    //! The use of normal pointer is intentional
    virtual U8* ToDataBuffer() = 0;
    virtual void SetByteAt(U32 Index, U8 Value) = 0;
};

VTSTOR_API_EXPORT_IMPL template class VTSTOR_API std::shared_ptr<cBufferInterface>;
VTSTOR_API_EXPORT_IMPL template class VTSTOR_API std::shared_ptr<const cBufferInterface>;

}

#endif