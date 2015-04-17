//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.
#ifndef __vtStorDriveAtaCommandExtensions_h__
#define __vtStorDriveAtaCommandExtensions_h__
#pragma once

#include <memory>

#include "ErrorCodes.h"
#include "DriveInterface.h"

//! These are like "extension methods"

namespace vtStor
{
namespace Ata
{

eErrorCode IssueCommand_IdentifyDevice( std::shared_ptr<cDriveInterface> Drive, std::shared_ptr<cBufferInterface> Data );

}
}

#endif