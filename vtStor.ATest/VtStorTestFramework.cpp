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

#include "ATestUtility.h"
#include "VtStorTestFramework.h"
#include "VTStorTestManager.h"
#include "VtStorATestDefine.h"

namespace vtStorATest
{
    std::shared_ptr<vtStorATest::VTStorTestManager> TestManager = std::make_shared<vtStorATest::VTStorTestManager>();

    VtStorTestFramework::VtStorTestFramework()
    {
    }

    VtStorTestFramework::~VtStorTestFramework()
    {
    }

    void MainMenu()
    {
        VtStorPrintln << "==============";
        VtStorPrintln << " Main Select";
        VtStorPrintln << "==============";
        VtStorPrintln << "0. Exit";
        VtStorPrintln << "1. Scan For Drives";
        VtStorPrintln << "2. List Test Objects";
        VtStorPrintln << "3. Run All Tests";
        VtStorPrintln << "4. Run A Specific Test";
        VtStorPrintln << "Select: ";
    }

    void ScanDrives()
    {
        std::shared_ptr<TestResource> testResource = TestResource::GetInstance();
        testResource->ResetDrives();

        // Scan all drives on system and add to list drives of TestResource 
        testResource->SetDrives(ATestUtility::ScanForDrives());
        testResource->GetAvailableDrives();

        VtStorPrintln << "Drives on your system: ";
        if (0 == testResource->GetDriveModelString().size())
        {
            VtStorPrintln << "[No drives found]";
        }

        for (vtStor::U32 i = 0; i < testResource->GetDriveModelString().size(); ++i)
        {
            VtStorPrintln << i << "." << " Drive " << i << ": " << testResource->GetDriveModelString()[i].c_str();
        }

        VtStorPrintln << "Select a drive for test: ";
        vtStor::U32 option;
        std::cin >> option;

        if (option < testResource->GetDriveModelString().size())
        {
            testResource->SetSelectedDrive(testResource->GetDrives()[option]);
            sSelectedDriveInfo driveInfo;
            driveInfo.MaxUserLBA = testResource->GetMaxUserLBA(testResource->GetSelectedDrive());
            driveInfo.ModelString = testResource->GetDriveModelString()[option];

            testResource->SetSelectedDriveInfo(driveInfo);
            VtStorPrintln << "Selected Drive: " << driveInfo.ModelString;
            VtStorPrintln << "MaxUserLBA: " << driveInfo.MaxUserLBA << std::endl;
        }
        else
        {
            VtStorPrintln << "Invalid option";
        }
    }

    void vtStorATest::VtStorTestFramework::Run()
    {
        ScanDrives();
        vtStor::U32 option;
        while (true)
        {
            MainMenu();
            std::cin >> option;

            switch (option)
            {
            case 0:
            {
                exit(1);
            }break;
            case 1:
            {
                ScanDrives();
            }break;
            case 2:
            {
                TestManager->ListAllTestObjects();
            }break;
            case 3:
            {
                TestManager->RunAll();
            }break;
            case 4:
            {
                TestManager->ListAllTestObjects();
                TestManager->RunSpecificTest();
            }break;
            default:
            {
                VtStorPrintln << "Invalid option";
            }break;
            }
        }
    }
}