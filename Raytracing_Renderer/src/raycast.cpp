#include "raycast.h"

Raycast::Raycast(Vec3 eye) : origin(eye) {}

Vec3 Raycast::GetOrigin() {
    return origin;
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
    this->raydir = (point - origin) / Vec3::Mag(point - origin);
}

Vec3 Raycast::GetRay(float t)
{
    return origin + raydir * t;
}

// Check each object in the screen
// if no object found in front of eye return background color
// otherwise call ShadeRay()
Color Raycast::TraceRay(Vec3 point, Color background, vector<Object*> objects, vector<Light*> lights)
{
    SetRayDirAtPoint(point);
    //cout << "tracing: " << objects[0]->GetName() << endl;
    Object* closest; 
    Vec3 distance(numeric_limits<float>::infinity(), numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
    bool isIntersected = false;
    for (Object* obj : objects) {
        pair<Vec3, bool> o = obj->CheckIntersection(Ray{origin, raydir});
        if (o.second) {
            if (Vec3::Dist(origin, o.first) < Vec3::Dist(origin, distance)) {
                closest = obj;
                distance = o.first;
            }
            isIntersected = true;
        }
    }
    if (isIntersected) {
        return ShadeRay(closest, distance, lights);
    }
    return background;
}

Color Raycast::ShadeRay(Object* obj, Vec3 intersectedPoint, vector<Light*> lights) {
    Material mat = obj->mat;
    Vec3 normal = obj->GetNormal(intersectedPoint);
    Vec3 lightDir = lights[0]->GetLightDir(intersectedPoint);
    Vec3 H = (lightDir + raydir) / Vec3::Mag(lightDir + raydir);
    Vec3 ambient = mat.diffuse.GetVec() * mat.k.x;
    Vec3 diffuse = mat.diffuse.GetVec() * mat.k.y * max(0.0f, Vec3::Dot(normal, lightDir));
    Vec3 specular = mat.specular.GetVec() * mat.k.z * pow(max(0.0f, Vec3::Dot(normal, H)), mat.n);
    return Color(ambient + diffuse + specular, true);
}