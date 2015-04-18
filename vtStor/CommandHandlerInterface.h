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
#ifndef __vtStorCommandHandlerInterface_h__
#define __vtStorCommandHandlerInterface_h__
#pragma once

#include <memory>

#include "ErrorCodes.h"
#include "BufferInterface.h"
#include "vtStorPlatformDefines.h"

namespace vtStor
{

class VTSTOR_API cCommandHandlerInterface
{
public:
    cCommandHandlerInterface();
    virtual ~cCommandHandlerInterface();

public:
    virtual eErrorCode IssueCommand( std::shared_ptr<const cBufferInterface> CommandDescriptor, std::shared_ptr<cBufferInterface> Data ) = 0;

};

}

#endif