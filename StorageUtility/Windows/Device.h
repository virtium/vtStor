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

#include <Windows.h>
#include <setupapi.h>

#include "DeviceDataType.h"
#include "DeviceInterface.h"
#include "ErrorCodes.h"

namespace vtStor
{

class cDevice : public cDeviceInterface
{
public:
    cDevice(const PSP_DEVINFO_DATA& DevInfoData, const PSP_DEVICE_INTERFACE_DATA& DevInterfaceData, const PSP_INTERFACE_DEVICE_DETAIL_DATA& DevDetailData, U32 SizeOfDevDetailData);
    virtual ~cDevice();

public:
    virtual void Data(std::unordered_map<eDeviceDataType, void*>& Data) override;

    virtual DeviceHandle Handle() override;

    virtual void DevicePath(tchar*& DevicePath) override;

private:
    eErrorCode GetStorageDeviceHandle(const String& DevicePath, HANDLE& Handle);

    void AllocateMemories(const PSP_DEVINFO_DATA& DevInfoData, const PSP_DEVICE_INTERFACE_DATA& DevInterfaceData, const PSP_INTERFACE_DEVICE_DETAIL_DATA& DevDetailData, U32 SizeOfDevDetailData);

    void CopyMemories(const PSP_DEVINFO_DATA& DevInfoData, const PSP_DEVICE_INTERFACE_DATA& DevInterfaceData, const PSP_INTERFACE_DEVICE_DETAIL_DATA& DevDetailData, U32 SizeOfDevDetailData);

    void DeallocateMemories();

private:
    PSP_DEVINFO_DATA m_DevInfoData;
    PSP_DEVICE_INTERFACE_DATA m_DevInterfaceData;
    PSP_INTERFACE_DEVICE_DETAIL_DATA m_DevDetailData;
};

}

#endif