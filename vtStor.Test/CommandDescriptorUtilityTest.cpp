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
            template<> static std::wstring ToString<vtStor::cAta::eDeviceReadyFlag>( const vtStor::cAta::eDeviceReadyFlag& t ) { RETURN_WIDE_STRING( t ); }
            template<> static std::wstring ToString<vtStor::cAta::eDataAccess>( const vtStor::cAta::eDataAccess& t ) { RETURN_WIDE_STRING( t ); }
            template<> static std::wstring ToString<vtStor::cAta::eFieldFormatting>( const vtStor::cAta::eFieldFormatting& t ) { RETURN_WIDE_STRING( t ); }
            template<> static std::wstring ToString<vtStor::cAta::eTransferMode>( const vtStor::cAta::eTransferMode& t ) { RETURN_WIDE_STRING( t ); }
            template<> static std::wstring ToString<vtStor::cAta::eMultipleMode>( const vtStor::cAta::eMultipleMode& t ) { RETURN_WIDE_STRING( t ); }
        }
    }
}

using namespace vtStor;

namespace vtStorTest
{
    TEST_CLASS( cAtaCommandDescriptorUtilityTest )
    {
    public:

        TEST_METHOD( CommandField )
        {
            std::shared_ptr<cBufferInterface> commandDescriptor = std::make_shared<cBuffer>( 128 );
            Ata::cCommandDescriptorVersion1 commandDescriptorVersion1( commandDescriptor );

            cAta::uCommandFields& commandFields = commandDescriptorVersion1.GetCommandFields();
            commandFields.InputFields.Command = Ata::ATA_COMMAND_IDENTIFY_DEVICE;
            commandFields.InputFields.Count = 1;
            //--Test are unrelevant to identify device command, but we're testing assigment only.
            commandFields.InputFields.ChsMode = false;
            commandFields.InputFields.Device = 0xe0;
            commandFields.InputFields.Feature = 0;
            commandFields.InputFields.Lba = 0;

            cAta::sCommandCharacteristic& commandCharacteristics = commandDescriptorVersion1.GetCommandCharacteristics();
            commandCharacteristics.DeviceReadyFlag = cAta::eDeviceReadyFlag::DEVICE_READY_REQUIRED;
            commandCharacteristics.DataAccess = cAta::eDataAccess::READ_FROM_DEVICE;
            commandCharacteristics.FieldFormatting = cAta::eFieldFormatting::COMMAND_28_BIT;
            commandCharacteristics.TransferMode = cAta::eTransferMode::PIO_PROTOCOL;
            commandCharacteristics.MultipleMode = cAta::eMultipleMode::NOT_MULTIPLE_COMMAND;
            commandCharacteristics.DataTransferLengthInBytes = cAta::SECTOR_SIZE_IN_BYTES;

            U8* buffer = commandDescriptor->ToDataBuffer();

            U16 version = (buffer[0] << 8) | (buffer[1]);
            Assert::AreEqual( (U16)1, version, L"Command descriptor version does not match.", LINE_INFO() );

            cAta::uCommandFields& commandFields2 = commandDescriptorVersion1.GetCommandFields();
            Assert::AreEqual( commandFields.InputFields.Command, commandFields2.InputFields.Command, L"Command descriptor input field <Command> does not match.", LINE_INFO() );
            Assert::AreEqual( commandFields.InputFields.Count, commandFields2.InputFields.Count, L"Command descriptor input field <Count> does not match.", LINE_INFO() );
            Assert::AreEqual( commandFields.InputFields.ChsMode, commandFields2.InputFields.ChsMode, L"Command descriptor input field <ChsMode> does not match.", LINE_INFO() );
            Assert::AreEqual( commandFields.InputFields.Device, commandFields2.InputFields.Device, L"Command descriptor input field <Device> does not match.", LINE_INFO() );
            Assert::AreEqual( commandFields.InputFields.Feature, commandFields2.InputFields.Feature, L"Command descriptor input field <Feature> does not match.", LINE_INFO() );
            Assert::AreEqual( commandFields.InputFields.Lba, commandFields2.InputFields.Lba, L"Command descriptor input field <Lba> does not match.", LINE_INFO() );

            cAta::sCommandCharacteristic& commandCharacteristics2 = commandDescriptorVersion1.GetCommandCharacteristics();
            Assert::AreEqual( cAta::eDeviceReadyFlag::DEVICE_READY_REQUIRED, commandCharacteristics2.DeviceReadyFlag, L"Command descriptor characteristic <DeviceReadyFlag> does not match.", LINE_INFO() );
            Assert::AreEqual( cAta::eDataAccess::READ_FROM_DEVICE, commandCharacteristics2.DataAccess, L"Command descriptor characteristic <DataAccess> does not match.", LINE_INFO() );
            Assert::AreEqual( cAta::eFieldFormatting::COMMAND_28_BIT, commandCharacteristics2.FieldFormatting, L"Command descriptor characteristic <FieldFormating> does not match.", LINE_INFO() );
            Assert::AreEqual( cAta::eTransferMode::PIO_PROTOCOL, commandCharacteristics2.TransferMode, L"Command descriptor characteristic <TransferMode> does not match.", LINE_INFO() );
            Assert::AreEqual( cAta::eMultipleMode::NOT_MULTIPLE_COMMAND, commandCharacteristics2.MultipleMode, L"Command descriptor characteristic <MultipleMode> does not match.", LINE_INFO() );
            Assert::AreEqual( cAta::SECTOR_SIZE_IN_BYTES, commandCharacteristics2.DataTransferLengthInBytes, L"Command descriptor characteristic <DataTransferLengthInBytes> does not match.", LINE_INFO() );
        }

        

    };
}