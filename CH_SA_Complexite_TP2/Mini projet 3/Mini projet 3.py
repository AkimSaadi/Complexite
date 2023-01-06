def Sudoku_to_SAT(tab) :
    fichier = open("clausesudoku.txt","w")
    n = len(tab)
    fichier.write("p cnf 729 11906\n")
    for i in range (n) :
        for j in range (n) :
            for l in range (1,n+1) :
                for m in range(1,n+1) :
                    if m > l :
                        #Chaque case contient au plus une fois chaque nombre
                        fichier.write('-'+str(i)+str(j)+str(l)+ ' ')
                        fichier.write('-'+str(i)+str(j)+str(m)+ ' ')
                        fichier.write("0\n")
            
    for q in range (n) :
        for p in range (1,n+1):
            for o in range (n) :
                #Chaque ligne contient au moins une fois chaque nombre
                fichier.write(str(q)+str(o)+str(p)+ ' ')
            fichier.write("0\n")
            for r in range (n) :
                #Chaque colonne contient au moins une fois chaque nombre
                fichier.write(str(r)+str(q)+str(p)+ ' ')
            fichier.write("0\n")

    for u in range (n) :
        for v in range(1,n+1) :
            for w in range(n) :
                for x in range(n):
                    if x > w :
                        #Chaque ligne contient au plus une fois chaque nombre
                        fichier.write('-'+str(u)+str(w)+str(v)+ ' ')
                        fichier.write('-'+str(u)+str(x)+str(v)+ ' ')
                        fichier.write("0\n")
                        #Chaque colonne contient au plus une fois chaque nombre
                        fichier.write('-'+str(x)+str(u)+str(v)+ ' ')
                        fichier.write('-'+str(w)+str(u)+str(v)+ ' ')
                        fichier.write("0\n")


    #Chaque region contient au moins une fois chaque nombre
    for r in range (int(n**0.5)) :
        for s in range (int(n**0.5)) :
            for w in range(1,n+1) :
                for t in range (r*3,(r*3)+int(n**0.5)) :
                    for u in range (s*3,(s*3)+int(n**0.5)) :
                        fichier.write(str(t)+str(u)+str(w)+ ' ')
                fichier.write("0\n")
                    #Chaque region contient au plus une fois chaque nombre
                for t in range (r*3,(r*3)+int(n**0.5)) :
                    for u in range (s*3,(s*3)+int(n**0.5)) :
                        for v in range (r*3,(r*3)+int(n**0.5)) :
                            for x in range (s*3,(s*3)+int(n**0.5)) :
                                if v*10+x > t*10 + u :
                                    fichier.write('-'+str(t)+str(u)+str(w)+ ' ')
                                    fichier.write('-'+str(v)+str(x)+str(w)+ ' ')
                                    fichier.write("0\n")
    
    #Littéral unitaire pour les valeurs déja connu
    for i in range (n) :
       for j in range (n) :
           if tab[i][j] != 0 :
               fichier.write(str(i)+str(j)+str(tab[i][j])+ ' 0\n')

    fichier.close()


tab = [[0,3,7,0,1,4,0,2,5],
       [5,1,0,0,2,0,8,3,7],
       [8,0,0,3,0,5,0,4,9],
       [4,0,5,1,8,0,2,0,0],
       [1,0,8,5,0,0,7,9,4],
       [3,7,0,9,0,0,5,1,8],
       [7,0,0,2,0,1,4,5,6],
       [2,4,3,0,5,0,0,0,1],
       [6,0,1,0,9,0,3,7,2]]
Sudoku_to_SAT(tab)