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

#include <memory>

#include "AsynIoCommandExtensionsManaged.h"
#include "IBuffer.h"
#include "IDrive.h"

namespace vtStor
{
    namespace AsynIo
    {
        namespace Managed
        {
            cAsynIoCommandExtensions::cAsynIoCommandExtensions(vtStor::Managed::IRunTimeDll^ RunTimeDll)
            {
                GetAsynIoCommandExtensionsDelegate getAsynIoCommandExtensionsDelegate = (GetAsynIoCommandExtensionsDelegate)RunTimeDll->GetFunction("cAsynIoCommandExtensions_GetAsynIoCommandExtensions");
                getAsynIoCommandExtensionsDelegate(*m_AsynIoCommandExtensions);
            }

            cAsynIoCommandExtensions::~cAsynIoCommandExtensions()
            {
            }

            cAsynIoCommandExtensions::!cAsynIoCommandExtensions()
            {
            }

            vtStor::Managed::eErrorCode cAsynIoCommandExtensions::IssueCommand_ReadAsynIo(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U32 Count, U64 Lba, vtStor::Managed::cOverlapped^ OverlappedPtr)
            {
                vtStor::Managed::eErrorCode errorCode;
                std::shared_ptr<vtStor::IDrive> spDriveInterface = *reinterpret_cast<std::shared_ptr<vtStor::IDrive>*>((void*)Drive);
                std::shared_ptr<vtStor::IBuffer> spBuffferInterface = *reinterpret_cast<std::shared_ptr<vtStor::IBuffer>*>((void*)Data);
                std::shared_ptr<vtStor::OverlappedIo> spOverlapped = *reinterpret_cast<std::shared_ptr<vtStor::OverlappedIo>*>((void*)OverlappedPtr);
                errorCode = static_cast<vtStor::Managed::eErrorCode>(m_AsynIoCommandExtensions->IssueCommand_ReadAsynIo(spDriveInterface, CommandType, spBuffferInterface, Count, Lba, spOverlapped));

                return(errorCode);
            }

            vtStor::Managed::eErrorCode cAsynIoCommandExtensions::IssueCommand_WriteAsynIo(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U32 Count, U64 Lba, vtStor::Managed::cOverlapped^ OverlappedPtr)
            {
                vtStor::Managed::eErrorCode errorCode;
                std::shared_ptr<vtStor::IDrive> spDriveInterface = *reinterpret_cast<std::shared_ptr<vtStor::IDrive>*>((void*)Drive);
                std::shared_ptr<vtStor::IBuffer> spBuffferInterface = *reinterpret_cast<std::shared_ptr<vtStor::IBuffer>*>((void*)Data);
                std::shared_ptr<vtStor::OverlappedIo> spOverlapped = *reinterpret_cast<std::shared_ptr<vtStor::OverlappedIo>*>((void*)OverlappedPtr);
                errorCode = static_cast<vtStor::Managed::eErrorCode>(m_AsynIoCommandExtensions->IssueCommand_WriteAsynIo(spDriveInterface, CommandType, spBuffferInterface, Count, Lba, spOverlapped));

                return(errorCode);
            }
        }
    }
}