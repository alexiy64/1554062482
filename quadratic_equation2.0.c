#include <stdio.h>
#include <math.h>

int main(void) {
    double first_coefficient;
    double second_coefficient;
    double third_coefficient;
    double D; 
    double x1, x2;

    // Ввод данных
    FILE *file; 
    file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Ошибка: файл не найден!\n");
        return 1;
}
    fscanf(file, "%lf %lf %lf", &first_coefficient, &second_coefficient, &third_coefficient);
    fclose(file);

    D = pow(second_coefficient, 2) - 4 * first_coefficient * third_coefficient;

    printf("%f\n", first_coefficient);
    printf("%f\n", second_coefficient);
    printf("%f\n", third_coefficient);
    // Условия
    if (D < 0) {
        printf("Решений в множестве действительных чисел нет\n");
    } else if (D == 0) {
        x1 = -second_coefficient / (2 * first_coefficient);
        printf("Один корень: %.10f\n", x1);
    } else {
        x1 = (-second_coefficient + sqrt(D)) / (2 * first_coefficient);
        x2 = (-second_coefficient - sqrt(D)) / (2 * first_coefficient);
        printf("Первый корень: %.10f\n", x1);
        printf("Второй корень: %.10f\n", x2);
    }

    return 0;
}