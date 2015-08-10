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
#ifndef __vtStorProtocolInterface_h__
#define __vtStorProtocolInterface_h__

#include <memory>

#include "ErrorCodes.h"
#include "BufferInterface.h"

namespace vtStor
{
namespace Protocol
{

class VTSTOR_API cProtocolInterface
{
public:
    static std::shared_ptr<vtStor::Protocol::cProtocolInterface> ToSharedPtr( void* Object );
    static void* ToVoidPointer( std::shared_ptr<vtStor::Protocol::cProtocolInterface>& Object );

public:
    cProtocolInterface();
    virtual ~cProtocolInterface();

public:
    virtual eErrorCode IssueCommand( const DeviceHandle& Handle, std::shared_ptr<cBufferInterface> Essense, std::shared_ptr<cBufferInterface> DataBuffer ) = 0;
};

VTSTOR_API_EXPORT_IMPL template class VTSTOR_API std::shared_ptr<Protocol::cProtocolInterface>;

}
}


#endif