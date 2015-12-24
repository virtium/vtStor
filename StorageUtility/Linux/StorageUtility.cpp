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
#include <fcntl.h>
#include <map>
#include <memory>
#include <string.h>
#include <unistd.h>

#include "Device.h"
#include "StorageUtility.h"

namespace vtStor
{

eErrorCode GetStorageDevices(std::vector<std::shared_ptr<cDeviceInterface>>& Devices, eOnErrorBehavior OnErrorBehavior)
{
    eErrorCode error = eErrorCode::None;
    std::vector<String> devicePaths;
    std::vector<String> sysDevicePaths;

    error = GetStorageDevicePaths(devicePaths, sysDevicePaths);
    for (int i = 0; i < devicePaths.size(); ++i)
    {
        std::shared_ptr<vtStor::cDevice> device = std::make_shared<cDevice>(devicePaths[i], sysDevicePaths[i]);
        Devices.push_back(device);
    }
    return(error);
}

bool IsAtaDeviceBus(udev_device* UdevDevice)
{
    const char* bus = udev_device_get_property_value(UdevDevice, "ID_BUS");

    if (nullptr != bus && (0 == (strcmp(bus, "ata")) || (0 == strcmp(bus, "sata"))))
    {
        return true;
    }
    return false;
}

bool IsScsiDeviceBus(udev_device* UdevDevice)
{
    const char* bus = udev_device_get_property_value(UdevDevice, "ID_BUS");

    if (nullptr != bus && (0 == (strcmp(bus, "usb"))))
    {
        return true;
    }
    return false;
}

bool IsAtaDeviceBus(sStorageAdapterProperty StorageAdapterProperty)
{
    return(StorageAdapterProperty.AtaBus);
}

bool IsScsiDeviceBus(sStorageAdapterProperty StorageAdapterProperty)
{
    return(StorageAdapterProperty.ScsiBus);
}

bool IsStorageDisk(udev_device* UdevDevice)
{
    const char* udevDeviceType = udev_device_get_devtype(UdevDevice);
    if (0 == strcmp(udevDeviceType, "disk"))
    {
        if (true == IsAtaDeviceBus(UdevDevice) || true == IsScsiDeviceBus(UdevDevice))
        {
            return true;
        }
    }
    return false;
}

eErrorCode GetStorageDevicePaths(std::vector<String>& DevicePaths, std::vector<String>& SysDevicePaths)
{
    struct udev *udevObject;
    struct udev_enumerate *enumerate;
    struct udev_list_entry *devices, *udevListEntry;
    struct udev_device *udevDevice;

    //! Create the udev object
    udevObject = udev_new();
    if (nullptr == udevObject)
    {
        //! ERROR: Can't create udev
        return(eErrorCode::Memory);
    }

    //! Create a list of the devices in the 'block' subsystem
    enumerate = udev_enumerate_new(udevObject);
    udev_enumerate_add_match_subsystem(enumerate, "block");

    udev_enumerate_scan_devices(enumerate);
    devices = udev_enumerate_get_list_entry(enumerate);

    udev_list_entry_foreach(udevListEntry, devices)
    {
        const char *devicePath;

        devicePath = udev_list_entry_get_name(udevListEntry);
        udevDevice = udev_device_new_from_syspath(udevObject, devicePath);
        String udeviceNode = udev_device_get_devnode(udevDevice);

        if (true == IsStorageDisk(udevDevice))
        {
            DevicePaths.push_back(udeviceNode);
            SysDevicePaths.push_back(devicePath);
        }

        udev_device_unref(udevDevice);
    }
    //! Free the enumerator object
    udev_enumerate_unref(enumerate);

    udev_unref(udevObject);

    return(eErrorCode::None);
}

eErrorCode GetAdapterBus(DeviceHandle& Handle, String SysDevicePath)
{
    struct udev *udevObject;
    struct udev_device *udevDevice;

    udevObject = udev_new();
    if (nullptr == udevObject)
    {
        return(eErrorCode::Memory);
    }
    udevDevice = udev_device_new_from_syspath(udevObject, SysDevicePath.c_str());

    if (true == IsAtaDeviceBus(udevDevice))
    {
        Handle.Bus = eBusType::Ata;
    }
    else if (true == IsScsiDeviceBus(udevDevice))
    {
        Handle.Bus = eBusType::Scsi;
    }
    else
    {
        //! Adapter Property is not Ata or Scsi
        return(eErrorCode::FormatNotSupported);
    }

    udev_device_unref(udevDevice);
    udev_unref(udevObject);

    return(eErrorCode::None);
}

eErrorCode GetStorageDeviceHandle(const String& DevicePath,String SysDevicePath, DeviceHandle& Handle)
{
    eErrorCode error = eErrorCode::None;
    Handle.Handle = open(DevicePath.c_str(), O_RDONLY|O_NONBLOCK);

    if (0 > Handle.Handle)
    {
        return(eErrorCode::Io);
    }

    error = GetAdapterBus(Handle, SysDevicePath);

    return(error);
}

eErrorCode GetStorageAdapterProperty(DeviceHandle Handle, sStorageAdapterProperty& AdapterProperty)
{
    if (eBusType::Ata == Handle.Bus)
    {
        AdapterProperty.AtaBus = true;
        AdapterProperty.ScsiBus = false;
    }
    else if (eBusType::Scsi == Handle.Bus)
    {
        AdapterProperty.ScsiBus = true;
        AdapterProperty.AtaBus = false;
    }

    //! TODO: Support for others adapter property.

    return(eErrorCode::None);
}

void CloseDeviceHandle(DeviceHandle& Handle)
{
    int closeHandleCode = close(Handle.Handle);
    if (-1 == closeHandleCode)
    {
        //! TODO: Catch error for not close Handle of Device
        //! throw std::runtime_error("Close DeviceHandle was not successful");
    }
}

}