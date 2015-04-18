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

#include <vector>

#include <Windows.h>
#include <Ntddscsi.h>
#include <setupapi.h>


#include "ErrorCodes.h"
#include "BasicTypes.h"
#include "vtStorPlatformDefines.h"

namespace vtStor
{

    eErrorCode GetStorageDevicePaths( std::vector<String>& Paths, eOnErrorBehavior OnErrorBehavior );
    eErrorCode GetDevicePaths( std::vector<String>& Paths, const GUID* InterfaceClassGUID, eOnErrorBehavior OnErrorBehavior );

    using EnumerateDevicesCallback = void(*)( void* Data, const HDEVINFO& DevInfoHandle, SP_DEVINFO_DATA& DevInfoData, const PSP_INTERFACE_DEVICE_DETAIL_DATA& DevDetailData, eErrorCode& ErrorCode );
    struct sEnumerateDevicesCallback
    {
        EnumerateDevicesCallback Function;
        void*                    Data;
    };
    //! Enumerate all devices that match the interface class
    //! the iCallback function will be called for each device
    //!
    eErrorCode EnumerateDevices( sEnumerateDevicesCallback& Callback, const GUID* InterfaceClassGUID, eOnErrorBehavior OnErrorBehavior );

    eErrorCode GetStorageDeviceHandle( const String& DevicePath, HANDLE& Handle );

    struct sStorageAdapterProperty
    {
        U8    BusType;
        U8    SrbType;
        U32   AlignmentMask;
    };

    eErrorCode GetStorageAdapterProperty( HANDLE Handle, sStorageAdapterProperty& AdapterProperty );

    bool IsAtaDeviceBus( sStorageAdapterProperty StorageAdapterProperty );
}

#endif