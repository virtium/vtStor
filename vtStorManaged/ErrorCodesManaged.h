/*
<License>
Copyright 2015 Virtium Technology

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http ://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
</License>
*/
//! =========
//!  WARNING
//! =========
//! This file was automatically generated. Changes to this file may cause
//! incorrect behavior and will be lost if the code is regenerated.

#ifndef __ErrorCodesManaged_h__
#define __ErrorCodesManaged_h__
#pragma once


namespace vtStor
{
namespace Managed
{
    public enum class eErrorCode
    {
        None = 0x00000000,
        Unknown = 0x00000001,
        Memory = 0x00000002,
        Io = 0x00000003,
        Timeout = 0x00000004,
        NoSupport = 0x00000005,
        Invalid = 0x00000006,
        NullPointer = 0x00000007,
        FormatNotSupported = 0x00000008,

    };
}
}

#endif