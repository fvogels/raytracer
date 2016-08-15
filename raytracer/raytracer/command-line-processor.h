#pragma once

#include <functional>
#include <string>
#include <map>


class CommandLineProcessor
{
public:
    void register_processor(const std::string& prefix, std::function<void(const std::string&)> processor);
    void process(int argc, char** argv);

private:
    void process(const std::string& argument) const;
    bool is_prefix_in_use(const std::string& prefix) const;

    std::map<std::string, std::function<void(const std::string&)>> m_map;
};
