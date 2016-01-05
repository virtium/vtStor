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
#ifndef __vtStorIDevice_h__
#define __vtStorIDevice_h__

#include <unordered_map>

#include "BasicTypes.h"
#include "DeviceDataType.h"

namespace vtStor
{
    struct IDevice
    {
        virtual ~IDevice() {}
        virtual void Data(std::unordered_map<eDeviceDataType, void*>& Data) = 0;
        virtual DeviceHandle Handle() = 0;
        virtual void DevicePath(tchar*& DevicePath) = 0;
    };
}

#endif // end __vtStorIDevice_h__