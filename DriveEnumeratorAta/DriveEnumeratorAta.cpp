//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#include "DriveAta.h"
#include "StorageUtility.h"

#include "DriveEnumeratorAta.h"

namespace vtStor
{
 
cDriveEnumeratorAta::~cDriveEnumeratorAta()
{

}

eErrorCode cDriveEnumeratorAta::EnumerateDrives( Vector_Drives& AddToList, U32& Count )
{
    Count = 0;

    std::vector<String> devicePaths;
    vtStor::GetStorageDevicePaths( devicePaths, eOnErrorBehavior::Continue );

    HANDLE deviceHandle;
    eErrorCode errorCode;
    for ( const auto& devicePath : devicePaths )
    {
        errorCode = GetStorageDeviceHandle( devicePath, deviceHandle );
        if ( eErrorCode::None != errorCode )
        {
            //TODO: handle error
            continue;
        }

        sStorageAdapterProperty storageAdapterProperty;
        errorCode = GetStorageAdapterProperty( deviceHandle, storageAdapterProperty );
        if ( eErrorCode::None != errorCode )
        {
            CloseHandle(deviceHandle);
            //TODO: handle error
            continue;
        }

        if ( true == IsAtaDeviceBus( storageAdapterProperty ) )
        {
            std::shared_ptr<cDriveInterface> drive = std::make_shared<cDriveAta>(devicePath);
            AddToList.push_back( drive );
            ++Count;
        }
    }

    return( eErrorCode::None );
}

}