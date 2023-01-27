#include "rendevox.h"

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
