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

#include "IDevice.h"
#include "DriveInterfaceManaged.h"

namespace vtStor
{
    namespace Managed
    {
        cDriveInterface::cDriveInterface( std::shared_ptr<vtStor::IDrive> Drive )
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
            return(reinterpret_cast<void*>(&(*m_Drive)));
        }

        void cDriveInterface::RegisterCommandHandler(U32 CommandType, vtStor::Managed::cCommandHandlerInterface^ CommandHandler)
        {
            m_Drive->RegisterCommandHandler(CommandType, *reinterpret_cast<std::shared_ptr<vtStor::ICommandHandler>* > ((void*)*CommandHandler));
        }

        eErrorCode cDriveInterface::IssueCommand(U32 CommandType, vtStor::Managed::cBufferInterface^ CommandDescriptor, vtStor::Managed::cBufferInterface^ Data)
        {
            return(m_Drive->IssueCommand(CommandType, *reinterpret_cast<std::shared_ptr<vtStor::IBuffer>*>((void*)*CommandDescriptor), *reinterpret_cast<std::shared_ptr<vtStor::IBuffer>*>((void*)*Data)));
        }

        vtStor::Managed::eBusType cDriveInterface::GetBusType()
        {
            return (static_cast<vtStor::Managed::eBusType>(m_Drive->GetBusType()));
        }

        System::String^ cDriveInterface::GetDevicePath()
        {
            // Get Drive instance from the current DriveInterface
            std::shared_ptr<vtStor::IDevice> drive = std::dynamic_pointer_cast<vtStor::IDevice>(*m_Drive);

            // Retrieve DevicePath from drive
            tchar* devicePath;
            drive->DevicePath(devicePath);

            return(gcnew System::String(devicePath));
        }
    }
}