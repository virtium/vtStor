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

#include "DriveManager.h"
#include "StorageUtility.h"

void cDriveManager_GetDriveManager(std::unique_ptr<vtStor::IDriveManager>& DriveManager)
{
    DriveManager = std::unique_ptr<vtStor::cDriveManager>(new vtStor::cDriveManager());
}

namespace vtStor
{
    cDriveManager::cDriveManager()
    {
    }

    cDriveManager::~cDriveManager()
    {
        m_Drives.clear();
    }

    void cDriveManager::RegisterDriveEnumerator(std::shared_ptr<IDriveEnumerator> DriveEnumerator)
    {
        m_DriveEnumerator = DriveEnumerator;
    }

    eErrorCode cDriveManager::EnumerateDrives(eScanForHardwareChanges ScanForHardwareChanges)
    {
        eErrorCode error = eErrorCode::None;
        bool successFlag = false;
        std::vector<std::shared_ptr<IDevice>> devices;

        m_Drives.clear();
        vtStor::GetStorageDevices(devices, eOnErrorBehavior::Continue);

        for (const auto& device : devices)
        {
            auto drive = m_DriveEnumerator->EnumerateDrive(device);
            if (nullptr != drive)
            {
                m_Drives.push_back(drive);
            }
        }
        return(error);
    }

    const Vector_Drives& cDriveManager::GetDrives()
    {
        return(m_Drives);
    }

    std::shared_ptr<IDrive> cDriveManager::GetDrive(const U32 DriveIndex)
    {
        std::shared_ptr<IDrive> driveInterface = nullptr;
        if (m_Drives.size() > DriveIndex)
        {
            driveInterface = m_Drives[DriveIndex];
        }
        return(driveInterface);
    }

}
