#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NMAX 30

typedef int SOMMET;

typedef struct { int A[NMAX][NMAX];
				 int n;
}GRAPHEMAT;

//Affichage d'un tableau 2D
void print_tableau (int t[][NMAX], int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",t[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//Initialisation d'un tableau 2D
void init_tab (int t[][NMAX], int n)
{
	int i,j;
	for (i=0;i<n;i++)
	{
		for (j=0;j<n;j++)
		{
			t[i][j]=0;
		}
	}
}


//Affichage d'une liste de SOMMET
void print_tab_sommet(SOMMET ssg[], int n)
{
	int i;
	for (i=0;i<n;i++)
	{
		printf("%d ",ssg[i]);
	}
	printf("\n");
}

//Crée une liste d'ordre de parcours de sommet pour zone_vide_maximal
void creer_liste (int liste[], int n){
	int i;
	for(i=0;i<n;i++){
		liste[i]=i;
	}
}

//Créer un fichier graph et initialise la matrice d'adjacence
GRAPHEMAT creer_graph()
{
FILE *f;
	int nbArete, sa, sb;
	GRAPHEMAT graph;
	f=fopen("graphe.txt","w+");
		fputs("13\n",f);
		fputs("21\n",f);
		fputs("0 1\n",f);
		fputs("1 2\n",f);
		fputs("2 3\n",f);
		fputs("3 4\n",f);
		fputs("4 0\n",f);
		fputs("0 5\n",f);
		fputs("1 6\n",f);
		fputs("2 7\n",f);
		fputs("5 7\n",f);
		fputs("3 8\n",f);
		fputs("6 8\n",f);
		fputs("5 8\n",f);
		fputs("4 9\n",f);
		fputs("9 6\n",f);
		fputs("9 7\n",f);
		fputs("0 10\n",f);
		fputs("10 11\n",f);
		fputs("2 11\n",f);
		fputs("12 11\n",f);
		fputs("3 12\n",f);
		fputs("12 10\n",f);
	rewind(f);
	fscanf(f,"%d",&(graph.n));
	if (graph.n<NMAX)
	{
		init_tab(graph.A,graph.n);
		fscanf(f,"%d",&nbArete);
		while (nbArete)
		{
			fscanf(f,"%d %d",&sa,&sb);
			graph.A[sa][sb]=1;
			graph.A[sb][sa]=1;
			nbArete--;
		}
		fclose(f);
	}else {
		fclose(f);
		perror("Le nombre de arete est trop grand\n");
		exit(0);
	}
	return graph;
}

//Calcul d'une zone vide maximal à partir d'un graphe
void zone_vide_maximal (GRAPHEMAT g, SOMMET zv_maximal[], int liste[])
{
	int i,j;
	for(i=0;i<g.n;i++){
		zv_maximal[i]=0;
	}
	SOMMET liste_sommet[g.n];
		for(i=0;i<g.n;i++){
		liste_sommet[i]=1;
	}
	for (i=0;i<g.n;i++){
		if (liste_sommet[liste[i]]==1)
		{
			zv_maximal[liste[i]]=1;
			for(j=0;j<g.n;j++)
			{
				if (g.A[liste[i]][liste[j]]==1)
				{
					liste_sommet[liste[j]]=0;
				}
			}
		}
	}
}

//Crée toutes les listes d'ordre de parcours de sommet puis lance 
//zone_vide_maximal avec cette liste et retourne la liste avec le plus
//de sommets
void  combinaison (GRAPHEMAT g, int rank, int element[], int liste [], SOMMET zv_maximum[]){
	int i,nombre_sommet, nombre_sommet_temp;
	SOMMET zv_maximum_temp[g.n];
	//si la liste est rempli
	if (rank >= g.n){
		nombre_sommet=0;
		nombre_sommet_temp=0;
		zone_vide_maximal(g,zv_maximum_temp,liste);
		//compte le nombre de sommet
		for(i=0;i<g.n;i++){
			if (zv_maximum[i]){
			nombre_sommet++;
			}
			if (zv_maximum_temp[i]){
			nombre_sommet_temp++;
			}
		}
		//La nouvelle zone vide maximal a plus de sommet que l'ancienne
		//ca devient la nouvelle maximum
		if (nombre_sommet_temp>nombre_sommet){
			for (i=0;i<g.n;i++){
				zv_maximum[liste[i]]=zv_maximum_temp[liste[i]];
			}
		}
		return;
		
	}
	//remplissage de la liste d'ordre de parcours de sommet
	for (i=0; i<g.n;i++){
		if (!element[i]){
			element[i]=1;
			liste[rank]=i;
			combinaison(g, rank+1, element, liste,zv_maximum);
			element[i]=0;
		}
	}
	
}

//Calcul de la zone vide maximum
void zone_vide_maximum (GRAPHEMAT g, SOMMET * zv_maximum){
	int element [g.n];
	int liste [g.n];
	int i;
	for (i=0;i<g.n;i++){
		element[i]=0;
	}
	combinaison(g,0,element,liste,zv_maximum);
	
}

//Calcul de la zone vide maximum, de la zone vide maximal et du temps d'execution
//en fonction d'une matrice d'adjacence et du nombre de sommet
void calcul_zv_maximum_maximal(GRAPHEMAT graph, int n){
	int liste[NMAX];
	float temps;
	clock_t t1,t2;
	printf("Pour n=%d\n",n);
	graph.n=n;
	printf("Matrice du graphe\n");
	print_tableau(graph.A, graph.n);
	SOMMET zone_vide[NMAX];
	creer_liste(liste, graph.n);
	t1 = clock();
	zone_vide_maximal(graph,zone_vide, liste);
	t2 = clock();
	printf("Zone vide maximal\n");
	print_tab_sommet(zone_vide,graph.n);
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	printf("Temps d'execution de zone vide maximal : %f\n",temps);
	t1 = clock();
	zone_vide_maximum(graph,zone_vide);
	t2 = clock();
	printf("Zone vide maximum\n");
	print_tab_sommet(zone_vide,graph.n);
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	printf("Temps d'execution de zone vide maximum : %f\n",temps);
	printf("\n");
}
int main(){
	GRAPHEMAT graph;
	graph=creer_graph();
	calcul_zv_maximum_maximal(graph,5);
	calcul_zv_maximum_maximal(graph,6);
	calcul_zv_maximum_maximal(graph,7);
	calcul_zv_maximum_maximal(graph,8);
	calcul_zv_maximum_maximal(graph,9);
	calcul_zv_maximum_maximal(graph,10);
	//calcul_zv_maximum_maximal(graph,11);
	//calcul_zv_maximum_maximal(graph,12);
	return 0;
}
	
