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
#include <memory>
#include <Rpc.h>
#pragma comment(lib, "Rpcrt4.lib")

#include "Device.h"
#include "StorageUtility.h"

namespace vtStor
{

    eErrorCode GetStorageDevices(std::vector<std::shared_ptr<IDevice>>& Devices, eOnErrorBehavior OnErrorBehavior)
    {
        eErrorCode error = eErrorCode::None;

        sEnumerateDevicesCallback callBack;
        callBack.Data = (void*)&Devices;
        callBack.Function = [](void* Data, const HDEVINFO& DevInfoHandle, SP_DEVINFO_DATA& DevInfoData, SP_DEVICE_INTERFACE_DATA& DevInterfaceData, const PSP_INTERFACE_DEVICE_DETAIL_DATA& DevDetailData, U32 SizeOfDevDetailData, eErrorCode& ErrorCode)
        {
            std::vector<std::shared_ptr<vtStor::IDevice>>* devices = (std::vector<std::shared_ptr<vtStor::IDevice>>*)Data;
            devices->push_back(std::make_shared<cDevice>((SP_DEVINFO_DATA*)&DevInfoData, (SP_DEVICE_INTERFACE_DATA*)&DevInterfaceData, DevDetailData, SizeOfDevDetailData));
        };

        error = EnumerateDevices(callBack, &GUID_DEVINTERFACE_DISK, OnErrorBehavior);
        return(error);
    }

    eErrorCode GetStorageDevicePaths(std::vector<String>& Paths, eOnErrorBehavior OnErrorBehavior)
    {
        return(GetDevicePaths(Paths, &GUID_DEVINTERFACE_DISK, OnErrorBehavior));
    }

    eErrorCode GetDevicePaths(std::vector<String>& Paths, const GUID* InterfaceClassGUID, eOnErrorBehavior OnErrorBehavior)
    {
        eErrorCode error = eErrorCode::None;

        sEnumerateDevicesCallback callBack;
        callBack.Data = (void*)&Paths;
        callBack.Function = [](void* Data, const HDEVINFO& DevInfoHandle, SP_DEVINFO_DATA& DevInfoData, SP_DEVICE_INTERFACE_DATA& DevInterfaceData, const PSP_INTERFACE_DEVICE_DETAIL_DATA& DevDetailData, U32 SizeOfDevDetailData, eErrorCode& ErrorCode)
        {
            std::vector<String>* paths = (std::vector<String>*)Data;
            paths->push_back(DevDetailData->DevicePath);
        };

        error = EnumerateDevices(callBack, InterfaceClassGUID, OnErrorBehavior);
        return(error);
    }

    eErrorCode EnumerateDevices(sEnumerateDevicesCallback& Callback, const GUID* InterfaceClassGUID, eOnErrorBehavior OnErrorBehavior)
    {
        HDEVINFO devInfoHandle =
            SetupDiGetClassDevs
            (
                InterfaceClassGUID,
                NULL,
                NULL,
                DIGCF_PRESENT | DIGCF_DEVICEINTERFACE
                );
        if (INVALID_HANDLE_VALUE == devInfoHandle)
        {
            return(eErrorCode::Unknown);
        }

        DWORD error = 0;
        DWORD memberIndex = 0;
        while (true == true)
        {
            SP_DEVICE_INTERFACE_DATA devInterfaceData;
            devInterfaceData.cbSize = sizeof(devInterfaceData);
            if (SetupDiEnumDeviceInterfaces(devInfoHandle, NULL, InterfaceClassGUID, memberIndex++, &devInterfaceData) == FALSE)
            {
                error = GetLastError();
                if (ERROR_NO_MORE_ITEMS == error)
                {
                    break;
                }
                else
                {
                    SetupDiDestroyDeviceInfoList(devInfoHandle);
                    return(eErrorCode::Unknown);
                }
            }

            DWORD bufferSize = 0;
            SP_DEVINFO_DATA devInfoData;
            devInfoData.cbSize = sizeof(devInfoData);

            // Get buffer size
            if (SetupDiGetDeviceInterfaceDetail(devInfoHandle, &devInterfaceData, NULL, 0, &bufferSize, &devInfoData) == FALSE)
            {
                error = GetLastError();
                if (ERROR_INSUFFICIENT_BUFFER != error)
                {
                    if (eOnErrorBehavior::Continue == OnErrorBehavior) { continue; }
                    SetupDiDestroyDeviceInfoList(devInfoHandle);
                    return(eErrorCode::Unknown);
                }
            }

            PSP_INTERFACE_DEVICE_DETAIL_DATA pDevDetailData = (PSP_INTERFACE_DEVICE_DETAIL_DATA)HeapAlloc(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS, bufferSize);
            if (NULL == pDevDetailData)
            {
                if (eOnErrorBehavior::Continue == OnErrorBehavior) { continue; }
                SetupDiDestroyDeviceInfoList(devInfoHandle);
                return(eErrorCode::Memory);
            }
            pDevDetailData->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);

            if (SetupDiGetDeviceInterfaceDetail(devInfoHandle, &devInterfaceData, pDevDetailData, bufferSize, NULL, NULL) == FALSE)
            {
                error = GetLastError();
                if (ERROR_INSUFFICIENT_BUFFER != error)
                {
                    HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, pDevDetailData);
                    if (eOnErrorBehavior::Continue == OnErrorBehavior) { continue; }
                    SetupDiDestroyDeviceInfoList(devInfoHandle);
                    return(eErrorCode::Unknown);
                }
            }

            eErrorCode errorCode;
            errorCode = eErrorCode::Unknown;
            Callback.Function(Callback.Data, devInfoHandle, devInfoData, devInterfaceData, pDevDetailData, bufferSize, errorCode);

            HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, pDevDetailData);
        }

        SetupDiDestroyDeviceInfoList(devInfoHandle);

        return(eErrorCode::None);
    }

    eErrorCode GetStorageAdapterProperty(const DeviceHandle& Handle, sStorageAdapterProperty& AdapterProperty)
    {
        STORAGE_DESCRIPTOR_HEADER storageDescHeader;

        STORAGE_PROPERTY_QUERY StorageProperty;
        StorageProperty.PropertyId = StorageAdapterProperty;
        StorageProperty.QueryType = PropertyStandardQuery;

        DWORD bytesReturned;
        DWORD ret =
            DeviceIoControl(
                Handle.Handle,
                IOCTL_STORAGE_QUERY_PROPERTY,
                &StorageProperty,
                sizeof(STORAGE_PROPERTY_QUERY),
                &storageDescHeader,
                sizeof(STORAGE_DESCRIPTOR_HEADER),
                &bytesReturned,
                NULL
                );
        if (0 == ret)
        {
            return(eErrorCode::Io);
        }

        if (0 == storageDescHeader.Size)
        {
            return(eErrorCode::Io);   //TODO: replace with more descriptive error
        }

        PSTORAGE_ADAPTER_DESCRIPTOR pstorageAdapterDesc = NULL;
        pstorageAdapterDesc = (PSTORAGE_ADAPTER_DESCRIPTOR)HeapAlloc(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS, storageDescHeader.Size);

        ret =
            DeviceIoControl(
                Handle.Handle,
                IOCTL_STORAGE_QUERY_PROPERTY,
                &StorageProperty,
                sizeof(STORAGE_PROPERTY_QUERY),
                pstorageAdapterDesc,
                storageDescHeader.Size,
                &bytesReturned,
                NULL
                );
        if (0 == ret)
        {
            HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, pstorageAdapterDesc);
            return(eErrorCode::Io);
        }

        AdapterProperty.BusType = pstorageAdapterDesc->BusType;
        //iAdapterProperty.SrbType = pstorageAdapterDesc->SrbType;  TODO check this
        AdapterProperty.AlignmentMask = pstorageAdapterDesc->AlignmentMask;

        HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, pstorageAdapterDesc);

        return(eErrorCode::None);
    }

    eErrorCode GetPhysicalDiskNumber(const DeviceHandle& Handle, U32& PhysicalDiskNumber)
    {
        STORAGE_DEVICE_NUMBER storageDevice = { 0 };
        DWORD bytesReturned;
        DWORD ret =
            DeviceIoControl(
                Handle.Handle,
                IOCTL_STORAGE_GET_DEVICE_NUMBER,
                NULL,
                0,
                &storageDevice,
                sizeof(storageDevice),
                &bytesReturned,
                NULL
                );
        if (0 == ret)
        {
            return(eErrorCode::Io);
        }

        PhysicalDiskNumber = storageDevice.DeviceNumber;
        return(eErrorCode::None);
    }

    void CloseDeviceHandle(DeviceHandle& Handle)
    {
        if (FALSE == CloseHandle(Handle.Handle))
        {
            //! TODO
            //fprintf(stderr, "\nCloseDeviceHandle was not successful. Error Code: %d", GetLastError());
        }
        Handle.Handle = INVALID_HANDLE_VALUE;
        Handle.Bus = eBusType::Undefined;
    }

    bool IsAtaDeviceBus(const sStorageAdapterProperty& StorageDeviceProperty)
    {
        switch (StorageDeviceProperty.BusType)
        {
        case BusTypeRAID:
        case BusTypeAta:
        case BusTypeSata:
        {
            return(true);
        } break;
        default:
        {
            return(false);
        } break;
        }
    }

    bool IsScsiDeviceBus(const sStorageAdapterProperty& StorageDeviceProperty)
    {
        switch (StorageDeviceProperty.BusType)
        {
        case BusTypeScsi:
        case BusTypeUsb:
        case BusTypeiScsi:
        {
            return(true);
        } break;
        default:
        {
            return(false);
        } break;
        }
    }

    U64 WaitForAsynCommands(Handle* EventHandlesArray, U8& NumberOfEvents)
    {
        // See more WaitForMultipleObjects() on msdn
        // INFINITE: time-out
        // FALSE: the function returns when the state of any one of the objects is set to signaled
        U64 dwReturn = WaitForMultipleObjects(NumberOfEvents, EventHandlesArray,
            FALSE, INFINITE);
        U64 eventId = dwReturn - WAIT_OBJECT_0;

        return(eventId);
    }

    bool RemoveEventSignaled(Handle Events[], U64 Size, U64 Index)
    {
        if ((0 > Index) || (Size <= Index))
        {
            return(false);
        }

        for (U64 i = Index + 1; i < Size; ++i)
        {
            Events[i - 1] = Events[i];
        }

        return(true);
    }

    void CreateUUID(UUID& Uuid)
    {
        UuidCreate(&Uuid);
    }

    bool CompareUUID(const UUID& Id1, const UUID& Id2)
    {
        if (IsEqualGUID(Id1, Id2))
        {
            return true;
        }
        return false;
    }

}