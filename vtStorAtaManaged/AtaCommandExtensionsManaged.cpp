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

#include <memory>

#include "IDrive.h"
#include "IBuffer.h"
#include "AtaCommandExtensionsManaged.h"

namespace vtStor
{
    namespace Ata
    {
        namespace Managed
        {
            cAtaCommandExtensions::cAtaCommandExtensions(vtStor::Managed::IRunTimeDll^ RunTimeDll)
            {
                GetAtaCommandExtensionsDelegate getAtaCommandExtensionsDelegate = (GetAtaCommandExtensionsDelegate)RunTimeDll->GetFunction("cAtaCommandExtensions_GetAtaCommandExtensions");
                getAtaCommandExtensionsDelegate(*m_AtaCommandExtensions);
            }

            cAtaCommandExtensions::~cAtaCommandExtensions()
            {
            }

            cAtaCommandExtensions::!cAtaCommandExtensions()
            {
            }

            vtStor::Managed::eErrorCode cAtaCommandExtensions::IssueCommand_IdentifyDevice(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data)
            {
                vtStor::Managed::eErrorCode errorCode;
                std::shared_ptr<vtStor::IDrive> spDriveInterface = *reinterpret_cast<std::shared_ptr<vtStor::IDrive>*>((void*)Drive);
                std::shared_ptr<vtStor::IBuffer> spBuffferInterface = *reinterpret_cast<std::shared_ptr<vtStor::IBuffer>*>((void*)Data);
                errorCode = static_cast<vtStor::Managed::eErrorCode>(m_AtaCommandExtensions->IssueCommand_IdentifyDevice(spDriveInterface, CommandType, spBuffferInterface));
                return(errorCode);
            }

            vtStor::Managed::eErrorCode cAtaCommandExtensions::IssueCommand_ReadDma(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U32 Lba, U8 Count)
            {
                vtStor::Managed::eErrorCode errorCode;
                std::shared_ptr<vtStor::IDrive> spDriveInterface = *reinterpret_cast<std::shared_ptr<vtStor::IDrive>*>((void*)Drive);
                std::shared_ptr<vtStor::IBuffer> spBuffferInterface = *reinterpret_cast<std::shared_ptr<vtStor::IBuffer>*>((void*)Data);
                errorCode = static_cast<vtStor::Managed::eErrorCode>(m_AtaCommandExtensions->IssueCommand_ReadDma(spDriveInterface, CommandType, spBuffferInterface, Lba, Count));
                return(errorCode);
            }

            vtStor::Managed::eErrorCode cAtaCommandExtensions::IssueCommand_WriteDma(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U32 Lba, U8 Count)
            {
                vtStor::Managed::eErrorCode errorCode;
                std::shared_ptr<vtStor::IDrive> spDriveInterface = *reinterpret_cast<std::shared_ptr<vtStor::IDrive>*>((void*)Drive);
                std::shared_ptr<vtStor::IBuffer> spBuffferInterface = *reinterpret_cast<std::shared_ptr<vtStor::IBuffer>*>((void*)Data);
                errorCode = static_cast<vtStor::Managed::eErrorCode>(m_AtaCommandExtensions->IssueCommand_WriteDma(spDriveInterface, CommandType, spBuffferInterface, Lba, Count));
                return(errorCode);
            }

            vtStor::Managed::eErrorCode cAtaCommandExtensions::IssueCommand_ReadBuffer(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data)
            {
                vtStor::Managed::eErrorCode errorCode;
                std::shared_ptr<vtStor::IDrive> spDriveInterface = *reinterpret_cast<std::shared_ptr<vtStor::IDrive>*>((void*)Drive);
                std::shared_ptr<vtStor::IBuffer> spBuffferInterface = *reinterpret_cast<std::shared_ptr<vtStor::IBuffer>*>((void*)Data);
                errorCode = static_cast<vtStor::Managed::eErrorCode>(m_AtaCommandExtensions->IssueCommand_ReadBuffer(spDriveInterface, CommandType, spBuffferInterface));
                return(errorCode);
            }

            vtStor::Managed::eErrorCode cAtaCommandExtensions::IssueCommand_WriteBuffer(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data)
            {
                vtStor::Managed::eErrorCode errorCode;
                std::shared_ptr<vtStor::IDrive> spDriveInterface = *reinterpret_cast<std::shared_ptr<vtStor::IDrive>*>((void*)Drive);
                std::shared_ptr<vtStor::IBuffer> spBuffferInterface = *reinterpret_cast<std::shared_ptr<vtStor::IBuffer>*>((void*)Data);
                errorCode = static_cast<vtStor::Managed::eErrorCode>(m_AtaCommandExtensions->IssueCommand_WriteBuffer(spDriveInterface, CommandType, spBuffferInterface));
                return(errorCode);
            }

            vtStor::Managed::eErrorCode cAtaCommandExtensions::IssueCommand_Smart(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U8 SubCommand)
            {
                vtStor::Managed::eErrorCode errorCode;
                std::shared_ptr<vtStor::IDrive> spDriveInterface = *reinterpret_cast<std::shared_ptr<vtStor::IDrive>*>((void*)Drive);
                std::shared_ptr<vtStor::IBuffer> spBuffferInterface = *reinterpret_cast<std::shared_ptr<vtStor::IBuffer>*>((void*)Data);
                errorCode = static_cast<vtStor::Managed::eErrorCode>(m_AtaCommandExtensions->IssueCommand_Smart(spDriveInterface, CommandType, spBuffferInterface, SubCommand));
                return(errorCode);
            }

            vtStor::Managed::eErrorCode cAtaCommandExtensions::IssueCommand_DownloadMicrocode(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U8 SubCommand, U16 BlockCount, U16 BufferOffset)
            {
                vtStor::Managed::eErrorCode errorCode;
                std::shared_ptr<vtStor::IDrive> spDriveInterface = *reinterpret_cast<std::shared_ptr<vtStor::IDrive>*>((void*)Drive);
                std::shared_ptr<vtStor::IBuffer> spBuffferInterface = *reinterpret_cast<std::shared_ptr<vtStor::IBuffer>*>((void*)Data);
                errorCode = static_cast<vtStor::Managed::eErrorCode>(m_AtaCommandExtensions->IssueCommand_DownloadMicrocode(spDriveInterface, CommandType, spBuffferInterface, SubCommand, BlockCount, BufferOffset));
                return(errorCode);
            }

            vtStor::Managed::eErrorCode cAtaCommandExtensions::IssueCommand_DownloadMicrocodeDma(vtStor::Managed::cDriveInterface^ Drive, U32 CommandType, vtStor::Managed::cBufferInterface^ Data, U8 SubCommand, U16 BlockCount, U16 BufferOffset)
            {
                vtStor::Managed::eErrorCode errorCode;
                std::shared_ptr<vtStor::IDrive> spDriveInterface = *reinterpret_cast<std::shared_ptr<vtStor::IDrive>*>((void*)Drive);
                std::shared_ptr<vtStor::IBuffer> spBuffferInterface = *reinterpret_cast<std::shared_ptr<vtStor::IBuffer>*>((void*)Data);
                errorCode = static_cast<vtStor::Managed::eErrorCode>(m_AtaCommandExtensions->IssueCommand_DownloadMicrocodeDma(spDriveInterface, CommandType, spBuffferInterface, SubCommand, BlockCount, BufferOffset));
                return(errorCode);
            }
        }
    }
}