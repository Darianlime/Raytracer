#ifndef MATRIX_H
#define MATRIX_H

#include "numbers.h"
#include <iostream>
#include <array>

using namespace math;

struct Matrix4;

struct Matrix4 {
    public:
        const int N = 4;
        std::array<float, 16> M;

        Matrix4() 
        : M{1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        } {}

        Matrix4(std::array<float, 16> Matrix) : M(Matrix) {}

        Matrix4& operator=(const Matrix4& other) {
            if (this != &other) {
                M = other.M;
            }
            return *this;
        }
        // bool operator==(const Vec3 &other) const {
        //     return x == other.x &&  y == other.y &&  z == other.z;
        // }

        // Matrix4 operator-() const {
        //     return Matrix4(-x, -y, -z);
        // }



        Matrix4 operator+(const Matrix4 &other) const {
            Matrix4 mat4{};
            for (int i = 0; i < 16; i++) {
                mat4.M[i] = M[i] + other.M[i];
            }
            return mat4;
        }

        Matrix4 operator-(const Matrix4 &other) const {
            Matrix4 mat4{};
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
            Matrix4 mat4{};
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

        Vec4 operator*(const Vec4& v) const {
            return Vec4(
                M[0]*v.x + M[4]*v.y + M[8]*v.z + M[12]*v.w,
                M[1]*v.x + M[5]*v.y + M[9]*v.z + M[13]*v.w,
                M[2]*v.x + M[6]*v.y + M[10]*v.z + M[14]*v.w,
                M[3]*v.x + M[7]*v.y + M[11]*v.z + M[15]*v.w
            );
        }

        static Matrix4 Translate(const Vec3& t) {
            return Matrix4({
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                t.x, t.y, t.z, 1
            });
        }

        static Matrix4 FromEuler(float pitch, float yaw, float roll) {
            float pCos = cos((double)pitch);
            float yCos = cos((double)yaw);
            float rCos = cos((double)roll);
            float pSin = sin((double)pitch);
            float ySin = sin((double)yaw);
            float rSin = sin((double)roll);

            Matrix4 Rx({
                1, 0, 0, 0,
                0, pCos, -pSin, 0,
                0, pSin, pCos, 0,
                0, 0, 0, 1
            });

            Matrix4 Ry({
                yCos, 0, ySin, 0,
                0, 1, 0, 0,
                -ySin,0, yCos, 0,
                0, 0, 0, 1
            });

            Matrix4 Rz({
                rCos, -rSin,0,0,
                rSin, rCos, 0,0,
                0,0,1,0,
                0,0,0,1
            });

            return Ry * Rx * Rz;
        }

        static Matrix4 Scale(const Vec3& t) {
            return Matrix4({
                t.x, 0, 0, 0,
                0, t.y, 0, 0,
                0, 0, t.z, 0,
                0, 0, 0, 1
            });
        }

        Matrix4 InverseAffine() const {
            // Extract 3x3 upper-left matrix (rotation + scale)
            float A[3][3] = {
                { M[0], M[4], M[8] },
                { M[1], M[5], M[9] },
                { M[2], M[6], M[10] }
            };

            // Compute determinant of 3x3
            float det = A[0][0]*(A[1][1]*A[2][2] - A[1][2]*A[2][1])
                    - A[0][1]*(A[1][0]*A[2][2] - A[1][2]*A[2][0])
                    + A[0][2]*(A[1][0]*A[2][1] - A[1][1]*A[2][0]);

            if (fabs(det) < 1e-8f) {
                return Matrix4();
            }

            float invDet = 1.0f / det;

            // Compute inverse of 3x3
            float A_inv[3][3];
            A_inv[0][0] =  (A[1][1]*A[2][2] - A[1][2]*A[2][1]) * invDet;
            A_inv[0][1] = -(A[0][1]*A[2][2] - A[0][2]*A[2][1]) * invDet;
            A_inv[0][2] =  (A[0][1]*A[1][2] - A[0][2]*A[1][1]) * invDet;

            A_inv[1][0] = -(A[1][0]*A[2][2] - A[1][2]*A[2][0]) * invDet;
            A_inv[1][1] =  (A[0][0]*A[2][2] - A[0][2]*A[2][0]) * invDet;
            A_inv[1][2] = -(A[0][0]*A[1][2] - A[0][2]*A[1][0]) * invDet;

            A_inv[2][0] =  (A[1][0]*A[2][1] - A[1][1]*A[2][0]) * invDet;
            A_inv[2][1] = -(A[0][0]*A[2][1] - A[0][1]*A[2][0]) * invDet;
            A_inv[2][2] =  (A[0][0]*A[1][1] - A[0][1]*A[1][0]) * invDet;

            // Extract translation
            Vec3 T(M[12], M[13], M[14]);

            // Compute inverse translation
            Vec3 T_inv(
                -(A_inv[0][0]*T.x + A_inv[0][1]*T.y + A_inv[0][2]*T.z),
                -(A_inv[1][0]*T.x + A_inv[1][1]*T.y + A_inv[1][2]*T.z),
                -(A_inv[2][0]*T.x + A_inv[2][1]*T.y + A_inv[2][2]*T.z)
            );

            return Matrix4({
                A_inv[0][0], A_inv[1][0], A_inv[2][0], 0,
                A_inv[0][1], A_inv[1][1], A_inv[2][1], 0,
                A_inv[0][2], A_inv[1][2], A_inv[2][2], 0,
                T_inv.x,     T_inv.y,     T_inv.z,     1
            });
        }

        Matrix4 Transpose() const {
            Matrix4 result{};
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    result.M[i * N + j] = M[j * N + i];
                }
            }
            return result;
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