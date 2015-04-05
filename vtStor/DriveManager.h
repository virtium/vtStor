//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#ifndef __DriveManager_h__
#define __DriveManager_h__

#include "DriveManagerInterface.h"

namespace vtStor
{

class cDriveManager : public cDriveManagerInterface
{
public:
    virtual ErrorCode EnumerateDrives( eScanForHardwareChanges ScanForHardwareChanges );

public:
    virtual const VECTOR_DRIVES& GetDrives();

public:
    cDriveManager();
    virtual ~cDriveManager();

private:


private:
    VECTOR_DRIVES   m_Drives;
};

}

#endif