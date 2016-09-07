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

#ifndef __vtStorCommandHandlerScsiManaged_h__
#define __vtStorCommandHandlerScsiManaged_h__
#pragma once

#include "ICommandHandler.h"
#include "SharedPtrManaged.h"

namespace vtStor
{
    namespace Managed
    {
        public ref class cCommandHandlerScsi : public cCommandHandlerInterface
        {
        public:
            cCommandHandlerScsi( IRunTimeDll^ RunTimeDll, cProtocolInterface^ Protocol );
            virtual ~cCommandHandlerScsi();

        protected:
            !cCommandHandlerScsi();

        public:
            virtual operator void*() override;

        private:
            cSharedPtr<vtStor::ICommandHandler> m_CommandHandler;
        };
    }
}

#endif