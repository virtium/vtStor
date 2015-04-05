//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#include "DriveManager.h"

#include "vtStor.h"

using namespace vtStor;

vtStor::ErrorCode vtStorInit( std::unique_ptr<vtStor::cDriveManagerInterface>& DriveManager )
{
    DriveManager = std::make_unique<cDriveManager>();

    return( ErrorCode::None );
}