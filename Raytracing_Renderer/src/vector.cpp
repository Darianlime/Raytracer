#include "vector.h"

Vec3::Vec3() : x(0.0f), y(0.0f), z(0.0f) {}

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3 Vec3::operator+(const Vec3& other) const
{
    return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3 &other) const
{
    return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator/(const float scalar) const
{
    return Vec3(x/scalar, y/scalar, z/scalar);
}

Vec3 Vec3::operator*(const float scalar) const
{
    return Vec3(x*scalar, y*scalar, z*scalar);
}

float Vec3::Mag(Vec3 vec)
{
    return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}

float Vec3::Dot(Vec3 vec1, Vec3 vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

Vec3 Vec3::Cross(Vec3 vec1, Vec3 vec2)
{
    float x = vec1.y * vec2.z - vec1.z * vec2.y;
    float y = -(vec1.x * vec2.z - vec1.z * vec2.x);
    float z = vec1.x * vec2.y - vec1.y * vec2.x;
    return Vec3(x, y, z);
}

void Vec3::ToString()
{
    cout << "Vec x: " << x << " y: " << y << " z: " << z << endl;
}
