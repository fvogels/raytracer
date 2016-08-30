require './shared.rb'


test_file 'matrix-tests' do
  template do
    <<-'END'
      #ifdef TEST_BUILD

      #include "Catch.h"
      #include "math/matrix.h"
      #include "math/transformation-matrices.h"

      using namespace math;
      using namespace math::transformation_matrices;


      <<<TESTS>>>

      #endif
    END
  end

  test_suite do
    template do
      <<-END
        TEST_CASE("[Matrix] Matrix transformation #{first} equals #{second}", "[Matrix]")
        {
            auto a = #{first};
            auto b = #{second};

            REQUIRE( a == approx(b) );
        }
      END
    end

    test_case do |data|
      data.first = 'identity<4>()'
      data.second = 'identity<4>()'
    end

    test_case do |data|
      data.first = 'translation(Vector3D(0,0,0))'
      data.second = 'identity<4>()'
    end


    test_case do |data|
      data.first = 'scaling(1,1,1)'
      data.second = 'identity<4>()'
    end

    test_case do |data|
      data.first = 'rotation_around_x(0_degrees)'
      data.second = 'identity<4>()'
    end

    test_case do |data|
      data.first = 'rotation_around_y(0_degrees)'
      data.second = 'identity<4>()'
    end

    test_case do |data|
      data.first = 'rotation_around_z(0_degrees)'
      data.second = 'identity<4>()'
    end

    test_case do |data|
      data.first = 'rotation_around_x(0_degrees)'
      data.second = 'rotation_around_x(360_degrees)'
    end

    test_case do |data|
      data.first = 'rotation_around_x(-90_degrees)'
      data.second = 'rotation_around_x(270_degrees)'
    end

    test_case do |data|
      data.first = 'rotation_around_x(-180_degrees)'
      data.second = 'rotation_around_x(180_degrees)'
    end

    test_case do |data|
      data.first = 'scaling(-1,1,-1)'
      data.second = 'rotation_around_y(180_degrees)'
    end

    test_case do |data|
      data.first = 'scaling(-1,-1,1)'
      data.second = 'rotation_around_z(180_degrees)'
    end

    test_case do |data|
      data.first = 'scaling(1,-1,-1)'
      data.second = 'rotation_around_x(180_degrees)'
    end
  end


  test_suite do
    template do
      <<-END
        TEST_CASE("[Matrix] Matrix multiplication of #{first} and #{second}", "[Matrix]")
        {
            auto a = #{first};
            auto b = #{second};
            auto actual = a * b;
            auto expected = #{expected};

            REQUIRE( actual == approx(expected) );
        }
      END
    end

    test_case do |data|
      data.first = 'identity<4>()'
      data.second = 'identity<4>()'
      data.expected = 'identity<4>()'
    end

    test_case do |data|
      data.first = 'identity<4>()'
      data.second = 'scaling(2, 1, 1)'
      data.expected = 'scaling(2, 1, 1)'
    end

    test_case do |data|
      data.first = 'identity<4>()'
      data.second = 'scaling(1, 3, 1)'
      data.expected = 'scaling(1, 3, 1)'
    end

    test_case do |data|
      data.first = 'identity<4>()'
      data.second = 'scaling(1, 1, 4)'
      data.expected = 'scaling(1, 1, 4)'
    end

    test_case do |data|
      data.first = 'identity<4>()'
      data.second = 'rotation_around_x(40_degrees)'
      data.expected = 'rotation_around_x(40_degrees)'
    end

    test_case do |data|
      data.first = 'identity<4>()'
      data.second = 'rotation_around_y(10_degrees)'
      data.expected = 'rotation_around_y(10_degrees)'
    end

    test_case do |data|
      data.first = 'identity<4>()'
      data.second = 'rotation_around_z(250_degrees)'
      data.expected = 'rotation_around_z(250_degrees)'
    end

    test_case do |data|
      data.first = 'scaling(2, 1, 1)'
      data.second = 'scaling(2, 1, 1)'
      data.expected = 'scaling(4, 1, 1)'
    end

    test_case do |data|
      data.first = 'scaling(2, 1, 1)'
      data.second = 'scaling(0.5, 1, 1)'
      data.expected = 'scaling(1, 1, 1)'
    end

    test_case do |data|
      data.first = 'scaling(2, 1, 1)'
      data.second = 'scaling(1, 2, 1)'
      data.expected = 'scaling(2, 2, 1)'
    end

    test_case do |data|
      data.first = 'scaling(2, 1, 1)'
      data.second = 'scaling(1, 1, 2)'
      data.expected = 'scaling(2, 1, 2)'
    end

    test_case do |data|
      data.first = 'scaling(1, 3, 1)'
      data.second = 'scaling(1, 1, 2)'
      data.expected = 'scaling(1, 3, 2)'
    end

    test_case do |data|
      data.first = 'rotation_around_x(10_degrees)'
      data.second = 'rotation_around_x(10_degrees)'
      data.expected = 'rotation_around_x(20_degrees)'
    end

    test_case do |data|
      data.first = 'rotation_around_x(10_degrees)'
      data.second = 'rotation_around_x(-10_degrees)'
      data.expected = 'identity<4>()'
    end

    test_case do |data|
      data.first = 'rotation_around_x(10_degrees)'
      data.second = 'rotation_around_x(20_degrees)'
      data.expected = 'rotation_around_x(30_degrees)'
    end

    test_case do |data|
      data.first = 'rotation_around_y(10_degrees)'
      data.second = 'rotation_around_y(20_degrees)'
      data.expected = 'rotation_around_y(30_degrees)'
    end

    test_case do |data|
      data.first = 'rotation_around_z(10_degrees)'
      data.second = 'rotation_around_z(20_degrees)'
      data.expected = 'rotation_around_z(30_degrees)'
    end

    test_case do |data|
      data.first = 'translation(Vector3D(1,0,0))'
      data.second = 'translation(Vector3D(-1,0,0))'
      data.expected = 'identity<4>()'
    end

    test_case do |data|
      data.first = 'translation(Vector3D(0,5,0))'
      data.second = 'translation(Vector3D(0,-5,0))'
      data.expected = 'identity<4>()'
    end

    test_case do |data|
      data.first = 'translation(Vector3D(0,0,9))'
      data.second = 'translation(Vector3D(0,0,-9))'
      data.expected = 'identity<4>()'
    end

    test_case do |data|
      data.first = 'translation(Vector3D(1,0,0))'
      data.second = 'translation(Vector3D(0,0,2))'
      data.expected = 'translation(Vector3D(1,0,2))'
    end

    test_case do |data|
      data.first = 'translation(Vector3D(1,0,0))'
      data.second = 'Vector3D(0,0,0)'
      data.expected = 'Vector3D(0,0,0)'
    end

    test_case do |data|
      data.first = 'translation(Vector3D(0,1,0))'
      data.second = 'Vector3D(0,0,0)'
      data.expected = 'Vector3D(0,0,0)'
    end

    test_case do |data|
      data.first = 'translation(Vector3D(0,0,1))'
      data.second = 'Vector3D(0,0,0)'
      data.expected = 'Vector3D(0,0,0)'
    end

    test_case do |data|
      data.first = 'translation(Vector3D(1,0,0))'
      data.second = 'Point3D(0,0,0)'
      data.expected = 'Point3D(1,0,0)'
    end

    test_case do |data|
      data.first = 'translation(Vector3D(0,1,0))'
      data.second = 'Point3D(0,0,0)'
      data.expected = 'Point3D(0,1,0)'
    end

    test_case do |data|
      data.first = 'translation(Vector3D(0,0,1))'
      data.second = 'Point3D(0,0,0)'
      data.expected = 'Point3D(0,0,1)'
    end

    test_case do |data|
      data.first = 'scaling(2,1,1)'
      data.second = 'Point3D(0,0,0)'
      data.expected = 'Point3D(0,0,0)'
    end

    test_case do |data|
      data.first = 'scaling(2,1,1)'
      data.second = 'Point3D(1,0,0)'
      data.expected = 'Point3D(2,0,0)'
    end

    test_case do |data|
      data.first = 'scaling(2,3,4)'
      data.second = 'Point3D(1,1,1)'
      data.expected = 'Point3D(2,3,4)'
    end

    test_case do |data|
      data.first = 'scaling(2,3,4)'
      data.second = 'Point3D(2,2,2)'
      data.expected = 'Point3D(4,6,8)'
    end

    test_case do |data|
      data.first = 'rotation_around_x(180_degrees)'
      data.second = 'Point3D(2,2,2)'
      data.expected = 'Point3D(2,-2,-2)'
    end

    test_case do |data|
      data.first = 'rotation_around_y(180_degrees)'
      data.second = 'Point3D(2,2,2)'
      data.expected = 'Point3D(-2,2,-2)'
    end

    test_case do |data|
      data.first = 'rotation_around_z(180_degrees)'
      data.second = 'Point3D(2,2,2)'
      data.expected = 'Point3D(-2,-2,2)'
    end

    test_case do |data|
      data.first = 'rotation_around_x(180_degrees)'
      data.second = 'Vector3D(2,2,2)'
      data.expected = 'Vector3D(2,-2,-2)'
    end

    test_case do |data|
      data.first = 'rotation_around_y(180_degrees)'
      data.second = 'Vector3D(2,2,2)'
      data.expected = 'Vector3D(-2,2,-2)'
    end

    test_case do |data|
      data.first = 'rotation_around_z(180_degrees)'
      data.second = 'Vector3D(2,2,2)'
      data.expected = 'Vector3D(-2,-2,2)'
    end
    
    test_case do |data|
      data.first = 'rotation_around_x(90_degrees)'
      data.second = 'Point3D(0,0,0)'
      data.expected = 'Point3D(0,0,0)'
    end

    test_case do |data|
      data.first = 'rotation_around_x(90_degrees)'
      data.second = 'Point3D(1,0,0)'
      data.expected = 'Point3D(1,0,0)'
    end

    test_case do |data|
      data.first = 'rotation_around_x(90_degrees)'
      data.second = 'Point3D(0,1,0)'
      data.expected = 'Point3D(0,0,1)'
    end

    test_case do |data|
      data.first = 'rotation_around_x(90_degrees)'
      data.second = 'Point3D(0,0,1)'
      data.expected = 'Point3D(0,-1,0)'
    end

    test_case do |data|
      data.first = 'rotation_around_y(90_degrees)'
      data.second = 'Point3D(0,0,0)'
      data.expected = 'Point3D(0,0,0)'
    end

    test_case do |data|
      data.first = 'rotation_around_y(90_degrees)'
      data.second = 'Point3D(0,1,0)'
      data.expected = 'Point3D(0,1,0)'
    end

    test_case do |data|
      data.first = 'rotation_around_y(90_degrees)'
      data.second = 'Point3D(1,0,0)'
      data.expected = 'Point3D(0,0,-1)'
    end

    test_case do |data|
      data.first = 'rotation_around_y(90_degrees)'
      data.second = 'Point3D(0,0,-1)'
      data.expected = 'Point3D(-1,0,0)'
    end

    test_case do |data|
      data.first = 'rotation_around_y(90_degrees)'
      data.second = 'Point3D(-1,0,0)'
      data.expected = 'Point3D(0,0,1)'
    end

    test_case do |data|
      data.first = 'rotation_around_z(90_degrees)'
      data.second = 'Point3D(0,0,0)'
      data.expected = 'Point3D(0,0,0)'
    end

    test_case do |data|
      data.first = 'rotation_around_z(90_degrees)'
      data.second = 'Point3D(0,0,1)'
      data.expected = 'Point3D(0,0,1)'
    end

    test_case do |data|
      data.first = 'rotation_around_z(90_degrees)'
      data.second = 'Point3D(1,0,0)'
      data.expected = 'Point3D(0,1,0)'
    end

    test_case do |data|
      data.first = 'rotation_around_z(90_degrees)'
      data.second = 'Point3D(0,1,0)'
      data.expected = 'Point3D(-1,0,0)'
    end
  end
end
