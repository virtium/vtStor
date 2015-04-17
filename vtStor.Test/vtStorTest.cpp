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

#include "stdafx.h"
#include "CppUnitTest.h"

#include "vtStor.h"
#include "vtStorAta.h"
#include "DriveEnumeratorAta.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace vtStorTest
{		
    TEST_CLASS(cVtStorTest)
    {
    public:
        
        TEST_METHOD(Enumeration)
        {
            std::unique_ptr<vtStor::cDriveManagerInterface> driveManager;
            vtStorInit( driveManager );

            vtStor::cAta::s_DefaultCommandHandlerCommandType = 1;
            std::shared_ptr<vtStor::cDriveEnumeratorInterface> driveEnumeratorAta = std::make_unique<vtStor::cDriveEnumeratorAta>();
            driveManager->RegisterDriveEnumerator( driveEnumeratorAta );
            driveManager->EnumerateDrives( vtStor::cDriveManagerInterface::eScanForHardwareChanges::No );
        }

    };
}