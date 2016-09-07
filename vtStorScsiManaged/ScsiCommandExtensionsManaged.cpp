/*
<License>
Copyright 2016 Virtium Technology

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

#include <memory>

#include "ScsiCommandExtensionsManaged.h"

namespace vtStor
{
    namespace Scsi
    {
        namespace Managed
        {
            cScsiCommandExtensions::cScsiCommandExtensions(vtStor::Managed::IRunTimeDll^ RunTimeDll)
            {
                GetScsiCommandExtensionsDelegate getScsiCommandExtensionsDelegate = (GetScsiCommandExtensionsDelegate)RunTimeDll->GetFunction("cScsiCommandExtensions_GetScsiCommandExtensions");
                getScsiCommandExtensionsDelegate(*m_ScsiCommandExtensions);
            }

            cScsiCommandExtensions::~cScsiCommandExtensions()
            {
            }

            cScsiCommandExtensions::!cScsiCommandExtensions()
            {
            }

            vtStor::Managed::eErrorCode cScsiCommandExtensions::IssueCommand_AtaIdentifyDevice(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data)
            {
                vtStor::Managed::eErrorCode errorCode;
                std::shared_ptr<vtStor::IDrive> spDriveInterface = *reinterpret_cast<std::shared_ptr<vtStor::IDrive>*>((void*)Drive);
                std::shared_ptr<vtStor::IBuffer> spBuffferInterface = *reinterpret_cast<std::shared_ptr<vtStor::IBuffer>*>((void*)Data);
                errorCode = static_cast<vtStor::Managed::eErrorCode>(m_ScsiCommandExtensions->IssueCommand_AtaIdentifyDevice(spDriveInterface, CommandType, spBuffferInterface));
                return(errorCode);
            }

            vtStor::Managed::eErrorCode cScsiCommandExtensions::IssueCommand_AtaReadDma(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U32 Lba, U8 Count)
            {
                vtStor::Managed::eErrorCode errorCode;
                std::shared_ptr<vtStor::IDrive> spDriveInterface = *reinterpret_cast<std::shared_ptr<vtStor::IDrive>*>((void*)Drive);
                std::shared_ptr<vtStor::IBuffer> spBuffferInterface = *reinterpret_cast<std::shared_ptr<vtStor::IBuffer>*>((void*)Data);
                errorCode = static_cast<vtStor::Managed::eErrorCode>(m_ScsiCommandExtensions->IssueCommand_AtaReadDma(spDriveInterface, CommandType, spBuffferInterface, Lba, Count));
                return(errorCode);
            }

            vtStor::Managed::eErrorCode cScsiCommandExtensions::IssueCommand_AtaWriteDma(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U32 Lba, U8 Count)
            {
                vtStor::Managed::eErrorCode errorCode;
                std::shared_ptr<vtStor::IDrive> spDriveInterface = *reinterpret_cast<std::shared_ptr<vtStor::IDrive>*>((void*)Drive);
                std::shared_ptr<vtStor::IBuffer> spBuffferInterface = *reinterpret_cast<std::shared_ptr<vtStor::IBuffer>*>((void*)Data);
                errorCode = static_cast<vtStor::Managed::eErrorCode>(m_ScsiCommandExtensions->IssueCommand_AtaWriteDma(spDriveInterface, CommandType, spBuffferInterface, Lba, Count));
                return(errorCode);
            }

            vtStor::Managed::eErrorCode cScsiCommandExtensions::IssueCommand_AtaReadBuffer(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data)
            {
                vtStor::Managed::eErrorCode errorCode;
                std::shared_ptr<vtStor::IDrive> spDriveInterface = *reinterpret_cast<std::shared_ptr<vtStor::IDrive>*>((void*)Drive);
                std::shared_ptr<vtStor::IBuffer> spBuffferInterface = *reinterpret_cast<std::shared_ptr<vtStor::IBuffer>*>((void*)Data);
                errorCode = static_cast<vtStor::Managed::eErrorCode>(m_ScsiCommandExtensions->IssueCommand_AtaReadBuffer(spDriveInterface, CommandType, spBuffferInterface));
                return(errorCode);
            }

            vtStor::Managed::eErrorCode cScsiCommandExtensions::IssueCommand_AtaWriteBuffer(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data)
            {
                vtStor::Managed::eErrorCode errorCode;
                std::shared_ptr<vtStor::IDrive> spDriveInterface = *reinterpret_cast<std::shared_ptr<vtStor::IDrive>*>((void*)Drive);
                std::shared_ptr<vtStor::IBuffer> spBuffferInterface = *reinterpret_cast<std::shared_ptr<vtStor::IBuffer>*>((void*)Data);
                errorCode = static_cast<vtStor::Managed::eErrorCode>(m_ScsiCommandExtensions->IssueCommand_AtaWriteBuffer(spDriveInterface, CommandType, spBuffferInterface));
                return(errorCode);
            }

            vtStor::Managed::eErrorCode cScsiCommandExtensions::IssueCommand_AtaSmart(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U8 SubCommand)
            {
                vtStor::Managed::eErrorCode errorCode;
                std::shared_ptr<vtStor::IDrive> spDriveInterface = *reinterpret_cast<std::shared_ptr<vtStor::IDrive>*>((void*)Drive);
                std::shared_ptr<vtStor::IBuffer> spBuffferInterface = *reinterpret_cast<std::shared_ptr<vtStor::IBuffer>*>((void*)Data);
                errorCode = static_cast<vtStor::Managed::eErrorCode>(m_ScsiCommandExtensions->IssueCommand_AtaSmart(spDriveInterface, CommandType, spBuffferInterface, SubCommand));
                return(errorCode);
            }
        }
    }
}