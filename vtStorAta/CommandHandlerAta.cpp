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
#include "vtStorAta.h"
#include "CommandDescriptorUtility.h"
#include "AtaPassThroughUtility.h"

#include "CommandHandlerAta.h"

namespace vtStor
{

cCommandHandlerAta::cCommandHandlerAta()
{
}


cCommandHandlerAta::~cCommandHandlerAta()
{
}

eErrorCode cCommandHandlerAta::IssueCommand( std::shared_ptr<const cBufferInterface> CommandDescriptor, std::shared_ptr<cBufferInterface> Data )
{
    eErrorCode errorCode = eErrorCode::None;

    Ata::cCommandDescriptorVersion1 commandDescriptorVersion1( CommandDescriptor );
    cAta::sCommandCharacteristic& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();

    AtaPassThroughUtility::IssueCommand( commandCharacteristics, Data );

    return(errorCode);
}

}