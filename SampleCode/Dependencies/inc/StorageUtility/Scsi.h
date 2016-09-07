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
            extern const U32 VTSTOR_API SCSI_SECTOR_SIZE_IN_BYTES;

#pragma pack(push, cdb, 1)

            struct sInputFields_Command6
            {
                U8  OpCode;
                U8  Service;
                U32 Lba;
                U16 Length;
                U8  Control;
            };

            struct sInputFields_Command10
            {
                U8  OpCode;
                U8  Service;
                U32 Lba;
                U16 Length;
                U8  Control;
                U8  MiscCdb;
            };

            struct sInputFields_Command12
            {
                U8  OpCode;
                U8  Service;
                U32 Lba;
                U32 Length;
                U8  Control;
                U8  MiscCdb;
            };

            struct sInputFields_Command16
            {
                U8  OpCode;
                U8  Service;
                U64 Lba;
                U32 Length;
                U8  Control;
                U8  MiscCdb;
            };

            struct sInputFields_AtaPassThrough16
            {
                U8  OpCode;
                U8  Extend;
                U8  Protocol;
                U8  MultipleCount;
                U8  TLength;
                U8  ByteBlock;
                U8  TDir;
                U8  CkCond;
                U8  Offline;
                U32 SectorCount;
                U16 Features;
                U64 Lba;
                U8  Device;
                U8  Command;
                U8  Control;
            };

            union uCommandInputFields
            {
                sInputFields_Command6            Command6;
                sInputFields_Command10           Command10;
                sInputFields_Command12           Command12;
                sInputFields_Command16           Command16;
                sInputFields_AtaPassThrough16    AtaPassThrough16;
            };

            union uCommandFields
            {
                uCommandInputFields InputFields;

                // TODO: Add command output fields
            };

            struct sCdb_16
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

            union uCdb_16
            {
                sCdb_16 Registers;
                U8 Bytes[16];
            };

            union uCdb
            {
                uCdb_16 Cdb_16;

                // TODO: Add cdb 32 bytes
            };

#pragma pack(pop, cdb)

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
                COMMAND_16,
                ATAPASSTHROUGH_16,
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