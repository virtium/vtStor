//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#ifndef __DriveManagerInterface_h__
#define __DriveManagerInterface_h__

#include "DriveInterface.h"
#include "DriveEnumeratorInterface.h"
#include "ErrorCodes.h"

namespace vtStor
{

class cDriveManagerInterface
{
public:
    enum eScanForHardwareChanges
    {
        No,
        Yes
    };

    virtual void RegisterDriveEnumerator( std::shared_ptr<cDriveEnumeratorInterface> DriveEnumerator ) = 0;

    virtual ErrorCode EnumerateDrives( eScanForHardwareChanges ScanForHardwareChanges ) = 0;

public:
    virtual ~cDriveManagerInterface() {};

public:
    virtual const Vector_Drives& GetDrives() = 0;
};

}

#endif