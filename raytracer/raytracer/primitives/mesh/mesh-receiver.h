#pragma once

#include "primitives/primitive.h"
#include <iostream>


namespace raytracer
{
    namespace primitives
    {
        class MeshReceiver
        {
        public:
            virtual void vertex(double x, double y, double z) = 0;
            virtual void normal(double x, double y, double z) = 0;
            virtual void triangle(unsigned vertex1, unsigned vertex2, unsigned vertex3) = 0;
            virtual void box(unsigned n_children) = 0;
        };
    }
}