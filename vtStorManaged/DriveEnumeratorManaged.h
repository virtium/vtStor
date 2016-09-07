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

#ifndef __vtStorDriveEnumeratorManaged_h__
#define __vtStorDriveEnumeratorManaged_h__
#pragma once

#include "DriveEnumeratorInterfaceManaged.h"
#include "IDriveEnumerator.h"
#include "ILoadRunTimeDll.h"
#include "SharedPtrManaged.h"

using namespace vtStor;
using namespace vtStor::Managed;

namespace vtStor
{
    namespace Managed
    {
        public ref class cDriveEnumerator : public cDriveEnumeratorInterface
        {
        public:
            cDriveEnumerator(IRunTimeDll^ RunTimeDll);
            ~cDriveEnumerator();
           
        protected:
            !cDriveEnumerator();

        public:
            virtual operator void*() override;

        public:
            cSharedPtr<vtStor::IDriveEnumerator> m_DriveEnumerator;
            cSharedPtr<vtStor::IDriveEnumerator> m_DriveEnumerateDecorator;
        };
    }
}
#endif