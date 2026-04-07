#ifndef MATRIX_H
#define MATRIX_H

#include "numbers.h"
#include <iostream>
#include <array>

using namespace math;

struct Matrix4;

struct Matrix4 {
    public:
        std::array<float, 16> M;

        Matrix4() 
        : M{1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        } {}

        Matrix4(std::array<float, 16> Matrix) : M(Matrix) {}
        // bool operator==(const Vec3 &other) const {
        //     return x == other.x &&  y == other.y &&  z == other.z;
        // }

        // Matrix4 operator-() const {
        //     return Matrix4(-x, -y, -z);
        // }

        Matrix4 operator+(const Matrix4 &other) const {
            Matrix4 mat4;
            for (int i = 0; i < 16; i++) {
                mat4.M[i] = M[i] + other.M[i];
            }
            return mat4;
        }

        Matrix4 operator-(const Matrix4 &other) const {
            Matrix4 mat4;
            for (int i = 0; i < 16; i++) {
                mat4.M[i] = M[i] - other.M[i];
            }
            return mat4;
        }

        // Vec3 operator/(const float scalar) const {
        //     return Vec3(x/scalar, y/scalar, z/scalar);
        // }

        // Vec3 operator*(const float scalar) const {
        //     return Vec3(x*scalar, y*scalar, z*scalar);
        // }

        Matrix4 operator*(const Matrix4& other) const {
            Matrix4 mat4;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    mat4.M[i + j * 4] = 0;
                    for (int k = 0; k < 4; k++) {
                        mat4.M[i + j * 4] += M[i + k * 4] * other.M[k + j * 4];
                    }
                }
            }
            return mat4;
        }

        // static float Dist(Vec3 vec1, Vec3 vec2) {
        //     return sqrt(pow(vec2.x - vec1.x, 2) + pow(vec2.y - vec1.y, 2) + pow(vec2.z - vec1.z, 2));
        // }

        // float Mag() {
        //     return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
        // }

        // static float Dot(Vec3 vec1, Vec3 vec2) {
        //     return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
        // }

        // static Vec3 Cross(Vec3 vec1, Vec3 vec2) {
        //     return Vec3(vec1.y * vec2.z - vec1.z * vec2.y, -(vec1.x * vec2.z - vec1.z * vec2.x), vec1.x * vec2.y - vec1.y * vec2.x);
        // }

        // Vec3 Normalize() {
        //     float m = Mag();
        //     return Vec3(x/m,y/m,z/m);
        // }

        static Matrix4 Identity() {
            return Matrix4();
        }

        // void ToString() {
        //     std::cout << "Vec3 - x: " << x << " y: " << y << " z: " << z << std::endl;
        // }
}; 

#endif