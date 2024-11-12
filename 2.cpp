#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void multiply_matrices(int size) {
    int i, j, r;
    // Динамическое выделение памяти для матриц
    int** a = (int**)malloc(size * sizeof(int*));
    int** b = (int**)malloc(size * sizeof(int*));
    int** c = (int**)malloc(size * sizeof(int*));
    for (i = 0; i < size; i++) {
        a[i] = (int*)malloc(size * sizeof(int));
        b[i] = (int*)malloc(size * sizeof(int));
        c[i] = (int*)malloc(size * sizeof(int));
    }

    // Генерация матриц a и b
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            a[i][j] = rand() % 100 + 1; // Заполняем массив случайными числами
        }
    }

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            b[i][j] = rand() % 100 + 1; // Заполняем массив случайными числами
        }
    }

    // Перемножение матриц
    clock_t start = clock();
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            int elem_c = 0;
            for (r = 0; r < size; r++) {
                elem_c += a[i][r] * b[r][j];
            }
            c[i][j] = elem_c;
        }
    }
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время выполнения для размера %d: %.6f секунд\n", size, time_spent);

    // Освобождение памяти
    for (i = 0; i < size; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);
}

int main(void) {
    setlocale(LC_ALL, "Rus");

    srand(time(NULL)); // Инициализируем генератор случайных чисел

    int sizes[] = { 100, 200, 400, 1000, 2000, 4000, 10000 };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_sizes; i++) {
        printf("Размер матрицы: %d\n", sizes[i]);
        multiply_matrices(sizes[i]);
    }

    return 0;
}
