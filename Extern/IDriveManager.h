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
#ifndef __vtStorIDriveManager_h__
#define __vtStorIDriveManager_h__

#include <memory>

#include "PlatformDefines.h"
#include "ScanForHardwareChanges.h"
#include "IDriveEnumerator.h"

namespace vtStor
{
    struct IDriveManager
    {
        virtual ~IDriveManager() {}
        virtual void RegisterDriveEnumerator(std::shared_ptr<IDriveEnumerator> DriveEnumerator) = 0;
        virtual eErrorCode EnumerateDrives(eScanForHardwareChanges ScanForHardwareChanges) = 0;
        virtual const Vector_Drives& GetDrives() = 0;
        virtual std::shared_ptr<IDrive> GetDrive(const U32 DriveIndex) = 0;
    };
}

extern "C"
{
    VTSTOR_API void cDriveManager_GetDriveManager(std::unique_ptr<vtStor::IDriveManager>& DriveManager);
}

typedef void (WINAPIV * GetDriveManagerDelegate) (std::unique_ptr<vtStor::IDriveManager>&);

#endif // end __vtStorIDriveManager_h__