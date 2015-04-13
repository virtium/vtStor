//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#ifndef __vtStorDrive_h__
#define __vtStorDrive_h__
#pragma once

#include <map>

#include "BasicTypes.h"
#include "DriveInterface.h"
#include "CommandHandlerInterface.h"

VTSTOR_API_EXPORT_IMPL template class VTSTOR_API std::map<vtStor::U32, std::shared_ptr<vtStor::cCommandHandlerInterface>>;

namespace vtStor
{

class VTSTOR_API cDrive : public cDriveInterface
{
public:
    cDrive();
    virtual ~cDrive();

public:
    virtual void RegisterComandHandler( U32 CommandType, std::shared_ptr<cCommandHandlerInterface> CommandHandler ) override;

protected:
    std::map<U32, std::shared_ptr<cCommandHandlerInterface>> m_CommandHandlers;
};

}

#endif