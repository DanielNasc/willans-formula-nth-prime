#include "willans_implementations.h"

int checkPrime(int n) {
    if (n == 2 || n == 3) return 1;
    else if (n < 2 || n % 2 == 0 || n % 3 == 0) return 0;

    for (int i = 5; i <= sqrt(n); i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }

    return 1;
}


double willans_impl_serial(int num) {
    double nthprime = 0.0, sum = 0.0;

    for(int i = 1; i <= pow(num, 2.0); i++) {
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


double willans_impl_parallel_omp(int num) {
    double nthprime = 0.0, sum = 0.0;

    #pragma omp parallel for reduction(+:nthprime) private(sum)
    for(int i = 1; i <= (num * num); i++) {
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

// double willans_impl_parallel_ompi(int num) {

// }