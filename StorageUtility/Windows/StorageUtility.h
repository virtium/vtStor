//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#ifndef __StorageUtility_h__
#define __StorageUtility_h__

#include <vector>

#include <Windows.h>
#include <Ntddscsi.h>
#include <setupapi.h>


#include "ErrorCodes.h"
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

    void GetDevicePathsCallback( void* Data, const HDEVINFO& DevInfoHandle, SP_DEVINFO_DATA& DevInfoData, const PSP_INTERFACE_DEVICE_DETAIL_DATA& DevDetailData, eErrorCode& ErrorCode );

}

#endif