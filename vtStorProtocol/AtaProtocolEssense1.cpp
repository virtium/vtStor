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

#include "AtaProtocolEssense1.h"

namespace vtStor
{
namespace Protocol
{
const size_t cEssenseAta1::COMMAND_CHARACTERISTICS_OFFSET   = cBufferFormatter::DATA_OFFSET;
const size_t cEssenseAta1::TASK_FILE_OFFSET                 = cEssenseAta1::COMMAND_CHARACTERISTICS_OFFSET + sizeof( StorageUtility::Ata::sCommandCharacteristic );
const size_t cEssenseAta1::TASK_FILE_EXT_OFFSET             = cEssenseAta1::TASK_FILE_OFFSET + sizeof( StorageUtility::Ata::uTaskFileRegister );

const size_t cEssenseAta1::SIZE_IN_BYTES    = sizeof( StorageUtility::Ata::sCommandCharacteristic )
                                            + sizeof( StorageUtility::Ata::uTaskFileRegister )
                                            + sizeof( StorageUtility::Ata::uTaskFileRegister );

cEssenseAta1::cEssenseAta1( std::shared_ptr<cBufferInterface> Buffer ) :
    cBufferFormatter( Buffer )
{
    Header& header = GetHeader();
    header.Format = 1;
}
            
cEssenseAta1::cEssenseAta1( std::shared_ptr<const cBufferInterface> Buffer ) :
    cBufferFormatter( Buffer )
{

}

StorageUtility::Ata::sCommandCharacteristic& cEssenseAta1::GetCommandCharacteristics()
{
    U8* buffer = m_Buffer->ToDataBuffer();
    return( (StorageUtility::Ata::sCommandCharacteristic&)buffer[ COMMAND_CHARACTERISTICS_OFFSET ] );

}
        
const StorageUtility::Ata::sCommandCharacteristic& cEssenseAta1::GetCommandCharacteristics() const
{
    U8* buffer = m_Buffer->ToDataBuffer();
    return( (StorageUtility::Ata::sCommandCharacteristic&)buffer[ COMMAND_CHARACTERISTICS_OFFSET ] );
}

StorageUtility::Ata::uTaskFileRegister& cEssenseAta1::GetTaskFile()
{
    U8* buffer = m_Buffer->ToDataBuffer();
    return( (StorageUtility::Ata::uTaskFileRegister&)buffer[ TASK_FILE_OFFSET ] );
}

const StorageUtility::Ata::uTaskFileRegister& cEssenseAta1::GetTaskFile() const
{
    U8* buffer = m_Buffer->ToDataBuffer();
    return( (StorageUtility::Ata::uTaskFileRegister&)buffer[ TASK_FILE_OFFSET ] );
}

StorageUtility::Ata::uTaskFileRegister& cEssenseAta1::GetTaskFileExt()
{
    U8* buffer = m_Buffer->ToDataBuffer();
    return( (StorageUtility::Ata::uTaskFileRegister&)buffer[ TASK_FILE_EXT_OFFSET ] );
}
        
const StorageUtility::Ata::uTaskFileRegister& cEssenseAta1::GetTaskFileExt() const
{
    U8* buffer = m_Buffer->ToDataBuffer();
    return( (StorageUtility::Ata::uTaskFileRegister&)buffer[ TASK_FILE_EXT_OFFSET ] );
}
            
}
}

