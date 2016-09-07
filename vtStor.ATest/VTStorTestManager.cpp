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

#include "VtStorATestDefine.h"
#include "VtStorTestManager.h"

namespace vtStorATest
{
    VTStorTestManager::VTStorTestManager()
    {
        m_TestObjectFactory = TestObjectFactory::GetInstance();
        m_MapTypeData = m_TestObjectFactory->GetMapTypeData();
    }

    VTStorTestManager::~VTStorTestManager()
    {
    }

    bool VTStorTestManager::RunAll()
    {
        bool result = true;
        sStatisticResult statisticResult;
        std::map<vtStor::String, std::shared_ptr<IVtStorTest>(*)()>::iterator it;

        statisticResult.TotalTest = m_MapTypeData.size();
        statisticResult.PassedTest = 0;
        statisticResult.FailedTest = 0;

        for (it = m_MapTypeData.begin(); it != m_MapTypeData.end(); ++it)
        {
            VtStorPrintln << "Run " << it->first;
            std::shared_ptr<IVtStorTest> testObject = m_TestObjectFactory->Create(it->first);
            if (nullptr != testObject)
            {
                if (true == testObject->Run())
                {
                    statisticResult.PassedTest = statisticResult.PassedTest + 1;
                    VtStorPrintln << "PASSED" << std::endl;
                }
                else
                {
                    statisticResult.FailedTest = statisticResult.FailedTest + 1;
                    result = false;
                    VtStorPrintln << "FAILED" << std::endl;
                }
            }
            else
            {
                // TODO : Duplicate name of TestObject registered
            }
        }

        VtStorPrintln << "Result of test process:";
        VtStorPrintln << "\t" << "Total tests = " << statisticResult.TotalTest;
        VtStorPrintln << "\t" << "Tests passed = " << statisticResult.PassedTest;
        VtStorPrintln << "\t" << "Tests failed = " << statisticResult.FailedTest;

        return result;
    }

    bool VTStorTestManager::RunSpecificTest()
    {
        vtStor::U32 option;

        VtStorPrintln << "Select a Test: ";
        std::cin >> option;

        std::map<vtStor::String, std::shared_ptr<IVtStorTest>(*)()>::iterator it = m_MapTypeData.begin();
        if (m_TestObjectFactory->GetMapTypeData().size() > option)
        {
            std::advance(it, option); // jump to number of option value
            VtStorPrintln << "Run " << it->first;

            std::shared_ptr<IVtStorTest> testObject = m_TestObjectFactory->Create(it->first);
            if (true == testObject->Run())
            {
                VtStorPrintln << "PASSED" << std::endl;
            }
            else
            {
                VtStorPrintln << "FAILED" << std::endl;
            }
        }
        else
        {
            VtStorPrintln << "Option out range";
        }
        return false;
    }

    void VTStorTestManager::ListAllTestObjects()
    {
        vtStor::U32 index = 0;
        std::map<vtStor::String, std::shared_ptr<IVtStorTest>(*)()>::iterator it;

        VtStorPrintln << "List Tests";
        for (it = m_MapTypeData.begin(); it != m_MapTypeData.end(); ++it)
        {
            VtStorPrintln << index++ << "." << " " << it->first.c_str();
        }
    }
}