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
        Vec2() : x(0.0f), y(0.0f) {}
        Vec2(float x, float y) : x(x), y(y) {}

        bool operator==(const Vec2 &other) const {
            return x == other.x &&  y == other.y;
        }

        Vec2 operator-() const {
            return Vec2(-x, -y);
        }

        Vec2 operator+(const Vec2 &other) const {
            return Vec2(x + other.x, y + other.y);
        }

        Vec2 operator-(const Vec2 &other) const {
            return Vec2(x - other.x, y - other.y);
        }

        Vec2 operator/(const float scalar) const {
            return Vec2(x/scalar, y/scalar);
        }

        Vec2 operator*(const float scalar) const {
            return Vec2(x*scalar, y*scalar);
        }

        static float Dist(Vec2 vec1, Vec2 vec2) {
            return sqrt(pow(vec2.x - vec1.x, 2) + pow(vec2.y - vec1.y, 2));
        }

        float Mag() {
            return sqrt(pow(x, 2) + pow(y, 2));
        }

        static float Dot(Vec2 vec1, Vec2 vec2) {
            return vec1.x * vec2.x + vec1.y * vec2.y;
        }

        static float Cross(Vec2 vec1, Vec2 vec2) {
            return vec1.x * vec2.y - vec1.y * vec2.x;
        }

        Vec2 Normalize() {
            float m = Mag();
            return Vec2(x/m,y/m);
        }

        static Vec2 Zero() {
            return Vec2(0,0);
        }

        void ToString() {
            std::cout << "Vec2 - x: " << x << " y: " << y << std::endl;
        }
};

struct Vec3 {
    public:
        float x;
        float y;
        float z;

        Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
        Vec3(Vec2 vec2) : x(vec2.x), y(vec2.y), z(0) {}
        Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

        bool operator==(const Vec3 &other) const {
            return x == other.x &&  y == other.y &&  z == other.z;
        }

        Vec3 operator-() const {
            return Vec3(-x, -y, -z);
        }

        Vec3 operator+(const Vec3 &other) const {
            return Vec3(x + other.x, y + other.y, z + other.z);
        }

        Vec3 operator-(const Vec3 &other) const {
            return Vec3(x - other.x, y - other.y, z - other.z);
        }

        Vec3 operator/(const float scalar) const {
            return Vec3(x/scalar, y/scalar, z/scalar);
        }

        Vec3 operator*(const float scalar) const {
            return Vec3(x*scalar, y*scalar, z*scalar);
        }

        static float Dist(Vec3 vec1, Vec3 vec2) {
            return sqrt(pow(vec2.x - vec1.x, 2) + pow(vec2.y - vec1.y, 2) + pow(vec2.z - vec1.z, 2));
        }

        float Mag() {
            return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
        }

        static float Dot(Vec3 vec1, Vec3 vec2) {
            return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
        }

        static Vec3 Cross(Vec3 vec1, Vec3 vec2) {
            return Vec3(vec1.y * vec2.z - vec1.z * vec2.y, -(vec1.x * vec2.z - vec1.z * vec2.x), vec1.x * vec2.y - vec1.y * vec2.x);
        }

        Vec3 Normalize() {
            float m = Mag();
            return Vec3(x/m,y/m,z/m);
        }

        static Vec3 Zero() {
            return Vec3(0,0,0);
        }

        void ToString() {
            std::cout << "Vec3 - x: " << x << " y: " << y << " z: " << z << std::endl;
        }
}; 

#endif