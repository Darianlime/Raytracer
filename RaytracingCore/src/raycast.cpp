#include "raycast.h"

namespace Raytracer {
    Raycast::Raycast(Vec3 eye) : eye(eye) {}

    Vec3 Raycast::GetEye() {
        return eye;
    }

    void Raycast::SetEye(Vec3 eye)
    {
        this->eye = eye;
    }

    Vec3 Raycast::CalcRayDirAtPoint(Vec3 point) const
    {
        return (point - eye) / Vec3::Mag(point - eye);
    }

    Vec3 Raycast::CalcRayDirAtPoint(Vec3 point, Vec3 intersectedPoint) const
    {
        return (point - intersectedPoint) / Vec3::Mag(point - intersectedPoint);
    }

    // Shoots a shadow ray from intersected point to light and checks for object intersections
    bool Raycast::IsShadow(Light* light, Vec3 intersectedPoint, Mesh* intersectedShape, vector<Mesh*>& shapes) {
        for (Mesh* shape : shapes) {
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
        //SetRayDirAtPoint(point);
        //cout << "tracing: " << objects[0]->GetName() << endl;
        vector<Mesh*> shapes = factories.GetFactory<MeshFactory>().GetObjects();
        //Vec3 intersectedPoint(numeric_limits<float>::infinity(), numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
        Mesh* closest = nullptr; 
        for (Mesh* shape : shapes) {
            pair<Vec3, bool> o = shape->CheckIntersection(Ray{eye, CalcRayDirAtPoint(point)});
            if (o.second) {
                if (Vec3::Dist(eye, o.first) < Vec3::Dist(eye, intersectedPoint.first)) {
                    closest = shape;
                    intersectedPoint.first = o.first;
                    intersectedPoint.second = true;
                }
            }
        }
        if (closest && intersectedPoint.second) {
            return ShadeRay(closest, factories.GetMatIndex(closest->mat), intersectedPoint.first, shapes, factories.GetFactory<LightFactory>().GetObjects());
        }
        return background;
    }

    // Shades pixel based on blin phong
    Color Raycast::ShadeRay(Mesh* obj, Material mat, Vec3 intersectedPoint, vector<Mesh*> shapes, vector<Light*> lights) {
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
}