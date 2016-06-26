#pragma once

#include "scripting/objects/callable.h"

namespace scripting
{
    class Function : public Callable
    {
    public:
        std::shared_ptr<Object> call(std::shared_ptr<scripting::Environment>, const std::vector<std::shared_ptr<Object>>&) const override;

    protected:
        virtual std::shared_ptr<Object> perform(const std::vector<std::shared_ptr<Object>>&) const = 0;
    };
}
