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

#include "Buffer.h"
#include "TrimBufferFormatter.h"

namespace vtStor
{
    namespace Ata
    {
        cTrimBufferFormatter::cTrimBufferFormatter()
        {
        }

        cTrimBufferFormatter::~cTrimBufferFormatter()
        {
        }

        void cTrimBufferFormatter::AddLbaRangeEntryToBuffer(std::shared_ptr<IBuffer>& DataBuffer, U64 StartLba, U16 SectorCount, U32 LbaRangeEntryOffset)
        {
            U32 byteOffset = LbaRangeEntryOffset * LBA_RANGE_ENTRY_SIZE_IN_BYTE;
            for (U32 i = 0; i < LBA_SIZE_IN_BYTE; ++i)
            {
                DataBuffer->SetByteAt(byteOffset + i, 0xFF & (StartLba >> (i * NUMBER_OF_BITS_OF_A_BYTE)));
            }

            for (U32 i = 0; i < SECTOR_COUNT_SIZE_IN_BYTE; ++i)
            {
                DataBuffer->SetByteAt(byteOffset + i, 0xFF & (SectorCount >> (i * NUMBER_OF_BITS_OF_A_BYTE)));
            }
        }

        void cTrimBufferFormatter::FillBufferWithLbaRangeEntries(std::shared_ptr<IBuffer>& DataBuffer, const std::vector<StorageUtility::Ata::sLbaRangeEntry>& LbaRangeEntries)
        {
            DataBuffer->Memset(0);
            for (U32 i = 0; i < LbaRangeEntries.size(); ++i)
            {
                U64 currentLba = LbaRangeEntries[i].Lba;
                U16 currentSectorCount = LbaRangeEntries[i].SectorCount;

                AddLbaRangeEntryToBuffer(DataBuffer, currentLba, currentSectorCount, i);
            }
        }

        U32 cTrimBufferFormatter::CalculateSectorCountInput(const std::vector<StorageUtility::Ata::sLbaRangeEntry>& LBARangeEntries)
        {
            return ((U32)(LBARangeEntries.size() / MAX_LBA_RANGE_ENTRIES_PER_512_BYTE_BLOCK) + 1);
        }
    }
}