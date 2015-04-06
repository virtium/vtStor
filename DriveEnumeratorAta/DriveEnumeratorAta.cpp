//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#include "StorageUtility.h"

#include "DriveEnumeratorAta.h"

namespace vtStor
{
 
cDriveEnumeratorAta::~cDriveEnumeratorAta()
{

}

eErrorCode cDriveEnumeratorAta::EnumerateDrives( Vector_Drives& AddToList, U32& Count )
{
    std::vector<String> devicePaths;
    vtStor::GetStorageDevicePaths( devicePaths, eOnErrorBehavior::Continue );

    return( eErrorCode::None );
}

}