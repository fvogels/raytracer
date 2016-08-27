#include "raytracing/ray-tracer-v6.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


namespace
{
    bool refract(const Vector3D& v, const Vector3D& n, double n1, double n2, Vector3D* output)
    {
        assert(v.is_unit());
        assert(n.is_unit());
        assert(v.dot(n) < 0);

        Vector3D rx = n1 / n2 * (v - v.dot(n) * n);

        double x = 1 - rx.norm_sqr();

        if (x >= 0)
        {
            Vector3D ry = -sqrt(x) * n;
            Vector3D r = rx + ry;

            assert(r.is_unit());

            *output = r;
            return true;
        }
        else
        {
            return false;
        }
    }
}


TraceResult raytracer::raytracers::_private_::RayTracerV6::trace(const Scene& scene, const Ray& eye_ray, double weight) const
{
    assert(weight >= 0);

    if (weight >= m_minimum_weight)
    {
        Hit hit;

        if (scene.root->find_first_positive_hit(eye_ray, &hit))
        {
            assert(hit.material);

            Color result = colors::black();
            auto material_properties = hit.material->at(hit.local_position);

            result += compute_ambient(material_properties);
            result += process_lights(scene, material_properties, hit, eye_ray);
            result += compute_reflection(scene, material_properties, hit, eye_ray, weight);
            result += compute_refraction(scene, material_properties, hit, eye_ray, weight);

            return TraceResult(result, hit.group_id, eye_ray, hit.t);
        }
        else
        {
            return TraceResult::no_hit(eye_ray);
        }
    }
    else
    {
        return TraceResult::no_hit(eye_ray);
    }
}

Color raytracer::raytracers::_private_::RayTracerV6::compute_refraction(const Scene& scene, const MaterialProperties& material_properties, const Hit& hit, const math::Ray& eye_ray, double weight) const
{
    if (material_properties.transparency > 0)
    {
        const Vector3D v = eye_ray.direction.normalized();
        const Vector3D n = hit.normal;
        const double n1 = 1;
        const double n2 = material_properties.refractive_index;

        Vector3D refracted_direction;

        if (refract(v, n, n1, n2, &refracted_direction))
        {
            const Point3D refracted_origin = hit.position + 0.000001 * refracted_direction;
            const Ray refracted_ray(refracted_origin, refracted_direction);

            Hit refracted_hit;
            if (!scene.root->find_first_positive_hit(refracted_ray, &refracted_hit))
            {
                return colors::black();
            }
            else
            {
                const Vector3D v = refracted_ray.direction;
                Vector3D n = refracted_hit.normal;
                const double n1 = material_properties.refractive_index;
                const double n2 = 1;

                if (refracted_ray.direction.dot(n) > 0)
                {
                    n = -n;
                }

                Vector3D refracted_direction;

                if (refract(v, n, n1, n2, &refracted_direction))
                {
                    const Point3D refracted_origin = refracted_hit.position + 0.000001 * refracted_direction;
                    const Ray refracted_ray(refracted_origin, refracted_direction);

                    return trace(scene, refracted_ray, material_properties.transparency * weight).color * weight;
                }
                else
                {
                    return colors::black();
                }
            }
        }
        else
        {
            return colors::black();
        }
    }
    else
    {
        return colors::black();
    }
}

raytracer::RayTracer raytracer::raytracers::v6(double minimum_weight)
{
    return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV6>(minimum_weight));
}