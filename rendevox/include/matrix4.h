typedef struct {
    float m[4][4];
} matrix4;

vector3 matrix4MultiplyVector3(matrix4 *m, vector3 *i);

matrix4 matrix4MakeIdentity();
matrix4 matrix4MakeRotationX(float angleRad);
matrix4 matrix4MakeRotationY(float angleRad);
matrix4 matrix4MakeRotationZ(float angleRad);
matrix4 matrix4MakeTranslation(float x, float y, float z);
matrix4 matrix4MakeProjection(float fovDegrees, float aspectRatio, float near, float far);
matrix4 matrix4MultiplyMatrix4(matrix4 *m1, matrix4 *m2);
matrix4 matrix4PointAt(vector3 *pos, vector3 *target, vector3 *up);
matrix4 matrix4QuickInverse(matrix4 *m);