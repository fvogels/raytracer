require './shared.rb'


test_file 'sphere' do
  template do
    <<-'END'
      #ifdef TEST_BUILD

      #include "Catch.h"
      #include "primitives/primitives.h"
      #include "math/approx.h"

      using namespace math;
      using namespace raytracer;
      using namespace raytracer::primitives;


      <<<TESTS>>>

      #endif
    END
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Sphere] No hit with ray #{ray_origin} + #{ray_direction} * t", "[Sphere]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto sphere = raytracer::primitives::sphere();
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            hit.t = #{t};

            REQUIRE(!sphere->find_first_positive_hit(ray, &hit));
        }
      END
    end

    test_case do |data|
      data.ray_origin = '(0,0,5)'
      data.ray_direction = '(0,0,1)'
      data.t = 10
    end

    test_case do |data|
      data.ray_origin = '(0,0,-5)'
      data.ray_direction = '(0,0,-1)'
      data.t = 10
    end

    test_case do |data|
      data.ray_origin = '(0,2,0)'
      data.ray_direction = '(0,1,0)'
      data.t = 10
    end

    test_case do |data|
      data.ray_origin = '(0,-2,0)'
      data.ray_direction = '(0,-1,0)'
      data.t = 10
    end

    test_case do |data|
      data.ray_origin = '(4,0,0)'
      data.ray_direction = '(1,0,0)'
      data.t = 10
    end

    test_case do |data|
      data.ray_origin = '(-4,0,0)'
      data.ray_direction = '(-1,0,0)'
      data.t = 10
    end

    test_case do |data|
      data.ray_origin = '(4,0,0)'
      data.ray_direction = '(-1,0,0)'
      data.t = 2
    end

    test_case do |data|
      data.ray_origin = '(40,0,0)'
      data.ray_direction = '(-1,0,0)'
      data.t = 10
    end

    test_case do |data|
      data.ray_origin = '(40,0,0)'
      data.ray_direction = '(-2,0,0)'
      data.t = 10
    end
    
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Sphere] First hit with ray #{ray_origin} + #{ray_direction} * t", "[Sphere]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto sphere = raytracer::primitives::sphere();
            Ray ray(ray_origin, ray_direction);

            Hit hit;

            REQUIRE(sphere->find_first_positive_hit(ray, &hit));
            CHECK(hit.t == Approx(#{expected_t}));
            CHECK(hit.position == approx(Point3D#{expected_hit_position}));
            CHECK(hit.normal == approx(Vector3D#{expected_normal_position}));
        }
      END
    end

    test_case do |data|
      data.ray_origin = '(0,0,5)'
      data.ray_direction = '(0,0,-1)'
      data.expected_t = '4'
      data.expected_hit_position = '(0,0,1)'
      data.expected_normal_position = data.expected_hit_position
    end

    test_case do |data|
      data.ray_origin = '(0,0,3)'
      data.ray_direction = '(0,0,-1)'
      data.expected_t = '2'
      data.expected_hit_position = '(0,0,1)'
      data.expected_normal_position = data.expected_hit_position
    end

    test_case do |data|
      data.ray_origin = '(0,0,-3)'
      data.ray_direction = '(0,0,+1)'
      data.expected_t = '2'
      data.expected_hit_position = '(0,0,-1)'
      data.expected_normal_position = data.expected_hit_position
    end

    test_case do |data|
      data.ray_origin = '(4,0,0)'
      data.ray_direction = '(-1,0,0)'
      data.expected_t = '3'
      data.expected_hit_position = '(1,0,0)'
      data.expected_normal_position = data.expected_hit_position
    end

    test_case do |data|
      data.ray_origin = '(-8,0,0)'
      data.ray_direction = '(1,0,0)'
      data.expected_t = '7'
      data.expected_hit_position = '(-1,0,0)'
      data.expected_normal_position = data.expected_hit_position
    end

    test_case do |data|
      data.ray_origin = '(0,4,0)'
      data.ray_direction = '(0,-1,0)'
      data.expected_t = '3'
      data.expected_hit_position = '(0,1,0)'
      data.expected_normal_position = data.expected_hit_position
    end

    test_case do |data|
      data.ray_origin = '(0,-2,0)'
      data.ray_direction = '(0,1,0)'
      data.expected_t = '1'
      data.expected_hit_position = '(0,-1,0)'
      data.expected_normal_position = data.expected_hit_position
    end

    test_case do |data|
      data.ray_origin = '(0,0,0)'
      data.ray_direction = '(0,1,0)'
      data.expected_t = '1'
      data.expected_hit_position = '(0,1,0)'
      data.expected_normal_position = '(0,-1,0)'
    end
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Sphere] All hits with ray #{ray_origin} + #{ray_direction} * t", "[Sphere]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};

            auto sphere = raytracer::primitives::sphere();
            Ray ray(ray_origin, ray_direction);

            Hit hit;

            auto hits = sphere->find_all_hits(ray);
            REQUIRE(hits.size() == 2);
            CHECK(hits[0]->t == #{expected_ts[0]});
            CHECK(hits[1]->t == #{expected_ts[1]});
        }
      END
    end

    test_case do |data|
      data.ray_origin = '(0,0,5)'
      data.ray_direction = '(0,0,-1)'
      data.expected_ts = [ '4', '6' ]
    end

    test_case do |data|
      data.ray_origin = '(0,0,4)'
      data.ray_direction = '(0,0,-1)'
      data.expected_ts = [ '3', '5' ]
    end

    test_case do |data|
      data.ray_origin = '(0,0,-5)'
      data.ray_direction = '(0,0,1)'
      data.expected_ts = [ '4', '6' ]
    end
    
    test_case do |data|
      data.ray_origin = '(0,0,-3)'
      data.ray_direction = '(0,0,1)'
      data.expected_ts = [ '2', '4' ]
    end

    test_case do |data|
      data.ray_origin = '(3,0,0)'
      data.ray_direction = '(-1,0,0)'
      data.expected_ts = [ '2', '4' ]
    end

    test_case do |data|
      data.ray_origin = '(-3,0,0)'
      data.ray_direction = '(1,0,0)'
      data.expected_ts = [ '2', '4' ]
    end

    test_case do |data|
      data.ray_origin = '(0,7,0)'
      data.ray_direction = '(0,-1,0)'
      data.expected_ts = [ '6', '8' ]
    end

    test_case do |data|
      data.ray_origin = '(0,-7,0)'
      data.ray_direction = '(0,1,0)'
      data.expected_ts = [ '6', '8' ]
    end

    test_case do |data|
      data.ray_origin = '(0,-7,0)'
      data.ray_direction = '(0,2,0)'
      data.expected_ts = [ '3', '4' ]
    end

    test_case do |data|
      data.ray_origin = '(0,0,0)'
      data.ray_direction = '(0,1,0)'
      data.expected_ts = [ '-1', '1' ]
    end

    test_case do |data|
      data.ray_origin = '(0,0,0)'
      data.ray_direction = '(0,0,1)'
      data.expected_ts = [ '-1', '1' ]
    end

    test_case do |data|
      data.ray_origin = '(0,0,0)'
      data.ray_direction = '(1,0,0)'
      data.expected_ts = [ '-1', '1' ]
    end
  end
end
