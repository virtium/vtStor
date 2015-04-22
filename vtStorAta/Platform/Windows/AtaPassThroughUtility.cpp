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
#include "AtaPassThroughUtility.h"

namespace vtStor
{
namespace AtaPassThroughUtility
{

void InitializeFlags(ATA_PASS_THROUGH_DIRECT& AtaPassThrough, const cAta::sCommandCharacteristic& AtaCommandCharacteristic)
{
    // Clear all flags
    AtaPassThrough.AtaFlags = 0;

    if (cAta::eDeviceReadyFlag::DEVICE_READY_REQUIRED == AtaCommandCharacteristic.DeviceReadyFlag)
    {
        AtaPassThrough.AtaFlags |= ATA_FLAGS_DRDY_REQUIRED;
    }

    switch (AtaCommandCharacteristic.DataAccess)
    {
    case cAta::eDataAccess::READ_FROM_DEVICE:
    {
        AtaPassThrough.AtaFlags |= ATA_FLAGS_DATA_IN;
    } break;
    case cAta::eDataAccess::WRITE_TO_DEVICE:
    {
        AtaPassThrough.AtaFlags |= ATA_FLAGS_DATA_OUT;
    } break;
    }

    if (cAta::eFieldFormatting::COMMAND_48_BIT == AtaCommandCharacteristic.FieldFormatting)
    {
        AtaPassThrough.AtaFlags |= ATA_FLAGS_48BIT_COMMAND;
    }

    if (cAta::eTransferMode::DMA_PROTOCOL == AtaCommandCharacteristic.TransferMode)
    {
        AtaPassThrough.AtaFlags |= ATA_FLAGS_USE_DMA;
    }

    if (cAta::eMultipleMode::NOT_MULTIPLE_COMMAND == AtaCommandCharacteristic.MultipleMode)
    {
        AtaPassThrough.AtaFlags |= ATA_FLAGS_NO_MULTIPLE;
    }
}

}
}