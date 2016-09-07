#ifndef __ITestManager_h__
#define __ITestManager_h__
#pragma once

namespace vtStorATest
{
    class ITestManager
    {
    public:
        // Run all tests, return true if all tests passed
        virtual bool RunAll() = 0;

        // Run a specific test
        virtual bool RunSpecificTest() = 0;

        // List all tests
        virtual void ListAllTestObjects() = 0;
    };
}

#endif