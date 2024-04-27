#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>



void binary_search(int[], int, int, int);
void bubble_sort(int[], int);
void print_list(int[], int);

int main()
{   
    int SIZE = 50;
    int key_index;
    int list[SIZE];

    srand(time(NULL));
    for (int i = 0; i < SIZE; i++)
    {
        list[i] = rand() % 100; // Generar números aleatorios entre 0 y 99
    }

    printf("\nGenerated list:\n");
    print_list(list, SIZE);

    // Generar un índice aleatorio en el rango de la lista
    key_index = rand() % SIZE;
    int key = list[key_index];
    printf("\nRandomly selected key: %d\n", key);

    double start_time = omp_get_wtime();

#pragma omp num_threads(1) parallel shared(list)
    {
        bubble_sort(list, SIZE);
    }

    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;

    printf("\nSorted list:\n");
    print_list(list, SIZE);

    printf("\nTime taken for sorting: %f seconds\n", elapsed_time);

    binary_search(list, 0, SIZE, key);

    return 0;
}

void bubble_sort(int list[], int size)
{
    int temp, i, j;
    for (i = 0; i < size; i++)
    {
        for (j = i; j < size; j++)
        {
            if (list[i] > list[j])
            {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
}

void binary_search(int list[], int lo, int hi, int key)
{
    int mid;

    if (lo > hi)
    {
        printf("Key not found\n");
        return;
    }

    mid = (lo + hi) / 2;

    if (list[mid] == key)
    {
        printf("Key found at index %d\n", mid);
    }
    else if (list[mid] > key)
    {
        binary_search(list, lo, mid - 1, key);
    }
    else if (list[mid] < key)
    {
        binary_search(list, mid + 1, hi, key);
    }
}

void print_list(int list[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", list[i]);
    }
    printf("\n");
}

