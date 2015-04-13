//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#ifndef __vtStorCommandHandlerInterface_h__
#define __vtStorCommandHandlerInterface_h__
#pragma once

#include <memory>

#include "ErrorCodes.h"
#include "BufferInterface.h"

namespace vtStor
{

class cCommandHandlerInterface
{
public:
    cCommandHandlerInterface();
    virtual ~cCommandHandlerInterface();

public:
    virtual eErrorCode IssueCommand( std::shared_ptr<const cBufferInterface> CommandDescriptor, std::shared_ptr<cBufferInterface> Data ) = 0;

};

}

#endif