//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#ifndef __DriveAta_h__
#define __DriveAta_h__

#include "BasicTypes.h"
#include "vtStorAtaPlatformDefines.h"
#include "Drive.h"

namespace vtStor
{
    class VT_STOR_ATA_API cDriveAta : public cDrive
    {
    public:
        static void SetCommandTypeForDefaultCommandHandler( U32 CommandType );
        static U32  GetCommandTypeForDefaultCommandHandler();

    public:
        cDriveAta(String DevicePath);

    public:
        virtual ~cDriveAta();

    

    protected:
        static U32 s_DefaultCommandHandlerCommandType;

    private:
        String m_DevicePath;
    };
}

#endif