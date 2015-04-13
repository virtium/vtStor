//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#ifndef __DriveAta_h__
#define __DriveAta_h__

#include "BasicTypes.h"
#include "DriveAtaPlatformDefines.h"
#include "Drive.h"

namespace vtStor
{
    class DRIVE_ATA_API cDriveAta : public cDrive
    {
    public:
        cDriveAta(String DevicePath);

    public:
        virtual ~cDriveAta();

    private:
        String m_DevicePath;
    };
}

#endif