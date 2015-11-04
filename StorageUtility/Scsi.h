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
            extern const U32 SCSI_SECTOR_SIZE_IN_BYTES;
                                    
            struct sCdbFields
            {
                U8  OpCode;
                U8  Service;
                U64 Lba;
                U32 TransferLen;
                U8  ParameterLen;
                U32 AllocationLen;
                U8  Group;
                U8  Control;
            };

            struct sCdbRegisters
            {
                U8 Register0;
                U8 Register1;
                U8 Register2;
                U8 Register3;
                U8 Register4;
                U8 Register5;
                U8 Register6;
                U8 Register7;
                U8 Register8;
                U8 Register9;
                U8 Register10;
                U8 Register11;
                U8 Register12;
                U8 Register13;
                U8 Register14;
                U8 Register15;
            };

            enum class eDataAccess
            {
                NONE,
                READ_FROM_DEVICE,
                WRITE_TO_DEVICE
            };

            enum class eFieldFormatting
            {
                COMMAND_6,
                COMMAND_10,
                COMMAND_12,
                COMMAND_16
            };
                        
            struct sCommandCharacteristics
            {
                eDataAccess          DataAccess;
                eFieldFormatting     FieldFormatting;
                U32                  DataTransferLengthInBytes;
            };
        }
    }
}

#endif