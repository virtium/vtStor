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

#include "AtaCommandExtensions.h"
#include "ATestUtility.h"
#include "Buffer.h"
#include "ProtocolAtaPassThrough.h"
#include "TestResource.h"

namespace vtStorATest
{
    const vtStor::U64 MAX_SIZE_OF_BUFFER = 65536 * 512;
    const vtStor::U32 DWORD = 2;
    const vtStor::U32 MAX_USER_LBA_28_BIT_ID_WORD = 60;
    const vtStor::U32 MAX_USER_LBA_48_BIT_ID_WORD = 100;

    std::shared_ptr<TestResource> TestResource::GetInstance()
    {
        static std::shared_ptr<TestResource> instance;
        if (nullptr == instance)
        {
            instance = std::shared_ptr<TestResource>(new TestResource());
        }
        return(instance);
    }

    TestResource::TestResource()
    {
        m_CommandHandler = nullptr;

        m_DataWriteBuffer = std::make_shared<vtStor::cBuffer>(MAX_SIZE_OF_BUFFER);
        m_DataReadBuffer = std::make_shared<vtStor::cBuffer>(MAX_SIZE_OF_BUFFER);
        m_DataIdentifyBuffer = std::make_shared<vtStor::cBuffer>(512);
        m_DataSmartBuffer = std::make_shared<vtStor::cBuffer>(512);

        // Use ATA
        m_AtaCommandExtensions = std::make_unique<vtStor::Ata::cAtaCommandExtensions>();
        m_AtaProtocol = std::make_shared<vtStor::Protocol::cAtaPassThrough>();
    }

    TestResource::~TestResource()
    {
    }

    void TestResource::GetAvailableDrives()
    {
        for (vtStor::U32 i = 0; i < m_Drives.size(); ++i)
        {
            std::shared_ptr<vtStor::IBuffer> identifyBuffer = std::make_shared<vtStor::cBuffer>(512);

            identifyBuffer->Memset(0); // Reset buffer
            vtStor::eErrorCode errorCode = vtStor::eErrorCode::None;

            // TODO: Detected Scsi drives
            if (vtStor::eBusType::Ata == m_Drives[i]->GetBusType())
            {
                cCommandHandlerAta_GetCommandHandler(m_CommandHandler, m_AtaProtocol);

                // Register command handler
                m_Drives[i]->RegisterCommandHandler(TestResource::COMMAND_HANDLE_ATA_COMMAND_TYPE, m_CommandHandler);

                // Issue identify device command
                errorCode = m_AtaCommandExtensions->IssueCommand_IdentifyDevice(m_Drives[i], TestResource::COMMAND_HANDLE_ATA_COMMAND_TYPE, identifyBuffer);
                if (vtStor::eErrorCode::None == errorCode)
                {
                    vtStor::String modelString = ATestUtility::GetModelString(identifyBuffer);
                    m_DriveModelString.push_back(modelString);
                }
                else
                {
                    m_Drives.erase(m_Drives.begin() + i);
                }
            }
        }
    }

    vtStor::U64 TestResource::GetMaxUserLBA(std::shared_ptr<vtStor::IDrive>& Drive)
    {
        vtStor::U64 maxUserLBA_28_Bit;
        vtStor::U64 maxUserLBA_48_Bit;
        std::shared_ptr<vtStor::IBuffer> identifyBuffer = std::make_shared<vtStor::cBuffer>(512);

        m_AtaCommandExtensions->IssueCommand_IdentifyDevice(Drive, TestResource::COMMAND_HANDLE_ATA_COMMAND_TYPE, identifyBuffer);
        maxUserLBA_28_Bit = ATestUtility::GetValueOfBuffer(MAX_USER_LBA_28_BIT_ID_WORD, DWORD, identifyBuffer);
        maxUserLBA_48_Bit = ATestUtility::GetValueOfBuffer(MAX_USER_LBA_48_BIT_ID_WORD, DWORD, identifyBuffer);

        return((maxUserLBA_28_Bit >= maxUserLBA_48_Bit) ? maxUserLBA_28_Bit : maxUserLBA_48_Bit);
    }

    void TestResource::MemsetReadWriteBuffer()
    {
        vtStor::U8 value = ATestUtility::MakeRandomValue(256); // Random for a number [0, 255], type of U8

        // Reset buffer
        m_DataWriteBuffer->Memset(value);
        m_DataReadBuffer->Memset(0);
    }

    std::shared_ptr<vtStor::IDrive> TestResource::GetSelectedDrive()
    {
        return m_SelectedDrive;
    }

    void TestResource::SetSelectedDrive(std::shared_ptr<vtStor::IDrive>& Drive)
    {
        m_SelectedDrive = Drive;
    }

    vtStor::Vector_Drives TestResource::GetDrives()
    {
        return m_Drives;
    }

    void TestResource::SetDrives(vtStor::Vector_Drives Drives)
    {
        m_Drives = Drives;
    }

    void TestResource::ResetDrives()
    {
        m_Drives.clear();
        m_DriveModelString.clear();
    }

    std::vector<vtStor::String> TestResource::GetDriveModelString()
    {
        return m_DriveModelString;
    }

    sSelectedDriveInfo TestResource::GetSelectedDriveInfo()
    {
        return m_SelectedDriveInfo;
    }

    void TestResource::SetDriveModelString(std::vector<vtStor::String>& DriveModel)
    {
        m_DriveModelString = DriveModel;
    }

    void TestResource::SetSelectedDriveInfo(sSelectedDriveInfo& DriveInfo)
    {
        m_SelectedDriveInfo = DriveInfo;
    }

    std::shared_ptr<vtStor::IBuffer> TestResource::GetDataWriteBuffer()
    {
        return m_DataWriteBuffer;
    }

    std::shared_ptr<vtStor::IBuffer> TestResource::GetDataReadBuffer()
    {
        return m_DataReadBuffer;
    }

    std::shared_ptr<vtStor::IBuffer> TestResource::GetDataIdentifyBuffer()
    {
        return m_DataIdentifyBuffer;
    }

    std::shared_ptr<vtStor::IBuffer> TestResource::GetDataSmartBuffer()
    {
        return m_DataSmartBuffer;
    }

    std::shared_ptr<vtStor::ICommandHandler> TestResource::GetCommandHandler()
    {
        return m_CommandHandler;
    }

    std::shared_ptr<vtStor::IAtaCommandExtensions> TestResource::GetAtaCommandExtensions()
    {
        return m_AtaCommandExtensions;
    }

    std::shared_ptr<vtStor::IProtocol> TestResource::GetAtaProtocol()
    {
        return m_AtaProtocol;
    }
}