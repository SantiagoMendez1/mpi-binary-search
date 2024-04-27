#!/bin/bash

#SBATCH -p normal
#SBATCH --ntasks=4
#SBATCH --output=output_mpi_BinarySearch.txt
#SBATCH --error=error_%j.txt
#SBATCH --cpus-per-task=1
#SBATCH -w guane10

module load devtools/mpi/openmpi/4.1.2
mpicc  mpi_BinarySearch.c -o mpi_BinarySearch
mpirun -np 4  ./mpi_BinarySearch