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
#include <memory>

#include "CppUnitTest.h"
#include "AtaCommandExtensions.h"
#include "DriveEnumeratorAta.h"
#include "ScanForHardwareChanges.h"
#include "IDriveManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace vtStorTest
{
    TEST_CLASS(cVtStorTest)
    {
    public:
        TEST_METHOD(Enumeration)
        {
            Enumerate();
        }

        TEST_METHOD(IssueCommand_IdentifyDevice)
        {
            Enumerate();
            //TODO: system needs to have a drive to test.
            //vtStor::Ata::IssueCommand_IdentifyDevice();
        }

        void Enumerate()
        {
            std::unique_ptr<vtStor::IDriveManager> m_DriveManager;
            cDriveManager_GetDriveManager(m_DriveManager);

            std::shared_ptr<vtStor::IDriveEnumerator> m_DriveEnumeratorAta = std::make_unique<vtStor::cDriveEnumeratorAta>();
            m_DriveManager->RegisterDriveEnumerator(m_DriveEnumeratorAta);
            m_DriveManager->EnumerateDrives(vtStor::eScanForHardwareChanges::No);
        }

    private:
        std::unique_ptr<vtStor::IDriveManager> m_DriveManager;
        std::shared_ptr<vtStor::IDriveEnumerator> m_DriveEnumeratorAta;
    };
}