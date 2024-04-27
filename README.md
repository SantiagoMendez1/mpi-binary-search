## Descripción del Código MPI para Ordenamiento y Búsqueda Binaria

Este código implementa el uso de MPI (Message Passing Interface) para paralelizar un algoritmo de ordenamiento y búsqueda binaria en un entorno distribuido. A continuación, se detallan los aspectos más relevantes de MPI utilizados en el código y una breve explicación del funcionamiento del programa:

## Aspectos Relevantes de MPI Utilizados

- **MPI_Init:** Inicializa el entorno MPI, permitiendo la comunicación y cooperación entre los procesos de MPI.
  
- **MPI_Comm_rank:** Obtiene el rango (ID) del proceso actual en el comunicador dado. En este caso, el comunicador es `MPI_COMM_WORLD`, que incluye todos los procesos.
  
- **MPI_Comm_size:** Obtiene el tamaño (número de procesos) del comunicador.
  
- **MPI_Scatter:** Divide un arreglo (en este caso, la lista generada aleatoriamente) en partes más pequeñas y distribuye estas partes entre los procesos del comunicador.
  
- **MPI_Gather:** Recolecta los datos de todos los procesos y los reúne en un solo proceso (en este caso, el proceso con rango 0).
  
- **MPI_Bcast:** Transmite un dato desde un único proceso (en este caso, el proceso con rango 0) a todos los demás procesos del comunicador.

## Funcionamiento del Código

El código comienza generando una lista aleatoria de números y la divide entre los procesos MPI. Cada proceso ordena su sublista utilizando el algoritmo de ordenamiento de burbuja (`bubble_sort`). Después de la ordenación, los resultados se recopilan en un solo proceso (rango 0) y se ordenan nuevamente para tener una lista ordenada completa.

Luego, se genera una clave aleatoria de la lista ordenada completa, que se transmite a todos los procesos utilizando `MPI_Bcast`. El proceso con rango 0 realiza una búsqueda binaria (`binary_search`) de esta clave en la lista ordenada completa.

Finalmente, se calcula el tiempo tomado para la ordenación y la búsqueda binaria, y se muestra el resultado junto con la lista ordenada y la clave aleatoria generada.
## Ejecucion dentro de Guane

dentro de guane, se realiza la carga del modulo MPI

```bash
  module av
  module load devtools/mpi/openmpi/4.0.2
```
reserva interactiva 
```bash
  srun -n 4 --pty /bin/bash
```
compilacion y ejecucion
```bash
  mpicc mpi_BinarySearch.c -o mpi_BinarySearch
  mpirun -np 4 mpi_BinarySearch
```
## Análisis de ejecución
    
| Secuencial (s) |   OPenMP  (s)  |     MPI (s)   |
|----------------|----------------|---------------|
|   0,000027     |    0.000005    |   0.000003    |

### Conclusion
En la compilacion del programa se jugo con el tipo de banderar o1, o2, o3, sin embargo el cambio en muy pocos segundo no fue tan relevante de resalta. Por otro lado, en el tiempo que se evidencia en la tabla anterior, podemos observar que para la medicion especifica del ordenamiento de la lista, el que resulta mas eficaz es el que usan MPI. Podemos concluir que es evidente que MPI se puede usar para aplicaciones que necesitan un gran paralelismo ya que garantiza la distribución eficiente del trabajo en entornos distribuidos,
