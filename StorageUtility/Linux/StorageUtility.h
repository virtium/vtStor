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
#ifndef __StorageUtility_h__
#define __StorageUtility_h__

#include "BasicTypes.h"
#include "DeviceInterface.h"
#include "ErrorCodes.h"

namespace vtStor
{
    eErrorCode GetStorageDevices(std::vector<std::shared_ptr<cDeviceInterface>>& Devices, eOnErrorBehavior OnErrorBehavior);
    eErrorCode GetStorageDeviceHandle( const String& DevicePath, DeviceHandle& Handle );
    eErrorCode GetStorageDevicePaths( std::vector<String>& Paths, eOnErrorBehavior OnErrorBehavior );

    struct sStorageAdapterProperty
    {
        bool AtaBus;
        U8    BusType;
        U8    SrbType;
        U32   AlignmentMask;
    };

    eErrorCode ShowDevicePaths(const std::vector<String> Paths);

    eErrorCode GetStorageAdapterProperty( DeviceHandle Handle, sStorageAdapterProperty& AdapterProperty );

    void CloseDeviceHandle(HANDLE& Handle);

    bool IsAtaDeviceBus( sStorageAdapterProperty StorageAdapterProperty );
    bool IsScsiDeviceBus( sStorageAdapterProperty StorageAdapterProperty );
}

#endif
