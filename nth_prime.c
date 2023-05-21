#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

    for(int i = 1; i <= pow(2.0,num); i++) {
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
    double nthprime = 0.0;
    printf("Digite o 'n' primo que deseja saber: ");
    scanf("%d", &num);
    nthprime = willans_impl_serial(num);
    printf("O %d primo e %f", num, nthprime);
    return 0;
}