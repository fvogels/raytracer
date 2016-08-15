#include "command-line-processor.h"
#include "util/misc.h"
#include "easylogging++.h"
#include "logging.h"
#include "util/beep.h"
#include "version.h"
#include "scripting/scripting.h"
#include <map>
#include <string>
#include <functional>
#include <assert.h>


namespace
{
    class CommandLineProcessor
    {
    public:
        void register_processor(const std::string& prefix, std::function<void(const std::string&)> processor)
        {
            assert(!is_prefix_in_use(prefix));

            m_map[prefix] = processor;
        }

        void process(const std::string& argument) const
        {
            for (auto it : m_map)
            {
                const auto& prefix = it.first;
                const auto& processor = it.second;

                if (starts_with(prefix, argument))
                {
                    std::string value = argument.substr(prefix.size());

                    processor(value);

                    return;
                }
            }

            LOG(ERROR) << "Unrecognized command line argument " << argument;
            abort();
        }

        void process(int argc, char** argv)
        {
            for (int i = 1; i != argc; ++i)
            {
                std::string argument = argv[i];

                process(argument);
            }
        }

    private:
        bool is_prefix_in_use(const std::string& prefix) const
        {
            return m_map.find(prefix) != m_map.end();
        }

        std::map<std::string, std::function<void(const std::string&)>> m_map;
    };

    void render_script(const std::string& filename)
    {
        LOG(INFO) << "Rendering " << filename;
        TIMED_SCOPE(timer, "Rendering " + filename);

#ifdef EXCLUDE_SCRIPTING
        LOG(ERROR) << "Cannot run script - scripting was excluded";
        abort();
#else
        raytracer::scripting::run_script(filename);
#endif
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
}

void process_command_line_arguments(int argc, char** argv)
{
    CommandLineProcessor processor;

    processor.register_processor("-s", render_script);
    processor.register_processor("--quiet", quiet);
    processor.register_processor("--version", show_version);
    processor.register_processor("--beep", emit_beep);

    processor.process(argc, argv);

    LOG(INFO) << "Terminated successfully";
}
