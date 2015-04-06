//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#include <memory>

#include "StorageUtility.h"

namespace vtStor
{

eErrorCode GetStorageDevicePaths( std::vector<String>& Paths, eOnErrorBehavior OnErrorBehavior )
{
    return( GetDevicePaths( Paths, &GUID_DEVINTERFACE_DISK, OnErrorBehavior ) );
}

eErrorCode GetDevicePaths( std::vector<String>& Paths, const GUID* InterfaceClassGUID, eOnErrorBehavior OnErrorBehavior )
{
    eErrorCode error = eErrorCode::None;

    sEnumerateDevicesCallback callBack;
    callBack.Data = (void*)&Paths;
    callBack.Function = GetDevicePathsCallback;

    //error = EnumerateDevices( callBack, InterfaceClassGUID, OnErrorBehavior );
    return( error );
}

void GetDevicePathsCallback( void* Data, const HDEVINFO& DevInfoHandle, SP_DEVINFO_DATA& DevInfoData, const PSP_INTERFACE_DEVICE_DETAIL_DATA& DevDetailData, eErrorCode& ErrorCode )
{
    std::vector<String>* paths = ( std::vector<String>* )Data;
    paths->push_back( DevDetailData->DevicePath );
}

}