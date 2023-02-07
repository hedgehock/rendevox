typedef struct {
    float x;
    float y;
    float z;
    float w;
} vector3;

vector3 vector3Add(vector3 *v1, vector3 *v2);
vector3 vector3Sub(vector3 *v1, vector3 *v2);
vector3 vector3Mul(vector3 *v1, float amount);
vector3 vector3Div(vector3 *v1, float amount);
float vector3DotProduct(vector3 *v1, vector3 *v2);
float vector3Length(vector3 *v);
vector3 vector3Normalise(vector3 *v);
vector3 vector3CrossProduct(vector3 *v1, vector3 *v2);
vector3 vector3IntersectPlane(vector3 *planeP, vector3 *planeN, vector3 *lineStart, vector3 *lineEnd);