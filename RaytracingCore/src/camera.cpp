#include "camera.h"

namespace Raytracer {
    Camera::Camera() : eye(Vec3(0.0f,0.0f,0.0f)), viewdir(Vec3(0.0f,0.0f,-1.0f)), updir(Vec3(0.0f,1.0f,0.0f)), vfov(45.0f) {
        CalcCoords();
    }

    Camera::Camera(Vec3 eye, Vec3 viewdir, Vec3 updir, float vfov) 
        : eye(eye), viewdir(viewdir), updir(updir), vfov(vfov) 
    {
        CalcCoords();
    }

    void Camera::CalcCoords() {
        u = Vec3::Cross(viewdir, updir) / Vec3::Cross(viewdir, updir).Mag();
        v = Vec3::Cross(u, viewdir) / Vec3::Cross(u, viewdir).Mag();
    }
}
