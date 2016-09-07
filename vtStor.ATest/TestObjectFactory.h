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

#ifndef __TestObjectFactory_h__
#define __TestObjectFactory_h__
#pragma once

#include <map>
#include <memory>

#include "IVtStorTest.h"
#include "BasicTypes.h"

namespace vtStorATest
{
    template<typename T>
    std::shared_ptr<IVtStorTest> Instantiate()
    {
        return(std::make_shared<T>());
    }

    // Create test objects based on registered name
    class TestObjectFactory
    {
    public:
        // Use Singelton pattern
        static std::shared_ptr<TestObjectFactory> GetInstance();

    private:
        TestObjectFactory();

    public:
        virtual ~TestObjectFactory();

    public:
        std::shared_ptr<IVtStorTest> Create(const vtStor::String& TypeName);
        std::map<vtStor::String, std::shared_ptr<IVtStorTest>(*)()> GetMapTypeData();

    public:
        template<typename T>
        void Register(const vtStor::String& TypeName)
        {
            m_MapTypeData.insert({ TypeName, Instantiate<T> });
        }

    private:
        // Mapping registered names with IVtStorTest objects
        std::map<vtStor::String, std::shared_ptr<IVtStorTest>(*)()> m_MapTypeData;
    };
}
#endif