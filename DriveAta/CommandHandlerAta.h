//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.
#ifndef __vtStorCommandHandlerAta_h__
#define __vtStorCommandHandlerAta_h__

#pragma once
#include "CommandHandlerInterface.h"

namespace vtStor
{

class cCommandHandlerAta : public cCommandHandlerInterface
{
public:
    cCommandHandlerAta();
    virtual ~cCommandHandlerAta();

public:
    virtual eErrorCode IssueCommand( std::shared_ptr<const cBufferInterface> CommandDescriptor, std::shared_ptr<cBufferInterface> Data ) override;

};

}

#endif