
def zone_vide_maximal (g, zv_maximal, liste) :
        for i in range (len(g)) :
            zv_maximal[i]=0 #initialisation de la zone vide maximal
        liste_sommet = []
        for i in range (len(g)) :
            liste_sommet.append(1) #initialisation de la liste de sommet disponible
        for i in range (len(g)) :
            if (liste_sommet[liste[i]]==1) : #si un sommet est disponible
                zv_maximal[liste[i]]=1 #on l'ajoute à la zone vide maximal
                for j in range (len(g)) :
                    if (g[liste[i]][liste[j]]==1) :
                        liste_sommet[liste[j]]=0 #on supprime les voisins du sommet choisi de la liste des sommets disponible
            
        
    

def  combinaison (graph, rank, element, liste, zv_maximum) :
    zv_maximum_temp = []
    for i in range (len(graph)) :
         zv_maximum_temp.append(0)
    if (rank >= len(graph)): #si la liste d'ordre de parcours de sommet est remplie
        nombre_sommet=0;
        nombre_sommet_temp=0;
        zone_vide_maximal(graph,zv_maximum_temp,liste)
        for i in range (len(graph)) :
            if (zv_maximum[i]) :
                 nombre_sommet+=1 #Compte le nombre de sommet de la zone vide maximum actuel
            if (zv_maximum_temp[i]) :
                 nombre_sommet_temp+=1 #Compte le nombre de sommet de la zone vide maximal calculé
        if (nombre_sommet_temp>nombre_sommet) : #Si la zone vide maximal calculé à plus de sommet que la zone vide maximum actuel, ça devient la zone vide maximum actuel
            for i in range (len(graph)) :
                zv_maximum[liste[i]]=zv_maximum_temp[liste[i]];
        return
        
    
    for i in range (len(graph)) : #remplissage de la liste d'ordre de parcours de sommet
        if (not element[i]) :
            element[i]=1 #enleve un sommet des elements disponibles
            liste[rank]=i #l'ajoute à la liste
            combinaison(graph, rank+1, element, liste,zv_maximum) #relance combinaison avec une nouvelle liste
            element[i]=0 #remet un sommet dans les elements disponibles
        
    
    

def zone_vide_maximum (graph,zv_maximum):
    element = []
    liste = []
    for i in range (len(graph)) :
        element.append(0)
        liste.append(0)
    combinaison (graph,0,element,liste,zv_maximum);
    
def Zone_Vide_vers_SAT (graph,zone_vide) :
    fichier = open("clausezonevide.txt","w")
    fichier.write("p cnf 5 20\n")
    #Ici pour k=3, on oblige le SAT à avoir au moins 3 variables positifs
    fichier.write ("1 2 3 0\n1 2 4 0\n1 2 5 0\n1 3 4 0\n1 3 5 0\n1 4 5 0\n")
    fichier.write ("2 3 4 0\n2 3 5 0\n2 4 5 0\n3 4 5 0\n1 2 3 4 0\n1 2 3 5 0\n")
    fichier.write ("1 2 4 5 0\n1 3 4 5 0\n2 3 4 5 0\n1 2 3 4 5 0\n")
    for i in range (len(graph)):
        if zone_vide[i] ==1 :
             for j in range (len(graph)) :
                    if (graph[i][j]==1) :
                        #Ici, on empeche que deux variable représentant des
                        #noeuds adjacents aient la même affectation
                        fichier.write('-'+str(i+1)+ ' ' +'-'+str(j+1)+' 0\n')
    fichier.close()
        
    
    
graph = [[0,1,0,0,0],[1,0,1,1,0],[0,1,0,1,0],[0,1,1,0,1],[0,0,0,1,0]]
zv_maximum = []
for i in range (len(graph)) :
    zv_maximum.append(0)
zone_vide_maximum(graph, zv_maximum)
Zone_Vide_vers_SAT(graph, zv_maximum)