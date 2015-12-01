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
#ifndef __Device_h__
#define __Device_h__
#pragma once

#include "DeviceDataType.h"
#include "DeviceInterface.h"
#include "ErrorCodes.h"

namespace vtStor
{

class cDevice : public cDeviceInterface
{
public:
    cDevice();
    cDevice (String Path);
    virtual ~cDevice();

public:
    virtual void Data(std::unordered_map<eDeviceDataType, void*>& Data) override;
    virtual DeviceHandle Handle() override;
    virtual void DevicePath(tchar*& DevicePath) override;

    String GetDevicePath();
    void SetDevicePath (const String DevicePath);
    DeviceHandle GetDeviceHandle();
    void SetDeviceHandle (const DeviceHandle Device_Handle);

private:
    String m_DevicePath;
    DeviceHandle m_DeviceHandle;

};

}

#endif
