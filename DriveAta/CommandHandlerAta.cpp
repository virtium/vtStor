//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.
#include "CommandHandlerAta.h"

namespace vtStor
{

cCommandHandlerAta::cCommandHandlerAta()
{
}


cCommandHandlerAta::~cCommandHandlerAta()
{
}

eErrorCode cCommandHandlerAta::IssueCommand( std::shared_ptr<const cBufferInterface> CommandDescriptor, std::shared_ptr<cBufferInterface> Data )
{
    eErrorCode errorCode = eErrorCode::None;

    //TODO: process issue command for Ata

    return(errorCode);
}

}