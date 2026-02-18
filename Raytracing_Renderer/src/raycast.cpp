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

bool Raycast::IsShadow(Light* light, Vec3 intersectedPoint, Shape* intersectedShape, vector<Shape*>& shapes) {
    SetRayDirAtPoint(light->pos, light->GetLightDir(intersectedPoint));
    for (Shape* shape : shapes) {
        if (shape == intersectedShape) continue;
        pair<Vec3, bool> o = shape->CheckIntersection(Ray{intersectedPoint, raydir});
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
Color Raycast::TraceRay(Vec3 point, Color background, ObjectFactory& factories)
{
    SetRayDirAtPoint(point);
    //cout << "tracing: " << objects[0]->GetName() << endl;
    vector<Shape*> shapes = factories.GetFactory<ShapeFactory>().GetObjects();
    Shape* closest; 
    Vec3 intersectedPoint(numeric_limits<float>::infinity(), numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
    bool isIntersected = false;
    for (Shape* shape : shapes) {
        pair<Vec3, bool> o = shape->CheckIntersection(Ray{eye, raydir});
        if (o.second) {
            if (Vec3::Dist(eye, o.first) < Vec3::Dist(eye, intersectedPoint)) {
                closest = shape;
                intersectedPoint = o.first;
            }
            isIntersected = true;
        }
    }
    if (isIntersected) {
        return ShadeRay(closest, factories.GetMats(), intersectedPoint, shapes, factories.GetFactory<LightFactory>().GetObjects());
    }
    return background;
}

Color Raycast::ShadeRay(Shape* obj, vector<Material> mats, Vec3 intersectedPoint, vector<Shape*> shapes, vector<Light*> lights) {
    Material mat = mats[obj->mat];
    Vec3 normal = obj->GetNormal(intersectedPoint);
    Vec3 lightDir = lights[0]->GetLightDir(intersectedPoint);
    Vec3 viewDir = (eye - intersectedPoint) / Vec3::Mag(eye - intersectedPoint);
    Vec3 H = (lightDir + viewDir) / Vec3::Mag(lightDir + viewDir);
    Vec3 ambient = mat.diffuse.GetVec() * mat.k.x;
    Vec3 diffuse = mat.diffuse.GetVec() * mat.k.y * max(0.0f, Vec3::Dot(normal, lightDir));
    Vec3 specular = mat.specular.GetVec() * mat.k.z * pow(max(0.0f, Vec3::Dot(normal, H)), mat.n);
    int shadow = IsShadow(lights[0], intersectedPoint, obj, shapes);
    return Color(ambient + ((diffuse + specular) * lights[0]->intensity * shadow), true);
}