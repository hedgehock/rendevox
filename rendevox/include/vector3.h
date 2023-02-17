typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vector3;

Vector3 Vector3Add(Vector3 *v1, Vector3 *v2);
Vector3 Vector3Sub(Vector3 *v1, Vector3 *v2);
Vector3 Vector3Mul(Vector3 *v1, float amount);
Vector3 Vector3Div(Vector3 *v1, float amount);
float Vector3DotProduct(Vector3 *v1, Vector3 *v2);
float Vector3Length(Vector3 *v);
Vector3 Vector3Normalise(Vector3 *v);
Vector3 Vector3CrossProduct(Vector3 *v1, Vector3 *v2);
Vector3 Vector3IntersectPlane(Vector3 *planeP, Vector3 *planeN, Vector3 *lineStart, Vector3 *lineEnd);