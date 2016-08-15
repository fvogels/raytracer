#include "command-line-processor.h"
#include "util/misc.h"
#include "easylogging++.h"
#include "logging.h"
#include "util/beep.h"
#include "version.h"



void process_command_line_arguments(int argc, char** argv)
{
    int i = 1;

    while (i < argc)
    {
        std::string current = argv[i];

        if (starts_with("-s", current))
        {
            std::string path = current.substr(2);

            LOG(INFO) << "Rendering " << path;
            TIMED_SCOPE(timer, "Rendering " + path);

#ifdef EXCLUDE_SCRIPTING
            LOG(ERROR) << "Cannot run script - scripting was excluded";
            abort();
#else
            scripting::run_script(path);
#endif
        }
        else if (current == "--quiet")
        {
            logging::quiet();
        }
        else if (current == "--version")
        {
            LOG(INFO) << "Build " << BUILD_NUMBER << std::endl;
        }
        else if (current == "--beep")
        {
            beep();
        }
        else
        {
            LOG(ERROR) << "Unknown flag " << current << std::endl;
            abort();
        }

        ++i;
    }

    LOG(INFO) << "Terminated successfully";
}
