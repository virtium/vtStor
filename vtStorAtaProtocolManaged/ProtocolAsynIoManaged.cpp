/*
<License>
Copyright 2016 Virtium Technology

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

#include "ProtocolAsynIoManaged.h"

#include "vtStorAtaProtocol/Platform/Windows/ProtocolAsynIo.h"

namespace vtStor
{
    namespace Protocol
    {
        namespace Managed
        {
            cProtocolAsynIo::cProtocolAsynIo(vtStor::Managed::IRunTimeDll^ RunTimeDll)
            {
                GetProtocolDelegate getProtocolDelegate = (GetProtocolDelegate)RunTimeDll->GetFunction("cAsynIo_GetProtocol");
                getProtocolDelegate(*m_Protocol);
            }

            cProtocolAsynIo::~cProtocolAsynIo()
            {
            }

            cProtocolAsynIo::!cProtocolAsynIo()
            {
            }

            cProtocolAsynIo::operator void*()
            {
                return(reinterpret_cast<void*>(&(*m_Protocol)));
            }
        }
    }
}