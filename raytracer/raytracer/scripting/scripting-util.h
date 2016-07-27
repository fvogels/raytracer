#pragma once

#include <chaiscript/chaiscript.hpp>
#include <string>
#include <map>

#define EXTRACT_ARGUMENT(TYPE, NAME)            auto NAME = raytracer::scripting::util::get_argument<TYPE>(argument_map, #NAME)
#define FACTORY_TYPE_DISPATCH(TYPE)             if ( type == #TYPE ) return TYPE(argument_map)
#define HANDLE_UNKNOWN_TYPE                     throw std::runtime_error("Unknown type")

namespace raytracer
{
    namespace scripting
    {
        namespace util
        {
            template<typename T>
            T get_argument(const std::map<std::string, chaiscript::Boxed_Value>& argument_map, const std::string& name)
            {
                return chaiscript::boxed_cast<T>(argument_map.at(name));
            }

            template<>
            double get_argument<double>(const std::map<std::string, chaiscript::Boxed_Value>& argument_map, const std::string& name)
            {
                auto value = argument_map.at(name);

                if (*value.get_type_info().bare_type_info() == typeid(int))
                {
                    return chaiscript::boxed_cast<int>(value);
                }
                else
                {
                    return chaiscript::boxed_cast<double>(value);
                }
            }
        }
    }
}