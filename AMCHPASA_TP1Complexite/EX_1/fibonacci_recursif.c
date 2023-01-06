#include <stdio.h>
#include <stdlib.h>


long double fibonacci_recursif(int n){
	if(n<2)
		return n;
	return fibonacci_recursif(n-1) + fibonacci_recursif(n-2);
	/*a chaque  etape  on  calcule  f_i en  fonction  des  deux  termes  precedents*/
	
}

int main(){
	long double nbFinal = fibonacci_recursif(50);
	printf("Nb final : %Lf", nbFinal);
	return 0;
}
