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
#ifndef __DriveInterface_h__
#define __DriveInterface_h__

#include <memory>
#include <vector>

#include "BasicTypes.h"
#include "ErrorCodes.h"
#include "BufferInterface.h"
#include "CommandHandlerInterface.h"
#include "vtStorPlatformDefines.h"

namespace vtStor
{

class VTSTOR_API cDriveInterface
{
public:
    static std::shared_ptr<vtStor::cDriveInterface> ToSharedPtr( void* Object );
    static void* ToVoidPointer( std::shared_ptr<vtStor::cDriveInterface>& Object );

public:
    virtual void RegisterComandHandler(U32 CommandType, std::shared_ptr<cCommandHandlerInterface> CommandHandler) = 0;

public:
    virtual eErrorCode IssueCommand(U32 CommandType, std::shared_ptr<const cBufferInterface> CommandDescriptor, std::shared_ptr<cBufferInterface> Data) = 0;

public:
    virtual ~cDriveInterface();

public:
    std::shared_ptr<Protocol::cProtocolInterface> m_Protocol;
};

using Vector_Drives = std::vector<std::shared_ptr<cDriveInterface>>;

}

#endif