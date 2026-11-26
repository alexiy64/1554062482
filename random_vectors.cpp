#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float get_random_float(int m, int M) {
    float a = (float)rand() / RAND_MAX; // Вернет от 0.0 до 1.0
    float b = rand() % (max - min + 1) + min; // Целые числа
    float c = a * b;
    return c;
}

int main()
{
    int m;
    int M;

}
