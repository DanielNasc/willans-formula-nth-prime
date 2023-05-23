#include "willans_implementations.h"

int main() {
    int num = 0;
    double nthprime = 0.0,
    start_serial, end_serial,
    start_parallel_omp, end_parallel_omp,
    start_parallel_ompi, end_parallel_ompi;


    printf("Digite o 'n' primo que deseja saber: ");
    scanf("%d", &num);
    start_serial = omp_get_wtime();
    nthprime = willans_impl_serial(num);
    end_serial = omp_get_wtime();
    printf("O %d primo e %f", num, nthprime);
    printf("\nTempo de execucao: %f\n", end_serial - start_serial);  

    start_parallel_omp = omp_get_wtime();
    nthprime = willans_impl_parallel_omp(num);
    end_parallel_omp = omp_get_wtime();
    printf("O %d primo e %.2f", num, nthprime);
    printf("\nTempo de execucao: %f\n", end_parallel_omp - start_parallel_omp);  

    return 0;
}