#include "rendevox.h"

void removeCharsFromArray(string* array, int* numberOfElements, string chars) {
    for (int i = 0; i < *numberOfElements; i++) {
        if (strcmp(array[i], chars) != 0) {
            array[i] = "empty";
            --*numberOfElements;
            break;
        }
    }
}
