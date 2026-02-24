#include "camera.h"

namespace Raytracer {
    Camera::Camera() {}

    Camera::Camera(Vec3 eye, Vec3 viewdir, Vec3 updir, float vfov) 
        : eye(eye), viewdir(viewdir), updir(updir), vfov(vfov) 
    {
        CalcCoords();
    }

    void Camera::CalcCoords() {
        u = Vec3::Cross(viewdir, updir) / Vec3::Mag(Vec3::Cross(viewdir, updir));
        v = Vec3::Cross(u, viewdir) / Vec3::Mag(Vec3::Cross(u, viewdir));
    }
}
