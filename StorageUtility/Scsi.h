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
#ifndef __vtStorStorageUtilityScsi_h__
#define __vtStorStorageutilityScsi_h__
#pragma once

#include "BasicTypes.h"

namespace vtStor
{
    namespace StorageUtility
    {
        namespace Scsi
        {
            extern const U32 SECTOR_SIZE_IN_BYTES;

            extern const U8  DEVICE_REGISTER_DEFAULT;
            extern const U8  DEVICE_REGISTER_CHSMODE_DEFAULT;

            extern const U8  CDB_REGISTER_SIZE;
            extern const U8  SCSI_COMMAND_ATA_PASS_THROUGH_12;
            extern const U8  SCSI_COMMAND_ATA_PASS_THROUGH_16;
            

            struct sCommandFields
            {
                U16  Feature;
                U32  Count;
                U64  Lba;
                U8   Device;
                U8   Command;
                U8   SubCommand;
                bool ChsMode;
            };

            using cdbRegister = U8 [16];

            enum eDataAccess
            {
                NONE,
                READ_FROM_DEVICE,
                WRITE_TO_DEVICE
            };

            enum eTransferMode
            {
                DMA_PROTOCOL,
                PIO_PROTOCOL
            };

            enum eFieldFormatting
            {
                COMMAND_12,
                COMMAND_16
            };
                        
            struct sCommandCharacteristics
            {
                //eDeviceReadyFlag     DeviceReadyFlag;
                eDataAccess          DataAccess;
                eFieldFormatting     FieldFormatting;
                eTransferMode        TransferMode;
                //eMultipleMode        MultipleMode;
                U32                  DataTransferLengthInBytes;
            };
        }
    }
}

#endif