//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#include "Drive.h"

namespace vtStor
{

cDrive::cDrive()
{
}


cDrive::~cDrive()
{
    m_CommandHandlers.clear();
}

void cDrive::RegisterComandHandler( U32 CommandType, std::shared_ptr<cCommandHandlerInterface> CommandHandler )
{
    m_CommandHandlers.insert({ CommandType, CommandHandler });
}

eErrorCode cDrive::IssueCommand( U32 CommandType, std::shared_ptr<const cBufferInterface> CommandDescriptor, std::shared_ptr<cBufferInterface> Data )
{
    return( m_CommandHandlers[CommandType]->IssueCommand( CommandDescriptor, Data ) );
}

}