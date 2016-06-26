#pragma once

#include "scripting/objects/object.h"
#include "scripting/objects/symbol.h"
#include <memory>

namespace scripting
{
    class Environment
    {
    public:
        Environment();
        Environment(std::shared_ptr<Environment>);
        ~Environment();

        bool is_bound(const Symbol&) const;
        std::shared_ptr<Object> lookup(const Symbol&) const;
        void bind(const Symbol&, std::shared_ptr<Object> value);

    private:
        struct Impl;
        std::unique_ptr<Impl> m_pimpl;
    };

    // Extends given environment with fresh frame, yielding new environment
    std::shared_ptr<Environment> extend(std::shared_ptr<Environment>);
}