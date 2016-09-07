/*
<License>
Copyright 2016 Virtium Technology

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

#ifndef __BusType_h__
#define __BusType_h__
#pragma once


namespace vtStor
{

enum class eBusType
{
    Ata = 0x00000000,
    Scsi = 0x00000001,
    Undefined = 0x00000002,

};
}

#endif __BusType_h__