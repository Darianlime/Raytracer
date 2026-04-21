#include "BVH/BoundingBox.h"
#include <numeric>

BoundingBox::BoundingBox() 
    : min(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()),
      max(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity()) {}

Vec3 BoundingBox::CalcCenter() const
{
    return (max + min) / 2.0f;
}

Vec3 BoundingBox::Size() const
{
    return max - CalcCenter(); 
}

Vec3 BoundingBox::Size(Vec3 center) const
{
    return max - center; 
}

void BoundingBox::GrowBox(Vec3& vertex)
{
    min = Vec3::Min(min, vertex);
    max = Vec3::Max(max, vertex);
}

void BoundingBox::GrowBoxTriangle(Triangle& tri)
{
    GrowBox(*tri.GetIndices().v1);
    GrowBox(*tri.GetIndices().v2);
    GrowBox(*tri.GetIndices().v3);
}

void BoundingBox::ToString()
{
    std::cout << "min: ";
    min.ToString();
    std::cout << "max: ";
    max.ToString();
}