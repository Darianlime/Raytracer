#include "raycast.h"
#include <limits> 
using std::numeric_limits;

namespace Raytracer {
    Raycast::Raycast(Vec3 eye, const ObjectFactory &objectFactory, const int SHADE_DEPTH) : eye(eye), objectFactory(objectFactory), SHADE_DEPTH(SHADE_DEPTH) {}

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

    RayHit Raycast::GetRayHit(Ray ray, Model* currentModelHit, int triangleHitIndex) {
        vector<unique_ptr<Model>>& models = objectFactory.GetFactory<ModelFactory>().GetObjects();
        Model* closest = nullptr; 
        float closestDist = numeric_limits<float>::infinity();
        Vec3 closestIntersection(numeric_limits<float>::infinity(), numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
        float closestEntryT{}, closestExitT{};
        int closestTriangleHit{};
        for (unique_ptr<Model>& model : models) {
            if (currentModelHit == model.get() && triangleHitIndex == -1) continue;
            HitRecord rec{};
            rec.triangleHitIndex = triangleHitIndex;
            if (model->CheckIntersection(ray, rec)) {
                float dist = Vec3::Dist(ray.origin, rec.intersection);
                const float EPSILON = 1e-4f;
                if (dist > EPSILON && dist < closestDist) {
                    closest = model.get();
                    closestEntryT = rec.entryIntersection;
                    closestExitT = rec.exitIntersection;
                    closestIntersection = rec.intersection;
                    closestTriangleHit = rec.triangleHitIndex;
                    closestDist = dist;
                }
            }
        }
        if (closest) {
            Material mat = objectFactory.GetMatIndex(closest->mat);
            if (closest->tex > -1 && closest->tex < objectFactory.GetTexSize() && objectFactory.GetTexSize() > 0) {
                Vec2 texUV = closest->GetTexUV(closestIntersection);
                mat.diffuse = objectFactory.GetTexIndex(closest->tex).GetPixel(texUV.x, texUV.y);
            }
            return RayHit{true, closest, mat, closestIntersection, (ray.origin - closestIntersection).Normalize(), closest->GetNormal(closestIntersection, ray.raydir, closestTriangleHit), closestExitT - closestEntryT, closestTriangleHit };
        }
        return RayHit{false, nullptr, Material(), Vec3(0,0,0), Vec3(0,0,0), Vec3(0,0,0)};
    }

    // Shoots a shadow ray from intersected point to light and checks for object intersections
    Vec3 Raycast::IsShadow(Light* light, Vec3 intersectedPoint, Model* intersectedModel, int triangleHitIndex) {
        Vec3 S(1.0f,1.0f,1.0f);
        const float EPSILON = 1e-4f;
        Vec3 lightDir = light->GetLightDir(intersectedPoint);
        Vec3 origin = intersectedPoint + lightDir * EPSILON;
        Ray ray{origin, lightDir};
        vector<unique_ptr<Model>>& models = objectFactory.GetFactory<ModelFactory>().GetObjects();
        for (unique_ptr<Model>& model : models) {
            if (model.get() == intersectedModel && triangleHitIndex == -1) continue;
            HitRecord rec{};
            rec.triangleHitIndex = triangleHitIndex;
            if (model->CheckIntersection(ray, rec) && !light->CompareDistToLight(origin, rec.intersection)) {
                Vec3 alpha = objectFactory.GetMatIndex(model->mat).alpha.GetVec();
                
                if (alpha.x >= 1.0f && alpha.y >= 1.0f && alpha.z >= 1.0f) {
                    return Vec3(0.0f, 0.0f, 0.0f);
                }
                // Beers law
                float distance = rec.exitIntersection - rec.entryIntersection;
                S.x *= exp(-alpha.x * distance);
                S.y *= exp(-alpha.y * distance);    
                S.z *= exp(-alpha.z * distance);
            }
        }
        return S;
    }

    // Check each object in the screen
    // if no object found in front of eye return background color
    // otherwise call ShadeRay()
    Color Raycast::TraceRay(Vec3 point, Color background, pair<Vec3, bool> &intersectedPoint)
    {
        RayHit hit = GetRayHit(Ray{eye, CalcRayDirAtPoint(point)}, nullptr, -1);
        if (hit) {
            intersectedPoint.first = hit.intersectedPoint;
            intersectedPoint.second = hit.hit;
            return ShadeRay(hit, background, SHADE_DEPTH, 1.0f);
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
        Vec3 viewDir = (eye - intersectedPoint).Normalize();

        Vec3 summation(0, 0, 0);

        for (unique_ptr<Light>& light : lights) {
            Vec3 lightDir = light->GetLightDir(intersectedPoint);
            // printf("normal: %f %f %f\n", normal.x, normal.y, normal.z);
            // printf("lightDir: %f %f %f\n", lightDir.x, lightDir.y, lightDir.z);
            // printf("dot: %f\n", Vec3::Dot(normal, lightDir));
            Vec3 halfway = (lightDir + hit.viewDir).Normalize();
            Vec3 diffuse = mat.diffuse.GetVec() * mat.k.y * std::max(0.0f, Vec3::Dot(hit.normal, lightDir));
            Vec3 specular = mat.specular.GetVec() * mat.k.z * pow(std::max(0.0f, Vec3::Dot(hit.normal, halfway)), mat.n);

            
            Vec3 shadow = IsShadow(light.get(), intersectedPoint, hit.model, hit.triangleHitIndex);
            float d = Vec3::Dist(intersectedPoint, light->pos);
            float attenuation = 1 / (light->consts.x + light->consts.y * d + light->consts.z * pow(d, 2));

            summation = summation + (diffuse + specular) * light->intensity * shadow * attenuation;
        }

        Vec3 ambient = mat.diffuse.GetVec() * mat.k.x;
        Vec3 surfaceColor = ambient + summation;

        Vec3 reflectionColor(0,0,0);
        if (mat.k.z > 0.1f && depth > 0) {
            Vec3 I = -hit.viewDir; 
            Vec3 R = (I - hit.normal * 2.0f * Vec3::Dot(I, hit.normal)).Normalize();
            const float EPSILON = 1e-4f;
            Vec3 origin = intersectedPoint + hit.normal * EPSILON; // offset outside surface

            RayHit reflectionHit = GetRayHit(Ray{origin, R}, hit.model, hit.triangleHitIndex); 
            reflectionColor = ShadeRay(reflectionHit, background, depth-1, currentIOR).GetVec();
        }

        Vec3 refractionColor(0,0,0);
        float transparency = (mat.alpha.r + mat.alpha.g + mat.alpha.b) / 3.0f;
        if (transparency < 0.99f && depth > 0) {
            Vec3 I = -hit.viewDir;
            bool entering = Vec3::Dot(hit.normal, I) < 0;
            Vec3 n = hit.normal;
            float nextIOR = mat.refractionIndex;

            if (!entering) {
                n = -hit.normal; // flip normal if exiting
                nextIOR = 1.0f;  // air
            }

            float eta = currentIOR / nextIOR;
            float cosI = Vec3::Dot(I, n);
            float sinT2 = (eta * eta) * (1 - (cosI * cosI));

            if (sinT2 <= 1.0f) { // no total internal reflection
                Vec3 T = (I * eta - n * (eta * cosI + sqrt(1 - sinT2))).Normalize();
                //Vec3 T = (-n * sqrt(sinT2) + (n * cosI - I) * eta).Normalize();
                const float EPSILON = 1e-4f;
                Vec3 origin = intersectedPoint + T * EPSILON;
                Model* skipModel = entering ? nullptr : hit.model;
                RayHit refractionHit = GetRayHit(Ray{origin, T}, skipModel, hit.triangleHitIndex);
                refractionColor = ShadeRay(refractionHit, background, depth-2, nextIOR).GetVec();
                Vec3 alpha = objectFactory.GetMatIndex(hit.model->mat).alpha.GetVec();
                refractionColor.x *= exp(-alpha.x * refractionHit.t);
                refractionColor.y *= exp(-alpha.y * refractionHit.t);
                refractionColor.z *= exp(-alpha.z * refractionHit.t);
            } else {
                refractionColor = reflectionColor;
            }
        }

        float f0 = pow((mat.refractionIndex - 1)/(mat.refractionIndex + 1), 2);
        float cosTheta = fabs(Vec3::Dot(hit.normal, -hit.viewDir));
        float fresnelR = f0 + (1 - f0) * pow(1 - cosTheta, 5);
        Vec3 finalColor =  surfaceColor + reflectionColor * fresnelR + refractionColor * (1 - fresnelR); 
        return Color(finalColor, false);
    }
}

