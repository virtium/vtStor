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

#ifndef __TestResource_h__
#define __TestResource_h__
#pragma once

#include <memory>

#include "IAtaCommandExtensions.h"
#include "ICommandHandler.h"

namespace vtStorATest
{
    struct sSelectedDriveInfo
    {
        vtStor::String ModelString;
        vtStor::U64 MaxUserLBA;
    };

    class TestResource
    {
    public:
        static std::shared_ptr<TestResource> GetInstance();

    private:
        TestResource();

    public:
        virtual ~TestResource();

    public:
        void GetAvailableDrives();
        void MemsetReadWriteBuffer();

        // Get and set functions
        void SetDrives(vtStor::Vector_Drives Drives);
        void ResetDrives();
        void SetSelectedDrive(std::shared_ptr<vtStor::IDrive>& Drive);
        void SetDriveModelString(std::vector<vtStor::String>& DriveModel);
        void SetSelectedDriveInfo(sSelectedDriveInfo & DriveInfo);
        vtStor::Vector_Drives GetDrives();
        vtStor::U64 GetMaxUserLBA(std::shared_ptr<vtStor::IDrive>& Drive);
        std::vector<vtStor::String> GetDriveModelString();
        std::shared_ptr<vtStor::IDrive> GetSelectedDrive();
        std::shared_ptr<vtStor::ICommandHandler> GetCommandHandler();
        sSelectedDriveInfo GetSelectedDriveInfo();

        // Buffers for test
        std::shared_ptr<vtStor::IBuffer> GetDataWriteBuffer();
        std::shared_ptr<vtStor::IBuffer> GetDataReadBuffer();
        std::shared_ptr<vtStor::IBuffer> GetDataIdentifyBuffer();
        std::shared_ptr<vtStor::IBuffer> GetDataSmartBuffer();

        // Use ATA
        std::shared_ptr<vtStor::IAtaCommandExtensions> GetAtaCommandExtensions();
        std::shared_ptr<vtStor::IProtocol> GetAtaProtocol();

    private:
        std::shared_ptr<vtStor::IDrive> m_SelectedDrive;
        vtStor::Vector_Drives m_Drives;
        std::vector<vtStor::String> m_DriveModelString;
        sSelectedDriveInfo m_SelectedDriveInfo;
        std::shared_ptr<vtStor::ICommandHandler> m_CommandHandler;

        // Define buffers for test
        std::shared_ptr<vtStor::IBuffer> m_DataWriteBuffer;
        std::shared_ptr<vtStor::IBuffer> m_DataReadBuffer;
        std::shared_ptr<vtStor::IBuffer> m_DataIdentifyBuffer;
        std::shared_ptr<vtStor::IBuffer> m_DataSmartBuffer;

        // Use ATA
        std::shared_ptr<vtStor::IAtaCommandExtensions> m_AtaCommandExtensions;
        std::shared_ptr<vtStor::IProtocol> m_AtaProtocol;

    public:
        static const vtStor::U32 COMMAND_HANDLE_ATA_COMMAND_TYPE = 0;
    };
}
#endif