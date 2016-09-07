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

#include "AtaReadWriteBufferTest.h"
#include "ATestUtility.h"
#include "TestObjectRegister.h"
#include "VtStorATestDefine.h"

namespace vtStorATest
{
    static TestObjectRegister<AtaReadWriteBufferTest> s_TestEntityRegister(__STORAPITEXT("AtaReadWriteBufferTest"));

    AtaReadWriteBufferTest::AtaReadWriteBufferTest()
    {
        m_TestResource = TestResource::GetInstance();
    }

    AtaReadWriteBufferTest::~AtaReadWriteBufferTest()
    {
    }

    bool AtaReadWriteBufferTest::Run()
    {
        bool result = true;
        vtStor::eErrorCode writeErrorCode = vtStor::eErrorCode::None;
        vtStor::eErrorCode readErrorCode = vtStor::eErrorCode::None;

        m_TestResource->MemsetReadWriteBuffer();
        
        // Use Ata
        cCommandHandlerAta_GetCommandHandler(m_TestResource->GetCommandHandler(), m_TestResource->GetAtaProtocol());

        // Register command handler
        m_TestResource->GetSelectedDrive()->RegisterCommandHandler(TestResource::COMMAND_HANDLE_ATA_COMMAND_TYPE, m_TestResource->GetCommandHandler());

        // Do some times (10 times) read, write and verify
        for (vtStor::U32 i = 0; i < 10; ++i)
        {
            writeErrorCode = m_TestResource->GetAtaCommandExtensions()->IssueCommand_WriteBuffer(m_TestResource->GetSelectedDrive(), TestResource::COMMAND_HANDLE_ATA_COMMAND_TYPE, m_TestResource->GetDataWriteBuffer());
            if (vtStor::eErrorCode::None != writeErrorCode)
            {
                VtStorPrintln << "\t" << "WriteBuffer error, errorCode " << ATestUtility::ConvertErrorCodeToString(writeErrorCode);
                return false;
            }

            readErrorCode = m_TestResource->GetAtaCommandExtensions()->IssueCommand_ReadBuffer(m_TestResource->GetSelectedDrive(), TestResource::COMMAND_HANDLE_ATA_COMMAND_TYPE, m_TestResource->GetDataReadBuffer());
            if (vtStor::eErrorCode::None != writeErrorCode)
            {
                VtStorPrintln << "\t" << "ReadBuffer error, errorCode " << ATestUtility::ConvertErrorCodeToString(readErrorCode);
                return false;
            }

            if (false == (ATestUtility::CompareBuffers(m_TestResource->GetDataWriteBuffer(), m_TestResource->GetDataReadBuffer(), 1)))
            {
                result = false;
            }
        }

        return result;
    }
}