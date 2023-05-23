#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>
#include <mpi.h>

double willans_impl_serial(int n);
double willans_impl_parallel_omp(int n);
double willans_impl_parallel_ompi(int n);