#include "chai/scripting.h"
#include "chai/math-module.h"
#include "chai/imaging-module.h"
#include "chai/primitives-module.h"
#include "chai/cameras-module.h"
#include "chai/lights-module.h"
#include "chai/raytracing-module.h"
#include "chai/materials-module.h"
#include <chaiscript/chaiscript.hpp>
#include <chaiscript/chaiscript_stdlib.hpp>

using namespace raytracer::scripting;
using namespace chaiscript;


namespace raytracer
{
    namespace scripting
    {
        ModulePtr create_modules()
        {
            using namespace raytracer::scripting::_private_;

            auto module = std::make_shared<chaiscript::Module>();

            module->add(create_imaging_module());
            module->add(create_math_module());
            module->add(create_primitives_module());
            module->add(create_cameras_module());
            module->add(create_lights_module());
            module->add(create_raytracing_module());
            module->add(create_materials_module());

            return module;
        }
    }
}


void raytracer::scripting::run_script(const std::string& path)
{
    ChaiScript chai(Std_Lib::library());
    chai.add(create_modules());

    try
    {
        chai.eval_file(path);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred while evaluating script" << std::endl << e.what() << std::endl;
        abort();
    }
}

void raytracer::scripting::run(const std::string& source)
{
    ChaiScript chai(Std_Lib::library());
    chai.add(create_modules());

    try
    {
        chai.eval(source);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred while evaluating script" << std::endl << e.what() << std::endl;
        abort();
    }
}

