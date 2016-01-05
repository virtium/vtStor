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

#include <memory>

#include "DriveEnumeratorAtaManaged.h"

namespace vtStor
{
    namespace Managed
    {
        cDriveEnumeratorAta::cDriveEnumeratorAta(IRunTimeDll^ RunTimeDll)
        {
            GetDriveEnumeratorDelegate getDriveEnumeratorDelegate = (GetDriveEnumeratorDelegate)RunTimeDll->GetFunction("cDriveEnumeratorAta_GetDriveEnumerator");
            getDriveEnumeratorDelegate(*m_DriveEnumerator);
        }

        cDriveEnumeratorAta::~cDriveEnumeratorAta()
        {
        }

        cDriveEnumeratorAta::!cDriveEnumeratorAta()
        {
        }

        cDriveEnumeratorAta::operator void*()
        {
            return(reinterpret_cast<void*>(&(*m_DriveEnumerator)));
        }
    }
}
