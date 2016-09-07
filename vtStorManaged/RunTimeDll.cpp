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

#include "RunTimeDll.h"

namespace vtStor
{
    namespace Managed
    {
        cRunTimeDll::cRunTimeDll(HMODULE Module, System::String^ ModulePath)
        {
            m_Module = Module;
            m_ModulePath = ModulePath;
        }

        cRunTimeDll::~cRunTimeDll()
        {
            this->!cRunTimeDll();
        }

        cRunTimeDll::!cRunTimeDll()
        {
            if (!FreeLibrary(m_Module))
            {
                throw gcnew System::Exception(System::String::Format("FreeLibrary failed to free '{0}'. Error code 0x{1:x}.", m_ModulePath, GetLastError()));
            }
        }

        FARPROC cRunTimeDll::GetFunction(LPCSTR name)
        {
            FARPROC function = GetProcAddress(m_Module, name);
            if (NULL == function)
            {
                throw gcnew System::Exception(System::String::Format("Failed to get '{0}' function. Error code 0x{1:x}.", gcnew System::String(name), GetLastError()));
            }
            return function;
        }
    }
}
