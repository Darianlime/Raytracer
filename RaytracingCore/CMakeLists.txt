set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
cmake_minimum_required(VERSION 3.10)

project(raytracer1a)

option(RAYTRACER_BUILD_APP "Build raytracer executable" ON)

add_library(lib
    src/viewport.cpp
    src/camera.cpp

    src/raycast.cpp

    src/color.cpp
    src/material.cpp
    src/texture.cpp

    src/object.cpp
    
    src/models/model.cpp
    src/models/mesh.cpp
    src/models/sphere.cpp
    src/models/cylinder.cpp
    src/models/cone.cpp
    src/models/ellipsoid.cpp
    src/models/geometry.cpp

    src/BVH/BoundingBox.cpp
    src/BVH/BVH.cpp

    src/lights/light.cpp
    src/lights/DirectionalLight.cpp
    src/lights/PointLight.cpp

    src/factory/ModelFactory.cpp
    src/factory/LightFactory.cpp
    src/factory/ObjectFactory.cpp

    src/file.cpp
)

target_include_directories(lib PUBLIC include)

if(RAYTRACER_BUILD_APP)
    add_executable(${PROJECT_NAME} main.cpp)
    target_link_libraries(${PROJECT_NAME} PRIVATE lib)
endif()