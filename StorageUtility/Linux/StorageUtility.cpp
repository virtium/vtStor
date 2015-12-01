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

#include <libudev.h>
#include <iostream>
#include <fcntl.h>
#include <map>
#include <memory>
#include <string.h>
#include <unistd.h>

#include "Device.h"
#include "StorageUtility.h"

namespace vtStor
{
std::map<String, vtStor::sStorageAdapterProperty> s_MappingSystemPathToProperties;
std::map<DeviceHandle, vtStor::String>  s_MappingDeviceHandleToSysPath;

eErrorCode GetStorageDevices(std::vector<std::shared_ptr<cDeviceInterface>>& Devices, eOnErrorBehavior OnErrorBehavior)
{
    std::vector<String> Paths;
    vtStor::GetStorageDevicePaths(Paths, eOnErrorBehavior::Continue);
    for (int i = 0; i < Paths.size(); i++)
    {
        std::shared_ptr<vtStor::cDevice> Device = std::make_shared<cDevice>(Paths[i]);
        Devices.push_back(Device);
    }

    eErrorCode error = eErrorCode::None;

    return(error);
}

bool IsStorageDisk(udev_device* Dev)
{
    const char* devt = udev_device_get_devtype(Dev);
    if(0 == strcmp(devt, "disk"))
    {
        return true;
    }
    return false;
}

bool IsAtaDeviceBus(udev_device* Dev)
{
    const char* bus = udev_device_get_property_value(Dev, "ID_BUS");
    if(NULL == bus)
    {

        return false;
    }
    if( 0 == strcmp(bus, "ata") || 0 == strcmp(bus, "sata"))
    {
        return true;
    }
    return false;
}

bool IsAtaDeviceBus( sStorageAdapterProperty StorageAdapterProperty )
{
    if(StorageAdapterProperty.AtaBus == true)
        return true;
    return false;
}

bool InitStorageAdapterProperty( sStorageAdapterProperty& StorageAdapterProperty, udev_device* dev )
{
    if( false == IsStorageDisk(dev))
    {
        return false;
    }
    if(true == IsAtaDeviceBus(dev))
    {
        StorageAdapterProperty.AtaBus = true;
        return true;
    }
    else
    {
        StorageAdapterProperty.AtaBus = false;
        return false;
    }
    return true;
}

eErrorCode GetStorageDevicePaths( std::vector<String>& ipPaths, eOnErrorBehavior OnErrorBehavior )
{
    struct udev *udev;
    struct udev_enumerate *enumerate;
    struct udev_list_entry *devices, *dev_list_entry;
    struct udev_device *dev;

    /* Create the udev object */
    udev = udev_new();
    if (NULL == udev)
    {
        printf("ERROR: Can't create udev\n");
        exit(1);
    }

    /* Create a list of the devices in the 'block' subsystem. */
    enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "block");

    udev_enumerate_scan_devices(enumerate);
    devices = udev_enumerate_get_list_entry(enumerate);

    s_MappingSystemPathToProperties.clear();
    udev_list_entry_foreach(dev_list_entry, devices)
    {
        const char *path;

        /* Get the filename of the /sys entry for the device
           and create a udev_device object (dev) representing it */
        path    = udev_list_entry_get_name(dev_list_entry);
        dev     = udev_device_new_from_syspath(udev, path);
        String devNode = udev_device_get_devnode(dev);
        sStorageAdapterProperty property;

        if( true == InitStorageAdapterProperty(property, dev) )
        {
            s_MappingSystemPathToProperties[devNode] = property;
            ipPaths.push_back( devNode );
        }

        udev_device_unref(dev);
    }
    /* Free the enumerator object */
    udev_enumerate_unref(enumerate);

    udev_unref(udev);
    return( eErrorCode::None);
}

eErrorCode GetStorageDeviceHandle( const String& DevicePath, DeviceHandle& Handle )
{
    if ((Handle = open(DevicePath.c_str(), O_RDONLY|O_NONBLOCK)) < 0)
    {
        printf("ERROR: Cannot open device %s\n", DevicePath.c_str());
        return eErrorCode::None;
    }
    s_MappingDeviceHandleToSysPath[Handle] = DevicePath;

    return( eErrorCode::None );
}

eErrorCode GetStorageAdapterProperty( DeviceHandle iHandle, sStorageAdapterProperty& iAdapterProperty )
{
    if(s_MappingDeviceHandleToSysPath.find(iHandle) == s_MappingDeviceHandleToSysPath.end())
    {
        // TODO : ASSERT(0);
    }
    String devSys       = s_MappingDeviceHandleToSysPath[iHandle];

    if(s_MappingSystemPathToProperties.find(devSys) == s_MappingSystemPathToProperties.end())
    {
        // TODO : ASSERT(0);
    }
    iAdapterProperty    = s_MappingSystemPathToProperties[devSys];
    return( eErrorCode::None );
}

eErrorCode ShowDevicePaths(const std::vector<String> Paths)
{
    for (int i = 0; i < Paths.size(); i++)
    {
        std::cout<<"Path of device: "<< Paths[i]<<"\n";
    }
    return eErrorCode::None;
}

bool IsScsiDeviceBus(sStorageAdapterProperty StorageDeviceProperty)
{
    // TODO:
}

void CloseDeviceHandle(HANDLE& Handle)
{
    close(Handle);
}

}