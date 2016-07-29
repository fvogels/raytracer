#include "scripting/scripting.h"
#include "scripting/math-module.h"
#include "scripting/imaging-module.h"
#include "scripting/primitives-module.h"
#include "scripting/cameras-module.h"
#include "scripting/lights-module.h"
#include "scripting/raytracing-module.h"
#include "scripting/materials-module.h"
#include "scripting/rendering-module.h"
#include "scripting/samplers-module.h"
#include "scripting/pipeline-module.h"
#include <chaiscript/chaiscript.hpp>
#include <chaiscript/chaiscript_stdlib.hpp>

using namespace raytracer::scripting;
using namespace chaiscript;


namespace raytracer
{
    namespace scripting
    {
        // Must be in raytracer::scripting for testing purposes
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
            module->add(create_rendering_module());
            module->add(create_samplers_module());
            module->add(create_pipeline_module());

            return module;
        }
    }
}

namespace
{
    std::shared_ptr<ChaiScript> initialize_chai()
    {
        auto chai = std::make_shared<ChaiScript>(Std_Lib::library());

        chai->add(create_modules());

        return chai;
    }
}


void raytracer::scripting::run_script(const std::string& path)
{
    auto chai = initialize_chai();

    try
    {
        chai->eval_file(path);
    }
    catch (const chaiscript::exception::eval_error& e)
    {
        std::cerr << "Error occurred while evaluating script" << std::endl << e.pretty_print() << std::endl;
        abort();
    }
}

void raytracer::scripting::run(const std::string& source)
{
    auto chai = initialize_chai();

    try
    {
        chai->eval(source);
    }
    catch (const chaiscript::exception::eval_error& e)
    {
        std::cerr << "Error occurred while evaluating script" << std::endl << e.pretty_print() << std::endl;
        abort();
    }
}

