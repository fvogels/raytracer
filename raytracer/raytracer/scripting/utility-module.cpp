#include "scripting/utility-module.h"

using namespace chaiscript;
using namespace raytracer;


namespace
{
    void println(const std::string& string)
    {
        std::cout << string << std::endl;
    }
}

ModulePtr raytracer::scripting::_private_::create_utility_module()
{
    auto module = std::make_shared<chaiscript::Module>();

#define BIND(NAME)  module->add(fun(NAME), #NAME)
    BIND(println);
#undef BIND

    return module;
}