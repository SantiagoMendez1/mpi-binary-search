#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define SIZE 50

void binary_search(int[], int, int, int);
void bubble_sort(int[], int);
void print_list(int[], int);

int main(int argc, char *argv[])
{
    int rank, size, key, i;
    int list[SIZE];

    srand(time(NULL));
    for (i = 0; i < SIZE; i++)
    {
        list[i] = rand() % 100;
    }

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int sublist_size = SIZE / size;
    int sublist[sublist_size];

    MPI_Scatter(list, sublist_size, MPI_INT, sublist, sublist_size, MPI_INT, 0, MPI_COMM_WORLD);

    double start_time_sort, end_time_sort, start_time_search, end_time_search;

    start_time_sort = MPI_Wtime(); // Iniciar medición de tiempo para la ordenación

    bubble_sort(sublist, sublist_size);

    end_time_sort = MPI_Wtime(); // Finalizar medición de tiempo para la ordenación

    int *merged_list = NULL;
    if (rank == 0)
    {
        merged_list = (int *)malloc(SIZE * sizeof(int));
    }
    MPI_Gather(sublist, sublist_size, MPI_INT, merged_list, sublist_size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        bubble_sort(merged_list, SIZE);
        printf("\nSorted list:\n");
        print_list(merged_list, SIZE);

        key = merged_list[rand() % SIZE]; // Generar una clave aleatoria de la lista
        printf("Randomly generated key: %d\n", key);
    }

    MPI_Bcast(&key, 1, MPI_INT, 0, MPI_COMM_WORLD); // Transmitir la clave aleatoria a todos los procesos

    start_time_search = MPI_Wtime(); // Iniciar medición de tiempo para la búsqueda

    if (rank == 0)
    {
        binary_search(merged_list, 0, SIZE - 1, key); // Realizar la búsqueda binaria con la clave generada
    }

    end_time_search = MPI_Wtime(); // Finalizar medición de tiempo para la búsqueda

    if (rank == 0)
    {
        double time_sort = end_time_sort - start_time_sort;
        double time_search = end_time_search - start_time_search;
        printf("Time taken for sorting: %lf seconds\n", time_sort);
        printf("Time taken for searching: %lf seconds\n", time_search);
    }

    MPI_Finalize();

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
        printf("Key not found\n"); // Clave no encontrada
        return;
    }

    mid = (lo + hi) / 2; // Calcular el índice de la mitad

    if (list[mid] == key)
    {
        printf("Key found at index %d\n", mid); // Clave encontrada
    }
    else if (list[mid] > key)
    {
        // Realizar la búsqueda en la mitad inferior de la lista
        binary_search(list, lo, mid - 1, key);
    }
    else if (list[mid] < key)
    {
        // Realizar la búsqueda en la mitad superior de la lista
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
