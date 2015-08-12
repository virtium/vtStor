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
#include "vtStorAta.h"
#include "CommandHandlerAta.h"
#include "DriveAta.h"
#include "StorageUtility.h"

#include "ProtocolAtaPassThrough.h"

#include "DriveEnumeratorAta.h"
#include "Device.h"

namespace vtStor
{
 
cDriveEnumeratorAta::~cDriveEnumeratorAta()
{

}

eErrorCode cDriveEnumeratorAta::EnumerateDrive( const std::shared_ptr<cDeviceInterface>& Device, Vector_Drives& AddToList, bool& SuccessFlag )
{
    DeviceHandle deviceHandle;
    eErrorCode errorCode;

    try
    {
        deviceHandle = Device->Handle();
    }
    catch (std::exception ex)
    {
        //fprintf(stderr, "\nEnumerateDrive was not successful. Exception:%s.", ex.what());
        errorCode = eErrorCode::NullPointer;
        return (errorCode);
    }

    sStorageAdapterProperty storageAdapterProperty;
    errorCode = GetStorageAdapterProperty( deviceHandle, storageAdapterProperty );
    if ( eErrorCode::None != errorCode )
    {
        CloseDeviceHandle(deviceHandle);
        //TODO: handle error
        return (errorCode);
    }

    if ( true == IsAtaDeviceBus( storageAdapterProperty ) )
    {
        std::shared_ptr<cDriveInterface> drive = std::make_shared<cDriveAta>(Device, deviceHandle);

        AddToList.push_back( drive );
        SuccessFlag = true;
    }

    return( eErrorCode::None );
}

}