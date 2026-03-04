#ifndef VECTOR_H
#define VECTOR_H

#include "numbers.h"
#include <iostream>

using namespace math;

struct Vec2;
struct Vec3;

struct Vec2 {
    public:
        float x;
        float y;
        Vec2();
        Vec2(float x, float y);
};

struct Vec3 {
    public:
        float x;
        float y;
        float z;

        Vec3();
        Vec3(Vec2 vec2);
        Vec3(float x, float y, float z);

        bool operator==(const Vec3& other) const;

        // negate
        Vec3 operator-() const;

        Vec3 operator+(const Vec3& other) const;
        Vec3 operator-(const Vec3& other) const;
        //Divsion By scalar
        Vec3 operator/(const float scalar) const;
        Vec3 operator*(const float scalar) const;

        static float Dist(Vec3 vec1, Vec3 vec2);
        static float Mag(Vec3 vector);
        static float Dot(Vec3 vec1, Vec3 vec2);
        static Vec3 Cross(Vec3 vec1, Vec3 vec2);

        static Vec3 Zero();

        void ToString();
}; 

#endif