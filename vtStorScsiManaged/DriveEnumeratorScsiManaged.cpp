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

#include "DriveEnumeratorScsiManaged.h"
#include "vtStorScsi.h"

namespace vtStor
{
    namespace Managed
    {
        cDriveEnumeratorScsi::cDriveEnumeratorScsi()
        {
            vtStorScsiInit( *m_DriveEnumerator );
        }

        cDriveEnumeratorScsi::~cDriveEnumeratorScsi()
        {
        }

        cDriveEnumeratorScsi::!cDriveEnumeratorScsi()
        {
        }

        cDriveEnumeratorScsi::operator void*()
        {
            return( vtStor::cDriveEnumeratorInterface::ToVoidPointer( *m_DriveEnumerator ) );
        }
    }
}