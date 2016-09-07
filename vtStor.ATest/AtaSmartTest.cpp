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

#include "AtaSmartTest.h"
#include "ATestUtility.h"
#include "TestObjectRegister.h"
#include "VtStorATestDefine.h"

namespace vtStorATest
{
    static TestObjectRegister<AtaSmartTest> s_TestEntityRegister(__STORAPITEXT("AtaSmartTest"));

    AtaSmartTest::AtaSmartTest()
    {
        m_TestResource = TestResource::GetInstance();
    }

    AtaSmartTest::~AtaSmartTest()
    {
    }

    bool AtaSmartTest::Run()
    {
        vtStor::eErrorCode smartErrorCode = vtStor::eErrorCode::None;
        m_TestResource->GetDataSmartBuffer()->Memset(0);

        // Use Ata
        cCommandHandlerAta_GetCommandHandler(m_TestResource->GetCommandHandler(), m_TestResource->GetAtaProtocol());

        // Register command handler
        m_TestResource->GetSelectedDrive()->RegisterCommandHandler(TestResource::COMMAND_HANDLE_ATA_COMMAND_TYPE, m_TestResource->GetCommandHandler());

        // Issue command
        smartErrorCode = m_TestResource->GetAtaCommandExtensions()->IssueCommand_Smart(m_TestResource->GetSelectedDrive(), TestResource::COMMAND_HANDLE_ATA_COMMAND_TYPE, m_TestResource->GetDataSmartBuffer(), READ_ATTRIBUTES);

        if (vtStor::eErrorCode::None != smartErrorCode)
        {
            VtStorPrintln << "\t" << "Smart command error, errorCode " << ATestUtility::ConvertErrorCodeToString(smartErrorCode);
            return false;
        }

        // Get last byte of buffer (size of 512 bytes)
        vtStor::U8 expectedCheckSum = m_TestResource->GetDataSmartBuffer()->ToDataBuffer()[511];

        // Calculate checksum 511 first bytes
        vtStor::U8 actualCheckSum = ATestUtility::CalculateChecksum(m_TestResource->GetDataSmartBuffer()->ToDataBuffer());

        VtStorPrintln << "\t" << "Expected checksum = " << expectedCheckSum;
        VtStorPrintln << "\t" << "Result calculate checksum = " << actualCheckSum;

        return (expectedCheckSum == actualCheckSum);
    }
}