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
#ifndef __DriveEnumeratorScsi_h__
#define __DriveEnumeratorScsi_h__

#include "vtStorScsiPlatformDefines.h"
#include "DriveEnumeratorInterface.h"

namespace vtStor
{
    class VT_STOR_SCSI_API cDriveEnumeratorScsi : public cDriveEnumeratorInterface
    {
    public:
        virtual std::shared_ptr<cDriveInterface> EnumerateDrive(const std::shared_ptr<cDeviceInterface>& Device) override;

    public:
        virtual ~cDriveEnumeratorScsi();
    };
}

#endif