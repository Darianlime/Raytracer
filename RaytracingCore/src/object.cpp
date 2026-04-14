#include "object.h"

Object::Object(Vec3 pos) : pos(pos), rot(Vec3(0,0,0)), size(Vec3(1,1,1))
{
    SetMatrix(pos, rot, size);
}

Object::Object(Vec3 pos, Vec3 rot, Vec3 size) : pos(pos), rot(rot), size(size)
{
    SetMatrix(pos, rot, size);
}

Object::Object(Vec3 pos, string name) : pos(pos), rot(Vec3(0,0,0)), size(Vec3(1,1,1)), name(name)
{
    SetMatrix(pos, rot, size);
}

Object::Object(Vec3 pos, Vec3 rot, Vec3 size, string name) : pos(pos), rot(rot), size(size), name(name)
{
    SetMatrix(pos, rot, size);
}

void Object::SetMatrix(Vec3 pos, Vec3 rot, Vec3 size)
{
    Matrix4 M_Translate = Matrix4::Translate(pos);
    Matrix4 M_Rot = Matrix4::FromEuler(rot.x, rot.y, rot.z);
    Matrix4 M_Size = Matrix4::Scale(size);

    localToWorld = M_Translate * M_Rot * M_Size;
    worldToLocal = localToWorld.InverseAffine();

    //printf("SetMatrix rot=%f %f %f\n", rot.x, rot.y, rot.z);
    //printf("M = [%f %f %f %f\n     %f %f %f %f\n     %f %f %f %f\n     %f %f %f %f]\n",localToWorld.M[0],localToWorld.M[4],localToWorld.M[8],localToWorld.M[12], localToWorld.M[1],localToWorld.M[5],localToWorld.M[9],localToWorld.M[13], localToWorld.M[2],localToWorld.M[6],localToWorld.M[10],localToWorld.M[14], localToWorld.M[3],localToWorld.M[7],localToWorld.M[11],localToWorld.M[15]);
}

void Object::UpdateTransformation()
{
    SetMatrix(pos, rot * M_PI / 180, size);
}

