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
#ifndef __vtStorCommonPlatformDefines_h__
#define __vtStorCommonPlatformDefines_h__

#include <string>
#include <cstring>

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

#define WINAPIV

#ifdef VTSTOR_DLL_EXPORTS
#define VTSTOR_API
#define VTSTOR_API_EXPORT_IMPL
#else
#define VTSTOR_API
#define VTSTOR_API_EXPORT_IMPL
#endif

#ifdef VT_STOR_ATA_DLL_EXPORTS
#define VT_STOR_ATA_API
#else
#define VT_STOR_ATA_API
#endif

#ifdef VT_STOR_ATA_PROTOCOL_DLL_EXPORTS
#define VT_STOR_ATA_PROTOCOL_API
#else
#define VT_STOR_ATA_PROTOCOL_API
#endif

#ifdef VT_STOR_SCSI_DLL_EXPORTS
#define VT_STOR_SCSI_API
#else
#define VT_STOR_SCSI_API
#endif

#ifdef VT_STOR_SCSI_PROTOCOL_DLL_EXPORTS
#define VT_STOR_SCSI_PROTOCOL_API
#else
#define VT_STOR_SCSI_PROTOCOL_API
#endif

#define INVALID_FILE_DESCRIPTOR -1
#define IOCTL_SG_IO_ERROR -1

namespace vtStor
{

struct sDeviceHandle
{
    int Handle;
    eBusType Bus;
};
using DeviceHandle = sDeviceHandle;

}

#endif
