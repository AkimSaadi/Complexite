import java.util.ArrayList;
import java.util.Scanner;

//creation d'une classe bande de lecture
class bandeDeLecture {
    private int taille; //taille du ruban
    public int case_courante; //represente la position de la tete de lecture
    public ArrayList<String> ruban; //represente le ruban de travail
    public String beta = "B"; //case blanche, ou beta

    public bandeDeLecture (int taille) {
        this.taille = taille;
        case_courante = 0;
        ruban = new ArrayList<String>(taille);
        for (int i=0; i<taille; i++){
            ruban.add("0");
        }
    }

    //on cree les fonctions de base liees a la tete de lecture: avancer, reculer, effacer
    //avancer() decale la tete de lecture d'une case vers la droite
    public String avancer() {
        //si on est en dehors du ruban, on arrete d'avancer
        if (case_courante >= taille - 1) {
            return this.ruban.get(case_courante);
        } else {
            case_courante++;
            return this.ruban.get(case_courante);
        }
    }

    //reculer() decale la tete de lecture d'une case vers la gauche
    public String reculer() {
        //si on est en dehors du ruban, on arrete de reculer
        if (case_courante <= -1) {
            return this.ruban.get(case_courante);
        } else {
            case_courante--;
            return this.ruban.get(case_courante);
        }
    }

    //efface la case d'indice case_courante, ie. pointee par la tete de lecture
    public void effacer(int case_courante) {
        ruban.remove(case_courante);
    }
}

//creation d'une classe qui represente la MTD
//elle recoit un mot (sur une bande de lecture) et une fonction de transition en entrées
class MTD {
    private bandeDeLecture bande;
    private bandeDeLecture bandeDeTravail;
    private fonctionDeTransition fonction;

    public MTD(bandeDeLecture bande, fonctionDeTransition fonction) {
        this.bande = bande;
        this.fonction = fonction;
    }

    void lireRuban() {
        //on copie d'abord le contenu du ruban d'entree sur le ruban de travail
        bandeDeTravail = new bandeDeLecture(bande.ruban.size());
        for (int j = 0; j < bandeDeTravail.ruban.size(); j++){
            bandeDeTravail.ruban.set(j, bandeDeTravail.beta);
        }
        for (int i =0; i<bande.ruban.size(); i++){
            bandeDeTravail.ruban.set(i, bande.ruban.get(i));
        }

        //la machine réalise ensuite le traitement du mot depuis son ruban de travail
        fonction.programmePourMTD(bandeDeTravail);
    }
}

//creation du main, ou sont instancies les objets MTD et bandeDEntree
//le programme ainsi que le mot sont choisis par l'utilisateur depuis la console
public class TuringMachine{
    public static void main(String[] args) {

        //choix du programme pour MTD par l'utilisateur
        Scanner prg = new Scanner(System.in);
        System.out.println("Les programmes pour MTD disponibles sont :");
        System.out.println("mot_palindrome : reconnait les mots palindromiques");
        System.out.println("mot_xy : reconnait les mots de forme x^ny^n");
        //System.out.println("votreProgramme : description de votre programme pour MTD");
        System.out.println("Entrez le nom du programme pour MTD choisi :");
        String prgInput = prg.nextLine();
        fonctionDeTransition programmeChoisi = new fonctionDeTransition(prgInput);

        //choix du mot a traiter par l'utilisateur
        Scanner mot = new Scanner(System.in);
        System.out.println("Entrez le mot devant être traité :");
        String motInput = prg.nextLine();
        //on transforme le mot en liste de caractères
        ArrayList<Character> lettres = convertStringToCharList(motInput);
        bandeDeLecture bandeDEntree = new bandeDeLecture(motInput.length());

        //on ecrit le mot sur le ruban d'entree
        for (int i =0; i<bandeDEntree.ruban.size(); i++){
            bandeDEntree.ruban.set(i, String.valueOf(lettres.get(i)));
        }

        //traitement du mot par la MTD, avec le programme choisi
        MTD mtd = new MTD(bandeDEntree, programmeChoisi);
        mtd.lireRuban();

    }

    //creation d'une methode pour convertir un mot en une liste de caracteres
    public static ArrayList<Character> convertStringToCharList(String mot) {
        ArrayList<Character> lettres = new ArrayList<>();

        for (char lettre : mot.toCharArray()) {
            lettres.add(lettre);
        }
        return lettres;
    }
}











