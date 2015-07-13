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

#ifndef __vtStorScsiDriveEnumeratorScsiManaged_h__
#define __vtStorScsiDriveEnumeratorScsiManaged_h__
#pragma once

#include "DriveEnumeratorInterface.h"
#include "SharedPtrManaged.h"

using namespace vtStor;
using namespace vtStor::Managed;

namespace vtStor
{
    namespace Managed
    {
        public ref class cDriveEnumeratorScsi : public cDriveEnumeratorInterface
        {
        public:
            cDriveEnumeratorScsi();
            virtual ~cDriveEnumeratorScsi();

        protected:
            !cDriveEnumeratorScsi();

        public:
            virtual operator void*() override;

        private:
            cSharedPtr<vtStor::cDriveEnumeratorInterface> m_DriveEnumerator;
        };
    }
}

#endif