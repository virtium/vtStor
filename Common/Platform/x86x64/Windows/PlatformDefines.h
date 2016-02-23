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
#ifndef __vtStorCommonPlatformDefines_h__
#define __vtStorCommonPlatformDefines_h__

#include <string>
#include <Windows.h>

#include "BusType.h"

#ifdef _UNICODE
#define    __STORAPITEXT( s ) L##s
#define tstrlen wcslen
#define tmemcpy_s wmemcpy_s
using tchar = wchar_t;
using tstring = std::wstring;
#else
#define    __STORAPITEXT( s ) s
#define tstrlen strlen
#define tmemcpy_s memcpy_s
using tchar = char;
using tstring = std::string;
#endif

#define OS_API WINAPIV

#if defined( VTSTOR_MANAGED_CPP )
#define VTSTOR_DLL_STL_IMPL(x)
#else
#define VTSTOR_DLL_STL_IMPL(x)  x
#endif

#ifdef VTSTOR_DLL_EXPORTS
#define VTSTOR_API _declspec( dllexport )
#define VTSTOR_API_EXPORT_IMPL
#else
#define VTSTOR_API _declspec( dllimport )
#define VTSTOR_API_EXPORT_IMPL  extern
#endif

#ifdef VT_STOR_ATA_DLL_EXPORTS
#define VT_STOR_ATA_API _declspec( dllexport )
#else
#define VT_STOR_ATA_API _declspec( dllimport )
#endif

#ifdef VT_STOR_ATA_PROTOCOL_DLL_EXPORTS
#define VT_STOR_ATA_PROTOCOL_API _declspec( dllexport )
#else
#define VT_STOR_ATA_PROTOCOL_API _declspec( dllimport )
#endif

#ifdef VT_STOR_SCSI_DLL_EXPORTS
#define VT_STOR_SCSI_API _declspec( dllexport )
#else
#define VT_STOR_SCSI_API _declspec( dllimport )
#endif

#ifdef VT_STOR_SCSI_PROTOCOL_DLL_EXPORTS
#define VT_STOR_SCSI_PROTOCOL_API _declspec( dllexport )
#else
#define VT_STOR_SCSI_PROTOCOL_API _declspec( dllimport )
#endif

namespace vtStor
{
    struct sDeviceHandle
    {
        HANDLE Handle;
        eBusType Bus;
    };
    using DeviceHandle = sDeviceHandle;
}

#endif
