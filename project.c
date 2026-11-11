#include <stdio.h>
#include <math.h>

int main(void) {
    float first_coefficient;
    float second_coefficient;
    float third_coefficient;
    float D; 
    float x1, x2;

    // Ввод
    printf("Введите старший коэффициент: ");
    scanf("%f", &first_coefficient);

    printf("Введите второй коэффициент: ");
    scanf("%f", &second_coefficient);

    printf("Введите третий коэффициент: ");
    scanf("%f", &third_coefficient);

    D = pow(second_coefficient, 2) - 4 * first_coefficient * third_coefficient;

    // Условия
    if (D < 0) {
        printf("Решений в множестве действительных чисел нет\n");
    } else if (D == 0) {
        x1 = -second_coefficient / (2 * first_coefficient);
        printf("Один корень: %f\n", x1);
    } else {
        x1 = (-second_coefficient + sqrt(D)) / (2 * first_coefficient);
        x2 = (-second_coefficient - sqrt(D)) / (2 * first_coefficient);
        printf("Первый корень: %f\n", x1);
        printf("Второй корень: %f\n", x2);
    }

    return 0;
}