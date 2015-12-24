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
#ifndef __vtStorIDrive_h__
#define __vtStorIDrive_h__

#include <memory>
#include <vector>

#include "ICommandHandler.h"
#include "IBuffer.h"
#include "IDevice.h"
#include "BusType.h"

namespace vtStor
{
    struct IDrive : public IDevice
    {
        virtual void RegisterCommandHandler(U32 CommandType, std::shared_ptr<ICommandHandler> CommandHandler) = 0;
        virtual eErrorCode IssueCommand(U32 CommandType, std::shared_ptr<const IBuffer> CommandDescriptor, std::shared_ptr<IBuffer> Data) = 0;
        virtual eBusType GetBusType() = 0;
    };

    using Vector_Drives = std::vector<std::shared_ptr<IDrive>>;
}

#endif // end __vtStorIDrive_h__