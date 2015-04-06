//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#ifndef __DriveEnumeratorAta_h__
#define __DriveEnumeratorAta_h__

#include "DriveEnumeratorInterface.h"

namespace vtStor
{
    class cDriveEnumeratorAta : public cDriveEnumeratorInterface
    {
    public:
        virtual ErrorCode EnumerateDrives( Vector_Drives& AddTo, U32& Count ) = 0;

    public:
        virtual ~cDriveEnumeratorInterface() {};
    };
}

#endif