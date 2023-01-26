## Matrix4

### Declaration
```c
typedef struct {
	float m[4][4];
} matrix4;
```

Output matrix
```
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0
```

### Make Identity
```c 
matrix4 matrixMakeIdentity() {
	matrix4 tempMatrix;
	tempMatrix.m[0][0] = 1.0f;
	tempMatrix.m[1][1] = 1.0f;
	tempMatrix.m[2][2] = 1.0f;
	tempMatrix.m[3][3] = 1.0f;
	return tempMatrix;
}
```

Output matrix
```
1 0 0 0
0 1 0 0
0 0 1 0
0 0 0 1
```

### Make rotation X
```c
matrix4 matrixMakeRotationX(float angleRad) {
	matrix4 tempMatrix;
	tempMatrix.m[0][0] = 1.0f;
	tempMatrix.m[1][1] = cosf(angleRad);
	tempMatrix.m[1][2] = sinf(angleRad);
	tempMatrix.m[2][1] = -sinf(angleRad);
	tempMatrix.m[2][2] = cosf(angleRad);
	tempMatrix.m[3][3] = 1.0f;
	
	return tempMatrix;
}
```

Output matrix
```
1 0     0    0 
0 cosf  sinf 0
0 -sinf cosf 0
0 0     0    1
```

### Make rotation Y
```c
matrix4 matrixMakeRotationY(float angleRad) {
	matrix4 tempMatrix;
	tempMatrix.m[0][0] = cosf(angleRad);
	tempMatrix.m[0][2] = sinf(angleRad);
	tempMatrix.m[2][0] = -sinf(angleRad);
	tempMatrix.m[1][1] = 1.0f;
	tempMatrix.m[2][2] = cosf(angleRad);
	tempMatrix.m[3][3] = 1.0f;
	
	return tempMatrix;
}
```

Output matrix
```
cosf  0    sinf 0
0     1    0    0
-sinf 0    cosf 0
0     0    0    1
```

### Make rotation Z
```c
matrix4 matrixMakeRotationZ(float angleRad) {
	matrix4 tempMatrix;
	tempMatrix.m[0][0] = cosf(angleRad);
	tempMatrix.m[0][1] = sinf(angleRad);
	tempMatrix.m[1][0] = -sinf(angleRad);
	tempMatrix.m[1][1] = cosf(angleRad);
	tempMatrix.m[2][2] = 1.0f;
	tempMatrix.m[3][3] = 1.0f;
	
	return tempMatrix;
}
```

Output matrix
```
cosf  sinf 0 0 
-sinf cosf 0 0
0     0    1 0
0     0    0 1
```

### Make translation
```c
matrix4 matrixMakeTranslation(float x, float y, float z) {
    matrix4 tempMatrix;
    tempMatrix.m[0][0] = 1.0f;
    tempMatrix.m[1][1] = 1.0f;
    tempMatrix.m[2][2] = 1.0f;
    tempMatrix.m[3][3] = 1.0f;
    tempMatrix.m[3][0] = x;
    tempMatrix.m[3][1] = y;
    tempMatrix.m[3][2] = z;
    
    return tempMatrix;
}
```

Output matrix
```
1 0 0 0
0 1 0 0
0 0 1 0
x y z 1
```

### Make projection
```c
matrix4 matrixMakeProjection(float fovDegrees, float aspectRatio, float near, float far) {
    float fovRad = 1.0f / tanf(fovDegrees * 0.5f / 180.0f * 3.14159f);
    
    matrix4 tempMatrix;
    tempMatrix.m[0][0] = aspectRatio * fovRad;
    tempMatrix.m[1][1] = fovRad;
    tempMatrix.m[2][2] = far / (far - near);
    tempMatrix.m[3][2] = (-far * near) / (far - near);
    tempMatrix.m[2][3] = 1.0f;
    tempMatrix.m[3][3] = 0.0f;
    
    return tempMatrix;
}
```

Output matrix
```
aspectRatio * fovRad 0      0                            0
0                    fovRad 0                            0
0                    0      far / (far - near)           1
0                    0      (-far * near) / (far - near) 0
```

### Multiply matrix
```c
matrix4 matrixMultiplyMatrix(matrix4 m1, matrix4 m2) {
    matrix4 tempMatrix;
    
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
	        tempMatrix.m[r][c] = m1->m[r][0] * m2->m[0][c] +
            m1->m[r][1] * m2->m[1][c] +
            m1->m[r][2] * m2->m[2][c] +
            m1->m[r][3] * m2->m[3][c];
        }
    }
    
    return tempMatrix;
}
```

Output matrix
```
m1*m2
```

## Sorting

### Quicksort

```c
void swap(triangle *a, triangle *b)  
{  
    triangle t = *a;  
    *a = *b;  
    *b = t;  
}  
    
int partition(triangle arr[], int low, int high)  
{  
   triangle pivot = arr[high];  
    int i = (low - 1);    
    for (int j = low; j <= high - 1; j++) {  
        if ((arr[j].p[0].z + arr[j].p[1].z + arr[j].p[2].z) / 3.0f > (pivot.p[0].z + pivot.p[1].z + pivot.p[2].z) / 3.0f) {  
            i++;  
            swap(&arr[i], &arr[j]);  
        }  
    }  
    swap(&arr[i + 1], &arr[high]);  
    return (i + 1);  
}  
    
void quickSort(triangle arr[], int low, int high)  
{  
    if (low < high) {  
        int pi = partition(arr, low, high);  
  quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);  
    }  
}
```

Example input
``` c
// -1 because array starts from 0  
quickSort(triangleBuff, 0, triangleBuffSize - 1);
```

## Vector3

### Declaration
```c
typedef struct {  
   float x;  
   float y;  
   float z;  
   float w;  
} vector3;
```

Output vector
```
0 0 0 0
```

### Matrix multiply vector3
```c
vector3 matrixMultiplyVector3(matrix4 *m, vector3 *i)  
{  
   vector3 tempVector;  
   tempVector.x = i->x * m->m[0][0] + i->y * m->m[1][0] + i->z * m->m[2][0] + i->w * m->m[3][0];  
   tempVector.y = i->x * m->m[0][1] + i->y * m->m[1][1] + i->z * m->m[2][1] + i->w * m->m[3][1];  
   tempVector.z = i->x * m->m[0][2] + i->y * m->m[1][2] + i->z * m->m[2][2] + i->w * m->m[3][2];  
   tempVector.w = i->x * m->m[0][3] + i->y * m->m[1][3] + i->z * m->m[2][3] + i->w * m->m[3][3];  
   return tempVector;  
}
```

### Vector3 addition
```c
vector3 vector3Add(vector3 *v1, vector3 *v2)  
{  
   return (vector3){ v1->x + v2->x, v1->y + v2->y, v1->z + v2->z };  
}
```

### Vector3 subtraction
```c
vector3 vector3Sub(vector3 *v1, vector3 *v2)  
{  
   return (vector3){ v1->x - v2->x, v1->y - v2->y, v1->z - v2->z };  
}
```

### Vector3 multiplication
```c
vector3 vector3Mul(vector3 *v1, float amount)  
{  
   return (vector3){ v1->x * amount, v1->y * amount, v1->z * amount };  
}
```

### Vector3 division
```c
vector3 vector3Div(vector3 *v1, float amount)  
{  
   return (vector3){ v1->x / amount, v1->y / amount, v1->z / amount };  
}
```

### Vector3 dot product
```c
float vector3DotProduct(vector3 *v1, vector3 *v2)  
{  
   return v1->x*v2->x + v1->y*v2->y + v1->z * v2->z;  
}
```

### Vector3 length
```c
float vector3Length(vector3 *v)  
{  
   return sqrtf(vector3DotProduct(v, v));  
}
```

### Vector3 normalise
```c
vector3 vector3Normalise(vector3 *v)  
{  
   float lenght = vector3Length(v);  
   return (vector3){ v->x / length, v->y / length, v->z / length };  
}
```

### Vector3 cross product
```c
vector3 vector3CrossProduct(vector3 *v1, vector3 *v2)  
{  
   vector3 tempVector;  
   tempVector.x = v1->y * v2->z - v1->z * v2->y;  
   tempVector.y = v1->z * v2->x - v1->x * v2->z;  
   tempVector.z = v1->x * v2->y - v1->y * v2->x;  
   return tempVector;  
}
```

### Vector3 intersect plane
```c
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
```