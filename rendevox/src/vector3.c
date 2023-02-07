#include <rendevox.h>

vector3 matrix4MultiplyVector3(matrix4 *m, vector3 *i)
{
    vector3 tempVector;
    tempVector.x = i->x * m->m[0][0] + i->y * m->m[1][0] + i->z * m->m[2][0] + i->w * m->m[3][0];
    tempVector.y = i->x * m->m[0][1] + i->y * m->m[1][1] + i->z * m->m[2][1] + i->w * m->m[3][1];
    tempVector.z = i->x * m->m[0][2] + i->y * m->m[1][2] + i->z * m->m[2][2] + i->w * m->m[3][2];
    tempVector.w = i->x * m->m[0][3] + i->y * m->m[1][3] + i->z * m->m[2][3] + i->w * m->m[3][3];
    return tempVector;
}

vector3 vector3Add(vector3 *v1, vector3 *v2)
{
    return (vector3){ v1->x + v2->x, v1->y + v2->y, v1->z + v2->z };
}

vector3 vector3Sub(vector3 *v1, vector3 *v2)
{
    return (vector3){ v1->x - v2->x, v1->y - v2->y, v1->z - v2->z };
}

vector3 vector3Mul(vector3 *v1, float amount)
{
    return (vector3){ v1->x * amount, v1->y * amount, v1->z * amount };
}

vector3 vector3Div(vector3 *v1, float amount)
{
    return (vector3){ v1->x / amount, v1->y / amount, v1->z / amount };
}

float vector3DotProduct(vector3 *v1, vector3 *v2)
{
    return v1->x*v2->x + v1->y*v2->y + v1->z * v2->z;
}

float vector3Length(vector3 *v)
{
    return sqrtf(vector3DotProduct(v, v));
}

vector3 vector3Normalise(vector3 *v)
{
    float length = vector3Length(v);
    return (vector3){ v->x / length, v->y / length, v->z / length };
}

vector3 vector3CrossProduct(vector3 *v1, vector3 *v2)
{
    vector3 tempVector;
    tempVector.x = v1->y * v2->z - v1->z * v2->y;
    tempVector.y = v1->z * v2->x - v1->x * v2->z;
    tempVector.z = v1->x * v2->y - v1->y * v2->x;
    return tempVector;
}

vector3 vector3IntersectPlane(vector3 *planeP, vector3 *planeN, vector3 *lineStart, vector3 *lineEnd)
{
    *planeN = vector3Normalise(planeN);
    float planeD = -vector3DotProduct(planeN, planeP);
    float ad = vector3DotProduct(lineStart, planeN);
    float bd = vector3DotProduct(lineEnd, planeN);
    float t = (-planeD - ad) / (bd - ad);
    vector3 lineStartToEnd = vector3Sub(lineEnd, lineStart);
    vector3 lineToIntersect = vector3Mul(&lineStartToEnd, t);
    return vector3Add(lineStart, &lineToIntersect);
}
