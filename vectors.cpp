#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>

float vector(float* arr1, float* arr2, int n) {
    float a = 0.0;
    for (int i = 0; i < n; i++) {
        float b;
        b = arr1[i] * arr2[i];
        a = a + b;
    }
    return a;
}
int main()
{
    int n;
    printf("Размерность: \n");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Неверно!");
        return 1;
    }

    float* arr1 = (float*)malloc(n * sizeof(float));
    float* arr2 = (float*)malloc(n * sizeof(float));

    if (arr1 == NULL || arr2 == NULL) {
        printf("Ошибка памяти!\n");
        if (arr1 != NULL) free(arr1); // Освобождаем, если выделилось
        if (arr2 != NULL) free(arr2);
        return 1;
    }

    printf("Координаты первого вектора: \n");
    for (int j = 0; j < n; j++) {
        scanf("%f", &arr1[j]);
    }

    printf("Координаты второго вектора: \n");
    for (int l = 0; l < n; l++) {
        scanf("%f", &arr2[l]);
    }

    float result = vector(arr1, arr2, n);
    printf("%f\n", result);

    free(arr1);
    free(arr2);
        
    return 0;
}