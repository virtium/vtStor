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

#ifndef __vtStorUniquePtrManaged_h__
#define __vtStorUniquePtrManaged_h__
#pragma once

#include <memory>

#include "LockManaged.h"

namespace vtStor
{
    namespace Managed
    {
        template <typename T>
        public ref class cUniquePtr
        {
        public:
            cUniquePtr() :
                m_UniquePtr( new std::unique_ptr<T>() ), m_IsDisposed( false )
            {
            }

            ~cUniquePtr()
            {
                Reset();
            }

            !cUniquePtr()
            {
            }

        public:
            inline operator std::unique_ptr<T>*()
            {
                return( m_UniquePtr );
            }

            inline T* operator->()
            {
                return( m_UniquePtr->get() );
            }

        public:
            inline void Reset()
            {
                if (true == m_IsDisposed)
                {
                    return;
                }

                cLockObject lock( this );
                if (nullptr != m_UniquePtr)
                {
                    delete m_UniquePtr;
                    m_UniquePtr = nullptr;
                }
                m_IsDisposed = true;
            }

        private:
            std::unique_ptr<T>* m_UniquePtr;
            bool m_IsDisposed;
        };
    }
}

#endif