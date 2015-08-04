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
#ifndef __DriveManager_h__
#define __DriveManager_h__

#include "DriveManagerInterface.h"

namespace vtStor
{

class cDriveManager : public cDriveManagerInterface
{
public:
    static std::unique_ptr<cDriveManager> GetInstance();
    static void ResetInstance();

public:
    virtual void RegisterDriveEnumerator( std::shared_ptr<cDriveEnumeratorInterface> DriveEnumerator ) override;

    virtual eErrorCode EnumerateDrives( eScanForHardwareChanges ScanForHardwareChanges ) override;

public:
    virtual const Vector_Drives& GetDrives() override;

    virtual std::shared_ptr<cDriveInterface> GetDrive(const U32 DriveIndex) override;

private:
    cDriveManager();
    static cDriveManager* s_Instance;

public:
    virtual ~cDriveManager();

private:
    using Vector_DriveEnumerator = std::vector<std::shared_ptr<cDriveEnumeratorInterface>>;
    Vector_DriveEnumerator m_DriveEnumerators;

private:
    Vector_Drives   m_Drives;
    std::vector<String> m_DevicePaths;
};

}

#endif