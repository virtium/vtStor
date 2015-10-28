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

namespace vtStor
{

cDriveManager::cDriveManager()
{
}

cDriveManager::~cDriveManager()
{
    m_DriveEnumerators.clear();
    m_Drives.clear();
}

void cDriveManager::RegisterDriveEnumerator( std::shared_ptr<cDriveEnumeratorInterface> DriveEnumerator )
{
    m_DriveEnumerators.push_back( DriveEnumerator );
}

eErrorCode cDriveManager::EnumerateDrives( eScanForHardwareChanges ScanForHardwareChanges )
{
    eErrorCode error = eErrorCode::None;
    bool successFlag = false;

    m_Drives.clear();
    m_Devices.clear();

    vtStor::GetStorageDevices(m_Devices, eOnErrorBehavior::Continue);

    for (const auto& device : m_Devices)
    {
        for (auto& enumerator : m_DriveEnumerators)
        {
            auto drive = enumerator->EnumerateDrive(device);
            if (nullptr != drive)
            {
                m_Drives.push_back(drive);
            }      
        }
    }    

    return( error );
}

const Vector_Drives& cDriveManager::GetDrives()
{
    return( m_Drives );
}

std::shared_ptr<cDriveInterface> cDriveManager::GetDrive(const U32 DriveIndex)
{
    std::shared_ptr<cDriveInterface> driveInterface = nullptr;
    if (m_Drives.size() > DriveIndex)
    {
        driveInterface = m_Drives[DriveIndex];
    }
    return(driveInterface);
}

}