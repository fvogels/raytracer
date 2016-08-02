require 'erb'

def apply_template(template, hash)
  hash.each do |key, value|
    template = template.gsub(/\$#{key.upcase}/, value)
  end

  template
end

def fisheye_tests
  file_template = <<'END'
#ifdef TEST_BUILD

#include "Catch.h"
#include "cameras/cameras.h"

using namespace math;

namespace
{
    void assert_equals(const Point3D& expected, const Point3D& actual)
    {
        INFO("Expected: " << expected << "\nActual: " << actual);

        REQUIRE(approx(expected) == actual);
    }

    void assert_equals(const Vector3D& expected, const Vector3D& actual)
    {
        INFO("Expected: " << expected << "\nActual: " << actual);

        REQUIRE(approx(expected) == actual);
    }

    std::string show(const Ray& ray)
    {
        std::ostringstream ss;

        ss << ray;

        return ss.str();
    }
}

$TESTS

#endif
END

  test_template = <<'END'
TEST_CASE("[FisheyeCamera] Eye = $EYE, Lookat = $LOOK_AT, Up = $UP, HAngle = $HANGLE, VAngle = $VANGLE, At $POSITION", "[FisheyeCamera]")
{
    Point3D eye($EYE);
    Point3D look_at($LOOK_AT);
    Vector3D up($UP);
    Angle hangle = $HANGLE_degrees;
    Angle vangle = $VANGLE_degrees;
    Point2D position($POSITION);
    Point3D expected_origin($EXPECTED_ORIGIN);
    Vector3D expected_direction($EXPECTED_DIRECTION);

    auto camera = raytracer::cameras::fisheye(eye, look_at, up, hangle, vangle);
    auto rays = camera->create_rays(position);

    REQUIRE(rays.size() == 1);
    auto ray = rays.front();
    INFO( "Actual ray: " + show(ray) + "\nExpected ray: " + show(Ray(expected_origin, expected_direction)));
    assert_equals(ray.origin, expected_origin);
    assert_equals(ray.direction, expected_direction);
}
END

  File.open('fisheye-tests.cpp', 'w') do |out|
    
    tests = [ { eye: '0,0,0', look_at: '0,0,1', up: '0,1,0', hangle: '180', vangle: '180', position: '0.5,0.5', expected_origin: '0,0,0', expected_direction: '0,0,1' },
              { eye: '0,0,0', look_at: '0,0,1', up: '0,1,0', hangle: '180', vangle: '180', position: '0,0.5', expected_origin: '0,0,0', expected_direction: '1,0,0' },
              { eye: '0,0,0', look_at: '0,0,1', up: '0,1,0', hangle: '180', vangle: '180', position: '1,0.5', expected_origin: '0,0,0', expected_direction: '-1,0,0' },
              { eye: '0,0,0', look_at: '0,0,1', up: '0,1,0', hangle: '180', vangle: '180', position: '0.5,1', expected_origin: '0,0,0', expected_direction: '0,1,0' },
              { eye: '0,0,0', look_at: '0,0,1', up: '0,1,0', hangle: '180', vangle: '180', position: '0.5,0', expected_origin: '0,0,0', expected_direction: '0,-1,0' },
              
              { eye: '1,0,0', look_at: '1,0,1', up: '0,1,0', hangle: '180', vangle: '180', position: '0.5,0.5', expected_origin: '1,0,0', expected_direction: '0,0,1' },
              { eye: '-1,0,0', look_at: '-1,0,1', up: '0,1,0', hangle: '180', vangle: '180', position: '0.5,0.5', expected_origin: '-1,0,0', expected_direction: '0,0,1' },
              { eye: '-2,0,0', look_at: '-2,0,1', up: '0,1,0', hangle: '180', vangle: '180', position: '0.5,0.5', expected_origin: '-2,0,0', expected_direction: '0,0,1' },
              { eye: '0,0,0', look_at: '1,0,0', up: '0,1,0', hangle: '180', vangle: '180', position: '0.5,0.5', expected_origin: '0,0,0', expected_direction: '1,0,0' },

              { eye: '0,0,0', look_at: '0,0,1', up: '0,1,0', hangle: '360', vangle: '180', position: '0.5,0.5', expected_origin: '0,0,0', expected_direction: '0,0,1' },
              { eye: '0,0,0', look_at: '0,0,1', up: '0,1,0', hangle: '360', vangle: '180', position: '1,0.5', expected_origin: '0,0,0', expected_direction: '0,0,-1' },
              { eye: '0,0,0', look_at: '0,0,1', up: '0,1,0', hangle: '360', vangle: '180', position: '0,0.5', expected_origin: '0,0,0', expected_direction: '0,0,-1' },
            ].map do |hash|
      apply_template(test_template, hash)
    end.join("\n\n")

    out.write( apply_template(file_template, { tests: tests }) )
  end
end

def generate
  fisheye_tests
end

generate
