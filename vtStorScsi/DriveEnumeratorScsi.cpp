/*
<License>
Copyright 2016 Virtium Technology

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

#include "DriveScsi.h"
#include "ProtocolScsiPassThrough.h"

#include "DriveEnumeratorScsi.h"

void cDriveEnumeratorScsi_GetDriveEnumerator(std::shared_ptr<vtStor::IDriveEnumerator>& DriveEnumerator)
{
    DriveEnumerator = std::shared_ptr<vtStor::IDriveEnumerator>(new vtStor::cDriveEnumeratorScsi());
}

namespace vtStor
{
    cDriveEnumeratorScsi::~cDriveEnumeratorScsi()
    {
    }

    std::shared_ptr<IDrive> cDriveEnumeratorScsi::EnumerateDrive(const std::shared_ptr<IDevice>& Device)
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
            return(nullptr);
        }

        sStorageAdapterProperty storageAdapterProperty;
        errorCode = GetStorageAdapterProperty(deviceHandle, storageAdapterProperty);

        if (eErrorCode::None != errorCode)
        {
            //TODO: handle error
            return(nullptr);
        }

        U32 physicalDiskNumber;
        errorCode = GetPhysicalDiskNumber(deviceHandle, physicalDiskNumber);
        if (eErrorCode::None != errorCode)
        {
            //TODO: handle error
            return(nullptr);
        }

        tchar* devicePath;
        Device->DevicePath(devicePath);

        // Add drive propeties to the container
        std::shared_ptr<vtStor::sDriveProperties> driveProperties = std::make_shared<vtStor::sDriveProperties>();
        driveProperties->PhysicalDiskNumber = physicalDiskNumber;
        driveProperties->DevicePath = devicePath;

        if (true == IsScsiDeviceBus(storageAdapterProperty))
        {
            std::shared_ptr<IDrive> drive = std::make_shared<cDriveScsi>(Device, deviceHandle, driveProperties);

            return(drive);
        }

        return(nullptr);
    }
}