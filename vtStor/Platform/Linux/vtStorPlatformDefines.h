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
#ifndef __vtStorPlatformDefines_h__
#define __vtStorPlatformDefines_h__

#include <string>
/*

#ifdef VTSTOR_DLL_EXPORTS
#define VTSTOR_API _declspec( dllexport )
#define VTSTOR_API_EXPORT_IMPL
#else
#define VTSTOR_API _declspec( dllimport )
#define VTSTOR_API_EXPORT_IMPL  extern
#endif
*/

#ifdef VTSTOR_DLL_EXPORTS
#define VTSTOR_API
#define VTSTOR_API_EXPORT_IMPL
#else
#define VTSTOR_API
#define VTSTOR_API_EXPORT_IMPL
#endif

#endif
