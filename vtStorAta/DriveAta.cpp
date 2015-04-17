//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#include "DriveAta.h"

namespace vtStor
{

U32 cDriveAta::s_DefaultCommandHandlerCommandType = 0;

void cDriveAta::SetCommandTypeForDefaultCommandHandler( U32 CommandType )
{
    s_DefaultCommandHandlerCommandType = CommandType;
}

U32 cDriveAta::GetCommandTypeForDefaultCommandHandler()
{
    return( s_DefaultCommandHandlerCommandType );
}

cDriveAta::cDriveAta(String DevicePath) :
    m_DevicePath(DevicePath)
{

}

cDriveAta::~cDriveAta()
{

}

}