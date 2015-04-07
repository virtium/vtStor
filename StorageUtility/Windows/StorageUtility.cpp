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

    error = EnumerateDevices( callBack, InterfaceClassGUID, OnErrorBehavior );
    return( error );
}

eErrorCode EnumerateDevices( sEnumerateDevicesCallback& Callback, const GUID* InterfaceClassGUID, eOnErrorBehavior OnErrorBehavior )
{
    HDEVINFO devInfoHandle =
        SetupDiGetClassDevs
        (
        InterfaceClassGUID,
        NULL,
        NULL,
        DIGCF_PRESENT | DIGCF_DEVICEINTERFACE
        );
    if ( INVALID_HANDLE_VALUE == devInfoHandle )
    {
        return( eErrorCode::Unknown );
    }

    DWORD error = 0;
    DWORD memberIndex = 0;
    while ( true == true )
    {
        SP_DEVICE_INTERFACE_DATA devInterfaceData;
        devInterfaceData.cbSize = sizeof( devInterfaceData );
        if ( SetupDiEnumDeviceInterfaces( devInfoHandle, NULL, InterfaceClassGUID, memberIndex++, &devInterfaceData ) == FALSE )
        {
            error = GetLastError();
            if ( ERROR_NO_MORE_ITEMS == error )
            {
                break;
            }
            else
            {
                SetupDiDestroyDeviceInfoList( devInfoHandle );
                return( eErrorCode::Unknown );
            }
        }

        DWORD bufferSize = 0;
        SP_DEVINFO_DATA devInfoData;
        devInfoData.cbSize = sizeof( devInfoData );

        // Get buffer size
        if ( SetupDiGetDeviceInterfaceDetail( devInfoHandle, &devInterfaceData, NULL, 0, &bufferSize, &devInfoData ) == FALSE )
        {
            error = GetLastError();
            if ( ERROR_INSUFFICIENT_BUFFER != error )
            {
                if ( eOnErrorBehavior::Continue == OnErrorBehavior ) { continue; }
                SetupDiDestroyDeviceInfoList( devInfoHandle );
                return( eErrorCode::Unknown );
            }
        }

        PSP_INTERFACE_DEVICE_DETAIL_DATA pDevDetailData = (PSP_INTERFACE_DEVICE_DETAIL_DATA)LocalAlloc( LPTR, bufferSize );
        if ( NULL == pDevDetailData )
        {
            if ( eOnErrorBehavior::Continue == OnErrorBehavior ) { continue; }
            SetupDiDestroyDeviceInfoList( devInfoHandle );
            return( eErrorCode::Memory );
        }
        pDevDetailData->cbSize = sizeof( SP_INTERFACE_DEVICE_DETAIL_DATA );

        if ( SetupDiGetDeviceInterfaceDetail( devInfoHandle, &devInterfaceData, pDevDetailData, bufferSize, NULL, NULL ) == FALSE )
        {
            error = GetLastError();
            if ( ERROR_INSUFFICIENT_BUFFER != error )
            {
                LocalFree( pDevDetailData );
                if ( eOnErrorBehavior::Continue == OnErrorBehavior ) { continue; }
                SetupDiDestroyDeviceInfoList( devInfoHandle );
                return( eErrorCode::Unknown );
            }
        }

        eErrorCode errorCode;
        errorCode = eErrorCode::Unknown;
        Callback.Function( Callback.Data, devInfoHandle, devInfoData, pDevDetailData, errorCode );

        LocalFree( pDevDetailData );
    }

    SetupDiDestroyDeviceInfoList( devInfoHandle );

    return( eErrorCode::None );
}

void GetDevicePathsCallback( void* Data, const HDEVINFO& DevInfoHandle, SP_DEVINFO_DATA& DevInfoData, const PSP_INTERFACE_DEVICE_DETAIL_DATA& DevDetailData, eErrorCode& ErrorCode )
{
    std::vector<String>* paths = ( std::vector<String>* )Data;
    paths->push_back( DevDetailData->DevicePath );
}

}