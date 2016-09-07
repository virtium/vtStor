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
#ifndef __vtStorAsynIoProtocolEssense_h__
#define __vtStorAsynIoProtocolEssense_h__

#include <memory>

#include "Ata.h"
#include "BasicTypes.h"
#include "ProtocolEssense.h"

namespace vtStor
{
    struct sAsynchronousIoInputs
    {
        OverlappedIo* OverlappedPtr;
        U32 m_DataTransferredInSectors;
        U32 Command;
    };

    static const U32 READ_ASYNIO = 0x01;
    static const U32 WRITE_ASYNIO = 0x02;

    class VT_STOR_ATA_PROTOCOL_API cAsynIoProtocolEssense : public cProtocolEssense
    {
    public:
        static const size_t SIZE_IN_BYTES;
        static const size_t COMMAND_FIELDS_OFFSET;
        static UUID FormatType;

    public:
        static cAsynIoProtocolEssense Reader(std::shared_ptr<const IBuffer> Buffer);
        static cAsynIoProtocolEssense Writer(std::shared_ptr<IBuffer> Buffer);
                
    public:
        sAsynchronousIoInputs& GetCommandFields();
        const sAsynchronousIoInputs& GetCommandFields() const;

    protected:
        cAsynIoProtocolEssense(std::shared_ptr<IBuffer> Buffer);
        cAsynIoProtocolEssense(std::shared_ptr<IBuffer> Buffer, const UUID& Format);
        cAsynIoProtocolEssense(std::shared_ptr<const IBuffer> Buffer);

    private:
        sAsynchronousIoInputs m_CommandFields;
    };
}

#endif
