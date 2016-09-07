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

#include "Ata.h"
#include "AsynIoCommandExtensions.h"

void cAsynIoCommandExtensions_GetAsynIoCommandExtensions(std::unique_ptr<vtStor::IAsynIoCommandExtensions>& asynIoCommandExtensions)
{
    asynIoCommandExtensions = std::unique_ptr<vtStor::IAsynIoCommandExtensions>(new vtStor::AsynIo::cAsynIoCommandExtensions());
}

namespace vtStor
{
    namespace AsynIo
    {
        cAsynIoCommandExtensions::cAsynIoCommandExtensions()
        {
        }

        cAsynIoCommandExtensions::~cAsynIoCommandExtensions()
        {
        }

        eErrorCode cAsynIoCommandExtensions::IssueCommand_ReadAsynIo(std::shared_ptr<vtStor::IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Count, U64 Lba, std::shared_ptr<OverlappedIo> OverlappedPtr)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cAsynIoProtocolEssense::SIZE_IN_BYTES);
            cAsynIoProtocolEssense commandDescriptorAsynIo = cAsynIoProtocolEssense::Writer(commandDescriptor);

            sAsynchronousIoInputs& commandFields = commandDescriptorAsynIo.GetCommandFields();
            commandFields.OverlappedPtr = OverlappedPtr.get();
            commandFields.Command = READ_ASYNIO;
            commandFields.m_DataTransferredInSectors = Count * StorageUtility::Ata::SECTOR_SIZE_IN_BYTES;
            commandFields.OverlappedPtr->Offset = (U32)(Lba * StorageUtility::Ata::SECTOR_SIZE_IN_BYTES);
            commandFields.OverlappedPtr->OffsetHigh = (U32)(Lba * StorageUtility::Ata::SECTOR_SIZE_IN_BYTES >> 32);

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }

        eErrorCode cAsynIoCommandExtensions::IssueCommand_WriteAsynIo(std::shared_ptr<vtStor::IDrive> Drive, U32 CommandType, std::shared_ptr<IBuffer> Data, U32 Count, U64 Lba, std::shared_ptr<OverlappedIo> OverlappedPtr)
        {
            std::shared_ptr<IBuffer> commandDescriptor = std::make_shared<cBuffer>(cAsynIoProtocolEssense::SIZE_IN_BYTES);
            cAsynIoProtocolEssense commandDescriptorAsynIo = cAsynIoProtocolEssense::Writer(commandDescriptor);

            sAsynchronousIoInputs& commandFields = commandDescriptorAsynIo.GetCommandFields();
            commandFields.OverlappedPtr = OverlappedPtr.get();
            commandFields.Command = WRITE_ASYNIO;
            commandFields.m_DataTransferredInSectors = Count * StorageUtility::Ata::SECTOR_SIZE_IN_BYTES;
            commandFields.OverlappedPtr->Offset = (U32)(Lba * StorageUtility::Ata::SECTOR_SIZE_IN_BYTES);
            commandFields.OverlappedPtr->OffsetHigh = (U32)(Lba * StorageUtility::Ata::SECTOR_SIZE_IN_BYTES >> 32);

            return(Drive->IssueCommand(CommandType, commandDescriptor, Data));
        }
    }
}