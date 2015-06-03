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
#include "vtStorAta.h"
#include "CommandDescriptorUtility.h"

#include "CommandHandlerAta.h"
#include "Buffer.h"
#include "BufferFormatter.h"

#include "vtStorProtocol/AtaProtocolEssense1.h"

namespace vtStor
{

cCommandHandlerAta::cCommandHandlerAta( std::shared_ptr<Protocol::cProtocolInterface> Protocol ):
    cCommandHandlerInterface( Protocol )
{
}


cCommandHandlerAta::~cCommandHandlerAta()
{
}

eErrorCode cCommandHandlerAta::IssueCommand( std::shared_ptr<const cBufferInterface> CommandDescriptor, std::shared_ptr<cBufferInterface> Data )
{
    eErrorCode errorCode = eErrorCode::None;

    //TODO: check command descriptor version and use the propriate parsing

    Ata::cCommandDescriptor1 commandDescriptor( CommandDescriptor );
    const StorageUtility::Ata::uCommandFields& commandFields = commandDescriptor.GetCommandFields();

    std::shared_ptr<cBufferInterface> buffer = std::make_shared<cBuffer>( cBufferFormatter::HEADER_SIZE_IN_BYTES + vtStor::Protocol::cEssenseAta1::SIZE_IN_BYTES );
    Protocol::cEssenseAta1 essense( buffer );

    StorageUtility::Ata::sCommandCharacteristic& commandCharacteristics = essense.GetCommandCharacteristics();
    commandCharacteristics = commandDescriptor.GetCommandCharacteristics();

    StorageUtility::Ata::uTaskFileRegister& taskFile = essense.GetTaskFile();
    StorageUtility::Ata::uTaskFileRegister& taskFileExt = essense.GetTaskFileExt();
    PrepareTaskFileRegisters( commandCharacteristics, commandFields, taskFile, taskFileExt );

    errorCode = m_Protocol->IssueCommand( buffer, Data );

    return(errorCode);
}

void cCommandHandlerAta::PrepareTaskFileRegisters( const StorageUtility::Ata::sCommandCharacteristic& AtaCommandCharacteristics, const StorageUtility::Ata::uCommandFields& CommandFields, StorageUtility::Ata::uTaskFileRegister& TaskFileRegister, StorageUtility::Ata::uTaskFileRegister& TaskFileRegisterExt )
{
    // If 28-bit command:
    if (StorageUtility::Ata::eFieldFormatting::COMMAND_28_BIT == AtaCommandCharacteristics.FieldFormatting)
    {
        TaskFileRegister.InputRegister.Feature = (U8)CommandFields.InputFields.Feature;
        TaskFileRegister.InputRegister.Count = (U8)CommandFields.InputFields.Count;
        TaskFileRegister.InputRegister.LbaLow = (U8)((CommandFields.InputFields.Lba) & 0x000000FF);
        TaskFileRegister.InputRegister.LbaMid = (U8)((CommandFields.InputFields.Lba >> 8) & 0x000000FF);
        TaskFileRegister.InputRegister.LbaHigh = (U8)((CommandFields.InputFields.Lba >> 16) & 0x000000FF);
        TaskFileRegister.InputRegister.Device = (U8)CommandFields.InputFields.Device;
        TaskFileRegister.InputRegister.Command = (U8)CommandFields.InputFields.Command;
        TaskFileRegister.InputRegister.Reserved = (U8)0;

        // If data access command:
        if (StorageUtility::Ata::eDataAccess::NONE != AtaCommandCharacteristics.DataAccess)
        {
            // Initialize the last 4 bits of the 28 bit LBA
            U8 last4BitInLBA;
            last4BitInLBA = (U8)((CommandFields.InputFields.Lba >> 24) & 0x0000000F);

            // 0x0E is used instead of 0x40 to be safe and support legacy systems
            if (false == CommandFields.InputFields.ChsMode)
            {
                TaskFileRegister.InputRegister.Device = (U8)(StorageUtility::Ata::DEVICE_REGISTER_DEFAULT | last4BitInLBA);
            }
            // Support for CHS mode
            else
            {
                TaskFileRegister.InputRegister.Device = (U8)(StorageUtility::Ata::DEVICE_REGISTER_CHSMODE_DEFAULT | last4BitInLBA);
            }
        }
    }
    // Otherwise 48-bit command:
    else
    {
        TaskFileRegister.InputRegister.Feature = (U8)CommandFields.InputFields.Feature;
        TaskFileRegister.InputRegister.Count = (U8)CommandFields.InputFields.Count;
        TaskFileRegister.InputRegister.LbaLow = (U8)((CommandFields.InputFields.Lba) & 0x000000FF);
        TaskFileRegister.InputRegister.LbaMid = (U8)((CommandFields.InputFields.Lba >> 8) & 0x000000FF);
        TaskFileRegister.InputRegister.LbaHigh = (U8)((CommandFields.InputFields.Lba >> 16) & 0x000000FF);
        TaskFileRegister.InputRegister.Device = (U8)CommandFields.InputFields.Device;
        TaskFileRegister.InputRegister.Command = (U8)CommandFields.InputFields.Command;
        TaskFileRegister.InputRegister.Reserved = (U8)0;

        TaskFileRegisterExt.InputRegister.Feature = (U8)((CommandFields.InputFields.Feature >> 8) & 0x00FF);
        TaskFileRegisterExt.InputRegister.Count = (U8)((CommandFields.InputFields.Count >> 8) & 0x00FF);
        TaskFileRegisterExt.InputRegister.LbaLow = (U8)((CommandFields.InputFields.Lba >> 24) & 0x000000FF);
        TaskFileRegisterExt.InputRegister.LbaMid = (U8)((CommandFields.InputFields.Lba >> 32) & 0x000000FF);
        TaskFileRegisterExt.InputRegister.LbaHigh = (U8)((CommandFields.InputFields.Lba >> 40) & 0x000000FF);
        TaskFileRegisterExt.InputRegister.Device = (U8)CommandFields.InputFields.Device;
        TaskFileRegisterExt.InputRegister.Command = (U8)CommandFields.InputFields.Command;
        TaskFileRegisterExt.InputRegister.Reserved = (U8)0;

        // If data access command:
        if (StorageUtility::Ata::eDataAccess::NONE != AtaCommandCharacteristics.DataAccess)
        {
            if (false == CommandFields.InputFields.ChsMode)
            {
                // 0x0E is used instead of 0x40 to be safe and support legacy systems
                TaskFileRegister.InputRegister.Device = (U8)(StorageUtility::Ata::DEVICE_REGISTER_DEFAULT | CommandFields.InputFields.Device);
                TaskFileRegisterExt.InputRegister.Device = (U8)(StorageUtility::Ata::DEVICE_REGISTER_DEFAULT | CommandFields.InputFields.Device);
            }
            // Support for CHS mode
            else
            {
                U8 last4BitInLBA;
                last4BitInLBA = (U8)((CommandFields.InputFields.Lba >> 24) & 0x0000000F);
                TaskFileRegister.InputRegister.Device = (U8)(StorageUtility::Ata::DEVICE_REGISTER_CHSMODE_DEFAULT | last4BitInLBA);
            }
        }
    }
}

}