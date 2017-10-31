require './shared.rb'

file_template = proc do
  <<-'END'
    #ifdef TEST_BUILD

    #include "Catch.h"
    #include "primitives/primitives.h"
    #include "math/approx.h"
    #include <algorithm>

    using namespace math;
    using namespace raytracer;
    using namespace raytracer::primitives;


    <<<TESTS>>>

    #endif
  END
end  


test_file 'primitives/triangle/is-triangle-hit' do
  template(&file_template)

  test_suite do
    template do
      <<-END
        TEST_CASE("[Triangle] Is there hit between Triangle #{a} #{b} #{c} and Ray #{ray_origin} + #{ray_direction} * t", "[Triangle]")
        {
            Point3D ray_origin#{ray_origin};
            Vector3D ray_direction#{ray_direction};
            Point3D a#{a};
            Point3D b#{b};
            Point3D c#{c};

            auto primitive = raytracer::primitives::triangle(a, b, c);
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            bool is_hit = primitive->find_first_positive_hit(ray, &hit);

            REQUIRE(is_hit == #{expected_is_hit});
        }
      END
    end

    [-7, -1, -0.001, 0.001, 0.5, 0.99, 1.01, 1.5].each do |x|
      test_case do |data|
        data.a = "(0, 0, 0)"
        data.b = "(2, 0, 0)"
        data.c = "(0, 2, 0)"
        data.ray_origin = "(#{x}, 1, 1)"
        data.ray_direction = "(0, 0, -1)"
        data.expected_is_hit = if 0 < x && x < 1 then 'true' else 'false' end
      end

      test_case do |data|
        data.a = "(0, 0, 0)"
        data.b = "(2, 0, 0)"
        data.c = "(0, 2, 0)"
        data.ray_origin = "(#{x}, 1, -1)"
        data.ray_direction = "(0, 0, 1)"
        data.expected_is_hit = if 0 < x && x < 1 then 'true' else 'false' end
      end
    end

    [-7, -1, -0.001, 0.001, 0.5, 1.99, 2.01, 2.5].each do |x|
      test_case do |data|
        data.a = "(0, 0, 0)"
        data.b = "(4, 0, 0)"
        data.c = "(0, 4, 0)"
        data.ray_origin = "(#{x}, 2, 5)"
        data.ray_direction = "(0, 0, -0.5)"
        data.expected_is_hit = if 0 < x && x < 2 then 'true' else 'false' end
      end

      test_case do |data|
        data.a = "(0, 0, 0)"
        data.b = "(4, 0, 0)"
        data.c = "(0, 4, 0)"
        data.ray_origin = "(#{x}, 2, -7)"
        data.ray_direction = "(0, 0, 0.25)"
        data.expected_is_hit = if 0 < x && x < 2 then 'true' else 'false' end
      end
    end

    [-8, 0.5, 1.5, 2.5, 2.99, 3.01, 5, 5.99, 6.01, 7, 99].each do |x|
      test_case do |data|
        data.a = "(0, 0, 0)"
        data.b = "(6, 6, 0)"
        data.c = "(6, 0, 0)"
        data.ray_origin = "(#{x}, 3, 5)"
        data.ray_direction = "(0, 0, -0.5)"
        data.expected_is_hit = if 3 < x && x < 6 then 'true' else 'false' end
      end
    end

    [-5, 0, 5, 9.99, 10.01, 10.99, 11.01, 19].each do |y|
      test_case do |data|
        data.a = "(0, 10, 10)"
        data.b = "(0, 10, 18)"
        data.c = "(0, 12, 18)"
        data.ray_origin = "(5, #{y}, 14)"
        data.ray_direction = "(-5, 0, 0)"
        data.expected_is_hit = if 10 < y && y < 11 then 'true' else 'false' end
      end
    end

    [-5, 0, 5, 9.99, 10.01, 10.99, 11.01, 19].each do |y|
      test_case do |data|
        data.a = "(-7, 10, 10)"
        data.b = "(-3, 10, 18)"
        data.c = "(-11, 12, 18)"
        data.ray_origin = "(5, #{y}, 14)"
        data.ray_direction = "(-5, 0, 0)"
        data.expected_is_hit = if 10 < y && y < 11 then 'true' else 'false' end
      end
    end
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Triangle] Is there hit between Triangle #{a} #{b} #{c} and Ray starting at #{ray_origin} through u=#{u} v=#{v}", "[Triangle]")
        {
            Point3D ray_origin#{ray_origin};
            Point3D a#{a};
            Point3D b#{b};
            Point3D c#{c};
            Vector3D ab = b - a;
            Vector3D ac = c - a;
            double u = #{u};
            double v = #{v};
            Point3D center = a + ab * u + ac * v;
            Vector3D ray_direction = center - ray_origin;

            auto primitive = raytracer::primitives::triangle(a, b, c);
            Ray ray(ray_origin, ray_direction);

            Hit hit;
            bool is_hit = primitive->find_first_positive_hit(ray, &hit);

            REQUIRE(is_hit == #{expected_is_hit});
        }
      END
    end

    [1, 1.5, 6].each do |x|
      [0.3, 1.2, 7].each do |y|
        [-0.1, 0.2, 0.49, 0.7, 1.5].each do |u|
          [-0.6, 0.25, 0.49, 0.6, 1.7, 9].each do |v|
            test_case do |data|
              data.a = "(0, 0, 0)"
              data.b = "(#{x}, 0, 0)"
              data.c = "(0, #{y}, 0)"
              data.ray_origin = "(0, 0, 5)"
              data.u = u
              data.v = v
              data.expected_is_hit = if 0 < u && 0 < v && u + v < 1  then 'true' else 'false' end
            end
          end
        end           
      end
    end
  end
end



# test_file 'primitives/triangle/triangle-hits' do
#   template do
#     instance_eval(&file_template)
#   end

#   test_suite do
#     template do
#       <<-END
#         TEST_CASE("[Triangle] No hit between Triangle[#{a}, #{b}, #{c}] and ray #{ray_origin} + #{ray_direction} * t", "[Triangle]")
#         {
#             Point3D a#{a};
#             Point3D b#{b};
#             Point3D c#{c};
#             Point3D ray_origin#{ray_origin};
#             Vector3D ray_direction#{ray_direction};

#             auto triangle = raytracer::primitives::triangle(a, b, c);
#             Ray ray(ray_origin, ray_direction);

#             Hit hit;
#             hit.t = #{t};

#             REQUIRE(!triangle->find_first_positive_hit(ray, &hit));
#         }
#       END
#     end

#     test_case do |data|
#       data.a = "(0, 0, 0)"
#       data.b = "(1, 0, 0)"
#       data.c = "(1, 0, 1)"
#       data.ray_origin = "(0, 1, 0)"
#       data.ray_direction = "(0, 0, 1)"
#       data.t = "std::numeric_limits<double>::infinity()"
#     end

#     test_case do |data|
#       data.a = "(0, 0, 0)"
#       data.b = "(1, 1, 0)"
#       data.c = "(1, 0, 1)"
#       data.ray_origin = "(0, 2, 0)"
#       data.ray_direction = "(0, 0, 1)"
#       data.t = "std::numeric_limits<double>::infinity()"
#     end

#     test_case do |data|
#       data.a = "(5, 5, 0)"
#       data.b = "(5, 6, 0)"
#       data.c = "(6, 6, 0)"
#       data.ray_origin = "(0, 0, 0)"
#       data.ray_direction = "(0, 0, 1)"
#       data.t = "std::numeric_limits<double>::infinity()"
#     end

#     test_case do |data|
#       data.a = "(-5, 5, 0)"
#       data.b = "(5, 0, 0)"
#       data.c = "(-5, -5, 0)"
#       data.ray_origin = "(0, 0, 0)"
#       data.ray_direction = "(0, 0, 1)"
#       data.t = "1"
#     end
#   end

#   test_suite do
#     template do
#       <<-END
#         TEST_CASE("[Triangle] Hit between Triangle[#{a}, #{b}, #{c}] and ray #{ray_origin} + #{ray_direction} * t", "[Triangle]")
#         {
#             Point3D a#{a};
#             Point3D b#{b};
#             Point3D c#{c};
#             Point3D ray_origin#{ray_origin};
#             Vector3D ray_direction#{ray_direction};

#             auto triangle = raytracer::primitives::triangle(a, b, c);
#             Ray ray(ray_origin, ray_direction);

#             Hit hit;
#             hit.t = #{t};

#             REQUIRE(triangle->find_first_positive_hit(ray, &hit));
#         }
#       END
#     end

#     test_case do |data|
#       data.a = "(-1, -1, 0)"
#       data.b = "(-1, 1, 0)"
#       data.c = "(1, 0, 0)"
#       data.ray_origin = "(0, 0, -5)"
#       data.ray_direction = "(0, 0, 1)"
#       data.t = "std::numeric_limits<double>::infinity();"
#     end

#     test_case do |data|
#       data.a = "(-1, -1, 0)"
#       data.b = "(1, 0, 0)"
#       data.c = "(-1, 1, 0)"
#       data.ray_origin = "(0, 0, 5)"
#       data.ray_direction = "(0, 0, -1)"
#       data.t = "std::numeric_limits<double>::infinity();"
#     end

#     test_case do |data|
#       data.a = "(-1, -1, 0)"
#       data.b = "(1, 0, 4)"
#       data.c = "(-1, 1, 0)"
#       data.ray_origin = "(0, 0, 5)"
#       data.ray_direction = "(0, 0, -1)"
#       data.t = "std::numeric_limits<double>::infinity();"
#     end

#     test_case do |data|
#       data.a = "(-1, 0, 1)"
#       data.b = "(1, 0, 1)"
#       data.c = "(0, 0, -10)"
#       data.ray_origin = "(0, 5, 0)"
#       data.ray_direction = "(0, -5, 0)"
#       data.t = "std::numeric_limits<double>::infinity();"
#     end

#     test_case do |data|
#       data.a = "(-1, 0, -1)"
#       data.b = "(1, 0, -1)"
#       data.c = "(0, 0, 10)"
#       data.ray_origin = "(0, 5, 0)"
#       data.ray_direction = "(0, -5, 0)"
#       data.t = "std::numeric_limits<double>::infinity();"
#     end

#     test_case do |data|
#       data.a = "(-1, 0, 1)"
#       data.b = "(1, 0, 1)"
#       data.c = "(0, 0, -10)"
#       data.ray_origin = "(0, -5, 0)"
#       data.ray_direction = "(0, 5, 0)"
#       data.t = "std::numeric_limits<double>::infinity();"
#     end

#     test_case do |data|
#       data.a = "(-1, -1, 0)"
#       data.b = "(-1, 1, 0)"
#       data.c = "(1, 0, 0)"
#       data.ray_origin = "(0, 0, 5)"
#       data.ray_direction = "(0, 0, -1)"
#       data.t = "std::numeric_limits<double>::infinity();"
#     end
#   end

#   test_suite do
#     template do
#       <<-END
#         TEST_CASE("[Triangle] Hit normal between Triangle[#{a}, #{b}, #{c}] and ray #{ray_origin} + #{ray_direction} * t", "[Triangle]")
#         {
#             Point3D a#{a};
#             Point3D b#{b};
#             Point3D c#{c};
#             Point3D ray_origin#{ray_origin};
#             Vector3D ray_direction#{ray_direction};
#             Vector3D expected_normal#{expected_normal};

#             auto triangle = raytracer::primitives::triangle(a, b, c);
#             Ray ray(ray_origin, ray_direction);

#             Hit hit;
#             hit.t = #{t};

#             REQUIRE(triangle->find_first_positive_hit(ray, &hit));
#             REQUIRE(hit.normal == approx(expected_normal));
#         }
#       END
#     end

#     test_case do |data|
#       data.a = "(-1, -1, 0)"
#       data.b = "(-1, 1, 0)"
#       data.c = "(1, 0, 0)"
#       data.ray_origin = "(0, 0, -5)"
#       data.ray_direction = "(0, 0, 1)"
#       data.t = "std::numeric_limits<double>::infinity();"
      
#       data.expected_normal = "(0, 0, -1)"
#     end

#     test_case do |data|
#       data.a = "(-1, -1, 0)"
#       data.b = "(-1, 1, 0)"
#       data.c = "(1, 0, 0)"
#       data.ray_origin = "(0, 0, 5)"
#       data.ray_direction = "(0, 0, -1)"
#       data.t = "std::numeric_limits<double>::infinity();"
      
#       data.expected_normal = "(0, 0, 1)"
#     end

#     test_case do |data|
#       data.a = "(-5, 0, -3)"
#       data.b = "(-2, 0, 8)"
#       data.c = "(10, 0, 0)"
#       data.ray_origin = "(0, 5, 0)"
#       data.ray_direction = "(0, -1, 0)"
#       data.t = "std::numeric_limits<double>::infinity();"
      
#       data.expected_normal = "(0, 1, 0)"
#     end

#     test_case do |data|
#       data.a = "(-5, 0, -3)"
#       data.b = "(-2, 0, 8)"
#       data.c = "(10, 0, 0)"
#       data.ray_origin = "(0, -5, 0)"
#       data.ray_direction = "(0, 1, 0)"
#       data.t = "std::numeric_limits<double>::infinity();"
      
#       data.expected_normal = "(0, -1, 0)"
#     end
#   end

#   test_suite do
#     template do
#       <<-END
#         TEST_CASE("[Triangle] Hit t between Triangle[#{a}, #{b}, #{c}] and ray #{ray_origin} + #{ray_direction} * t", "[Triangle]")
#         {
#             Point3D a#{a};
#             Point3D b#{b};
#             Point3D c#{c};
#             Point3D ray_origin#{ray_origin};
#             Vector3D ray_direction#{ray_direction};
#             double expected_t = #{expected_t};

#             auto triangle = raytracer::primitives::triangle(a, b, c);
#             Ray ray(ray_origin, ray_direction);

#             Hit hit;
#             hit.t = #{t};

#             REQUIRE(triangle->find_first_positive_hit(ray, &hit));
#             REQUIRE(hit.t == approx(expected_t));
#         }
#       END
#     end

#     test_case do |data|
#       data.a = "(-1, -1, 0)"
#       data.b = "(-1, 1, 0)"
#       data.c = "(1, 0, 0)"
#       data.ray_origin = "(0, 0, -5)"
#       data.ray_direction = "(0, 0, 1)"
#       data.t = "std::numeric_limits<double>::infinity();"
      
#       data.expected_t = "(0, 0, 5)"
#     end

#     test_case do |data|
#       data.a = "(-1, -1, 0)"
#       data.b = "(-1, 1, 0)"
#       data.c = "(1, 0, 0)"
#       data.ray_origin = "(0, 0, 10)"
#       data.ray_direction = "(0, 0, -1)"
#       data.t = "std::numeric_limits<double>::infinity();"
      
#       data.expected_t = "(0, 0, 10)"
#     end
#   end
# end
