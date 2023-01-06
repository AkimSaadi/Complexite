# Simulation de MTD

Le code source fourni (écrit en java) permet de simuler une Machine de Turing Déterministe (MTD). La MTD prend en entrée un mot (inscrit sur une bande de lecture) et un programme pour MTD.

## Installation

L'installation repose principalement sur l'execution des fichiers TuringMachine.java et fonctionDeTransition.java, à l'aide des commandes suivantes depuis un terminal :

```shell
$ javac *.java
$ java TuringMachine
```

## Utilisation

A l'execution, le programme affiche le nom de deux programmes de MTD ainsi que leur description. Il est ensuite demandé à l'utilisateur de choisir un programme pour MTD (faire attention à la syntaxe), puis d'indiquer le mot à traiter par la MTD.

Il est possible d'ajouter des programmes pour MTD en modifiant le fichier fonctionDeTransition.java. Il suffit d'y ajouter une méthode (écrite en java) correspondant à la fonction de transition voulue, et de modifier programmePourMTD() en conséquence. Un exemple est laissé en commentaire dans le fichier.

Il est possible d'ajouter le nom de votre programme à la liste affichée à l'execution par la console, pour cela il suffit d'ajouter un print dans le main (un exemple est laissé en commentaire également).
