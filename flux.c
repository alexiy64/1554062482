#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <windows.h>
#include <limits.h>

int main(void) {

    // Настройка русскоязычной консоли
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Открываем исходный файл
    FILE* input = fopen("numbers.txt", "r");

    if (input == NULL) {
        printf("Ошибка открытия numbers.txt!\n");
        return 1;
    }

    // Считываем количество чисел
    long long n;

    if (fscanf(input, "%lld", &n) != 1 ||
        n <= 0 || n > INT_MAX) {

        printf("Ошибка: неверное количество чисел!\n");
        fclose(input);
        return 1;
    }

    // Выделяем память
    int* arr = malloc((size_t)n * sizeof(int));

    if (arr == NULL) {
        printf("Ошибка выделения памяти!\n");
        fclose(input);
        return 1;
    }

    // Заполняем массив из файла
    for (int i = 0; i < (int)n; i++) {

        if (fscanf(input, "%d", &arr[i]) != 1) {
            printf("Ошибка чтения файла!\n");
            free(arr);
            fclose(input);
            return 1;
        }
    }

    fclose(input);

    printf("Файл успешно прочитан!\n");
    printf("Количество чисел: %lld\n\n", n);

    // Количество потоков для проверки
    int thread_counts[] = {1, 2, 4};

    // Открываем файл результатов
    FILE* output = fopen("results.txt", "w");

    if (output == NULL) {
        printf("Ошибка создания results.txt!\n");
        free(arr);
        return 1;
    }

    fprintf(output, "Количество чисел: %lld\n\n", n);

    // Проверяем 1, 2 и 4 потока
    for (int t = 0; t < 3; t++) {

        int threads = thread_counts[t];

        double sum = 0.0;
        double squares = 0.0;

        double mean;
        double deviation;

        double total_time = 0.0;

        const int repetitions = 5;

        // Повторяем вычисления 5 раз
        for (int r = 0; r < repetitions; r++) {

            // Обнуляем промежуточные результаты
            sum = 0.0;
            squares = 0.0;

            // Устанавливаем количество потоков
            omp_set_num_threads(threads);

            double start = omp_get_wtime();

            // Первый проход: вычисляем сумму
            int i;

            #pragma omp parallel for reduction(+:sum) schedule(static)
            for (i = 0; i < (int)n; i++) {
                sum += arr[i];
            }

            // Вычисляем среднее арифметическое
            mean = sum / n;

            // Второй проход: сумма квадратов отклонений
            #pragma omp parallel for reduction(+:squares) schedule(static)
            for (i = 0; i < (int)n; i++) {

                double difference = arr[i] - mean;

                squares += difference * difference;
            }

            // Вычисляем среднеквадратическое отклонение
            deviation = sqrt(squares / n);

            double end = omp_get_wtime();

            total_time += end - start;
        }

        // Среднее время пяти запусков
        double average_time = total_time / repetitions;

        // Выводим результаты
        printf("Количество потоков: %d\n", threads);
        printf("Среднее арифметическое: %.6f\n", mean);
        printf("Среднеквадратическое отклонение: %.6f\n",
               deviation);
        printf("Время вычислений: %.6f сек.\n\n",
               average_time);

        // Записываем результаты в файл
        fprintf(output, "Потоков: %d\n", threads);
        fprintf(output, "Среднее: %.6f\n", mean);
        fprintf(output, "Отклонение: %.6f\n", deviation);
        fprintf(output, "Время: %.6f сек.\n\n",
                average_time);
    }

    fclose(output);

    // Освобождаем память
    free(arr);

    printf("Результаты записаны в results.txt\n");

    return 0;
}
