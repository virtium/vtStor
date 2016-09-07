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

#include "DriveEnumerator.h"

void cDriveEnumerator_GetDriveEnumerator(std::shared_ptr<vtStor::IDriveEnumerator>& DriveEnumerator)
{
    DriveEnumerator = std::shared_ptr<vtStor::IDriveEnumerator>(new vtStor::cDriveEnumerator());
}

namespace vtStor
{
    cDriveEnumerator::cDriveEnumerator()
    {
    }

    std::shared_ptr<IDrive> cDriveEnumerator::EnumerateDrive(const std::shared_ptr<IDevice>& Device)
    {
        return nullptr;
    }
}