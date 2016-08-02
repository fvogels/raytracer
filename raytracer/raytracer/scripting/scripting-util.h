#pragma once

#include <chaiscript/chaiscript.hpp>
#include <string>
#include <map>
#include <algorithm>
#include <memory>
#include <sstream>


#define START_ARGUMENTS(MAP)                    auto& _argument_map_ = MAP; raytracer::scripting::util::ArgumentMapParser _parser_
#define ARGUMENT(TYPE, NAME)                    TYPE NAME; _parser_.add<TYPE>(#NAME, &NAME)
#define OPTIONAL_ARGUMENT(TYPE, NAME, VALUE)    TYPE NAME = VALUE; _parser_.add<TYPE>(#NAME, &NAME, true)
#define END_ARGUMENTS()                         _parser_.parse(_argument_map_)

namespace raytracer
{
    namespace scripting
    {
        namespace util
        {
            template<typename T>
            T smart_boxed_cast(chaiscript::Boxed_Value boxed)
            {
                return chaiscript::boxed_cast<T>(boxed);
            }

            template<>
            inline double smart_boxed_cast(chaiscript::Boxed_Value boxed)
            {
                if (*boxed.get_type_info().bare_type_info() == typeid(int))
                {
                    return chaiscript::boxed_cast<int>(boxed);
                }
                else
                {
                    return chaiscript::boxed_cast<double>(boxed);
                }
            }

            template<typename T>
            std::vector<T> cast_vector_elements(const std::vector<chaiscript::Boxed_Value>& boxed_values)
            {
                std::vector<T> unboxed_values(boxed_values.size());
 
                std::transform(boxed_values.begin(), boxed_values.end(), unboxed_values.begin(), [](chaiscript::Boxed_Value boxed_value) {
                    return chaiscript::boxed_cast<T>(boxed_value);
                });

                return unboxed_values;
            }

            struct SingleArgumentParser
            {
                SingleArgumentParser(bool optional)
                    : found(false), optional(optional) { }

                bool found;
                bool optional;

                virtual void parse(chaiscript::Boxed_Value) = 0;
            };            

            template<typename T>
            struct SpecializedSingleArgumentParser : public SingleArgumentParser
            {
                SpecializedSingleArgumentParser(T* storage, bool optional)
                    : SingleArgumentParser(optional), storage(storage) { }

                void parse(chaiscript::Boxed_Value boxed) override
                {
                    if (!found)
                    {
                        *storage = smart_boxed_cast<T>(boxed);
                        found = true;
                    }
                    else
                    {
                        throw std::runtime_error("Parameter assigned value twice");
                    }
                }
                
                T* storage;
            };

            class ArgumentMapParser
            {
            public:
                template<typename T>
                void add(const std::string& tag, T* storage, bool optional = false)
                {
                    m_parsers[tag] = std::make_shared<SpecializedSingleArgumentParser<T>>(storage, optional);
                }

                void parse(const std::map<std::string, chaiscript::Boxed_Value>& argument_map)
                {
                    parse_arguments(argument_map);
                    verify(argument_map);
                }

            private:
                void parse_arguments(const std::map<std::string, chaiscript::Boxed_Value>& argument_map)
                {
                    for (auto argument_it : argument_map)
                    {
                        auto& tag = argument_it.first;
                        auto& boxed = argument_it.second;

                        parse_argument(tag, boxed);
                    }
                }

                void parse_argument(const std::string& tag, chaiscript::Boxed_Value boxed)
                {
                    auto parser_it = m_parsers.find(tag);

                    if (parser_it == m_parsers.end())
                    {
                        std::ostringstream ss;
                        ss << "Invalid tag " << tag;

                        throw std::runtime_error(ss.str());
                    }
                    else
                    {
                        parser_it->second->parse(boxed);
                    }
                }

                void verify(const std::map<std::string, chaiscript::Boxed_Value>& argument_map)
                {
                    for (auto parser_it : m_parsers)
                    {
                        auto& tag = parser_it.first;
                        auto& parser = parser_it.second;

                        verify(tag, parser);
                    }
                }

                void verify(const std::string& tag, std::shared_ptr<SingleArgumentParser> parser)
                {
                    if (!parser->found && !parser->optional)
                    {
                        std::ostringstream ss;
                        ss << "Missing nonoptional parameter " << tag;

                        throw std::runtime_error(ss.str());
                    }
                }

                std::map<std::string, std::shared_ptr<SingleArgumentParser>> m_parsers;
            };
        }
    }
}
