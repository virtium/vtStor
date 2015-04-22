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

#include "CppUnitTest.h"

#include "vtStor.h"
#include "vtStorAta.h"
#include "DriveEnumeratorAta.h"
#include "DriveAtaCommandExtensions.h"
#include "Buffer.h"
#include "CommandDescriptorUtility.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft
{
    namespace VisualStudio
    {
        namespace CppUnitTestFramework
        {
            template<> static std::wstring ToString<vtStor::U16>( const vtStor::U16& t ) { RETURN_WIDE_STRING( t ); }
        }
    }
}

namespace vtStorTest
{
    TEST_CLASS( cAtaCommandDescriptorUtilityTest )
    {
    public:

        TEST_METHOD( CommandField )
        {
            std::shared_ptr<vtStor::cBufferInterface> commandDescriptor = std::make_shared<vtStor::cBuffer>( 128 );
            vtStor::Ata::cCommandDescriptorVersion1 commandDescriptorVersion1( commandDescriptor );

            vtStor::cAta::uCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
            commandFields.InputFields.Command = vtStor::Ata::ATA_COMMAND_IDENTIFY_DEVICE;
            commandFields.InputFields.Count = 1;

            //--Test are unrelevant to identify device command, but we're testing assigment only.
            commandFields.InputFields.ChsMode = false;
            commandFields.InputFields.Device = 0xe0;
            commandFields.InputFields.Feature = 0;
            commandFields.InputFields.Lba = 0;

            vtStor::U8* buffer = commandDescriptor->ToDataBuffer();

            vtStor::U16 version = (buffer[0] << 8) | (buffer[1]);
            Assert::AreEqual( (vtStor::U16)1, version, L"Command descriptor version does not match.", LINE_INFO() );

            vtStor::cAta::uCommandFields& commandFields2 = commandDescriptorVersion1.GetCommandFields();

            Assert::AreEqual( commandFields.InputFields.Command, commandFields2.InputFields.Command, L"Command descriptor input field <Command> does not match.", LINE_INFO() );
            Assert::AreEqual( commandFields.InputFields.Count, commandFields2.InputFields.Count, L"Command descriptor input field <Count> does not match.", LINE_INFO() );
            Assert::AreEqual( commandFields.InputFields.ChsMode, commandFields2.InputFields.ChsMode, L"Command descriptor input field <ChsMode> does not match.", LINE_INFO() );
            Assert::AreEqual( commandFields.InputFields.Device, commandFields2.InputFields.Device, L"Command descriptor input field <Device> does not match.", LINE_INFO() );
            Assert::AreEqual( commandFields.InputFields.Feature, commandFields2.InputFields.Feature, L"Command descriptor input field <Feature> does not match.", LINE_INFO() );
            Assert::AreEqual( commandFields.InputFields.Lba, commandFields2.InputFields.Lba, L"Command descriptor input field <Lba> does not match.", LINE_INFO() );
        }

        

    };
}