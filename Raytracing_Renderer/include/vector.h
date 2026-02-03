#include <math.h>
#include <iostream>

using namespace std;

#ifndef VECTOR_H
#define VECTOR_H

struct Vec3 {
    public:
        float x;
        float y;
        float z;

        Vec3();
        Vec3(float x, float y, float z);

        Vec3 operator+(const Vec3& other) const;
        Vec3 operator-(const Vec3& other) const;
        //Divsion By scalar
        Vec3 operator/(const float scalar) const;
        Vec3 operator*(const float scalar) const;

        static float Mag(Vec3 vector);
        static float Dot(Vec3 vec1, Vec3 vec2);
        static Vec3 Cross(Vec3 vec1, Vec3 vec2);

        void ToString();
}; 

#endif