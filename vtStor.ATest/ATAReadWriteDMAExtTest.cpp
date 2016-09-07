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

#include "AtaReadWriteDmaExtTest.h"
#include "ATestUtility.h"
#include "TestObjectRegister.h"
#include "VtStorATestDefine.h"

namespace vtStorATest
{
    static TestObjectRegister<AtaReadWriteDmaExtTest> s_TestEntityRegister(__STORAPITEXT("AtaReadWriteDmaExtTest"));

    AtaReadWriteDmaExtTest::AtaReadWriteDmaExtTest()
    {
    }

    AtaReadWriteDmaExtTest::~AtaReadWriteDmaExtTest()
    {
    }

    vtStor::eErrorCode AtaReadWriteDmaExtTest::SendReadCommand(vtStor::U32 Lba, vtStor::U32 SectorCount)
    {
        vtStor::eErrorCode readErrorCode = vtStor::eErrorCode::None;
        readErrorCode = m_TestResource->GetAtaCommandExtensions()->IssueCommand_ReadDmaExt(m_TestResource->GetSelectedDrive(), TestResource::COMMAND_HANDLE_ATA_COMMAND_TYPE, m_TestResource->GetDataReadBuffer(), Lba, SectorCount);
        if (vtStor::eErrorCode::None != readErrorCode)
        {
            VtStorPrintln << "\t" << "ReadDmaExt error, errorCode " << ATestUtility::ConvertErrorCodeToString(readErrorCode);
        }

        return readErrorCode;
    }

    vtStor::eErrorCode AtaReadWriteDmaExtTest::SendWriteCommand(vtStor::U32 Lba, vtStor::U32 SectorCount)
    {
        vtStor::eErrorCode writeErrorCode = vtStor::eErrorCode::None;
        writeErrorCode = m_TestResource->GetAtaCommandExtensions()->IssueCommand_WriteDmaExt(m_TestResource->GetSelectedDrive(), TestResource::COMMAND_HANDLE_ATA_COMMAND_TYPE, m_TestResource->GetDataWriteBuffer(), Lba, SectorCount);
        if (vtStor::eErrorCode::None != writeErrorCode)
        {
            VtStorPrintln << "\t" << "WriteDmaExt error, errorCode " << ATestUtility::ConvertErrorCodeToString(writeErrorCode);
        }

        return writeErrorCode;
    }
}