//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#ifndef __vtStorDrive_h__
#define __vtStorDrive_h__
#pragma once

#include <map>

#include "BasicTypes.h"
#include "DriveInterface.h"
#include "CommandHandlerInterface.h"

namespace vtStor
{

class cDrive : public cDriveInterface
{
public:
    cDrive();
    virtual ~cDrive();

protected:
    std::map<U32, cCommandHandlerInterface> m_CommandHandlers;
};

}

#endif