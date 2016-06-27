#include "materials/brdfs/lambert.h"
#include <algorithm>
#include <assert.h>

using namespace math;
using namespace raytracer::brdfs;


double raytracer::brdfs::_private_::Lambert::evaluate(const math::Vector3D& in, const math::Vector3D& out) const
{
    assert(in.is_unit());
    assert(out.is_unit());

    double cosine = in.dot(out);

    return std::max(0.0, cosine);
}