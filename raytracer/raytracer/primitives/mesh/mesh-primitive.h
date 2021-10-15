#pragma once

#include "primitives/primitive.h"
#include <string>


namespace raytracer
{
    namespace primitives
    {
        Primitive mesh(const std::string& path);

        Primitive mesh_unique_groups(const std::string& path);
    }
}