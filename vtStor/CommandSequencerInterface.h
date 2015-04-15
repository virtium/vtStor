//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#ifndef __vtStorCommandSequencerInterface_h__
#define __vtStorCommandSequencerInterface_h__
#pragma once

#include "BasicTypes.h"
#include "CommandHandlerInterface.h"
#include "vtStorPlatformDefines.h"

namespace vtStor
{

class VTSTOR_API cCommandSequencerInterface : public cCommandHandlerInterface
{
public:
    cCommandSequencerInterface();
    virtual ~cCommandSequencerInterface();

public:
    virtual void RegisterComandHandler( U32 CommandType, std::shared_ptr<cCommandHandlerInterface> CommandHandler ) = 0;

};

}

#endif