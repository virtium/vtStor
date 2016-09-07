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

#ifndef __DriveEnumerateDecorator_h__
#define __DriveEnumerateDecorator_h__

#include "IDriveEnumerator.h"

namespace vtStor
{
    class VTSTOR_API cDriveEnumerateDecorator : public IDriveEnumerator
    {
    public:
        cDriveEnumerateDecorator(std::shared_ptr<IDriveEnumerator> DecoratedDriveEnumerator);
        virtual ~cDriveEnumerateDecorator() {}

    public:
        virtual std::shared_ptr<IDrive> EnumerateDrive(const std::shared_ptr<IDevice>& Device) override;

    protected:
        virtual std::shared_ptr<IDrive> DoEnumerate(const std::shared_ptr<IDevice>& Device) = 0;

    protected:
        std::shared_ptr<IDriveEnumerator> m_DecoratedDriveEnumerator;
    };
}
#endif