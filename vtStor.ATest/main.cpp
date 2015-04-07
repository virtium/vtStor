//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#include <memory>

#include "DriveEnumeratorAta.h"

void main()
{
    std::unique_ptr<vtStor::cDriveEnumeratorInterface> driveEnumeratorAta = std::make_unique<vtStor::cDriveEnumeratorAta>();
    vtStor::Vector_Drives drives;
    vtStor::U32 count;
    driveEnumeratorAta->EnumerateDrives( drives, count );



}