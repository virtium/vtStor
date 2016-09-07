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

#include "AtaReadWriteSectorExtTest.h"
#include "ATestUtility.h"
#include "TestObjectRegister.h"
#include "VtStorATestDefine.h"

namespace vtStorATest
{
    static TestObjectRegister<AtaReadWriteSectorExtTest> s_TestEntityRegister(__STORAPITEXT("AtaReadWriteSectorExtTest"));

    AtaReadWriteSectorExtTest::AtaReadWriteSectorExtTest()
    {
    }

    AtaReadWriteSectorExtTest::~AtaReadWriteSectorExtTest()
    {
    }

    vtStor::eErrorCode AtaReadWriteSectorExtTest::SendReadCommand(vtStor::U32 Lba, vtStor::U32 SectorCount)
    {
        vtStor::eErrorCode readErrorCode = vtStor::eErrorCode::None;

        readErrorCode = m_TestResource->GetAtaCommandExtensions()->IssueCommand_ReadSectorExt(m_TestResource->GetSelectedDrive(), TestResource::COMMAND_HANDLE_ATA_COMMAND_TYPE, m_TestResource->GetDataReadBuffer(), Lba, SectorCount);
        if (vtStor::eErrorCode::None != readErrorCode)
        {
            VtStorPrintln << "\t" << "ReadSectorExt error, errorCode " << ATestUtility::ConvertErrorCodeToString(readErrorCode);
        }

        return readErrorCode;
    }

    vtStor::eErrorCode AtaReadWriteSectorExtTest::SendWriteCommand(vtStor::U32 Lba, vtStor::U32 SectorCount)
    {
        vtStor::eErrorCode writeErrorCode = vtStor::eErrorCode::None;

        writeErrorCode = m_TestResource->GetAtaCommandExtensions()->IssueCommand_WriteSectorExt(m_TestResource->GetSelectedDrive(), TestResource::COMMAND_HANDLE_ATA_COMMAND_TYPE, m_TestResource->GetDataWriteBuffer(), Lba, SectorCount);
        if (vtStor::eErrorCode::None != writeErrorCode)
        {
            VtStorPrintln << "\t" << "WriteSectorExt error, errorCode " << ATestUtility::ConvertErrorCodeToString(writeErrorCode);
        }

        return writeErrorCode;
    }
}