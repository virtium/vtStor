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
#include "Device.h"
#include "StorageUtility.h"

namespace vtStor
{

cDevice::cDevice()
{

}

cDevice::~cDevice()
{

}

 cDevice::cDevice (String Path)
 {
     this->m_DevicePath = Path;
 }

String cDevice::GetDevicePath()
{
    return m_DevicePath;
}

void cDevice::SetDevicePath(const String DevicePath)
{
    m_DevicePath = DevicePath;
}

DeviceHandle cDevice::GetDeviceHandle()
{
    return m_DeviceHandle;
}

void cDevice::SetDeviceHandle (const DeviceHandle Handle)
{
    m_DeviceHandle = Handle;
}
void cDevice::Data(std::unordered_map<eDeviceDataType, void*>& Data)
{
    // TODO:
}

void cDevice::DevicePath(tchar*& DevicePath)
{

}

DeviceHandle cDevice::Handle()
{
    eErrorCode errorCode;
    DeviceHandle Handle;
    errorCode = vtStor::GetStorageDeviceHandle(this->m_DevicePath,Handle);
    if (eErrorCode::None != errorCode)
    {
        // TODO:
       // throw std::exception("Failed to create device handle", GetLastError());
    }
    return Handle;
}

}