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

#ifndef __DrivePropertiesManaged_h__
#define __DrivePropertiesManaged_h__
#pragma once

namespace vtStor
{
    namespace Managed
    {
        public ref struct DriveProperties
        {
        public:
            System::UInt32 PhysicalDiskNumber;
            System::String^ DevicePath;
        };

    }
}

#endif // __DrivePropertiesManaged_h__