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
#ifndef __StorageUtility_h__
#define __StorageUtility_h__

#include <memory>
#include <vector>

#include <Windows.h>
#include <Ntddscsi.h>
#include <setupapi.h>

#include "PlatformDefines.h"

#include "BasicTypes.h"
#include "ErrorCodes.h"
#include "IDevice.h"

namespace vtStor
{
    eErrorCode VTSTOR_API GetStorageDevices(std::vector<std::shared_ptr<IDevice>>& Devices, eOnErrorBehavior OnErrorBehavior);
    eErrorCode VTSTOR_API GetStorageDevicePaths(std::vector<String>& Paths, eOnErrorBehavior OnErrorBehavior);
    eErrorCode VTSTOR_API GetDevicePaths(std::vector<String>& Paths, const GUID* InterfaceClassGUID, eOnErrorBehavior OnErrorBehavior);

    using EnumerateDevicesCallback = void(*)(void* Data, const HDEVINFO& DevInfoHandle, SP_DEVINFO_DATA& DevInfoData, SP_DEVICE_INTERFACE_DATA& DevInterfaceData, const PSP_INTERFACE_DEVICE_DETAIL_DATA& DevDetailData, U32 SizeOfDevDetailData, eErrorCode& ErrorCode);
    struct sEnumerateDevicesCallback
    {
        EnumerateDevicesCallback Function;
        void*                    Data;
    };
    //! Enumerate all devices that match the interface class
    //! the iCallback function will be called for each device
    //!
    eErrorCode VTSTOR_API EnumerateDevices(sEnumerateDevicesCallback& Callback, const GUID* InterfaceClassGUID, eOnErrorBehavior OnErrorBehavior);

    struct sStorageAdapterProperty
    {
        U8    BusType;
        U8    SrbType;
        U32   AlignmentMask;
    };

    eErrorCode VTSTOR_API GetStorageAdapterProperty(const DeviceHandle& Handle, sStorageAdapterProperty& AdapterProperty);
    eErrorCode VTSTOR_API GetPhysicalDiskNumber(const DeviceHandle& Handle, U32& PhysicalDiskNumber);

    void VTSTOR_API CreateUUID(UUID& Uuid);
    bool VTSTOR_API CompareUUID(const UUID& Id1, const UUID& Id2);
    void VTSTOR_API CloseDeviceHandle(DeviceHandle& Handle);

    bool VTSTOR_API IsAtaDeviceBus(const sStorageAdapterProperty& StorageAdapterProperty);
    bool VTSTOR_API IsScsiDeviceBus(const sStorageAdapterProperty& StorageAdapterProperty);

    //! Functions used for asynchronously on Windows
    U64 VTSTOR_API WaitForAsynCommands(Handle* EventHandlesArray, U8& Size);

    // This function is to remove event signaled from event array
    bool VTSTOR_API RemoveEventSignaled(Handle Events[], U64 Size, U64 Index);
}

#endif
