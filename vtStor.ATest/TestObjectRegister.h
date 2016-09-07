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

#ifndef __TestObjectRegister_h__
#define __TestObjectRegister_h__
#pragma once

#include "TestObjectFactory.h"

namespace vtStorATest
{
    // Make the registration of the test object to management by name
    template<typename T>
    class TestObjectRegister
    {
    public:
        TestObjectRegister(const vtStor::String &ClassName)
        {
            std::shared_ptr<TestObjectFactory> testConvertFactory = TestObjectFactory::GetInstance();
            testConvertFactory->Register<T>(ClassName);
        }

        ~TestObjectRegister()
        {
        }
    };
}
#endif