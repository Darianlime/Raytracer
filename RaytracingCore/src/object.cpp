#include "object.h"

Object::Object(Vec3 pos) : pos(pos)
{
}

Object::Object(Vec3 pos, Vec3 rot, Vec3 size) : pos(pos), rot(rot), size(size)
{
}

Object::Object(Vec3 pos, string name) : pos(pos), name(name)
{
}

Object::Object(Vec3 pos, Vec3 rot, Vec3 size, string name) : pos(pos), rot(rot), size(size), name(name)
{
}
