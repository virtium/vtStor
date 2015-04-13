//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#ifndef __DriveEnumeratorInterface_h__
#define __DriveEnumeratorInterface_h__

#include "BasicTypes.h"
#include "ErrorCodes.h"
#include "DriveInterface.h"
#include "vtStorPlatformDefines.h"

namespace vtStor
{

class VTSTOR_API cDriveEnumeratorInterface
{
public:
    virtual eErrorCode EnumerateDrives( Vector_Drives& AddToList, U32& Count ) = 0;

public:
    virtual ~cDriveEnumeratorInterface();
};

}

#endif