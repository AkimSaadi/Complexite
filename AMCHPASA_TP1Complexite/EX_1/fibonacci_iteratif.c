#include <stdio.h>
#include <stdlib.h>

long long int fibonacci_iteratif(long long int n){

    long int i = 0, j = 1, cpt = 0; //initialisation d'un compteur
    long long int k = 1;

    while(cpt < n) {
        if (cpt < 2) {
            k = cpt;
        }
        else {
            i = j; /* f_(i-2) devient f_(i-1) */
            j = k; /* f_(i-1) devient f_i */
            k = i + j; /* on calcule f_(i+1) a partir des deux termes precedents */

        }
    cpt+=1;
    }
    return k;
}

int main() {
   long long int nbFinal = fibonacci_iteratif(1000000000);
   printf("nombre final : %lld", nbFinal);
   return 0;
}
