#pragma once

#include <chaiscript/chaiscript.hpp>


namespace raytracer
{
    namespace scripting
    {
        namespace _private_
        {
            chaiscript::ModulePtr create_rendering_module();
        }
    }
}