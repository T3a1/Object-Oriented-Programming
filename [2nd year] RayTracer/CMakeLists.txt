cmake_minimum_required(VERSION 3.10)
project(raytracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(
    src
    src/Lights
    src/Math
    src/Raytracer
    src/Raytracer/SceneBuilding 
    src/Shapes
    src/Utils
    src/Utils/FileWatcher
    src/Utils/Plugin
    src/Utils/DLloader
    src/Factory
)

# Add individual subdirectories to include paths
foreach(dir Lights Math Raytracer Shapes Utils Factory)
    include_directories(src/${dir})
endforeach()

# ============ CORE LIBRARY (libraytracer_core.so) ============
set(CORE_SOURCES
    src/Math/Vector3D.cpp
    src/Math/Point3D.cpp
    src/Math/Rotate3D.cpp
    src/Raytracer/Ray.cpp
    src/Raytracer/Rectangle3D.cpp
    src/Raytracer/Camera.cpp
    src/Raytracer/Scene.cpp
    src/Raytracer/SceneBuilding/LibConfigSceneBuilder.cpp
    src/Raytracer/SceneBuilding/HardCodedSceneBuilder.cpp
    src/Shapes/Sphere.cpp
    src/Shapes/Plane.cpp
    src/Shapes/Cylinder.cpp
    src/Shapes/Cone.cpp
    src/Shapes/LimitedCylinder.cpp
    src/Shapes/LimitedCone.cpp
    src/Shapes/Triangle.cpp
    src/Shapes/ObjShape.cpp
    src/Shapes/GroupShape.cpp
    src/Shapes/BVHNode.cpp
    src/Factory/ShapeFactory.cpp
    src/Factory/LightFactory.cpp
    src/Lights/AmbientLight.cpp
    src/Lights/DirectionalLight.cpp
    src/Lights/PointLight.cpp
    src/Utils/FileWatcher/FileWatcher.cpp
    src/Utils/AABB.cpp
)

add_library(raytracer_core SHARED ${CORE_SOURCES})
target_link_libraries(raytracer_core config++ dl)

set_target_properties(raytracer_core PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins
)

# ============ MAIN EXECUTABLE ============
add_executable(raytracer src/main.cpp)
target_link_libraries(raytracer raytracer_core config++ dl)

set_target_properties(raytracer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# ============ PLUGINS ============
set(PLUGINS_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/plugins)

# Plugin: Basic Primitives
add_library(primitives SHARED src/Utils/Plugin/ShapesPlugin/ShapesPlugin.cpp)
target_include_directories(primitives PRIVATE src src/Shapes src/Factory src/Utils/Plugin)
target_link_libraries(primitives raytracer_core)

set_target_properties(primitives PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_OUTPUT_DIR}
    PREFIX "lib"
    SUFFIX ".so"
)

# Plugin: Standard Lights
add_library(lights SHARED src/Utils/Plugin/LightsPlugin/LightsPlugin.cpp)
target_include_directories(lights PRIVATE src src/Lights src/Factory src/Utils/Plugin)
target_link_libraries(lights raytracer_core)

set_target_properties(lights PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PLUGINS_OUTPUT_DIR}
    PREFIX "lib"
    SUFFIX ".so"
)
