//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#ifndef __DriveEnumeratorInterface_h__
#define __DriveEnumeratorInterface_h__

#include "BasicTypes.h"
#include "ErrorCodes.h"
#include "DriveInterface.h"

namespace vtStor
{
    class cDriveEnumeratorInterface
    {
    public:
        virtual ErrorCode EnumerateDrives( Vector_Drives& AddTo, U32& Count ) = 0;

    public:
        virtual ~cDriveEnumeratorInterface() {};
    };
}

#endif