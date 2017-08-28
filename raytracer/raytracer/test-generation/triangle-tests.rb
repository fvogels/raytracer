require './shared.rb'


test_file 'primitives/triangle' do
  template do
    #ifdef TEST_BUILD

    #include "Catch.h"
    #include "primitives/primitives.h"
    #include "math/approx.h"

    using namespace math;
    using namespace raytracer;
    using namespace raytracer::primitives;


    <<<TESTS>>>

    #endif
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Triangle] Ray #{origin} + #{direction} * t hits triangle #{p}, #{q}, #{r}", "[Triangle]")
        {
            Point3D origin#{origin};
            Vector3D direction#{direction};
            Ray ray(origin, direction);

            Point3D p#{p};
            Point3D q#{q};
            Point3D r#{r};
            Triangle triangle(p, q, r);

            Hit hit;
            REQUIRE( triangle->find_first_positive_hit(ray, &hit) );
            
        }
      END
    end

    [ -77, 0, 15 ].each do |ox|
      [ -16, 0, 64 ].each do |oy|
        [ -50, 0, 37 ].each do |oz|
          [ 1, 5, 16 ].each do |b|
            [ 1, 7, 99 ].each do |h|
              
    test_case do |data|
      data.origin = "()"
      data.direction = "()"
      data.p = "()"
      data.q = "()"
      data.r = "()"
    end
  end
end
