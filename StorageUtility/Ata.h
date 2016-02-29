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
#ifndef __vtStorStorageUtilityAta_h__
#define __vtStorStorageutilityAta_h__
#pragma once

#include "BasicTypes.h"

namespace vtStor
{
    namespace StorageUtility
    {
        namespace Ata
        {
            extern const U32 VTSTOR_API SECTOR_SIZE_IN_BYTES;
            extern const U8  VTSTOR_API DEVICE_REGISTER_DEFAULT;
            extern const U8  VTSTOR_API DEVICE_REGISTER_CHSMODE_DEFAULT;

            struct sCommandInputFields
            {
                U16  Feature;
                U32  Count;
                U64  Lba;
                U8   Device;
                U8   Command;
                bool ChsMode;
            };

            struct sCommandOutputFields
            {
                U16 Error;
                U32 Count;
                U64 Lba;
                U8  Device;
                U8  Status;
            };

            union uCommandFields
            {
                sCommandInputFields  InputFields;
                sCommandInputFields OutputFields;
            };

            enum class eDeviceReadyFlag
            {
                DEVICE_READY_REQUIRED,
                DEVICE_READY_NOT_REQUIRED
            };

            enum class eDataAccess
            {
                NONE,
                READ_FROM_DEVICE,
                WRITE_TO_DEVICE
            };

            enum class eFieldFormatting
            {
                COMMAND_28_BIT,
                COMMAND_48_BIT
            };

            enum class eTransferMode
            {
                DMA_PROTOCOL,
                PIO_PROTOCOL
            };

            enum class eMultipleMode
            {
                MULTIPLE_COMMAND,
                NOT_MULTIPLE_COMMAND
            };

            struct sCommandCharacteristic
            {
                eDeviceReadyFlag     DeviceReadyFlag;
                eDataAccess          DataAccess;
                eFieldFormatting     FieldFormatting;
                eTransferMode        TransferMode;
                eMultipleMode        MultipleMode;
                U32                  DataTransferLengthInBytes;
            };

            struct sTaskFileInputRegister
            {
                U8 Feature;
                U8 Count;
                U8 LbaLow;
                U8 LbaMid;
                U8 LbaHigh;
                U8 Device;
                U8 Command;
                U8 Reserved;
            };

            struct sTaskFileOutputRegister
            {
                U8 Error;
                U8 Count;
                U8 LbaLow;
                U8 LbaMid;
                U8 LbaHigh;
                U8 Device;
                U8 Status;
                U8 Reserved;
            };

            union uTaskFileRegister
            {
                sTaskFileInputRegister  InputRegister;
                sTaskFileOutputRegister OutputRegister;
            };

            struct sLbaRangeEntry
            {
                U64 Lba;
                U16 SectorCount;
            };
        }
    }
}

#endif