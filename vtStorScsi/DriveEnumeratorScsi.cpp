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
#include "vtStorScsi.h"
#include "CommandHandlerScsi.h"
#include "DriveScsi.h"
#include "StorageUtility.h"

#include "ProtocolScsiPassThrough.h"

#include "DriveEnumeratorScsi.h"

namespace vtStor
{ 
cDriveEnumeratorScsi::~cDriveEnumeratorScsi()
{

}

eErrorCode cDriveEnumeratorScsi::EnumerateDrive(const String& DevicePath, Vector_Drives& AddToList, bool& SuccessFlag)
{
    DeviceHandle deviceHandle;
    eErrorCode errorCode;

    errorCode = GetStorageDeviceHandle(DevicePath, deviceHandle);
    if (eErrorCode::None != errorCode)
    {
        //TODO: handle error
        return (errorCode);
    }

    sStorageAdapterProperty storageAdapterProperty;
    errorCode = GetStorageAdapterProperty(deviceHandle, storageAdapterProperty);
    
    CloseDeviceHandle(deviceHandle);

    if (eErrorCode::None != errorCode)
    {        
        //TODO: handle error
        return (errorCode);
    }

    if (true == IsScsiDeviceBus(storageAdapterProperty))
    {
        std::shared_ptr<cDriveInterface> drive = std::make_shared<cDriveScsi>(std::make_shared<String>(DevicePath));

        AddToList.push_back(drive);
        SuccessFlag = true;
    }

    return(eErrorCode::None);
}

}