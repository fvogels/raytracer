#ifndef TEST_BUILD

#include "easylogging++.h"
#include "version.h"
#include "command-line-processor.h"
#include "logging.h"
#include "demo/demos.h"
#include "pipeline/pipelines.h"
#include "util/beep.h"
#include <assert.h>

using namespace raytracer;


namespace
{
    // Note: these are not used anywhere for now
    std::map<std::string, std::string> external_variables;

    void render_script(const std::string& filename)
    {
        LOG(INFO) << "Rendering " << filename;
        TIMED_SCOPE(timer, "Rendering " + filename);

#       ifdef EXCLUDE_SCRIPTING
        LOG(ERROR) << "Cannot run script - scripting was excluded";
        abort();
#       else
        raytracer::scripting::run_script(filename);
#       endif
    }

    void quiet(const std::string&)
    {
        logging::quiet();
    }

    void show_version(const std::string&)
    {
        LOG(INFO) << "Build " << BUILD_NUMBER << std::endl;
    }

    void emit_beep(const std::string&)
    {
        ::beep();
    }

    void define_external_variable(const std::string& string)
    {
        auto equal_sign_location = string.find('=');

        if (equal_sign_location == std::string::npos)
        {
            LOG(ERROR) << "Invalid variable definition:" << string;
            abort();
        }
        else
        {
            std::string variable_name = string.substr(0, equal_sign_location);
            std::string variable_value = string.substr(equal_sign_location + 1);

            external_variables[variable_name] = variable_value;
        }
    }
}

void process_command_line_arguments(int argc, char** argv)
{
    CommandLineProcessor processor;

    processor.register_processor("-s", render_script);
    processor.register_processor("--quiet", quiet);
    processor.register_processor("--version", show_version);
    processor.register_processor("--beep", emit_beep);
    processor.register_processor("-d", define_external_variable);

    processor.process(argc, argv);

    LOG(INFO) << "Terminated successfully";
}

int main(int argc, char** argv)
{
    const std::string path = "e:/temp/output/test.wif";
    logging::configure();

    // process_command_line_arguments(argc, argv);

    // demos::fisheye(pipeline::wif(path)); beep();
    // demos::bumpify_sphere(pipeline::wif(path)); beep();
    // demos::bumpify_plane(pipeline::wif(path)); beep();
    // demos::marble(pipeline::wif(path)); beep();
    // demos::mesh(pipeline::wif(path)); beep();
    demos::terrain(pipeline::wif(path)); beep();
    // demos::samplers(pipeline::wif(path)); beep();
    // demos::depth_of_field(pipeline::wif(path)); beep();
    // demos::split_depth(pipeline::wif(path)); beep();

    // scripting::run_script("e:/repos/ucll/3dcg/raytracer2/scripts/test.chai");    
}

#endif
