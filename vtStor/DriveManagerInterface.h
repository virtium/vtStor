//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#ifndef __DriveManagerInterface_h__
#define __DriveManagerInterface_h__

#include <memory>
#include <vector>

#include "DriveInterface.h"
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

    virtual ErrorCode EnumerateDrives( eScanForHardwareChanges ScanForHardwareChanges ) = 0;

public:
    virtual ~cDriveManagerInterface() {};

public:
    using VECTOR_DRIVES = std::vector<std::unique_ptr<cDriveInterface>>;
    virtual const VECTOR_DRIVES& GetDrives() = 0;
};

}

#endif