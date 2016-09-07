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

#ifndef __vtStorDriveAsynIoCommandExtensionManaged_h__
#define __vtStorDriveAsynIoCommandExtensionManaged_h__
#pragma once

#include "IAsynIoCommandExtensions.h"
#include "UniquePtrManaged.h"

using namespace System::Collections::Generic;

namespace vtStor
{
    namespace AsynIo
    {
        namespace Managed
        {
            public ref class cAsynIoCommandExtensions
            {
            public:
                cAsynIoCommandExtensions(vtStor::Managed::IRunTimeDll^ RunTimeDll);

            protected:
                ~cAsynIoCommandExtensions();

            protected:
                !cAsynIoCommandExtensions();

            public:
                vtStor::Managed::eErrorCode IssueCommand_ReadAsynIo(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U32 Count, U64 Lba, vtStor::Managed::cOverlapped^ OverlappedPtr);
                vtStor::Managed::eErrorCode IssueCommand_WriteAsynIo(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U32 Count, U64 Lba, vtStor::Managed::cOverlapped^ OverlappedPtr);

            private:
                vtStor::Managed::cUniquePtr<vtStor::IAsynIoCommandExtensions> m_AsynIoCommandExtensions;
            };
        }
    }
}

#endif