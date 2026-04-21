#ifndef VECTOR_H
#define VECTOR_H

#include "numbers.h"
#include <iostream>
#include <algorithm>

using namespace math;

struct Vec2;
struct Vec3;
struct Vec4;

struct Vec2 {
    public:
        float x, y;
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
        float x, y, z;
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

        Vec3 operator*(const Vec3& other) const {
            return Vec3(x * other.x, y * other.y, z * other.z);
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

        static Vec3 Min(Vec3 vec1, Vec3 vec2) {
            return Vec3(std::min(vec1.x, vec2.x), std::min(vec1.y, vec2.y), std::min(vec1.z, vec2.z));
        }

        static Vec3 Max(Vec3 vec1, Vec3 vec2) {
            return Vec3(std::max(vec1.x, vec2.x), std::max(vec1.y, vec2.y), std::max(vec1.z, vec2.z));
        }

        float GetAxisValue(int axis) {
            return axis == 0 ? x : axis == 1 ? y : z; 
        }

        Vec3 Normalize() {
            float m = Mag();
            return Vec3(x/m,y/m,z/m);
        }

        static int Size() {
            return 3;
        }

        static Vec3 Zero() {
            return Vec3(0.0f,0.0f,0.0f);
        }

        void ToString() {
            std::cout << "Vec3 - x: " << x << " y: " << y << " z: " << z << std::endl;
        }
}; 

struct Vec4 {
    public:
        float x, y, z, w;

        Vec4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
        Vec4(Vec3 vec3, float w = 1.0f) : x(vec3.x), y(vec3.y), z(vec3.z), w(w) {}
        Vec4(float x, float y, float z, float w = 1.0f) : x(x), y(y), z(z), w(w) {}

        bool operator==(const Vec4 &other) const {
            return x == other.x &&  y == other.y &&  z == other.z && w == other.w;
        }

        Vec4 operator-() const {
            return Vec4(-x, -y, -z, -w);
        }

        Vec4 operator+(const Vec4 &other) const {
            return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
        }

        Vec4 operator-(const Vec4 &other) const {
            return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
        }

        Vec4 operator/(const float scalar) const {
            return Vec4(x/scalar, y/scalar, z/scalar);
        }

        Vec4 operator*(float s) const {
            return Vec4(x*s, y*s, z*s);
        }

        Vec4 operator*(const Vec4& other) const {
            return Vec4(x * other.x, y * other.y, z * other.z);
        }

        static float Dist(Vec4 vec1, Vec4 vec2) {
            return sqrt(pow(vec2.x - vec1.x, 2) + pow(vec2.y - vec1.y, 2) + pow(vec2.z - vec1.z, 2));
        }

        float Mag() {
            return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
        }

        static float Dot(Vec4 vec1, Vec4 vec2) {
            return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
        }

        static Vec4 Cross(Vec4 vec1, Vec4 vec2) {
            return Vec4(vec1.y * vec2.z - vec1.z * vec2.y, -(vec1.x * vec2.z - vec1.z * vec2.x), vec1.x * vec2.y - vec1.y * vec2.x, 0);
        }

        Vec4 Normalize() {
            float m = Mag();
            return Vec4(x/m,y/m,z/m);
        }

        Vec3 toVec3() const {
            if (w != 0) {
                return Vec3(x/w, y/w, z/w);
            } else {
                return Vec3(x, y, z); // for directions
            }
        }

        static Vec4 Zero() {
            return Vec4(0,0,0);
        }

        static int Size() {
            return 4;
        }

        void ToString() {
            std::cout << "Vec4 - x: " << x << " y: " << y << " z: " << z << " w: " << w << std::endl;
        }
}; 

#endif