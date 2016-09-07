#ifndef __DataAccessCommandTest_h__
#define __DataAccessCommandTest_h__
#pragma once

#include "IVtStorTest.h"
#include "TestResource.h"

namespace vtStorATest
{
    class DataAccessCommandTest : public IVtStorTest
    {
    public:
        DataAccessCommandTest();
        ~DataAccessCommandTest();

    public:
        virtual vtStor::eErrorCode SendReadCommand(vtStor::U32 Lba, vtStor::U32 SectorCount) = 0;
        virtual vtStor::eErrorCode SendWriteCommand(vtStor::U32 Lba, vtStor::U32 SectorCount) = 0;

    protected:
        // Run all testcases, passed when all testcases passed
        // 1. TestBoundary
        // 2. TestRandom
        // 3. TestOutOfBound
        virtual bool Run() override;

        // Call ReadWriteVerify with Lba and SectorCount at boundary values
        virtual bool TestBoundary();

        // Call ReadWriteVerify with random Lba and SectorCount in exceptable values
        virtual bool TestRandom();

        // Call ReadWriteVerify with Lba and SectorCount out of bound exceptable values
        virtual bool TestOutOfBound();

    private:
        // Issue read and write commands then verify ReadBuffer and WriteBuffer
        bool ReadWriteVerify(vtStor::U32 Lba, vtStor::U32 SectorCount);

    protected:
        std::shared_ptr<TestResource> m_TestResource;
    };
}
#endif