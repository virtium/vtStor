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

#include "Buffer.h"
#include "BufferInterfaceManaged.h"

namespace vtStor
{
    namespace Managed
    {
        cBufferInterface::cBufferInterface( U32 SizeInByte )
        {
            std::shared_ptr<vtStor::cBufferInterface> dataBuffer = std::make_shared<vtStor::cBuffer>( SizeInByte );
            m_Buffer = dataBuffer;
        }

        cBufferInterface::~cBufferInterface()
        {
        }

        cBufferInterface::!cBufferInterface()
        {
        }

        cBufferInterface::operator void*()
        {
            return( vtStor::cBufferInterface::ToVoidPointer( *m_Buffer ) );
        }

        void cBufferInterface::SetByteAt( U32 Index, U8 Value )
        {
            return( m_Buffer->SetByteAt( Index, Value ) );
        }
    }
}
