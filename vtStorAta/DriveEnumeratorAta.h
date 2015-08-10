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
#ifndef __DriveEnumeratorAta_h__
#define __DriveEnumeratorAta_h__

#include "vtStorAtaPlatformDefines.h"
#include "DriveEnumeratorInterface.h"

namespace vtStor
{
    class VT_STOR_ATA_API cDriveEnumeratorAta : public cDriveEnumeratorInterface
    {
    public:
        virtual eErrorCode EnumerateDrive( const String& DevicePath, Vector_Drives& AddToList, bool& SuccessFlag ) override;

    public:
        virtual ~cDriveEnumeratorAta();
    };
}

#endif