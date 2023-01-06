//creation d'une classe qui centralise les fonctions de transition des programmes pour MTD
class fonctionDeTransition {
    private static String programmeChoisi;

    public fonctionDeTransition(String programmeChoisi) {
        this.programmeChoisi = programmeChoisi;
    }

    //cette methode permet d'appeler les fonctions de transition, qui sont des méthodes individuelles
    static void programmePourMTD(bandeDeLecture bande) {

        if (programmeChoisi.equals("mot_xy")) {
            mot_xy(bande);
        }

        else if (programmeChoisi.equals("mot_palindrome")) {
            mot_palindrome(bande);
        }

        //si vous voulez ajouter d'autres programmes pour MTD, il suffit d'indiquer le nom de votre programme ici
        //et de creer la methode correspondante, voir plus bas
        else if (programmeChoisi.equals("votreProgramme")) {
            //votreProgramme(bande);
        }

        else {
            System.out.println("ERREUR: Veuillez entrer un nom de programme pour MTD valide.");
            return;
        }

    }

    //la premiere fonction reconnait les mots de forme x^ny^n
    static boolean mot_xy(bandeDeLecture bande) {
        int n = bande.ruban.size();
        int cx = 0;
        int cy = 0;

        while (bande.ruban.get(bande.case_courante).equals("x")) {
            cx++;
            if (bande.case_courante == n - 1) {
                break;
            }
            bande.avancer();
        }
        while (bande.ruban.get(bande.case_courante).equals("y")) {
            cy++;
            if (bande.case_courante == n - 1) {
                break;
            }
            bande.avancer(); //si on le met avant le if, ça marche pas
        }
        if (n == 0 | bande.ruban.get(0).equals("B")) {
            System.out.println("Le mot est rejeté.");
            return false;
        } else if ((bande.case_courante < n & bande.ruban.get(bande.case_courante).equals("B")) |
                bande.case_courante == n - 1) {
            if (cx == cy) {
                System.out.println("Le mot est accepté.");
                return true;
            } else if (!(cx == cy)) {
                System.out.println("Le mot est rejeté.");
                return false;
            }
        } else {
            System.out.println("Le mot est rejeté.");
            return false;
        } return false;
    }

    //la seconde fonction reconnait les mots palindromiques
    static boolean mot_palindrome(bandeDeLecture bande){
        while (bande.ruban.size() != 0) {
            bande.case_courante = 0;
            String lettre = bande.ruban.get(bande.case_courante);

            while (bande.case_courante < bande.ruban.size()) {
                if (bande.case_courante == bande.ruban.size() - 1) {
                    break;
                }
                bande.avancer();
            }
            if (bande.ruban.get(bande.case_courante).equals(lettre)) {
                if (bande.case_courante == 0) {
                    bande.effacer(0);
                } else {
                    bande.effacer(bande.case_courante);
                    bande.effacer(0);
                }
            } else {
                System.out.println("Le mot est rejeté.");
                return false;
            }
        }
        System.out.println("Le mot est accepté.");
        return true;
    }

    //c'est ici que vous pouvez ajouter d'autres fonctions de transition
}
