#include "BVH/BoundingBox.h"

BoundingBox::BoundingBox() {}

Vec3 BoundingBox::CalcCenter()
{
    center = (max + min) / 2.0f;
    return center;
}

Vec3 BoundingBox::Size()
{
    return max - CalcCenter(); 
}

Vec3 BoundingBox::Size(Vec3 center)
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