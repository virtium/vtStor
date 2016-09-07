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
#ifndef __vtStorIDriveEnumerator_h__
#define __vtStorIDriveEnumerator_h__

#include <memory>

#include "PlatformDefines.h"
#include "IDevice.h"
#include "IDrive.h"

namespace vtStor
{
    class VTSTOR_API IDriveEnumerator
    {
    public:
        virtual ~IDriveEnumerator() {}
        virtual std::shared_ptr<IDrive> EnumerateDrive(const std::shared_ptr<IDevice>& Device) = 0;
    };

    VTSTOR_DLL_STL_IMPL(VTSTOR_API_EXPORT_IMPL template class VTSTOR_API std::shared_ptr<IDriveEnumerator>);
}

extern "C"
{
    VTSTOR_API void cDriveEnumerator_GetDriveEnumerator(std::shared_ptr<vtStor::IDriveEnumerator>& DriveEnumerator);
    VT_STOR_ATA_API void cDriveEnumeratorAta_GetDriveEnumerator(std::shared_ptr<vtStor::IDriveEnumerator>& DriveEnumerator, const std::shared_ptr<vtStor::IDriveEnumerator>& DecoratedDriveEnumerator);
    VT_STOR_SCSI_API void cDriveEnumeratorScsi_GetDriveEnumerator(std::shared_ptr<vtStor::IDriveEnumerator>& DriveEnumerator, const std::shared_ptr<vtStor::IDriveEnumerator>& DecoratedDriveEnumerator);
}

typedef void (OS_API * GetDriveEnumeratorDecoratorDelegate) (std::shared_ptr<vtStor::IDriveEnumerator>&, const std::shared_ptr<vtStor::IDriveEnumerator>&);
typedef void (OS_API * GetDriveEnumeratorDelegate) (std::shared_ptr<vtStor::IDriveEnumerator>&);

#endif // end __vtStorIDriveEnumerator_h__