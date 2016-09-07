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

#include "BasicTypes.h"
#include "ErrorCodes.h"
#include "IDevice.h"


namespace vtStor
{

    struct sStorageAdapterProperty
    {
        //! TODO: Define adapter buses using BusType
        bool  AtaBus;
        bool  ScsiBus;
    };

    eErrorCode GetStorageDevices(std::vector<std::shared_ptr<IDevice>>& Devices, eOnErrorBehavior OnErrorBehavior);
    eErrorCode GetStorageDeviceHandle(const String& DevicePath, const String& SysDevicePath, DeviceHandle& Handle);
    eErrorCode GetStorageDevicePaths(std::vector<String>& DevicePaths, std::vector<String>& SysDevicePaths);
    eErrorCode GetStorageAdapterProperty(const DeviceHandle& Handle, sStorageAdapterProperty& AdapterProperty);
    eErrorCode GetPhysicalDiskNumber(const DeviceHandle& Handle, U32& PhysicalDiskNumber);

    void CreateUUID(UUID& Uuid);
    bool CompareUUID(const UUID& Id1, const UUID& Id2);

    void CloseDeviceHandle(DeviceHandle& Handle);
    bool IsAtaDeviceBus(const sStorageAdapterProperty& StorageAdapterProperty);
    bool IsScsiDeviceBus(const sStorageAdapterProperty& StorageAdapterProperty);

}

#endif
