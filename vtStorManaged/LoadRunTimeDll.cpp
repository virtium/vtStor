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

#include "LoadRunTimeDll.h"
#include "RunTimeDll.h"
#include <msclr\marshal.h>

using namespace msclr::interop;

namespace vtStor
{
    namespace Managed
    {
        cLoadRunTimeDll::cLoadRunTimeDll(System::String^ moduleName)
        {
            m_ModulePath = System::IO::Path::Combine(System::AppDomain::CurrentDomain->BaseDirectory, moduleName);
        }

        cLoadRunTimeDll::~cLoadRunTimeDll()
        {
        }

        cLoadRunTimeDll::!cLoadRunTimeDll()
        {
        }

        IRunTimeDll^ cLoadRunTimeDll::Load()
        {
            marshal_context context;
            SetDllDirectory(NULL); // Restores the default search order.
            HMODULE module = LoadLibrary(context.marshal_as<const TCHAR*>(m_ModulePath));
            if (NULL == module)
            {
                throw gcnew System::Exception(System::String::Format("Failed to load '{0}'. Error code 0x{1:x}.", m_ModulePath, GetLastError()));
            }
            return gcnew cRunTimeDll(module, m_ModulePath);
        }
    }
}
