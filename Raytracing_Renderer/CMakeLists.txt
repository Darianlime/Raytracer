cmake_minimum_required(VERSION 3.10)

project(raytracer1a)

add_library(lib
    src/vector.cpp

    src/screen.cpp
    src/camera.cpp

    src/raycast.cpp

    src/color.cpp
    src/material.cpp

    src/object.cpp
    
    src/shapes/shape.cpp
    src/shapes/sphere.cpp
    src/shapes/cylinder.cpp
    src/shapes/cone.cpp
    src/shapes/ellipsoid.cpp

    src/lights/light.cpp
    src/lights/DirectionalLight.cpp
    src/lights/PointLight.cpp

    src/factory/ShapeFactory.cpp
    src/factory/LightFactory.cpp

    src/factory/ObjectFactory.cpp

    include/ray.h

    src/file.cpp
)

target_include_directories(lib PUBLIC include)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE lib)