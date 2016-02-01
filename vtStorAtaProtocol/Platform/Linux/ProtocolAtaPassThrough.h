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
#include <scsi/sg.h>

#include "Ata.h"
#include "IBuffer.h"
#include "ErrorCodes.h"
#include "IProtocol.h"
#include "vtStorAtaProtocolPlatformDefines.h"

namespace vtStor
{
namespace Protocol
{

const U8  SG_ATA_LBA48 = 0x01; // Extend 48 bit

//! Structure for send Ata command pass through SG drivers
enum class eSgAtaPassThough16
{
    SgInterfaceId       = 'S',  // 'S' for SCSI generic
    SgAtaPassThough     = 0x85, // Send Ata command pass through SG drivers
    SgCdbLengh          = 16,   // Command Descriptor Block length
    MaxSenseDataLength  = 32,   // Max of Sense Data Length
};

enum class eTransferLenghValue
{
    NoDataTranfer         = 0x0, // No data is transferred
    SpecInFeature         = 0x1, // The transfer length is specified in the FEATURE field
    SpecInSectorCount     = 0x2, // The transfer length is specified in the SECTOR COUNT field
};

//! Specifies the number of bytes to transfer or the number of blocks to transfer
enum class eByteBlockBit
{
    TransferByteMode   = 0, // Transfer the number of bytes specified in the transfer lengh field
    TransferSectorMode = 1, // Transfer the number of blocks specified in the transfer lengh field
};

enum class eTransferDirection
{
    TransferToDevice   = 0,
    TransferFromDevice = 1,
};

enum class eCheckCondition
{
    ErrorTerminate  = 0,
    CommonTerminate = 1,
};

enum class eATAProtocolField
{
    HardReset                   = 0,
    SRST                        = 1,
    NonData                     = 3,
    PIO_Data_In                 = 4,
    PIO_Data_Out                = 5,
    DMA                         = 6,
    DMA_Queued                  = 7,
    DeviceDiagnostic            = 8,
    DeviceReset                 = 9,
    UDMA_Data_In                = 10,
    UDMA_Data_Out               = 11,
    FPDMA                       = 12,
    ResponseInformation         = 15,
};

//! Using bit field
struct sCommandDescBlock16Field1
{
    U8 Extend           : 1; // 1 bit
    U8 Protocol         : 4; // 4 bit
    U8 MultipleCount    : 3; // 3 bit
};

//! Using bit field
struct sCommandDescBlock16Field2
{
    U8 TLength          : 2; // 2 bit
    U8 BytBlock         : 1; // 1 bit
    U8 TDir             : 1; // 1 bit
    U8 Reserved         : 1; // 1 bit
    U8 CheckCondition   : 1; // 1 bit
    U8 OffLine          : 2; // 2 bit
};

struct sCommandDescBlock16
{
    U8                             Opcode;                 // Byte 0
    sCommandDescBlock16Field1      ExtendProtocol;         // Byte 1
    sCommandDescBlock16Field2      Param;                  // Byte 2
    U8                             HighFeature;            // Byte 3
    U8                             LowFeature;             // Byte 4
    U8                             HighSectorCount;        // Byte 5
    U8                             LowSectorCount;         // Byte 6
    U8                             HighObLbaLow;           // Byte 7
    U8                             LowObLbaLow;            // Byte 8
    U8                             HighObLbaMid;           // Byte 9
    U8                             LowObLbaMid;            // Byte 10
    U8                             HighObLbaHigh;          // Byte 11
    U8                             LowObLbaHigh;           // Byte 12
    U8                             LowDevice;              // Byte 13
    U8                             LowCommand;             // Byte 14
    U8                             Control;                // Byte 15
};

class VT_STOR_ATA_PROTOCOL_API cAtaPassThrough : public IProtocol
{

public:
    virtual eErrorCode IssueCommand(const DeviceHandle& Handle, std::shared_ptr<const IBuffer> Essense, std::shared_ptr<IBuffer> DataBuffer) override;

private:
    void InitializeCommandDescBlock16Registers(const StorageUtility::Ata::uTaskFileRegister& PreviousTaskFile, const StorageUtility::Ata::uTaskFileRegister& CurrentTaskFile);

    void cAtaPassThrough::InitializePassThroughDirect(
            const StorageUtility::Ata::sCommandCharacteristic& CommandCharacteristics,
            const StorageUtility::Ata::uTaskFileRegister& PreviousTaskFile,
            const StorageUtility::Ata::uTaskFileRegister& CurrentTaskFile,
            std::shared_ptr<IBuffer> DataBuffer, U32 TimeoutValueInSeconds
            );

    void InitializeCommandDescBlock16Flags(const StorageUtility::Ata::sCommandCharacteristic& AtaCommandCharacteristic);

    void InitializeFlags(const StorageUtility::Ata::sCommandCharacteristic& AtaCommandCharacteristic);

    eErrorCode IssuePassThroughDirectCommand(const U32& FileDescriptor);

private:
    sg_io_hdr m_ATAPassThrough;
    sCommandDescBlock16 m_CommandDescBlock16;
};

}
}