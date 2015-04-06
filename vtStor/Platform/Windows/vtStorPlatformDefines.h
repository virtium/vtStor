//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#ifndef __vtStorPlatformDefines_h__
#define __vtStorPlatformDefines_h__

#include <string>

#ifdef VTSTOR_DLL_EXPORTS
#define VTSTOR_API _declspec( dllexport )
#else
#define VTSTOR_API _declspec( dllimport )
#endif

#ifdef _UNICODE
#define    __STORAPITEXT( s ) L##s
using tchar     = wchar_t;
using tstring   = std::wstring;
#else
#define    __STORAPITEXT( s ) s
using tchar     = char;
using tstring   = string;
#endif

namespace vtStor
{

using String = tstring;

}

#endif
