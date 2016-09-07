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

#include <stdlib.h>
#include <ctime> 

#include "ATestUtility.h"
#include "DriveEnumerator.h"
#include "DriveEnumeratorAta.h"
#include "DriveEnumeratorScsi.h"
#include "IDriveManager.h"

namespace vtStorATest
{
    // Constants utility
    const vtStor::U32 WORD_SIZE_IN_BYTE = 2;
    const vtStor::U32 MODEL_NUMBER_SIZE_IN_BYTE = 40;
    const vtStor::U32 MODEL_NUMBER_ID_WORD = 27;

    vtStor::Vector_Drives ATestUtility::ScanForDrives()
    {
        std::unique_ptr<vtStor::IDriveManager> driveManager;
        std::shared_ptr<vtStor::IDriveEnumerator> driveEnumerator;

        // Enumerate drive
        cDriveManager_GetDriveManager(driveManager);
        driveEnumerator = std::make_shared<vtStor::cDriveEnumerator>();
        driveEnumerator = std::make_shared<vtStor::cDriveEnumeratorAta>(driveEnumerator);
        driveEnumerator = std::make_shared<vtStor::cDriveEnumeratorScsi>(driveEnumerator);
        driveManager->RegisterDriveEnumerator(driveEnumerator);
        driveManager->EnumerateDrives(vtStor::eScanForHardwareChanges::No);

        // Get all the drives enumerated
        return driveManager->GetDrives();
    }

    vtStor::String ATestUtility::GetModelString(std::shared_ptr<vtStor::IBuffer>& IdentifyBuffer)
    {
        vtStor::String modelNumber;
        vtStor::U32 byteOffset = WORD_SIZE_IN_BYTE * MODEL_NUMBER_ID_WORD;
        for (vtStor::U32 i = 0; i < MODEL_NUMBER_SIZE_IN_BYTE; i += 2)
        {
            modelNumber += ((vtStor::U8)IdentifyBuffer->GetByteAt(byteOffset + 1));
            modelNumber += ((vtStor::U8)IdentifyBuffer->GetByteAt(byteOffset));
            byteOffset += 2;
        }
        return modelNumber;
    }

    bool ATestUtility::CompareBuffers(const std::shared_ptr<vtStor::IBuffer>& SrcBuffer, const std::shared_ptr<vtStor::IBuffer>& DestBuffer, vtStor::U32 SectorCount)
    {
        vtStor::U8* writeBytes = SrcBuffer->ToDataBuffer();
        vtStor::U8* readBytes = DestBuffer->ToDataBuffer();
        return(0 == memcmp(writeBytes, readBytes, (SectorCount * 512)));
    }

    vtStor::U32 ATestUtility::MakeRandomValue(vtStor::U32 Value)
    {
        std::srand(std::time(NULL)); // Use current time as seed for random generator
        vtStor::U32 randValue = std::rand() % Value;
        return randValue;
    }

    // Sum of 511 frist bytes of buffer then use bitwise NOT and sum with 1
    vtStor::U8 ATestUtility::CalculateChecksum(vtStor::U8 *DataBuffer)
    {
        vtStor::U8 sum = 0;
        for (vtStor::U16 i = 0; i < 511; ++i)
        {
            sum += *DataBuffer;
            ++DataBuffer;
        }
        return (~sum + 1);
    }

    vtStor::U64 ATestUtility::GetValueOfBuffer(vtStor::U32 IdWord, vtStor::U32 WordCount, std::shared_ptr<vtStor::IBuffer> IdentifyBuffer)
    {
        vtStor::U64 value;
        vtStor::U32 byteOffset;
        vtStor::U32 numberOfBytes;
        vtStor::U8 shiftOffset;

        byteOffset = (WORD_SIZE_IN_BYTE * IdWord);
        numberOfBytes = (WORD_SIZE_IN_BYTE * WordCount);
        shiftOffset = 0;
        value = 0;
        for (vtStor::U32 i = 0; i < numberOfBytes; ++i)
        {
            value |= ((vtStor::U64)IdentifyBuffer->GetByteAt(byteOffset + i) << shiftOffset);
            shiftOffset += 8;
        }
        return(value);
    }

    vtStor::String ATestUtility::ConvertErrorCodeToString(vtStor::eErrorCode ErrorCode)
    {
        vtStor::String result;
        switch (ErrorCode)
        {
        case vtStor::eErrorCode::None:
        {
            result = __STORAPITEXT("None");
        }break;
        case vtStor::eErrorCode::Unknown:
        {
            result = __STORAPITEXT("Unknown");
        }break;
        case vtStor::eErrorCode::Memory:
        {
            result = __STORAPITEXT("Memory");
        }break;
        case vtStor::eErrorCode::Io:
        {
            result = __STORAPITEXT("Io");
        }break;
        case vtStor::eErrorCode::Timeout:
        {
            result = __STORAPITEXT("Timeout");
        }break;
        case vtStor::eErrorCode::NoSupport:
        {
            result = __STORAPITEXT("NoSupport");
        }break;
        case vtStor::eErrorCode::Invalid:
        {
            result = __STORAPITEXT("Invalid");
        }break;
        case vtStor::eErrorCode::NullPointer:
        {
            result = __STORAPITEXT("NullPointer");
        }break;
        case vtStor::eErrorCode::FormatNotSupported:
        {
            result = __STORAPITEXT("FormatNotSupported");
        }break;
        case vtStor::eErrorCode::SyncIo:
        {
            result = __STORAPITEXT("SyncIo");
        }break;
        default:
        {
        }break;
        }

        return result;
    }
}