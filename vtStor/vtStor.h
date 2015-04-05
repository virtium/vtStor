//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#ifndef __vtStor_h__
#define __vtStor_h__

#include <memory>

#include "DriveManagerInterface.h"
#include "vtStorPlatformDefines.h"

extern "C"
{
    VTSTOR_API vtStor::ErrorCode vtStorInit( std::unique_ptr<vtStor::cDriveManagerInterface>& DriveManager );
}

#endif