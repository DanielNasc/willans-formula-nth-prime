#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

int checkPrime(int n) {
    if (n == 2 || n == 3) return 1;
    else if (n < 2 || n % 2 == 0 || n % 3 == 0) return 0;

    for (int i = 5; i <= sqrt(n); i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }

    return 1;
}

double willans_impl_parallel(int num) {
    double nthprime = 0.0, sum = 0.0;

    #pragma omp parallel for reduction(+:sum) num_threads(6)
    for(int i = 1; i <= (num*num); i++) {
        for(int j = 1; j <= i; j++)  {
            sum += (double) checkPrime(j);
        }
        sum += 1.0;
        sum = num/sum;
        sum = pow(sum, 1.0/num);
        sum = floor(sum);
        nthprime += sum;
        sum = 0.0;
    }
    nthprime += 1.0;
    return nthprime;
}

int main() {
    int num = 0;
    double nthprime = 0.0, start = 0.0, end = 0.0;
    printf("Digite o 'n' primo que deseja saber: ");
    scanf("%d", &num);
    start = omp_get_wtime();
    nthprime = willans_impl_parallel(num);
    end = omp_get_wtime();
    printf("O %d primo e %.2f", num, nthprime);
    printf("\nTempo de execucao: %f\n", end - start);   
    return 0;
}