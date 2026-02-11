cmake_minimum_required(VERSION 3.10)

project(raytracer1a)

add_library(lib
    src/vector.cpp

    src/screen.cpp
    src/camera.cpp

    src/raycast.cpp

    src/color.cpp
    src/object.cpp
    src/sphere.cpp
    src/cylinder.cpp
    src/cone.cpp
    src/ellipsoid.cpp

    src/ObjectFactory.cpp

    include/ray.h

    src/file.cpp
)

target_include_directories(lib PUBLIC include)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE lib)