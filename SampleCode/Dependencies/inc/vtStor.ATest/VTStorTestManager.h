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

#ifndef __VtStorTestManager_h__
#define __VtStorTestManager_h__
#pragma once

#include "IVtStorTest.h"
#include "ITestManager.h"
#include "TestResource.h"
#include "TestObjectFactory.h"

namespace vtStorATest
{
    struct sStatisticResult
    {
        vtStor::U32 TotalTest;
        vtStor::U32 PassedTest;
        vtStor::U32 FailedTest;
        // TODO: Number of Errors
        // TODO: Time for run test
    };

    class VTStorTestManager :public ITestManager
    {
    public:
        VTStorTestManager();
        ~VTStorTestManager();

    public:
        virtual bool RunAll() override;
        virtual bool RunSpecificTest() override;
        virtual void ListAllTestObjects() override;

    private:
        std::shared_ptr<TestObjectFactory> m_TestObjectFactory;
        std::map<vtStor::String, std::shared_ptr<IVtStorTest>(*)()> m_MapTypeData;
    };
}

#endif