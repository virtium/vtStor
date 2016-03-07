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

cDevice::cDevice(const PSP_DEVINFO_DATA& DevInfoData, const PSP_DEVICE_INTERFACE_DATA& DevInterfaceData, const PSP_INTERFACE_DEVICE_DETAIL_DATA& DevDetailData, U32 SizeOfDevDetailData)
{
    AllocateMemories(DevInfoData, DevInterfaceData, DevDetailData, SizeOfDevDetailData);
    CopyMemories(DevInfoData, DevInterfaceData, DevDetailData, SizeOfDevDetailData);
}

cDevice::~cDevice()
{
    DeallocateMemories();
}

void cDevice::Data(std::unordered_map<eDeviceDataType, void*>& Data)
{
    Data.insert({ eDeviceDataType::PSP_DEVINFO_DATA, m_DevInfoData });
    Data.insert({ eDeviceDataType::PSP_DEVICE_INTERFACE_DATA, m_DevInterfaceData });
    Data.insert({ eDeviceDataType::PSP_INTERFACE_DEVICE_DETAIL_DATA, m_DevDetailData });
}

DeviceHandle cDevice::Handle()
{
    eErrorCode errorCode;
    DeviceHandle deviceHandle;

    errorCode = GetStorageDeviceHandle(m_DevDetailData->DevicePath, deviceHandle);
    if (eErrorCode::None != errorCode)
    {
        throw std::exception("Failed to create device handle", GetLastError());
    }
    return deviceHandle;
}

void cDevice::DevicePath(tchar*& DevicePath)
{
    DevicePath = m_DevDetailData->DevicePath;
}

eErrorCode cDevice::GetStorageDeviceHandle(const String& DevicePath, HANDLE& Handle)
{
    Handle =
        CreateFile(
        DevicePath.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
        NULL
        );

    if (INVALID_HANDLE_VALUE == Handle)
    {
        return(eErrorCode::Io);
    }

    return(eErrorCode::None);
}

void cDevice::AllocateMemories(const PSP_DEVINFO_DATA& DevInfoData, const PSP_DEVICE_INTERFACE_DATA& DevInterfaceData, const PSP_INTERFACE_DEVICE_DETAIL_DATA& DevDetailData, U32 SizeOfDevDetailData)
{
    m_DevInfoData = (PSP_DEVINFO_DATA)HeapAlloc(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS, DevInfoData->cbSize);
    m_DevInterfaceData = (PSP_DEVICE_INTERFACE_DATA)HeapAlloc(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS, DevInterfaceData->cbSize);
    m_DevDetailData = (PSP_INTERFACE_DEVICE_DETAIL_DATA)HeapAlloc(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS, SizeOfDevDetailData);
}

void cDevice::CopyMemories(const PSP_DEVINFO_DATA& DevInfoData, const PSP_DEVICE_INTERFACE_DATA& DevInterfaceData, const PSP_INTERFACE_DEVICE_DETAIL_DATA& DevDetailData, U32 SizeOfDevDetailData)
{
    memcpy_s(m_DevInfoData, DevInfoData->cbSize, DevInfoData, DevInfoData->cbSize);
    memcpy_s(m_DevInterfaceData, DevInfoData->cbSize, DevInterfaceData, DevInterfaceData->cbSize);

    size_t devicePathLength = (tstrlen(DevDetailData->DevicePath) + 1);
    m_DevDetailData->cbSize = DevDetailData->cbSize;
    tmemcpy_s(m_DevDetailData->DevicePath, devicePathLength, DevDetailData->DevicePath, devicePathLength);
}

void cDevice::DeallocateMemories()
{
    HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, m_DevInfoData);
    HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, m_DevInterfaceData);
    HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, m_DevDetailData);
}

}