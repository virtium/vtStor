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

#ifndef __vtStorSharedPtrManaged_h__
#define __vtStorSharedPtrManaged_h__
#pragma once

#include <memory>

#include "LockManaged.h"

namespace vtStor
{
    namespace Managed
    {
        template <typename T>
        public ref class cSharedPtr
        {
        public:
            cSharedPtr() :
                m_SharedPtr( new std::shared_ptr<T>() ), m_IsDisposed( false )
            {
            }

            ~cSharedPtr()
            {
                Reset();
            }

            !cSharedPtr()
            {
            }

        public:
            inline operator std::shared_ptr<T>*()
            {
                return( m_SharedPtr );
            }

            inline T* operator->()
            {
                return( m_SharedPtr->get() );
            }

            inline cSharedPtr<T>^ operator=(std::shared_ptr<T>& Ptr)
            {
                cLockObject lock( this );
                if ((nullptr != m_SharedPtr) || (Ptr != *m_SharedPtr))
                {
                    if (nullptr != m_SharedPtr)
                    {
                        delete m_SharedPtr;
                        m_SharedPtr = nullptr;
                    }
                    m_SharedPtr = new std::shared_ptr<T>( Ptr );
                }
                return( this );
            }

        public:
            inline void Reset()
            {
                if (true == m_IsDisposed)
                {
                    return;
                }

                cLockObject lock( this );
                if (nullptr != m_SharedPtr)
                {
                    delete m_SharedPtr;
                    m_SharedPtr = nullptr;
                }
                m_IsDisposed = true;
            }

        private:
            std::shared_ptr<T>* m_SharedPtr;
            bool m_IsDisposed;
        };
    }
}

#endif