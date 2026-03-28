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

    RayHit Raycast::GetRayHit(Ray ray, Mesh* currentMeshHit) {
        vector<unique_ptr<Mesh>>& meshs = objectFactory.GetFactory<MeshFactory>().GetObjects();
        Mesh* closest = nullptr; 
        float closestDist = numeric_limits<float>::infinity();
        pair<Vec3, bool> intersection(Vec3(numeric_limits<float>::infinity(), numeric_limits<float>::infinity(), numeric_limits<float>::infinity()), false);
        for (unique_ptr<Mesh>& mesh : meshs) {
            //if (currentMeshHit == mesh.get()) continue;

            pair<Vec3, bool> o = mesh->CheckIntersection(ray);
            float dist = Vec3::Dist(ray.origin, o.first);
            if (o.second) {
                const float EPSILON = 1e-4f;
                if (dist > EPSILON && dist < closestDist) {
                    closest = mesh.get();
                    intersection.first = o.first;
                    intersection.second = true;
                    closestDist = dist;
                }
            }
        }
        if (closest && intersection.second) {
            Material mat = objectFactory.GetMatIndex(closest->mat);
            if (closest->tex > -1 && closest->tex < objectFactory.GetTexSize() && objectFactory.GetTexSize() > 0) {
                pair<float, float> texUV = closest->GetTexUV(intersection.first);
                mat.diffuse = objectFactory.GetTexIndex(closest->tex).GetPixel(texUV.first, texUV.second);
            }
            return RayHit{true, closest, mat, intersection.first, (ray.origin - intersection.first).Normalize()};
        }
        return RayHit{false, closest, Material(), Vec3(0,0,0), Vec3(0,0,0)};
    }


    // Shoots a shadow ray from intersected point to light and checks for object intersections
    bool Raycast::IsShadow(Light* light, Vec3 intersectedPoint, Mesh* intersectedShape) {
        vector<unique_ptr<Mesh>>& meshs = objectFactory.GetFactory<MeshFactory>().GetObjects();
        for (unique_ptr<Mesh>& mesh : meshs) {
            if (mesh.get() == intersectedShape) continue;
            pair<Vec3, bool> o = mesh->CheckIntersection(Ray{intersectedPoint, light->GetLightDir(intersectedPoint)});
            const float EPSILON = 1e-4f;
            Vec3 origin = intersectedPoint + light->GetLightDir(intersectedPoint) * EPSILON;
            if (o.second && !light->CompareDistToLight(origin, o.first)) {
                return false;
            }
        }
        return true;
    }

    // Check each object in the screen
    // if no object found in front of eye return background color
    // otherwise call ShadeRay()
    Color Raycast::TraceRay(Vec3 point, Color background, pair<Vec3, bool> &intersectedPoint)
    {
        RayHit hit = GetRayHit(Ray{eye, CalcRayDirAtPoint(point)}, nullptr);
        if (hit) {
            intersectedPoint.first = hit.intersectedPoint;
            intersectedPoint.second = hit.hit;
            return ShadeRay(hit, background, 10, 1.0f);
        }
        return background;
    }

    // Shades pixel based on blin phong
    Color Raycast::ShadeRay(RayHit hit, Color background, int depth, float currentIOR) {
        if (depth < 0) return background;
        if (!hit) return background;

        vector<unique_ptr<Light>>& lights = objectFactory.GetFactory<LightFactory>().GetObjects();
        Material mat = hit.mat;
        Vec3 intersectedPoint = hit.intersectedPoint;
        Vec3 normal = hit.mesh->GetNormal(intersectedPoint).Normalize();
        Vec3 viewDir = (eye - intersectedPoint).Normalize();

        // Ambient + direct lighting
        Vec3 ambient = mat.diffuse.GetVec() * mat.k.x;
        Vec3 summation(0, 0, 0);

        for (unique_ptr<Light>& light : lights) {
            Vec3 lightDir = light->GetLightDir(intersectedPoint);
            Vec3 halfway = (lightDir + hit.viewDir).Normalize();
            Vec3 diffuse = mat.diffuse.GetVec() * mat.k.y * std::max(0.0f, Vec3::Dot(normal, lightDir));
            Vec3 specular = mat.specular.GetVec() * mat.k.z * pow(std::max(0.0f, Vec3::Dot(normal, halfway)), mat.n);

            float shadow = IsShadow(light.get(), intersectedPoint, hit.mesh) ? 1.0f : 0.0f;
            float d = Vec3::Dist(intersectedPoint, light->pos);
            float attenuation = 1 / (light->consts.x + light->consts.y * d + light->consts.z * pow(d, 2));

            summation = summation + (diffuse + specular) * light->intensity * shadow * attenuation;
        }

        Vec3 surfaceColor = ambient + summation;

        Vec3 reflectionColor(0,0,0);
        if (mat.k.z > 0.0f && depth > 0) {
            Vec3 I = -hit.viewDir; 
            Vec3 R = (I - normal * 2.0f * Vec3::Dot(I, normal)).Normalize();
            const float EPSILON = 1e-4f;
            Vec3 origin = intersectedPoint + normal * EPSILON; // offset outside surface

            RayHit reflectionHit = GetRayHit(Ray{origin, R}, nullptr); 
            reflectionColor = ShadeRay(reflectionHit, background, depth-1, currentIOR).GetVec();
        }

        // --- Refraction ---
        Vec3 refractionColor(0,0,0);
        if (mat.opacity < 1.0f && depth > 0) {
            Vec3 I = -hit.viewDir;
            bool entering = Vec3::Dot(normal, I) < 0;
            Vec3 n = normal;
            float nextIOR = mat.refractionIndex;

            if (!entering) {
                n = -normal;          // flip normal if exiting
                nextIOR = 1.0f;       // air
            }

            float eta = currentIOR / nextIOR;
            float cosI = Vec3::Dot(I, n);
            float sinT2 = (eta * eta) * (1 - (cosI * cosI));

            if (sinT2 <= 1.0f) { // no total internal reflection
                Vec3 T = (I * eta - n * (eta * cosI + sqrt(1 - sinT2))).Normalize();
                //Vec3 T = (-n * sqrt(sinT2) + (n * cosI - I) * eta).Normalize();
                const float EPSILON = 1e-4f;
                Vec3 origin = intersectedPoint + T * EPSILON;
                //Mesh* skipMesh = entering ? nullptr : hit.mesh;
                RayHit refractionHit = GetRayHit(Ray{origin, T}, nullptr);
                refractionColor = ShadeRay(refractionHit, background, depth-1, nextIOR).GetVec();
            } else {
                refractionColor = reflectionColor;
            }
        }

        float f0 = pow((mat.refractionIndex - 1)/(mat.refractionIndex + 1), 2);
        float cosTheta = fabs(Vec3::Dot(normal, -hit.viewDir));
        float fresnelR = f0 + (1 - f0) * pow(1 - cosTheta, 5);
        
        Vec3 finalColor =  surfaceColor + reflectionColor * fresnelR + refractionColor * (1 - fresnelR) * (1 - mat.opacity); 
        return Color(finalColor, false);
    }
}

