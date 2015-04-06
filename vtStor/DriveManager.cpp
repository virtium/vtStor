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
    m_DriveEnumerators.clear();
    m_Drives.clear();
}

void cDriveManager::RegisterDriveEnumerator( std::shared_ptr<cDriveEnumeratorInterface> DriveEnumerator )
{
    m_DriveEnumerators.push_back( DriveEnumerator );
}

ErrorCode cDriveManager::EnumerateDrives( eScanForHardwareChanges ScanForHardwareChanges )
{
    return( ErrorCode::None );
}

const Vector_Drives& cDriveManager::GetDrives()
{
    return( m_Drives );
}

}