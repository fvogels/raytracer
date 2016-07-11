#pragma once

#include <chaiscript/chaiscript.hpp>
// #include <chaiscript/chaiscript_stdlib.hpp>


namespace raytracer
{
    namespace scripting
    {
        namespace _private_
        {
            chaiscript::ModulePtr create_imaging_module();
        }
    }
}