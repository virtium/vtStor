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
#include "vtStorScsi.h"
#include "ScsiCommandDescriptor.h"

#include "CommandHandlerScsi.h"
#include "Buffer.h"
#include "BufferFormatter.h"

#include "vtStorScsiProtocol/ScsiProtocolEssense1.h"

namespace vtStor
{

    cCommandHandlerScsi::cCommandHandlerScsi(std::shared_ptr<Protocol::cProtocolInterface> Protocol) :
    cCommandHandlerInterface( Protocol )
{
}


    cCommandHandlerScsi::~cCommandHandlerScsi()
{
}

    eErrorCode cCommandHandlerScsi::IssueCommand(std::shared_ptr<const cBufferInterface> CommandDescriptor, std::shared_ptr<cBufferInterface> Data)
{
    eErrorCode errorCode = eErrorCode::None;

    cBufferFormatter bufferFormatter = cBufferFormatter::Reader(CommandDescriptor);
    switch (bufferFormatter.GetHeader().Format)
    {
        case 1:
        {
            Scsi::cScsiCommandDescriptor commandDescriptor = Scsi::cScsiCommandDescriptor::Reader(CommandDescriptor);
            const StorageUtility::Scsi::sCommandFields& commandFields = commandDescriptor.GetCommandFields();

            std::shared_ptr<cBufferInterface> buffer = std::make_shared<cBuffer>(vtStor::Protocol::cEssenseScsi1::SIZE_IN_BYTES);
            Protocol::cEssenseScsi1 essense = Protocol::cEssenseScsi1::Writer(buffer);
    
            DeviceHandle& deviceHandle = essense.GetDeviceHandle();
            deviceHandle = commandDescriptor.GetDeviceHandle();

            StorageUtility::Scsi::sCommandCharacteristics& commandCharacteristics = essense.GetCommandCharacteristics();
            commandCharacteristics = commandDescriptor.GetCommandCharacteristics();

            StorageUtility::Scsi::sTaskFileRegister& taskFileRegister = essense.GetTaskFileRegister();
            PrepareTaskFileRegister(commandCharacteristics, commandFields, taskFileRegister);

            errorCode = m_Protocol->IssueCommand( buffer, Data );

        } break;

        default:
        {
            errorCode = eErrorCode::FormatNotSupported;
        } break;
    }

    return(errorCode);
}

    void cCommandHandlerScsi::PrepareTaskFileRegister(const StorageUtility::Scsi::sCommandCharacteristics& ScsiCommandCharacteristics, const StorageUtility::Scsi::sCommandFields& CommandFields, StorageUtility::Scsi::sTaskFileRegister& TaskFileRegister)
    {        
        // If command 12:
        if (StorageUtility::Scsi::eFieldFormatting::COMMAND_12 == ScsiCommandCharacteristics.FieldFormatting)
        {
            TaskFileRegister.Feature = CommandFields.InputFields.Feature;
            TaskFileRegister.Count = CommandFields.InputFields.Count;
            TaskFileRegister.LbaLow = ((CommandFields.InputFields.Lba) & 0x000000FF);
            TaskFileRegister.LbaMid = ((CommandFields.InputFields.Lba >> 8) & 0x000000FF);
            TaskFileRegister.LbaHigh = ((CommandFields.InputFields.Lba >> 16) & 0x000000FF);
            TaskFileRegister.Device = CommandFields.InputFields.Device;
            TaskFileRegister.Command = CommandFields.InputFields.Command;
            TaskFileRegister.SubCommand = CommandFields.InputFields.SubCommand;
            TaskFileRegister.Reserved = 0;
                        
        }
        // Otherwise command 16:
        else
        {
            TaskFileRegister.Feature = CommandFields.InputFields.Feature;
            TaskFileRegister.Count = CommandFields.InputFields.Count;
            TaskFileRegister.LbaLow = ((CommandFields.InputFields.Lba) & 0x0000FFFF);
            TaskFileRegister.LbaMid = ((CommandFields.InputFields.Lba >> 16) & 0x0000FFFF);
            TaskFileRegister.LbaHigh = ((CommandFields.InputFields.Lba >> 32) & 0x0000FFFF);
            TaskFileRegister.Device = CommandFields.InputFields.Device;
            TaskFileRegister.Command = CommandFields.InputFields.Command;
            TaskFileRegister.SubCommand = CommandFields.InputFields.SubCommand;
            TaskFileRegister.Reserved = 0;
            
        }
    }
}

VT_STOR_SCSI_API void vtStorCommandHandlerScsiInit( std::shared_ptr<vtStor::cCommandHandlerInterface>& CommandHandler, std::shared_ptr<vtStor::Protocol::cProtocolInterface> Protocol )
{
    CommandHandler = std::make_shared<vtStor::cCommandHandlerScsi>( Protocol );
}