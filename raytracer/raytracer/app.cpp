#ifndef TEST_BUILD

#include "easylogging++.h"
#include "version.h"
#include "command-line-parser.h"
#include "logging.h"
#include "pipeline/pipelines.h"
#include "util/beep.h"
#include "scripting/scripting.h"
#include "performance/performance.h"
#include <assert.h>
#include <string>
#include <map>

using namespace raytracer;


namespace
{
    std::map<std::string, std::string> constants;

    void render_script(const std::string& filename)
    {
        TIMED_SCOPE(timer, "Rendering script");

#       ifdef EXCLUDE_SCRIPTING
        LOG(ERROR) << "Cannot run script - scripting was excluded";
        abort();
#       endif

        if (filename != "-")
        {
            LOG(INFO) << "Rendering " << filename;

            raytracer::scripting::run_script(filename, constants);
        }
        else
        {
            LOG(INFO) << "Rendering script from STDIN";

            std::string script;

            while (!std::cin.eof())
            {
                std::string line;
                std::getline(std::cin, line);
                script += line + "\n";
            }

            raytracer::scripting::run(script, constants);
        }
    }

    void define_constant(const std::string& name, const std::string& value)
    {
        constants[name] = value;
    }

    void quiet()
    {
        logging::quiet();
    }

    void show_version()
    {
        LOG(INFO) << "Build " << BUILD_NUMBER << std::endl;
    }

    void emit_beep()
    {
        ::beep();
    }

    void print_statistics()
    {
        performance::print_statistics();
    }

    void enable_3dstudio_output()
    {
        logging::enable("studio");

        LOG(INFO) << "Activated 3d studio mode";
    }
}

void process_command_line_arguments(int argc, char** argv)
{
    CommandLineParser parser;

    parser.register_processor("-s", render_script);
    parser.register_processor("--quiet", quiet);
    parser.register_processor("--version", show_version);
    parser.register_processor("--beep", emit_beep);
    parser.register_processor("--statistics", print_statistics);
    parser.register_processor("--studio", enable_3dstudio_output);
    parser.register_processor("--define", define_constant);

    parser.process(argc, argv);

    LOG(INFO) << "Terminated successfully";
}

int main(int argc, char** argv)
{
#   ifdef NDEBUG
    LOG(INFO) << "Release build (#" << BUILD_NUMBER << ")";
#   else
    LOG(INFO) << "Debug build (#" << BUILD_NUMBER << ")";
#   endif

    TIMED_FUNC(timer);

    logging::configure();
    process_command_line_arguments(argc, argv);

#ifdef _DEBUG
    const std::string path = R"(G:\temp\yenthe.chai)";
    render_script(path);
#endif

    performance::print_statistics();
    performance::cleanup();
}

#endif
