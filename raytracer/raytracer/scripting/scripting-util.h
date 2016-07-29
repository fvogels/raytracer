#pragma once

#include <chaiscript/chaiscript.hpp>
#include <string>
#include <map>
#include <algorithm>
#include <memory>
#include <sstream>


#define EXTRACT_ARGUMENT(TYPE, NAME)            auto NAME = raytracer::scripting::util::get_argument<TYPE>(argument_map, #NAME)
#define FACTORY_TYPE_DISPATCH(TYPE)             if ( type == #TYPE ) return TYPE(argument_map)
#define HANDLE_UNKNOWN_TYPE                     throw std::runtime_error("Unknown type")

#define START_ARGUMENTS(MAP)                    auto& _argument_map_ = MAP; raytracer::scripting::util::ArgumentMapParser _parser_
#define ARGUMENT(TYPE, NAME)                    TYPE NAME; _parser_.add<TYPE>(#NAME, &NAME)
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
            inline T get_argument(const std::map<std::string, chaiscript::Boxed_Value>& argument_map, const std::string& name)
            {
                return smart_boxed_cast<T>(argument_map.at(name));
            }

            template<typename T>
            std::vector<T> cast_vector_elements(const std::vector<chaiscript::Boxed_Value>& boxed_values)
            {
                std::vector<T> unboxed_values(boxed_values.size());
 
                std::transform(boxed_values.begin(), boxed_values.end(), unboxed_values.begin(), [](Boxed_Value boxed_value) {
                    return boxed_cast<T>(boxed_value);
                });

                return unboxed_values;
            }

            struct SingleArgumentParser
            {
                SingleArgumentParser()
                    : found(false) { }

                bool found;

                virtual void parse(chaiscript::Boxed_Value) = 0;
            };            

            template<typename T>
            struct SpecializedSingleArgumentParser : public SingleArgumentParser
            {
                SpecializedSingleArgumentParser(T* storage)
                    : storage(storage) { }

                void parse(chaiscript::Boxed_Value boxed) override
                {
                    *storage = smart_boxed_cast<T>(boxed);
                    found = true;
                }
                
                T* storage;
            };

            class ArgumentMapParser
            {
            public:
                template<typename T>
                void add(const std::string& tag, T* storage)
                {
                    m_parsers[tag] = std::make_shared<SpecializedSingleArgumentParser<T>>(storage);
                }

                void parse(const std::map<std::string, chaiscript::Boxed_Value>& argument_map)
                {
                    for (auto argument_it : argument_map)
                    {
                        auto& tag = argument_it.first;
                        auto& boxed = argument_it.second;

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

                    for (auto parser_it : m_parsers)
                    {
                        auto& tag = parser_it.first;
                        auto& parser = parser_it.second;

                        if (!parser->found)
                        {
                            std::ostringstream ss;
                            ss << "Missing parameter " << tag;

                            throw std::runtime_error(ss.str());
                        }
                    }
                }

            private:
                std::map<std::string, std::shared_ptr<SingleArgumentParser>> m_parsers;
            };
        }
    }
}