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

#include "TestObjectFactory.h"

namespace vtStorATest
{
    TestObjectFactory::TestObjectFactory()
    {
    }

    TestObjectFactory::~TestObjectFactory()
    {
        m_MapTypeData.clear();
    }

    std::shared_ptr<TestObjectFactory> TestObjectFactory::GetInstance()
    {
        static std::shared_ptr<TestObjectFactory> instance;
        if (nullptr == instance)
        {
            instance = std::shared_ptr<TestObjectFactory>(new TestObjectFactory());
        }
        return(instance);
    }

    std::shared_ptr<IVtStorTest> TestObjectFactory::Create(const vtStor::String& TypeName)
    {
        std::map< vtStor::String, std::shared_ptr<IVtStorTest>(*)()>::iterator it = m_MapTypeData.find(TypeName);
        if (it == m_MapTypeData.end())
        {
            return(nullptr);
        }
        return(it->second());
    }

    std::map<vtStor::String, std::shared_ptr<IVtStorTest>(*)()> TestObjectFactory::GetMapTypeData()
    {
        return m_MapTypeData;
    }
}
