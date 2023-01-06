#include <stdio.h>
#include <stdlib.h>

#define NMAX 30

typedef int SOMMET;

typedef struct { int A[NMAX][NMAX];
				 int n;
}GRAPHEMAT;

int zone_vide(GRAPHEMAT g, SOMMET sommetsg[]){
	int i,j;
	for(i=0;i<g.n;i++){
		if (sommetsg[i]==1){
			for (j=0;j<g.n;j++){
				if (sommetsg[j]==1){
					if (g.A[i][j]==1){//Le programme test si deux sommets du sous graphe sont voisins
						return 0;
					}
				}
			}
		}
	}
	return 1;
}

void zone_vide_maximal (GRAPHEMAT g, SOMMET zv_maximal[], int liste[])
{
	int i,j;
	for(i=0;i<g.n;i++){
		zv_maximal[i]=0; //initialisation de la zone vide maximal
	}
	SOMMET liste_sommet[g.n];
		for(i=0;i<g.n;i++){
		liste_sommet[i]=1; //initialisation de la liste de sommet disponible
	}
	for (i=0;i<g.n;i++){
		if (liste_sommet[liste[i]]==1)//si un sommet est disponible
		{
			zv_maximal[liste[i]]=1; //on l'ajoute à la zone vide maximal
			for(j=0;j<g.n;j++)
			{
				if (g.A[liste[i]][liste[j]]==1)
				{
					liste_sommet[liste[j]]=0; //on supprime les voisins du sommet choisi de la liste des sommets disponible
				}
			}
		}
	}
}

void print_liste(int ssg[], int n)
{
	int i;
	for (i=0;i<n;i++)
	{
		printf("%d ",ssg[i]);
	}
	printf("\n");
}

void  combinaison (GRAPHEMAT g, int rank, int element[], int liste [], SOMMET zv_maximum[]){
	int i,nombre_sommet, nombre_sommet_temp;
	SOMMET zv_maximum_temp[g.n];
	if (rank >= g.n){ //si la liste d'ordre de parcours de sommet est remplie
		nombre_sommet=0;
		nombre_sommet_temp=0;
		zone_vide_maximal(g,zv_maximum_temp,liste);
		for(i=0;i<g.n;i++){
			if (zv_maximum[i]){
			nombre_sommet++;//Compte le nombre de sommet de la zone vide maximum actuel
			}
			if (zv_maximum_temp[i]){
			nombre_sommet_temp++;//Compte le nombre de sommet de la zone vide maximal calculé
			}
		}
		if (nombre_sommet_temp>nombre_sommet){//Si la zone vide maximal calculé à plus de sommet que la zone vide maximum actuel, ça devient la zone vide maximum actuel
			for (i=0;i<g.n;i++){
				zv_maximum[liste[i]]=zv_maximum_temp[liste[i]];
			}
		}
		return;
		
	}
	for (i=0; i<g.n;i++){//remplissage de la liste d'ordre de parcours de sommet
		if (!element[i]){
			element[i]=1;//enleve un sommet des elements disponibles
			liste[rank]=i;//l'ajoute à la liste
			combinaison(g, rank+1, element, liste,zv_maximum);//relance combinaison avec une nouvelle liste
			element[i]=0;//remet un sommet dans les elements disponibles
		}
	}
	
}
	
void zone_vide_maximum (GRAPHEMAT g, SOMMET * zv_maximum){
	int element [g.n];
	int liste [g.n];
	int i;
	for (i=0;i<g.n;i++){
		element[i]=0;//initialisation de la liste de sommets disponible
	}
	combinaison(g,0,element,liste,zv_maximum);
	
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

//Lecture du fichier graph et initialisation de GRAPHEMAT
GRAPHEMAT litGraphe (char *adr)
{
	FILE *f;
	GRAPHEMAT graph;
	int sa,sb,nbArete;
	f=fopen(adr,"r");
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

//Test si un sous ensemble de sommet est une zone vide
void est_une_zone_vide(GRAPHEMAT g, SOMMET * sg){
	if (zone_vide(g,sg)){
		print_tab_sommet(sg,g.n);
		printf("est une zone vide du graphe\n");
	}
	else{
		print_tab_sommet(sg,g.n);
		printf("n'est pas une zone vide du graphe\n\n");
	}
}

//Creer une zone non vide
void creer_zone_non_vide(SOMMET * zone_vide, int n){
	int i;
	for (i=0;i<n;i++){
		if (i<3){
			zone_vide[i]=1;
		}
		else {
			zone_vide[i]=0;
		}
	}
}

//Creer une zone vide
void creer_zone_vide(SOMMET * zone_vide, int n){
	int i;
	for (i=0;i<n;i++){
		if (i==0){
			zone_vide[i]=1;
		}
		else {
			zone_vide[i]=0;
		}
	}
}

int main(){
	int i;
	GRAPHEMAT graph;
	graph=litGraphe("./graph.txt");
	printf("Matrice du graphe\n");
	int liste[graph.n];
	print_tableau(graph.A, graph.n);
	SOMMET zv_maximum[graph.n];
	SOMMET zone_vide[graph.n];
	SOMMET zone_non_vide[graph.n];
	creer_zone_vide(zone_vide,graph.n);
	creer_zone_non_vide(zone_non_vide,graph.n);
	est_une_zone_vide(graph,zone_vide);
	est_une_zone_vide(graph,zone_non_vide);
	for(i=0;i<graph.n;i++){
		liste[i]=i;
	}
	zone_vide_maximal(graph,zv_maximum,liste);
	printf("Zone vide maximal :\n");
	print_tab_sommet(zv_maximum,graph.n);
	zone_vide_maximum(graph, zv_maximum);
	printf("Zone vide maximum :\n");
	print_tab_sommet(zv_maximum,graph.n);
	return 0;
}
