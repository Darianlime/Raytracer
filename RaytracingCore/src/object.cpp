#include "object.h"

Object::Object(Vec3 pos) : pos(pos)
{
}

Object::Object(Vec3 pos, string name) : pos(pos), name(name)
{
}