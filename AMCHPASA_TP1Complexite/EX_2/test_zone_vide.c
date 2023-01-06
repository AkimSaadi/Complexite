#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NMAX 30

typedef int SOMMET;

typedef struct { int A[NMAX][NMAX];
				 int n;
}GRAPHEMAT;

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

void print_tab_sommet(SOMMET ssg[], int n)
{
	int i;
	for (i=0;i<n;i++)
	{
		printf("%d ",ssg[i]);
	}
	printf("\n");
}

int zone_vide(GRAPHEMAT g, SOMMET sommetsg[]){
	int i,j;
	for(i=0;i<g.n;i++){
		if (sommetsg[i]==1){
			for (j=0;j<g.n;j++){
				if (sommetsg[j]==1){
					if (g.A[i][j]==1){
						return 0;
					}
				}
			}
		}
	}
	return 1;
}
GRAPHEMAT creer_graph(char * nom_graph)
{
FILE *f;
	int i, nbArete, sa, sb;
	GRAPHEMAT graph;
	f=fopen("graphe.txt","w+");
	if (!(strcmp("graph",nom_graph))){
		fputs("8\n",f);
		fputs("8\n",f);
		for(i=0;i<8;i++){
		fprintf(f,"0 %d\n",i+1);
		}
	}
	else if (!(strcmp("graph1",nom_graph))){
		fputs("4\n",f);
		fputs("4\n",f);
		for(i=0;i<4;i++){
		fprintf(f,"%d %d\n",i,i+1);
		}
	}
	else if (!(strcmp("graph2",nom_graph))){
		fputs("5\n",f);
		fputs("5\n",f);
		for(i=0;i<3;i++){
		fprintf(f,"%d %d\n",i,i+1);
		}
		fputs("1 3\n",f);
		fputs("3 4\n",f);
	}
	else if (!(strcmp("graph3",nom_graph))){
		fputs("8\n",f);
		fputs("12\n",f);
		for(i=0;i<4;i++){
			if (i<3){
			fprintf(f,"%d %d\n",i,i+1);
			fprintf(f,"%d %d\n",i+4,i+5);}
			fprintf(f,"%d %d\n",i,i+4);
		}
		fputs("3 1\n",f);
		fputs("4 7\n",f);
	}
	else if (!(strcmp("graph4",nom_graph))){
		fputs("6\n",f);
		fputs("8\n",f);
		fputs("0 1\n",f);
		fputs("0 2\n",f);
		fputs("1 3\n",f);
		fputs("1 4\n",f);
		fputs("2 3\n",f);
		fputs("2 5\n",f);
		fputs("3 5\n",f);
		fputs("3 4\n",f);
	}
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


void creer_zone_vide(SOMMET * zone_vide, int n, char * nom_graph){
	int i;
	if (!(strcmp("graph",nom_graph))){
		for (i=0;i<n;i++){
			if (i==0){
				zone_vide[i]=0;
			}
			else{
				zone_vide[i]=1;
			}
		}
	}
	else if (!(strcmp("graph1",nom_graph))){
		for (i=0;i<n;i++){
			if (i%2==0){
				zone_vide[i]=0;
			}
			else{
				zone_vide[i]=1;
			}
		}
	}
	else if (!(strcmp("graph2",nom_graph))){
		for (i=0;i<n;i++){
			if (i==0||i==2||i==4){
				zone_vide[i]=1;
			}
			else{
				zone_vide[i]=0;
			}
		}
	}
	else if (!(strcmp("graph3",nom_graph))){
		for (i=0;i<n;i++){
			if (i==0||i==2||i==5||i==7){
				zone_vide[i]=1;
			}
			else{
				zone_vide[i]=0;
			}
		}
	}
	else if (!(strcmp("graph4",nom_graph))){
		for (i=0;i<n;i++){
			if (i==0||i==4||i==5){
				zone_vide[i]=1;
			}
			else{
				zone_vide[i]=0;
			}
		}
	}	
}

void creer_zone_non_vide(SOMMET * zone_vide, int n, char * nom_graph){
	int i;
	if (!strcmp("graph",nom_graph)){
		for (i=0;i<n;i++){
			if (i%2==0){
				zone_vide[i]=1;
			}
			else{
				zone_vide[i]=0;
			}
		}	
	}
	else if (!strcmp("graph1",nom_graph)){
		for (i=0;i<n;i++){
			if (i>0){
				zone_vide[i]=1;
			}
			else{
				zone_vide[i]=0;
			}
		}	
	}
	else if (!strcmp("graph2",nom_graph)){
		for (i=0;i<n;i++){
			if (i==0||i==1||i==2){
				zone_vide[i]=1;
			}
			else{
				zone_vide[i]=0;
			}
		}	
	}
	else if (!(strcmp("graph3",nom_graph))){
		for (i=0;i<n;i++){
			if (i<4){
				zone_vide[i]=1;
			}
			else{
				zone_vide[i]=0;
			}
		}
	}
	else if (!(strcmp("graph4",nom_graph))){
		for (i=0;i<n;i++){
			if (i==0||i==1||i==2||i==3){
				zone_vide[i]=1;
			}
			else{
				zone_vide[i]=0;
			}
		}
	}	
}
void est_une_zone_vide(GRAPHEMAT g, SOMMET * sg){
	if (zone_vide(g,sg)){
		print_tab_sommet(sg,g.n);
		printf("est une zone vide du graph\n");
	}
	else{
		print_tab_sommet(sg,g.n);
		printf("n'est pas une zone vide du graph\n\n");
	}
}
int main(){
	GRAPHEMAT graph;
	graph=creer_graph("graph");
	printf("Matrice du graphe\n");
	print_tableau(graph.A,graph.n);
	SOMMET zone_vide[graph.n];
	SOMMET zone_non_vide[graph.n];
	creer_zone_vide(zone_vide,graph.n,"graph");
	est_une_zone_vide(graph,zone_vide);
	creer_zone_non_vide(zone_non_vide,graph.n,"graph");
	est_une_zone_vide(graph,zone_non_vide );
	
	/* ci-apres differents exemples de graphe pouvant etre testes
	
	graph=creer_graph("graph1");
	printf("Matrice du graphe 1\n");
	print_tableau(graph.A,graph.n);
	creer_zone_vide(zone_vide,graph.n,"graph1");
	est_une_zone_vide(graph,zone_vide);
	creer_zone_non_vide(zone_non_vide,graph.n,"graph1");
	est_une_zone_vide(graph,zone_non_vide );
	
	graph=creer_graph("graph2");
	printf("Matrice du graphe 2\n");
	print_tableau(graph.A,graph.n);
	creer_zone_vide(zone_vide,graph.n,"graph2");
	est_une_zone_vide(graph,zone_vide);
	creer_zone_non_vide(zone_non_vide,graph.n,"graph2");
	est_une_zone_vide(graph,zone_non_vide );
	
	graph=creer_graph("graph3");
	printf("Matrice du graphe 3\n");
	print_tableau(graph.A,graph.n);
	creer_zone_vide(zone_vide,graph.n,"graph3");
	est_une_zone_vide(graph,zone_vide);
	creer_zone_non_vide(zone_non_vide,graph.n,"graph3");
	est_une_zone_vide(graph,zone_non_vide );
	
	graph=creer_graph("graph4");
	printf("Matrice du graphe 4\n");
	print_tableau(graph.A,graph.n);
	creer_zone_vide(zone_vide,graph.n,"graph4");
	est_une_zone_vide(graph,zone_vide);
	creer_zone_non_vide(zone_non_vide,graph.n,"graph4");
	est_une_zone_vide(graph,zone_non_vide ); */
	
	remove("graphe.txt");
return 0;
}
