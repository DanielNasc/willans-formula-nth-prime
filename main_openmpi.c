#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define MAIN_RANK 0

int checkPrime(int n) {
    if (n == 2 || n == 3) return 1;
    else if (n < 2 || n % 2 == 0 || n % 3 == 0) return 0;

    for (int i = 5; i <= sqrt(n); i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }

    return 1;
}

int main() {
    MPI_Init(NULL, NULL);

    int rank, n_cpus;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n_cpus);

    int num = 20;
    double nthprime_partial = 0, sum = 0, *partial_results,
            start, end;

    if (rank == 0) {
        start = MPI_Wtime();
    }

    MPI_Bcast(&num, 1, MPI_INT, 0, MPI_COMM_WORLD);

    for(int i = rank + 1; i <= pow(2.0,num); i += n_cpus) {
        for(int j = 1; j <= i; j++)  {
            sum += (double) checkPrime(j);
        }
        sum += 1.0;
        sum = num/sum;
        sum = pow(sum, 1.0/num);
        sum = floor(sum);
        nthprime_partial += sum;
        sum = 0.0;
    }


    if (rank == 0) {
        partial_results = (double *) malloc(sizeof(double) * n_cpus);
    }

    MPI_Gather(&nthprime_partial, 1, MPI_DOUBLE, partial_results, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        double nthprime = 0;    
        for (int i = 0; i < n_cpus; i++) {
            nthprime += partial_results[i];
        }
        nthprime++;

        end = MPI_Wtime();

        printf("Primo: %f\n", nthprime);
        printf("Tempo total: %f\n", end - start);
    }

    MPI_Finalize();

    return 0;
}