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

#include "DriveInterfaceManaged.h"
#include "DriveManagerInterfaceManaged.h"
#include "vtStor.h"

namespace vtStor
{
    namespace Managed
    {
        cDriveManagerInterface::cDriveManagerInterface()
        {
            vtStor::eErrorCode errorCode;
            errorCode = vtStorInit( *m_DriveManager );
        }

        cDriveManagerInterface::~cDriveManagerInterface()
        {
        }

        cDriveManagerInterface::!cDriveManagerInterface()
        {
        }

        void cDriveManagerInterface::RegisterDriveEnumerator( cDriveEnumeratorInterface^ DriveEnumerator )
        {
            std::shared_ptr<vtStor::cDriveEnumeratorInterface> driveEnumerator = vtStor::cDriveEnumeratorInterface::ToSharedPtr( DriveEnumerator );
            m_DriveManager->RegisterDriveEnumerator( driveEnumerator );
        }

        eErrorCode cDriveManagerInterface::EnumerateDrives( eScanForHardwareChanges ScanForHardwareChanges )
        {
            eErrorCode errorCode;
            errorCode = eErrorCode::NullPointer;
            if (nullptr != *m_DriveManager)
            {
                errorCode = static_cast<eErrorCode>( m_DriveManager->EnumerateDrives( static_cast<vtStor::eScanForHardwareChanges>( ScanForHardwareChanges ) ) );
            }
            return( errorCode );
        }

        U32 cDriveManagerInterface::GetDriveCount()
        {
            U32 driveCount = 0;
            if (nullptr != *m_DriveManager)
            {
                driveCount = static_cast<U32>( m_DriveManager->GetDrives().size() );
            }
            return( driveCount );
        }

        cDriveInterface^ cDriveManagerInterface::GetDrive( U32 DriveIndex )
        {
            cDriveInterface^ drive = nullptr;
            if (nullptr != *m_DriveManager)
            {
                std::shared_ptr<vtStor::cDriveInterface> driveInterface;
                driveInterface = m_DriveManager->GetDrive( DriveIndex );

                if (nullptr != driveInterface)
                {
                    drive = gcnew cDriveInterface( driveInterface );
                }
            }
            return( drive );
        }
    }
}