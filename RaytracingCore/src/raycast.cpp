#include "raycast.h"
#include <limits> 
using std::numeric_limits;

namespace Raytracer {
    Raycast::Raycast(Vec3 eye, const ObjectFactory &objectFactory) : eye(eye), objectFactory(objectFactory) {}

    Vec3 Raycast::GetEye()
    {
        return eye;
    }

    void Raycast::SetEye(Vec3 eye)
    {
        this->eye = eye;
    }

    Vec3 Raycast::CalcRayDirAtPoint(Vec3 point) const
    {
        return (point - eye).Normalize();
    }

    Vec3 Raycast::CalcRayDirAtPoint(Vec3 point, Vec3 intersectedPoint) const
    {
        return (point - intersectedPoint).Normalize();
    }

    RayHit Raycast::GetRayHit(Ray ray) {
        vector<unique_ptr<Mesh>>& meshs = objectFactory.GetFactory<MeshFactory>().GetObjects();
        Mesh* closest = nullptr; 
        pair<Vec3, bool> intersection(Vec3(numeric_limits<float>::infinity(), numeric_limits<float>::infinity(), numeric_limits<float>::infinity()), false);
        for (unique_ptr<Mesh>& mesh : meshs) {
            pair<Vec3, bool> o = mesh->CheckIntersection(ray);
            if (o.second) {
                if (Vec3::Dist(ray.origin, o.first) < Vec3::Dist(ray.origin, intersection.first)) {
                    closest = mesh.get();
                    intersection.first = o.first;
                    intersection.second = true;
                }
            }
        }
        if (closest && intersection.second) {
            Material mat = objectFactory.GetMatIndex(closest->mat);
            if (closest->tex > -1 && closest->tex < objectFactory.GetTexSize() && objectFactory.GetTexSize() > 0) {
                pair<float, float> texUV = closest->GetTexUV(intersection.first);
                mat.diffuse = objectFactory.GetTexIndex(closest->tex).GetPixel(texUV.first, texUV.second);
            }
            return RayHit{true, closest, mat, intersection.first};
        }
        return RayHit{false, closest, Material(), Vec3(0,0,0)};
    }


    // Shoots a shadow ray from intersected point to light and checks for object intersections
    bool Raycast::IsShadow(Light* light, Vec3 intersectedPoint, Mesh* intersectedShape) {
        vector<unique_ptr<Mesh>>& meshs = objectFactory.GetFactory<MeshFactory>().GetObjects();
        for (unique_ptr<Mesh>& mesh : meshs) {
            if (mesh.get() == intersectedShape) continue;
            pair<Vec3, bool> o = mesh->CheckIntersection(Ray{intersectedPoint, light->GetLightDir(intersectedPoint)});
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
    Color Raycast::TraceRay(Vec3 point, Color background, pair<Vec3, bool> &intersectedPoint)
    {
        RayHit hit = GetRayHit(Ray{eye, CalcRayDirAtPoint(point)});
        if (hit) {
            intersectedPoint.first = hit.intersectedPoint;
            intersectedPoint.second = hit.hit;
            return ShadeRay(hit, background, 10);
        }
        return background;
    }

    // Shades pixel based on blin phong
    Color Raycast::ShadeRay(RayHit hit, Color background, int depth) {
        if (!hit) {
            return background;
        }
        vector<unique_ptr<Light>>& lights = objectFactory.GetFactory<LightFactory>().GetObjects();
        Material mat = hit.mat;
        Vec3 intersectedPoint = hit.intersectedPoint;
        Vec3 normal = hit.mesh->GetNormal(hit.intersectedPoint).Normalize();
        Vec3 ambient = mat.diffuse.GetVec() * mat.k.x;
        Vec3 viewDir = (eye - intersectedPoint).Normalize();
    
        Vec3 summation(0, 0, 0);

        for (unique_ptr<Light>& light : lights) {
            Vec3 lightDir = light->GetLightDir(intersectedPoint);
            Vec3 halfway = (lightDir + viewDir).Normalize();
            Vec3 diffuse = mat.diffuse.GetVec() * mat.k.y * std::max(0.0f, Vec3::Dot(normal, lightDir));
            Vec3 specular = mat.specular.GetVec() * mat.k.z * pow(std::max(0.0f, Vec3::Dot(normal, halfway)), mat.n);
            int shadow = IsShadow(light.get(), intersectedPoint, hit.mesh);
            float d = Vec3::Dist(intersectedPoint, light->pos);
            float attenuation = 1 / (light->consts.x + light->consts.y * d + light->consts.z * pow(d, 2));

            summation = summation + (diffuse + specular) * light->intensity * shadow * attenuation;
        }

        // reflective material
        Vec3 reflectionColor{ 0,0,0 };
        float frensnel = pow(((mat.refractionIndex - 1) / (mat.refractionIndex + 1)), 2);
        Vec3 incomingRay = -((intersectedPoint - eye).Normalize());
        float NdotIncomingRay = Vec3::Dot(normal, incomingRay);
        float frensnelR = frensnel + (1 - frensnel) * pow(1 - NdotIncomingRay, 5);
        if (mat.k.z > 0 && depth > 0) {
            Vec3 reflectiveRay = (normal * Vec3::Dot(normal, incomingRay) * 2 - incomingRay).Normalize();
            const float EPSILON = 1e-4f;
            Vec3 origin = intersectedPoint + normal * EPSILON;
            RayHit hit = GetRayHit(Ray{ origin, reflectiveRay });
            reflectionColor = ShadeRay(hit, background, depth - 1).GetVec();
        }

        // Vec3 refractionColor(0,0,0);
        // float eta = 1 / mat.refractionIndex;
        // if (mat.opacity < 1 && depth > 0) {
        //     Vec3 refractionRay = -normal * sqrt(1 - (pow(eta,2) * (1 - pow(NdotIncomingRay,2)))) + ((normal * NdotIncomingRay) - incomingRay) * eta;
        //     const float EPSILON = 1e-4f;
        //     Vec3 origin = intersectedPoint + normal * EPSILON;
        //     RayHit hit = GetRayHit(Ray{origin, refractionRay});
        //     refractionColor = ShadeRay()
        // }
        //return Color(ambient + summation * (1 - frensnelR) + reflectionColor + refractionColor * (1 - frensnelR) * (1 - mat.opacity), false);
        return Color(ambient + summation * (1 - frensnelR) + reflectionColor, false);
    }
}

