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