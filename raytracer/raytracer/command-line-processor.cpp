#include "command-line-processor.h"
#include "util/misc.h"
#include "easylogging++.h"
#include "logging.h"
#include <assert.h>


void CommandLineProcessor::register_processor(const std::string& prefix, std::function<void(const std::string&)> processor)
{
    assert(!is_prefix_in_use(prefix));

    m_map[prefix] = processor;
}

void CommandLineProcessor::process(const std::string& argument) const
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

void CommandLineProcessor::process(int argc, char** argv)
{
    for (int i = 1; i != argc; ++i)
    {
        std::string argument = argv[i];

        process(argument);
    }
}

bool CommandLineProcessor::is_prefix_in_use(const std::string& prefix) const
{
    return m_map.find(prefix) != m_map.end();
}
