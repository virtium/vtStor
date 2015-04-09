//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#ifndef __DriveAtaPlatformDefines_h__
#define __DriveAtaPlatformDefines_h__

#ifdef DRIVE_ATA_DLL_EXPORTS
#define DRIVE_ATA_API _declspec( dllexport )
#else
#define DRIVE_ATA_API _declspec( dllimport )
#endif

#endif
