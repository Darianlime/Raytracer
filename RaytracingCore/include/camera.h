#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"

class Camera {
    private:
        Vec3 eye;
        Vec3 viewdir;   
        Vec3 updir;
        float vfov;

        Vec3 u;
        Vec3 v;
    public:
        Camera();
        Camera(Vec3 eye, Vec3 viewdir, Vec3 updir, float vfov);
        void CalcCoords();

        Vec3 GetU() const { return u; }
        Vec3 GetV() const { return v; }

        Vec3 GetViewDir() const { return viewdir; }
        Vec3 GetEye() const { return eye; }
        Vec3 GetUp() const { return updir; }
        float GetVFov() const { return vfov; }
}; 

#endif