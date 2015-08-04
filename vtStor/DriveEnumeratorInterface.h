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
#ifndef __DriveEnumeratorInterface_h__
#define __DriveEnumeratorInterface_h__

#include "BasicTypes.h"
#include "ErrorCodes.h"
#include "DriveInterface.h"
#include "vtStorPlatformDefines.h"

namespace vtStor
{

class VTSTOR_API cDriveEnumeratorInterface
{
public:
    static std::shared_ptr<vtStor::cDriveEnumeratorInterface> ToSharedPtr( void* Object );
    static void* ToVoidPointer( std::shared_ptr<vtStor::cDriveEnumeratorInterface>& Object );

public:
    virtual eErrorCode EnumerateDrives( std::vector<String>& PathsList, Vector_Drives& AddToList, U32& Count ) = 0;

public:
    virtual ~cDriveEnumeratorInterface();
};

}

#endif