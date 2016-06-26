#pragma once

#include "scripting/objects/object.h"

namespace scripting
{
    class Readable : public virtual Object
    {
    public:
        virtual std::shared_ptr<Object> read() const = 0;
    };
}
