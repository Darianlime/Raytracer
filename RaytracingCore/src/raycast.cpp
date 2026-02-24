#include "raycast.h"

Raycast::Raycast(Vec3 eye) : eye(eye) {}

Vec3 Raycast::GetEye() {
    return eye;
}

Vec3 Raycast::GetRayDir() {
    return raydir;
}

void Raycast::SetRayDir(Vec3 raydir)
{
    this->raydir = raydir;
}

void Raycast::SetRayDirAtPoint(Vec3 point)
{
    this->raydir = (point - eye) / Vec3::Mag(point - eye);
}

void Raycast::SetRayDirAtPoint(Vec3 point, Vec3 intersectedPoint)
{
    this->raydir = (point - intersectedPoint) / Vec3::Mag(point - intersectedPoint);
}

// Shoots a shadow ray from intersected point to light and checks for object intersections
bool Raycast::IsShadow(Light* light, Vec3 intersectedPoint, Shape* intersectedShape, vector<Shape*>& shapes) {
    for (Shape* shape : shapes) {
        if (shape == intersectedShape) continue;
        pair<Vec3, bool> o = shape->CheckIntersection(Ray{intersectedPoint, light->GetLightDir(intersectedPoint)});
        if (o.second) {
            if (!light->CompareDistToLight(intersectedShape->pos, o.first)) {
                return false;
            }
        }
    }
    return true;
}

// Check each object in the screen
// if no object found in front of eye return background color
// otherwise call ShadeRay()
Color Raycast::TraceRay(Vec3 point, Color background, ObjectFactory& factories, pair<Vec3, bool> &intersectedPoint)
{
    SetRayDirAtPoint(point);
    //cout << "tracing: " << objects[0]->GetName() << endl;
    vector<Shape*> shapes = factories.GetFactory<ShapeFactory>().GetObjects();
    //Vec3 intersectedPoint(numeric_limits<float>::infinity(), numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
    Shape* closest; 
    for (Shape* shape : shapes) {
        pair<Vec3, bool> o = shape->CheckIntersection(Ray{eye, raydir});
        if (o.second) {
            if (Vec3::Dist(eye, o.first) < Vec3::Dist(eye, intersectedPoint.first)) {
                closest = shape;
                intersectedPoint.first = o.first;
            }
            intersectedPoint.second = true;
        }
    }
    if (intersectedPoint.second) {
        return ShadeRay(closest, factories.GetMats(), intersectedPoint.first, shapes, factories.GetFactory<LightFactory>().GetObjects());
    }
    return background;
}

// Shades pixel based on blin phong
Color Raycast::ShadeRay(Shape* obj, vector<Material> mats, Vec3 intersectedPoint, vector<Shape*> shapes, vector<Light*> lights) {
    Material mat = mats[obj->mat];
    Vec3 normal = obj->GetNormal(intersectedPoint);
    Vec3 viewDir = (eye - intersectedPoint) / Vec3::Mag(eye - intersectedPoint);
    Vec3 ambient = mat.diffuse.GetVec() * mat.k.x;

    Vec3 summation;

    for (Light* light : lights) {
        Vec3 lightDir = light->GetLightDir(intersectedPoint);
        Vec3 H = (lightDir + viewDir) / Vec3::Mag(lightDir + viewDir);
        Vec3 diffuse = mat.diffuse.GetVec() * mat.k.y * max(0.0f, Vec3::Dot(normal, lightDir));
        Vec3 specular = mat.specular.GetVec() * mat.k.z * pow(max(0.0f, Vec3::Dot(normal, H)), mat.n);
        int shadow = IsShadow(light, intersectedPoint, obj, shapes);
        float d = Vec3::Dist(intersectedPoint, light->pos);
        float attenuation = 1 / (light->consts.x + light->consts.y * d + light->consts.z * pow(d, 2));
        
        summation = summation + (diffuse + specular) * light->intensity * shadow * attenuation;
    }

    return Color(ambient + summation, false);
}