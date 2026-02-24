# Raytracer

A raytracer that gets input from a text file and output a ppm file with objects like cones, cylinders, ellipsoids and spheres.

# Build Instructions
1. cd Raytracing_Renderer/
2. mkdir build
3. cmake -S . -B build
4. cmake --build build
5. ./build/raytracer1a out/shapes.txt
6. run ppm file in gimp, krita or any art software that supports ppm