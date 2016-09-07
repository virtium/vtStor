#include "DataAccessCommandTest.h"
#include "ATestUtility.h"
#include "VtStorATestDefine.h"
#include "TestResource.h"

namespace vtStorATest
{
    DataAccessCommandTest::DataAccessCommandTest()
    {
        m_TestResource = TestResource::GetInstance();
    }

    DataAccessCommandTest::~DataAccessCommandTest()
    {
    }

    // Issue read and write commands then verify ReadBuffer and WriteBuffer
    bool DataAccessCommandTest::ReadWriteVerify(vtStor::U32 Lba, vtStor::U32 SectorCount)
    {
        m_TestResource->MemsetReadWriteBuffer();

        VtStorPrintln << "\t" << "Lba = " << Lba << ", " << "SectorCount = " << SectorCount;

        if ((vtStor::eErrorCode::None != SendWriteCommand(Lba, SectorCount))
            || (vtStor::eErrorCode::None != SendReadCommand(Lba, SectorCount)))
        {
            return false;
        }

        bool result = ATestUtility::CompareBuffers(m_TestResource->GetDataWriteBuffer(), m_TestResource->GetDataReadBuffer(), SectorCount);

        return (result);
    }

    bool DataAccessCommandTest::Run()
    {
        vtStor::eErrorCode identifyErrorCode = vtStor::eErrorCode::None;

        // Use ATA
        cCommandHandlerAta_GetCommandHandler(m_TestResource->GetCommandHandler(), m_TestResource->GetAtaProtocol());

        // Register command handler
        m_TestResource->GetSelectedDrive()->RegisterCommandHandler(TestResource::COMMAND_HANDLE_ATA_COMMAND_TYPE, m_TestResource->GetCommandHandler());

        bool result = true;
        result &= TestBoundary();
        result &= TestRandom();
        result &= TestOutOfBound();

        return (result);
    }

    // Call ReadWriteVerify with Lba and SectorCount at boundary values
    bool vtStorATest::DataAccessCommandTest::TestBoundary()
    {
        VtStorPrintln << "\t" << "_TestBoundary : Test min and max values";

        vtStor::U32 maxUserLba = m_TestResource->GetSelectedDriveInfo().MaxUserLBA - 1;
        vtStor::U32 maxSectorCountExt = 256;
        vtStor::U32 minLba = 0;
        vtStor::U32 minSectorCount = 1;

        if ((true == ReadWriteVerify(minLba, minSectorCount))
            && (true == ReadWriteVerify(minLba, maxSectorCountExt))
            && (true == ReadWriteVerify(maxUserLba, minSectorCount))
            )
        {
            VtStorPrintln << "\t" << "TestCase passed";
            VtStorPrintln;
            return true;
        }
        else
        {
            VtStorPrintln << "\t" << "TestCase failed";
            VtStorPrintln;
            return false;
        }
    }

    // Call ReadWriteVerify with random Lba and SectorCount in exceptable values
    bool vtStorATest::DataAccessCommandTest::TestRandom()
    {
        bool result = true;
        VtStorPrintln << "\t" << "_TestRandom : Random LBA and SectorCount between min value and max value";

        // Do some times (10 times) read, write and verify with random values
        for (vtStor::U32 i = 0; i < 10; ++i)
        {
            vtStor::U32 randLba = ATestUtility::MakeRandomValue(m_TestResource->GetSelectedDriveInfo().MaxUserLBA);
            vtStor::U32 randSectorCount = ATestUtility::MakeRandomValue(256) + 1; // Windows support issue command with maximum 256 sectors

            if (false == (ReadWriteVerify(randLba, randSectorCount)))
            {
                VtStorPrintln << "\t" << "TestCase failed ";
                VtStorPrintln;
                result = false;
            }
        }

        if (true == result)
        {
            VtStorPrintln << "\t" << "TestCase passed";
            VtStorPrintln;
        }

        return result;
    }

    // Call ReadWriteVerify with Lba and SectorCount out of bound exceptable values
    bool vtStorATest::DataAccessCommandTest::TestOutOfBound()
    {
        VtStorPrintln << "\t" << "Test_OutOfBound: Value for test out of expected values";

        vtStor::U32 outOfBoundLba = m_TestResource->GetSelectedDriveInfo().MaxUserLBA;
        vtStor::U32 outOfBoundSectorCount = 257;
        vtStor::U32 minLba = 0;
        vtStor::U32 minSectorCount = 1;

        if ((false == (ReadWriteVerify(outOfBoundLba, outOfBoundSectorCount))
            && (false == ReadWriteVerify(minLba, outOfBoundSectorCount))
            && (false == ReadWriteVerify(outOfBoundLba, minSectorCount))
            && (false == ReadWriteVerify(outOfBoundLba, outOfBoundSectorCount))
            )
            )
        {
            VtStorPrintln << "\t" << "TestCase passed";
            VtStorPrintln;
            return true;
        }
        else
        {
            VtStorPrintln << "\t" << "TestCase failed";
            VtStorPrintln;
            return false;
        }
    }
}