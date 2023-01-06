#include <stdio.h>
#include <math.h>


/*
cette fonction retourne le produit de deux matrices de dimension 2
pour aller au plus simple, nous avons choisi de representer les
matrices sous forme de liste de 4 elements
*/
long int * matrix_dot(long int A[4], long int B[4]){
	static long int result[4];
	
	result[0] = A[0]*B[0] + A[1]*B[2];
	result[1] = A[0]*B[1] + A[1]*B[3];
	result[2] = A[2]*B[0] + A[3]*B[2];
	result[3] = A[2]*B[1] + A[3]*B[3];

	return result;
}

/*cette methode-ci permet l'exponentiation d'une matrice A en dimension 2*/
long int * powerMat(long long int power, long int A[4]){
	
	static long int temp[4];
	static long int result[4];
	long int *mat;
	long int *powMat;
	int i;
	for (i = 0; i < 4; ++i) {	
		temp[i] = A[i];
	}
	
	if(power == 1) {
		return temp;
		}
		
	/* comme l'exposant peut etre impair, il est necessaire de separer les cas
	si l'exposant est pair, on peut sortir un carre a chaque etape, ce qui
	simplifie le calcul */
    if(power%2 == 0 ){
		while (power != 1){	
			mat = matrix_dot(temp, temp);
			for (i = 0; i < 4; ++i) {
				result[i] = mat[i];	
				temp[i] = result[i];
			}
			power = power/2;
		}
		return result;
		
	/* si l'exposant est impair, on realise l'exponentiation de la matrice a 
	la puissance (exposant-1) que l'on multiplie ensuite par la matrice
	pour obtenir le resultat voulu */
		
    }else {
		powMat = powerMat(power-1, temp);
		mat = matrix_dot(powMat, A);
		for (i = 0; i < 4; ++i) {	
			result[i] = mat[i];
		}  
	}
	return result;
}


/* on cree ici la fonction qui calcule la suite, en fournissant la matrice
necessaire et les termes initiaux; comme f_0 est parfois initialise a 1
on laisse le choix a l'utilisateur en donnant f_0 en parametre */
long long int fibonacci_matriciel(long long int power, int f0){
	long int matrix[4] = {0,1, 1,1};
	long int *temp;
	long int result;
	int i;
	
	temp = powerMat(power, matrix);
	for (i = 0; i < 4; ++i) {	
	}
	result = temp[0]*f0 + temp[1];
	/* la formule d'exponentiation de matrice peut etre reduite a cette expression 
	car nous ne sommes interesses que par f_n, c'est a dire la premiere coordonnee 
	du vecteur resultat (f_n, f_n+1) */
	
	return result;
	
}


int main() {
	char result[50]; 
	long long int k = fibonacci_matriciel(100000000000000000, 0);
	sprintf(result, "%lld", k); 
  	puts(result);
	
    return(0);
}
