//Copyright( c ) 2015 Virtium Technology
//See the file license.txt for copying permission.
#ifndef __vtStorAta_h__
#define __vtStorAta_h__
#pragma once

#include "BasicTypes.h"
#include "vtStorAtaPlatformDefines.h"

namespace vtStor
{

class VT_STOR_ATA_API cAta
{
public:
    cAta() = delete;

public:
    static U32 s_DefaultCommandHandlerCommandType;
};


}

#endif