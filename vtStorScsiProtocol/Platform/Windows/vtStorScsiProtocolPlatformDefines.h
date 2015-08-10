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
#ifndef __vtStorScsiProtocolPlatformDefines_h__
#define __vtStorScsiProtocolPlatformDefines_h__



#ifdef VT_STOR_SCSI_PROTOCOL_DLL_EXPORTS
#define VT_STOR_SCSI_PROTOCOL_API _declspec( dllexport )
#else
#define VT_STOR_SCSI_PROTOCOL_API _declspec( dllimport )
#endif

#endif
