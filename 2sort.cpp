#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

// ���������� �����
void shell(int* items, int count) {
    int i, j, gap;
    int x;
    int a[5] = { 9, 5, 3, 2, 1 }; // ������������������ �����

    for (int k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (j >= 0) && (x < items[j]); j -= gap) {
                items[j + gap] = items[j];
            }
            items[j + gap] = x;
        }
    }
}

// ������� ����������
void qs(int* items, int left, int right) {
    int i = left, j = right;
    int x = items[(left + right) / 2];

    do {
        while (items[i] < x) i++;
        while (x < items[j]) j--;
        if (i <= j) {
            int temp = items[i];
            items[i] = items[j];
            items[j] = temp;
            i++;
            j--;
        }
    } while (i <= j);

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

// ��������� ���������� �������
void generate_random_array(int* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 100000; // ��������� ��������� ����� �� 0 �� 99999
    }
}

// ��������� ������������� �������
void generate_sorted_array(int* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = i; // ������������ ������������������
    }
}

// ��������� ���������� �������
void generate_descending_array(int* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = size - i; // ��������� ������������������
    }
}

// ��������� ���������� ������� (������������ + ���������)
void generate_mixed_array(int* array, int size) {
    int half_size = size / 2;
    for (int i = 0; i < half_size; i++) {
        array[i] = i; // ������ �������� - ������������
    }
    for (int i = half_size; i < size; i++) {
        array[i] = size - i; // ������ �������� - ���������
    }
}

// ������� ��������� ��� qsort
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// ��������� ������� ����������
void measure_sorting_time() {
    int count = 100000; // ������ �������
    int* random_array = (int*)malloc(count * sizeof(int));
    int* sorted_array = (int*)malloc(count * sizeof(int));
    int* descending_array = (int*)malloc(count * sizeof(int));
    int* mixed_array = (int*)malloc(count * sizeof(int));

    // ��������� ��������
    generate_random_array(random_array, count);
    generate_sorted_array(sorted_array, count);
    generate_descending_array(descending_array, count);
    generate_mixed_array(mixed_array, count);

    // ��������� ������� ������ ���������� ����� �� ��������� �������
    int* temp_array = (int*)malloc(count * sizeof(int));
    memcpy(temp_array, random_array, count * sizeof(int)); // �������� ������
    clock_t start_shell_random = clock();
    shell(temp_array, count);
    clock_t end_shell_random = clock();
    double time_shell_random = (double)(end_shell_random - start_shell_random) / CLOCKS_PER_SEC;
    printf("����� ���������� ���������� ����� �� ��������� �������: %.6f ������\n", time_shell_random);

    // ��������� ������� ������ ���������� ����� �� ������������ �������
    memcpy(temp_array, sorted_array, count * sizeof(int)); // �������� ������
    clock_t start_shell_sorted = clock();
    shell(temp_array, count);
    clock_t end_shell_sorted = clock();
    double time_shell_sorted = (double)(end_shell_sorted - start_shell_sorted) / CLOCKS_PER_SEC;
    printf("����� ���������� ���������� ����� �� ������������ �������: %.6f ������\n", time_shell_sorted);

    // ��������� ������� ������ ���������� ����� �� ��������� �������
    memcpy(temp_array, descending_array, count * sizeof(int)); // �������� ������
    clock_t start_shell_descending = clock();
    shell(temp_array, count);
    clock_t end_shell_descending = clock();
    double time_shell_descending = (double)(end_shell_descending - start_shell_descending) / CLOCKS_PER_SEC;
    printf("����� ���������� ���������� ����� �� ��������� �������: %.6f ������\n", time_shell_descending);

    // ��������� ������� ������ ���������� ����� �� ��������� �������
    memcpy(temp_array, mixed_array, count * sizeof(int)); // �������� ������
    clock_t start_shell_mixed = clock();
    shell(temp_array, count);
    clock_t end_shell_mixed = clock();
    double time_shell_mixed = (double)(end_shell_mixed - start_shell_mixed) / CLOCKS_PER_SEC;
    printf("����� ���������� ���������� ����� �� ��������� �������: %.6f ������\n", time_shell_mixed);

    // ��������� ������� ������ ������� ���������� �� ��������� �������
    memcpy(temp_array, random_array, count * sizeof(int)); // �������� ������
    clock_t start_qs_random = clock();
    qs(temp_array, 0, count - 1);
    clock_t end_qs_random = clock();
    double time_qs_random = (double)(end_qs_random - start_qs_random) / CLOCKS_PER_SEC;
    printf("\n����� ���������� ������� ���������� �� ��������� �������: %.6f ������\n", time_qs_random);

    // ��������� ������� ������ ������� ���������� �� ������������ �������
    memcpy(temp_array, sorted_array, count * sizeof(int)); // �������� ������
    clock_t start_qs_sorted = clock();
    qs(temp_array, 0, count - 1);
    clock_t end_qs_sorted = clock();
    double time_qs_sorted = (double)(end_qs_sorted - start_qs_sorted) / CLOCKS_PER_SEC;
    printf("����� ���������� ������� ���������� �� ������������ �������: %.6f ������\n", time_qs_sorted);

    // ��������� ������� ������ ������� ���������� �� ��������� �������
    memcpy(temp_array, descending_array, count * sizeof(int)); // �������� ������
    clock_t start_qs_descending = clock();
    qs(temp_array, 0, count - 1);
    clock_t end_qs_descending = clock();
    double time_qs_descending = (double)(end_qs_descending - start_qs_descending) / CLOCKS_PER_SEC;
    printf("����� ���������� ������� ���������� �� ��������� �������: %.6f ������\n", time_qs_descending);

    // ��������� ������� ������ ����������� qsort �� ��������� �������
    memcpy(temp_array, random_array, count * sizeof(int)); // �������� ������
    clock_t start_qsort_random = clock();
    qsort(temp_array, count, sizeof(int), compare);
    clock_t end_qsort_random = clock();
    double time_qsort_random = (double)(end_qsort_random - start_qsort_random) / CLOCKS_PER_SEC;
    printf("\n����� ���������� ����������� qsort �� ��������� �������: %.6f ������\n", time_qsort_random);

    // ��������� ������� ������ ����������� qsort �� ������������ �������
    memcpy(temp_array, sorted_array, count * sizeof(int)); // �������� ������
    clock_t start_qsort_sorted = clock();
    qsort(temp_array, count, sizeof(int), compare);
    clock_t end_qsort_sorted = clock();
    double time_qsort_sorted = (double)(end_qsort_sorted - start_qsort_sorted) / CLOCKS_PER_SEC;
    printf("����� ���������� ����������� qsort �� ������������ �������: %.6f ������\n", time_qsort_sorted);

    // ��������� ������� ������ ����������� qsort �� ��������� �������
    memcpy(temp_array, descending_array, count * sizeof(int)); // �������� ������
    clock_t start_qsort_descending = clock();
    qsort(temp_array, count, sizeof(int), compare);
    clock_t end_qsort_descending = clock();
    double time_qsort_descending = (double)(end_qsort_descending - start_qsort_descending) / CLOCKS_PER_SEC;
    printf("����� ���������� ����������� qsort �� ��������� �������: %.6f ������\n", time_qsort_descending);

    // ��������� ������� ������ ����������� qsort �� ��������� �������
    memcpy(temp_array, mixed_array, count * sizeof(int)); // �������� ������
    clock_t start_qsort_mixed = clock();
    qsort(temp_array, count, sizeof(int), compare);
    clock_t end_qsort_mixed = clock();
    double time_qsort_mixed = (double)(end_qsort_mixed - start_qsort_mixed) / CLOCKS_PER_SEC;
    printf("����� ���������� ����������� qsort �� ��������� �������: %.6f ������\n", time_qsort_mixed);

    // ������������ ������
    free(random_array);
    free(sorted_array);
    free(descending_array);
    free(mixed_array);
    free(temp_array);
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL)); // ������������� ���������� ��������� �����
    measure_sorting_time(); // ������ ��������� ������� ����������
    return 0;
}