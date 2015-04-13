//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#ifndef __DriveInterface_h__
#define __DriveInterface_h__

#include <memory>
#include <vector>

#include "BasicTypes.h"
#include "CommandHandlerInterface.h"
#include "vtStorPlatformDefines.h"

namespace vtStor
{

class VTSTOR_API cDriveInterface
{
public:
    virtual void RegisterComandHandler(U32 CommandType, std::shared_ptr<cCommandHandlerInterface> CommandHandler) = 0;

public:
    virtual ~cDriveInterface();
};

using Vector_Drives = std::vector<std::shared_ptr<cDriveInterface>>;

}

#endif