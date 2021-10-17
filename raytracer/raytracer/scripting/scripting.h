#pragma once

#ifndef EXCLUDE_SCRIPTING

#include <string>
#include <map>
#ifdef TEST_BUILD
#include <chaiscript/chaiscript.hpp>
#include <chaiscript/chaiscript_stdlib.hpp>
#endif

namespace raytracer
{
    namespace scripting
    {
        void run_script(const std::string& path, const std::map<std::string, std::string>& constants);
        void run(const std::string& source, const std::map<std::string, std::string>& constants);

#       ifdef TEST_BUILD
        chaiscript::ModulePtr create_modules();

        template<typename T>
        T evaluate(const std::string& source)
        {
            chaiscript::ChaiScript chai(chaiscript::Std_Lib::library());
            chai.add(create_modules());
            return chai.eval<T>(source);
        }

        template<>
        inline void evaluate(const std::string& source)
        {
            chaiscript::ChaiScript chai(chaiscript::Std_Lib::library());
            chai.add(create_modules());
            chai.eval(source);
        }
#       endif
    }
}

#endif
