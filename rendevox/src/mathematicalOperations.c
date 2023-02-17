#include <rendevox.h>

int clamp(int number, int minValue, int maxValue) {
    if (number < maxValue) {
        if (number > minValue) {
            return number;
        } else {
            return minValue;
        }
    } else {
        if (maxValue > minValue) {
            return maxValue;
        } else {
            return minValue;
        }
    }
}
