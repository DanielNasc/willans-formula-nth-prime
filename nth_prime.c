#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double checkPrime(int num) {
    double rest = 1.0;
    if(num == 0 || num == 1) {
        rest = 0.0;
        return rest;
    }
    else if(num == 2 || num == 3) {
        rest = 1.0;
        return rest;
    }
    else {
        for(int i = 2; i <= num/2; i++) {
            if(num % i == 0) {
                rest = 0.0;
            }
        }
    }
    return rest;
}

double willans_impl_serial(int num) {
    double nthprime = 0.0, sum = 0.0;

    for(int i = 1; i <= pow(2.0,num); i++) {
        for(int j = 1; j <= i; j++)  {
            sum += checkPrime(j);
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