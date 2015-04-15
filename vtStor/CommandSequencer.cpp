//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#include "CommandSequencer.h"

namespace vtStor
{

cCommandSequencer::cCommandSequencer()
{
}

cCommandSequencer::~cCommandSequencer()
{
    m_CommandHandlers.clear();
}

void cCommandSequencer::RegisterComandHandler( U32 CommandType, std::shared_ptr<cCommandHandlerInterface> CommandHandler )
{
    m_CommandHandlers.insert( { CommandType, CommandHandler } );
}

}