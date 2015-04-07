//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#ifndef __DriveEnumeratorAtaPlatformDefines_h__
#define __DriveEnumeratorAtaPlatformDefines_h__

#include <string>

#ifdef DRIVE_ENUMERATOR_ATA_DLL_EXPORTS
#define DRIVE_ENUMERATOR_ATA_API _declspec( dllexport )
#else
#define DRIVE_ENUMERATOR_ATA_API _declspec( dllimport )
#endif

#endif
