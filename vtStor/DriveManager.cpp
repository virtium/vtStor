//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#include "DriveManager.h"

namespace vtStor
{
cDriveManager::cDriveManager()
{

}

cDriveManager::~cDriveManager()
{

}

ErrorCode cDriveManager::EnumerateDrives( eScanForHardwareChanges ScanForHardwareChanges )
{
    return( ErrorCode::None );
}

const cDriveManagerInterface::VECTOR_DRIVES& cDriveManager::GetDrives()
{
    return( m_Drives );
}

}