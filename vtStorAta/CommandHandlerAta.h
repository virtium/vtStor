//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.
#ifndef __vtStorCommandHandlerAta_h__
#define __vtStorCommandHandlerAta_h__

#pragma once
#include "CommandHandlerInterface.h"
#include "vtStorAtaPlatformDefines.h"

namespace vtStor
{

class VT_STOR_ATA_API cCommandHandlerAta : public cCommandHandlerInterface
{
public:
    cCommandHandlerAta();
    virtual ~cCommandHandlerAta();

public:
    virtual eErrorCode IssueCommand( std::shared_ptr<const cBufferInterface> CommandDescriptor, std::shared_ptr<cBufferInterface> Data ) override;

};

}

#endif