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
#ifndef __vtStorAta_h__
#define __vtStorAta_h__
#pragma once

#include "BasicTypes.h"
#include "vtStorAtaPlatformDefines.h"

namespace vtStor
{

class VT_STOR_ATA_API cAta
{
public:
    static const U32 SECTOR_SIZE_IN_BYTES;

public:
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

    enum eDeviceReadyFlag
    {
        DEVICE_READY_REQUIRED,
        DEVICE_READY_NOT_REQUIRED
    };

    enum eDataAccess
    {
        NONE,
        READ_FROM_DEVICE,
        WRITE_TO_DEVICE
    };

    enum eFieldFormatting
    {
        COMMAND_28_BIT,
        COMMAND_48_BIT
    };

    enum eTransferMode
    {
        DMA_PROTOCOL,
        PIO_PROTOCOL
    };

    enum eMultipleMode
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

public:
    cAta() = delete;

public:
    static U32 s_DefaultCommandHandlerCommandType;
};


}

#endif