//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#ifndef __vtStorAtaPlatformDefines_h__
#define __vtStorAtaPlatformDefines_h__

#include <string>

#ifdef VT_STOR_ATA_DLL_EXPORTS
#define VT_STOR_ATA_API _declspec( dllexport )
#else
#define VT_STOR_ATA_API _declspec( dllimport )
#endif

#endif
