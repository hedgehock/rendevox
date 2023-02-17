#include <rendevox.h>

Vector3 matrix4MultiplyVector3(matrix4 *m, Vector3 *i)
{
    Vector3 tempVector;
    tempVector.x = i->x * m->m[0][0] + i->y * m->m[1][0] + i->z * m->m[2][0] + i->w * m->m[3][0];
    tempVector.y = i->x * m->m[0][1] + i->y * m->m[1][1] + i->z * m->m[2][1] + i->w * m->m[3][1];
    tempVector.z = i->x * m->m[0][2] + i->y * m->m[1][2] + i->z * m->m[2][2] + i->w * m->m[3][2];
    tempVector.w = i->x * m->m[0][3] + i->y * m->m[1][3] + i->z * m->m[2][3] + i->w * m->m[3][3];
    return tempVector;
}

Vector3 Vector3Add(Vector3 *v1, Vector3 *v2)
{
    return (Vector3){v1->x + v2->x, v1->y + v2->y, v1->z + v2->z };
}

Vector3 Vector3Sub(Vector3 *v1, Vector3 *v2)
{
    return (Vector3){v1->x - v2->x, v1->y - v2->y, v1->z - v2->z };
}

Vector3 Vector3Mul(Vector3 *v1, float amount)
{
    return (Vector3){v1->x * amount, v1->y * amount, v1->z * amount };
}

Vector3 Vector3Div(Vector3 *v1, float amount)
{
    return (Vector3){v1->x / amount, v1->y / amount, v1->z / amount };
}

float Vector3DotProduct(Vector3 *v1, Vector3 *v2)
{
    return v1->x*v2->x + v1->y*v2->y + v1->z * v2->z;
}

float Vector3Length(Vector3 *v)
{
    return sqrtf(Vector3DotProduct(v, v));
}

Vector3 Vector3Normalise(Vector3 *v)
{
    float length = Vector3Length(v);
    return (Vector3){v->x / length, v->y / length, v->z / length };
}

Vector3 Vector3CrossProduct(Vector3 *v1, Vector3 *v2)
{
    Vector3 tempVector;
    tempVector.x = v1->y * v2->z - v1->z * v2->y;
    tempVector.y = v1->z * v2->x - v1->x * v2->z;
    tempVector.z = v1->x * v2->y - v1->y * v2->x;
    return tempVector;
}

Vector3 Vector3IntersectPlane(Vector3 *planeP, Vector3 *planeN, Vector3 *lineStart, Vector3 *lineEnd)
{
    *planeN = Vector3Normalise(planeN);
    float planeD = -Vector3DotProduct(planeN, planeP);
    float ad = Vector3DotProduct(lineStart, planeN);
    float bd = Vector3DotProduct(lineEnd, planeN);
    float t = (-planeD - ad) / (bd - ad);
    Vector3 lineStartToEnd = Vector3Sub(lineEnd, lineStart);
    Vector3 lineToIntersect = Vector3Mul(&lineStartToEnd, t);
    return Vector3Add(lineStart, &lineToIntersect);
}
