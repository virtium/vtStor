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

#include "DriveInterfaceManaged.h"

namespace vtStor
{
    namespace Managed
    {
        cDriveInterface::cDriveInterface( std::shared_ptr<vtStor::cDriveInterface> Drive )
        {
            m_Drive = Drive;
        }

        cDriveInterface::~cDriveInterface()
        {
        }

        cDriveInterface::!cDriveInterface()
        {
        }

        cDriveInterface::operator void*()
        {
            return( vtStor::cDriveInterface::ToVoidPointer( *m_Drive ) );
        }

        void cDriveInterface::RegisterCommandHandler(U32 CommandType, vtStor::Managed::cCommandHandlerInterface^ CommandHandler)
        {
            m_Drive->RegisterCommandHandler(CommandType, vtStor::cCommandHandlerInterface::ToSharedPtr(*CommandHandler));
        }

        eErrorCode cDriveInterface::IssueCommand(U32 CommandType, vtStor::Managed::cBufferInterface^ CommandDescriptor, vtStor::Managed::cBufferInterface^ Data)
        {
            return( m_Drive->IssueCommand( CommandType, vtStor::cBufferInterface::ToSharedPtr( *CommandDescriptor ), vtStor::cBufferInterface::ToSharedPtr( *Data ) ) );
        }
    }
}