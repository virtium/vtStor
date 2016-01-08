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
#include "StorageUtility.h"
#include "DriveAta.h"
#include "ProtocolAtaPassThrough.h"
#include "Device.h"
#include "DriveEnumeratorAta.h"

void cDriveEnumeratorAta_GetDriveEnumerator(std::shared_ptr<vtStor::IDriveEnumerator>& DriveEnumerator)
{
    DriveEnumerator = std::shared_ptr<vtStor::IDriveEnumerator>(new vtStor::cDriveEnumeratorAta());
}

namespace vtStor
{
 
cDriveEnumeratorAta::~cDriveEnumeratorAta()
{
}

std::shared_ptr<IDrive> cDriveEnumeratorAta::EnumerateDrive(const std::shared_ptr<IDevice>& Device)
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
        //TODO: handle error
        return( nullptr );
    }

    sStorageAdapterProperty storageAdapterProperty;
    errorCode = GetStorageAdapterProperty( deviceHandle, storageAdapterProperty );

    if ( eErrorCode::None != errorCode )
    {
        //TODO: handle error
        return( nullptr );
    }

    if ( true == IsAtaDeviceBus( storageAdapterProperty ) )
    {
        std::shared_ptr<IDrive> drive = std::make_shared<cDriveAta>(Device, deviceHandle);

        return( drive );
    }

    return( nullptr );
}

}
