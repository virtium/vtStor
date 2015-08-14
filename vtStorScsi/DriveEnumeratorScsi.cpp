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

#include "vtStorScsi.h"
#include "DriveScsi.h"
#include "ProtocolScsiPassThrough.h"

#include "DriveEnumeratorScsi.h"

namespace vtStor
{ 
cDriveEnumeratorScsi::~cDriveEnumeratorScsi()
{

}

std::shared_ptr<cDriveInterface> cDriveEnumeratorScsi::EnumerateDrive(const String& DevicePath)
{
    DeviceHandle deviceHandle;
    eErrorCode errorCode;

    errorCode = GetStorageDeviceHandle(DevicePath, deviceHandle);
    if (eErrorCode::None != errorCode)
    {
        //TODO: handle error
        return( nullptr );
    }

    sStorageAdapterProperty storageAdapterProperty;
    errorCode = GetStorageAdapterProperty(deviceHandle, storageAdapterProperty);
    
    CloseDeviceHandle(deviceHandle);

    if (eErrorCode::None != errorCode)
    {        
        //TODO: handle error
        return( nullptr );
    }

    if (true == IsScsiDeviceBus(storageAdapterProperty))
    {
        std::shared_ptr<cDriveInterface> drive = std::make_shared<cDriveScsi>(std::make_shared<String>(DevicePath));

        return( drive );
    }

    return( nullptr );
}

}