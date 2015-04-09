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

eErrorCode cDriveManager::EnumerateDrives( eScanForHardwareChanges ScanForHardwareChanges )
{
    eErrorCode error = eErrorCode::None;

    if ( eScanForHardwareChanges::Yes == ScanForHardwareChanges )
    {
        //TODO: scan for hardware changes
    }

    U32 count = 0;
    for ( auto& enumerator : m_DriveEnumerators )
    {
        error = enumerator->EnumerateDrives(m_Drives, count);
        if (eErrorCode::None != error)
        {
            //TODO: handle error
        }
    }

    return( error );
}

const Vector_Drives& cDriveManager::GetDrives()
{
    return( m_Drives );
}

}