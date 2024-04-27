#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// Tamaño de la lista fijo para probar con 5 elementos segun indicaciones del taller
#define SIZE 50

// Declaración de funciones
void binary_search(int[], int, int, int);
void bubble_sort(int[], int);
void print_list(int[], int);

int main()
{
    int key, i;
    int list[SIZE];

    /*
        Se implementa generacion de numeros aletorios en un rango de 0 - 99 para envitar introducir
        los elementos uno a uno por en la ejecucion del codigo
    */
    srand(time(NULL)); // Inicializar el generador de números aleatorios con el tiempo actual
    for (i = 0; i < SIZE; i++)
    {
        list[i] = rand() % 100; // Generar números aleatorios entre 0 y 99
    }

    printf("\nGenerated list:\n");
    print_list(list, SIZE); // Imprimir la lista generada

    /*
        Se implementa un calculo de tiempo con el fin de analizar el tiempo
        demora en ejecutar el trozo de codigo antes de ser paralelizado
    */

    // Obtener el tiempo antes de la ordenación
    clock_t start_time = clock();

    // Ordenar la lista utilizando bubble_sort
    bubble_sort(list, SIZE);

    // Obtener el tiempo después de la ordenación
    clock_t end_time = clock();

    // Calcular el tiempo transcurrido
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("\nSorted list:\n");
    print_list(list, SIZE);

    printf("\nTime taken for sorting: %f seconds\n", elapsed_time);

    printf("\nEnter key to search: ");
    scanf("%d", &key); // Leer la clave a buscar desde la entrada estándar

    // Realizar la búsqueda binaria
    binary_search(list, 0, SIZE, key);

    return 0;
}

// Definición de la función bubble_sort
void bubble_sort(int list[], int size)
{
    int temp, i, j;
    for (i = 0; i < size; i++)
    {
        for (j = i; j < size; j++)
        {
            if (list[i] > list[j])
            {
                // Intercambiar elementos si están en orden incorrecto
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
}

// Definición de la función binary_search
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
        printf("Key found\n"); // Clave encontrada
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

/*
    Se implementa funcion para visualizar la lista con lo numeros generados
    aleatoriamente para escoger la 'KEY' a buscar
*/
void print_list(int list[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", list[i]); // Imprimir cada elemento de la lista
    }
    printf("\n");
}