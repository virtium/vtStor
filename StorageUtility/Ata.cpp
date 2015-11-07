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

#include "Ata.h"

namespace vtStor
{
namespace StorageUtility
{
namespace Ata
{

const U32 SECTOR_SIZE_IN_BYTES = 512;

const U8  DEVICE_REGISTER_DEFAULT = 0xE0;
const U8  DEVICE_REGISTER_CHSMODE_DEFAULT = 0xA0;

}
}
}
