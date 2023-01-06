class SAT :

    def __init__(self,nom_fichier) :
       fichier = open(nom_fichier, "r")
       caractere = fichier.read().split()
       fichier.close()
       self.liste_clause = []
       for i,c in enumerate(caractere) :
           if (i != 0 and i != 1) :
               if (i==2) :
                   self.nombre_literal = int(c)
               elif (i==3) :
                   self.nombre_clause = int(c)
                   clause = []
               elif (c=='0'):
                   self.liste_clause.append(clause)
                   clause = []
               else:
                   clause.append(int(c))
        
    def add_affectation(self,nom_fichier) :
        fichier = open(nom_fichier,"r")
        affectation = fichier.read().split()
        fichier.close()
        self.affectation= list(map(int, affectation))
        print("Les affectations sont ",self.affectation)
    
    def print_clauses(self) :
        for i,clause in enumerate(self.liste_clause) :
            print('La clause ',i+1,' est : ',end=' ')
            for literal in clause :
                print (literal,end=' ')
            print('\n',end='')
            
    def print_nombre_clause (self) :
        print('Il y a ', self.nombre_clause, ' clause(s)')
        
    def print_nombre_literal (self) :
        print('Il y a ',self.nombre_literal,' literal(s)')

    @staticmethod
    def clause_is_false (clause) :
        for i in range (len(clause)) :
            if clause[i] != False:
                return False
        return True
    
    def is_sat(self) :
        for literal in self.affectation :
            for clause in self.liste_clause :
                changer_close=False
                if (clause != True) :
                    for literal_clause in clause :
                        if(changer_close==False) :
                            if literal_clause == literal :
                                self.liste_clause[self.liste_clause.index(clause)]=True
                                changer_close = True
                            elif (-1 * literal_clause == literal) :
                                clause[clause.index(literal_clause)]=False
                                if (SAT.clause_is_false(clause)) :
                                    print("La probléme SAT n'est pas satisfiable.")
                                    return False
        print(self.nombre_clause)
        for i in range (self.nombre_clause) :
            if self.liste_clause[i] != True:
                print("La probléme SAT n'est pas satisfiable.")
                return False
        print("La probléme SAT est satisfiable.")
        return True

sat1 = SAT('clause.txt')
sat1.add_affectation('affectation.txt')
sat1.is_sat()    