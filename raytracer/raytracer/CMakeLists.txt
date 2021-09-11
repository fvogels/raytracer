cmake_minimum_required(VERSION 3.10)

# set the project name
project(raytracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_definitions(-DELPP_CUSTOM_OUT=std::cerr -DELPP_THREAD_SAFE -DELPP_FEATURE_PERFORMANCE_TRACKING)

include_directories(".")

add_compile_options(-Wall -Wextra -pedantic -Werror -ldl)

set(CMAKE_CXX_FLAGS -pthread)

# add the executable
add_executable(raytracer
        ./animation/animation.cpp
        ./animation/circular-animation.cpp
        ./animation/duration.cpp
        ./animation/lissajous.cpp
        ./animation/time-stamp.cpp
        ./app.cpp
        ./cameras/camera.cpp
        ./cameras/depth-of-field-perspective-camera.cpp
        ./cameras/displaceable-camera.cpp
        ./cameras/fisheye-camera.cpp
        ./cameras/orthographic-camera.cpp
        ./cameras/perspective-camera.cpp
        ./command-line-parser.cpp
        ./imaging/bitmap-function.cpp
        ./imaging/bitmap.cpp
        ./imaging/bmp-format.cpp
        ./imaging/color-mapper.cpp
        ./imaging/color.cpp
        ./imaging/ppm-format.cpp
        ./imaging/wif/wif-image-reader.cpp
        ./imaging/wif-format.cpp
        ./io/file-binary-reader.cpp
        ./lights/anisotropic-light.cpp
        ./lights/area-light.cpp
        ./lights/directional-light.cpp
        ./lights/light-ray.cpp
        ./lights/omnidirectional-point-light.cpp
        ./lights/point-light.cpp
        ./lights/spot-light.cpp
        ./logging.cpp
        ./materials/composition-material.cpp
        ./materials/marble-material.cpp
        ./materials/material-properties.cpp
        ./materials/material-transformer.cpp
        ./materials/material.cpp
        ./materials/pattern-material.cpp
        ./materials/perlin-material.cpp
        ./materials/texture-material.cpp
        ./materials/uniform-material.cpp
        ./materials/wood-material.cpp
        ./materials/worley-material.cpp
        ./math/angle.cpp
        ./math/box.cpp
        ./math/functions/easing/bounce-easing-function.cpp
        ./math/functions/easing/cubic-easing-function.cpp
        ./math/functions/easing/elastic-easing-function.cpp
        ./math/functions/easing/linear-easing-function.cpp
        ./math/functions/easing/quadratic-easing-function.cpp
        ./math/functions/easing/quintic-easing-function.cpp
        ./math/functions/easing/stretch-easing-function.cpp
        ./math/functions/gauss.cpp
        ./math/functions/marble.cpp
        ./math/functions/perlin.cpp
        ./math/functions/random-function.cpp
        ./math/functions/voronoi.cpp
        ./math/functions/wood.cpp
        ./math/functions/worley.cpp
        ./math/matrix.cpp
        ./math/plane.cpp
        ./math/quadratic_equation.cpp
        ./math/quantize.cpp
        ./math/quaternion.cpp
        ./math/rasterizer.cpp
        ./math/ray.cpp
        ./math/rectangle2d.cpp
        ./math/rectangle3d.cpp
        ./math/transformation-matrices.cpp
        ./math/transformation2d.cpp
        ./math/transformation3d.cpp
        ./patterns/checkered-pattern.cpp
        ./patterns/dalmatian-pattern.cpp
        ./patterns/flower-pattern.cpp
        ./patterns/grid-pattern.cpp
        ./patterns/lambda-pattern.cpp
        ./patterns/lines-pattern.cpp
        ./patterns/mirror-pattern.cpp
        ./patterns/pattern-logic-operations.cpp
        ./patterns/pattern-tiling.cpp
        ./patterns/pattern-transformations.cpp
        ./patterns/polar-pattern.cpp
        ./patterns/polka-dots-pattern.cpp
        ./patterns/revolution-pattern.cpp
        ./patterns/spiral-pattern.cpp
        ./patterns/split-pattern.cpp
        ./performance/performance.cpp
        ./pipeline/animation-processor.cpp
        ./pipeline/base64-processor.cpp
        ./pipeline/bmp-consumer.cpp
        ./pipeline/inverter-processor.cpp
        ./pipeline/motion-blur-processor.cpp
        ./pipeline/overprint-processor.cpp
        ./pipeline/ppm-consumer.cpp
        ./pipeline/renderer-processor.cpp
        ./pipeline/studio-export-consumer.cpp
        ./pipeline/text-writer-consumer.cpp
        ./pipeline/wif-consumer.cpp
        ./pipeline/wif-processor.cpp
        ./primitives/bounding-box-accelerator-primitive.cpp
        ./primitives/box-primitive.cpp
        ./primitives/bumpifier-primitive.cpp
        ./primitives/cone-primitive.cpp
        ./primitives/cropper-primitive.cpp
        ./primitives/csg-difference-primitive.cpp
        ./primitives/csg-intersection-primitive.cpp
        ./primitives/csg-union-primitive.cpp
        ./primitives/cube-primitive.cpp
        ./primitives/cylinder-primitive.cpp
        ./primitives/decorator-primitive.cpp
        ./primitives/disk-primitive.cpp
        ./primitives/fast-mesh-primitive.cpp
        ./primitives/group-primitive.cpp
        ./primitives/mesh/mesh-binary-reader.cpp
        ./primitives/mesh/mesh-primitive.cpp
        ./primitives/mesh/mesh-text-reader.cpp
        ./primitives/plane-primitive.cpp
        ./primitives/primitive.cpp
        ./primitives/rectangle-primitive.cpp
        ./primitives/resizer-primitive.cpp
        ./primitives/smooth-triangle-primitive.cpp
        ./primitives/sphere-primitive.cpp
        ./primitives/square-primitive.cpp
        ./primitives/terrain-primitive.cpp
        ./primitives/transformer-primitive.cpp
        ./primitives/triangle-primitive.cpp
        ./primitives/unify.cpp
        ./primitives/union-primitive.cpp
        ./raytracers/ray-tracer-v0.cpp
        ./raytracers/ray-tracer-v1.cpp
        ./raytracers/ray-tracer-v2.cpp
        ./raytracers/ray-tracer-v3.cpp
        ./raytracers/ray-tracer-v4.cpp
        ./raytracers/ray-tracer-v5.cpp
        ./raytracers/ray-tracer-v6.cpp
        ./raytracers/ray-tracer-v7.cpp
        ./raytracers/ray-tracer-v8.cpp
        ./renderers/cartoon-renderer.cpp
        ./renderers/distance-renderer.cpp
        ./renderers/edge-renderer.cpp
        ./renderers/masking-renderer.cpp
        ./renderers/renderer-base.cpp
        ./renderers/split-depth-renderer.cpp
        ./renderers/standard-renderer.cpp
        ./samplers/multi-jittered-sampler.cpp
        ./samplers/nrooks-sampler.cpp
        ./samplers/random-sampler.cpp
        ./samplers/sampler.cpp
        ./samplers/single-sampler.cpp
        ./samplers/stratified-fixed-sampler.cpp
        ./samplers/stratified-half-jittered-sampler.cpp
        ./samplers/stratified-jittered-sampler.cpp
        ./scripting/animation-module.cpp
        ./scripting/cameras-module.cpp
        ./scripting/imaging-module.cpp
        ./scripting/lights-module.cpp
        ./scripting/materials-module.cpp
        ./scripting/math-module.cpp
        ./scripting/patterns-module.cpp
        ./scripting/pipeline-module.cpp
        ./scripting/primitives-module.cpp
        ./scripting/raytracing-module.cpp
        ./scripting/rendering-module.cpp
        ./scripting/samplers-module.cpp
        ./scripting/scripting.cpp
        ./tasks/lambda-task.cpp
        ./tasks/parallel-task-scheduler.cpp
        ./tasks/serial-task-scheduler.cpp
        ./util/base64.cpp
        ./util/beep.cpp
        ./util/misc.cpp
        ./easylogging++.cc)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(raytracer ${CMAKE_DL_LIBS} Threads::Threads)

