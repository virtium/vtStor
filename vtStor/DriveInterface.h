//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.

#ifndef __DriveInterface_h__
#define __DriveInterface_h__

#include <memory>
#include <vector>

namespace vtStor
{
    class cDriveInterface
    {
    public:

    public:
        virtual ~cDriveInterface() {};
    };

    using Vector_Drives = std::vector<std::unique_ptr<cDriveInterface>>;
}

#endif