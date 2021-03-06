### Vincent DAO
### INFO 1 Semestre 1
# **Portfolio**
## Introduction
---

J’ai choisi de ne pas suivre le fil rouge car je ne connaissais pas vraiment malloc mais je
connaissais déjà des bases rudimentaires du C. J’ai donc fait le TP malloc après quelques TPs.

Source d’aide en cas de difficultés : M. Borie, le cours, internet

Vous trouverez [mon github avec les projets ainsi que ce même document ici](https://github.com/daovincent/ESIPE/tree/main/C) (Document que je conseille de lire sur github plutôt qu'en pdf)

[Les sujets des TP ici](http://igm.univ-mlv.fr/~borie/ressources_info1.php)

[Les grilles d'évaluation pour les différents TP ici](http://igm.univ-mlv.fr/~borie/projet_info1.php)


## Table des matières
[Introduction](#Introduction)

[Les TP réalisés : ](#Les-TP-réalisés)

[TP2](#TP2-Premiers-programmes)

["Deviner un entier secret"](#Projet-Deviner-un-entier-secret)

[TP3](#TP3-Dautres-programmes)

[TP5](#TP5-Tableaux-dentiers)

[TP8](#TP8-Challenge-Syracuse)

[TP9](#TP9-Exercices-avec-malloc)

[TP10](#TP-10-tri-multicritères)

[Total points accumulés](#Total-points-accumulés)
    

## Les TP réalisés
---
TP 2, TP 3 (en partie), TP 9, une partie du TP 10

## TP2, Premiers programmes
---
Ce tp m'a servi de rappel pour des bases de C, que je n'avais pas utilisé depuis très longtemps.

### Ex1 :
Pas de difficultés pour afficher hello world

### Ex2:
Difficultés rencontrées :
scanf : ne fonctionnait pas correctement avec plusieurs appels consécutifs
Solution : en ajoutant un espace avant “ %d” dans la fonction. (partie commentée dû à la suite
de l’exercice.
Saisie sécurisée : en cas de “mauvais input” de la part de l’utilisateur, le programme qui donnait
des résultats incorrects ou des problèmes.
Solution : utiliser la variable errno, avec la fonction strtol pour pouvoir discerner les cas
différents
→ si l’input ne contient pas de nombres
→ si l’input a un nombre suivi d’autres caractères, cas dans lequel le chiffre sera pris en compte
mais pas le reste de la chaine de caractère.
→ Underflow / Overflow détectés
Pour chaque erreur, le programme renvoie la nature de l’erreur puis termine le programme.

Ce que j’ai appris :
Faire une saisie sécurisée qui détecte les différents inputs incorrects.
Critique réflexive des choix faits :
La saisie sécurisée n’était pas demandée, du coup j’ai pris du temps en plus pour faire des tests
avec différentes fonctions (atoi, atol…) et en utilisant gets au lieu de scanf.
Faire une fonction pour évaluer chaque input aurait été + efficace que de faire un copié collé
pour les 2 inputs, ce qui n’est pas spécialement dérangeant pour 2 inputs mais aurait pu l’être
s’il y avait besoin de + d’inputs.
Terminer le programme (return 0) en cas de mauvais input est peut être un peu overkill,
enchainer avec un scanf/gets + passer par la fonction de vérification de saisie (qui n’a pas été
faite du coup) aurait pu être + efficace.

### Ex3 : 
Critique réflexive des choix faits :
Il faut toujours indiquer l’argument dans la ligne de commande avec l’exécution du programme.

### Ex5 :
Difficultés rencontrées :
Je n’étais pas familier avec les manipulations de fichier (fopen etc).
Assez rarement, avec l’exécution du programme un caractère spécial s’affiche tout à la fin, mais
je n’ai pas trouvé d’où venait le problème et je n’ai pas non plus réussi à le reproduire.
Sinon, le programme fonctionne correctement.

| Projet | Pts | I/0 | Type | Progr | Module | Compil | Récursion | Tableaux | Pointeurs | Structures | Allocation | Fichier | Bit à bit | Fct Pointer | Biblio |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| TP2 | 6 | 1 | 1 | 1 | | 1 | 1 | | | | | 1 | | 

## Projet Deviner un entier secret
---
L'utilisateur entre un entier positif pour le max du nombre qu'il faudra trouver.
Ensuite, il essaie de trouver le nombre qui a été généré aléatoirement.
J'ai juste ajouté une fonction supplémentaire pour qu'il puisse abandonner.

| Projet | Pts | I/0 | Type | Progr | Module | Compil | Récursion | Tableaux | Pointeurs | Structures | Allocation | Fichier | Bit à bit | Fct Pointer | Biblio |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Deviner Entier Secret | 4 | 1 | 1 | 1 | | 1 |  | | | | |  | | 

## TP3, D’autres programmes
---
Toujours sur des bases, je n'ai pas fait l'exercice 2 et 3 car je les avait déjà faits en DUT.

### Ex1 :
Les résultats de calculs de puissances sont corrects.
Critique réflexive des choix faits :
Les valeurs sont entrées en dur et non pas en passant par des inputs utilisateur, il faut donc
modifier le code pour avoir des résultats différents.

### Ex4 : 
Critique réflexive des choix faits :
Fonction de saisie sécurisée (entiers non nuls) qui n’était pas demandée
Problème : si saisie incorrecte, sera quand même ramené à 0
J’ai utilisé une allocation dynamique pour allouer un tableau d’entiers avec la taille définie par
l’utilisateur + remplissage aléatoire du tableau puis utilisation de qsort pour qu’il soit trié (encore
une fois, pas demandé).
Pas utilisé de fonction récursive pour la recherche dichotomique
Ce que j’ai appris : utiliser qsort, malloc pour un tableau simple

### Ex5 :
Critique réflexive des choix faits :
Fonctions supplémentaires → swap, création de tableau dynamique, remplissage du tableau
aléatoire, print du tableau
Pour que le main soit plus propre.
Le tri se fait correctement pour différentes tailles de tableaux, en revanche les valeurs aléatoires
sont toutes positives.

| Projet | Pts | I/0 | Type | Progr | Module | Compil | Récursion | Tableaux | Pointeurs | Structures | Allocation | Fichier | Bit à bit | Fct Pointer | Biblio |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| TP3 | 6 | 1 | 1 | 1 | | 1 | 1 | 1 | | | |  | | 

## TP5 Tableaux d’entiers
---
Fonctions simples pour des tableaux et fonctions pour un tri fusion. la première partie du TP était plutôt simple car j'avais déjà fait certaines parties dans les exercices d'avant juste pour être à l'aise avec mes tests. Je n'avais jamais fait de tri fusion avant.

### Ex1, ex2 et 3 (tout dans le même fichier) : 
Quelques fonctions que j’ai déjà fait dans les tp d’avant quand ce n’était pas demandé.
Je remarque qu’il n’est pas possible d’entrer plusieurs valeurs dans le tableau en utilisant
“espace” entre chaque input, il faut utiliser “entrer” parce que strtol ignore les chaînes de
caractères après l’integer, catégorie dans laquelle l’espace tombe malheureusement.
Ce que j’ai appris : Faire un tri fusion
Preuve factuelle :
J’ai un affichage similaire à l’exemple du tp5, et des tableaux de différentes tailles finissent triés
(même si pour les tableaux de grande taille l’affichage dans le terminal est interminable).

| Projet | Pts | I/0 | Type | Progr | Module | Compil | Récursion | Tableaux | Pointeurs | Structures | Allocation | Fichier | Bit à bit | Fct Pointer | Biblio |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| TP5 | 7 | 1 | 1 | 1 | | 1 | 1 | 1 | 1 | | |  | | 

## TP8, Challenge Syracuse
---
Ce TP a été plutôt pratique pour revoir la récursivité car je n'y suis pas habitué.
Cependant je ne suis pas sûr d'avoir bien compris si la valeur maximale (pour le tableau de memo) doit atteindre 200 millions ou si on doit calculer la hauteur de vol maximale pour les entrées de 1 à 200 millions, j'ai donc mis la valeur du tableau à 200 millions (1ere option).

| Projet | Pts | I/0 | Type | Progr | Module | Compil | Récursion | Tableaux | Pointeurs | Structures | Allocation | Fichier | Bit à bit | Fct Pointer | Biblio |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| TP8 | 8 |  | 2 | 1 | | 1 | 2 | 1 | 1 | | | | | 

## TP9, Exercices avec malloc
---
Valgrind pour montrer que les malloc sont faits correctement, assez pratique.

### EX1 :
Critique réflexive des choix faits :
Méthode différente de saisie sécurisée en utilisant un do while pour que le programme ne se
termine pas après une saisie incorrecte. Pas demandé ni nécessaire d’utiliser une méthode
différente, donc passé du temps sans avancer dans le tp.
Atoi renvoie “0” pour des chaines de caractères mais vu que le but était de récupérer un entier
positif ce n’était pas trop un problème. Il faut également faire un “buffer” pour l’input avec le
fgets. Peut être pas la meilleure solution selon les cas (entier négatif par exemple).
Ce que j’ai appris :
Faire une saisie sécurisée différente (fgets + atoi).
Preuve factuelle : Valgrind me dit que tout est ok et mes saisies fonctionnent correctement.

### Ex2 : 
Critique réflexive des choix faits :
Encore une méthode différente de saisie sécurisée (scanf(“%*[^\n]”)).
Ce que j’ai appris : utiliser malloc sur un tableau 2d
Preuve factuelle : valgrind me dit que tout a été free et qu’il n’y a pas de problème.

### Ex3 : 
Ce que j‘ai appris : utiliser strcpy pour recopier une chaine de caractère dans un tableau.
Preuve factuelle : Les valeurs des tableaux copiés sont correctes.
Valgrind ne renvoie pas de problèmes.

| Projet | Pts | I/0 | Type | Progr | Module | Compil | Récursion | Tableaux | Pointeurs | Structures | Allocation | Fichier | Bit à bit | Fct Pointer | Biblio |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| TP9 | 10 | 1 | 1 | 1 | | 1 |  | 2 | 1 | 1 | 2 |  | | 

## TP 10, tri multicritères
---
J'ai peut être visé trop haut avec ce TP, j'ai réussi l'exercice 1 mais pour la fonction principale du 2 je n'y suis pas du tout.

### Ex1 : 
Difficultés rencontrées :
Pas certain de comment faire pour échanger bit par bit les variables
Ce que j’ai appris : à échanger n’importe quelle variable bit par bit, tant que leur taille est la
même.
Preuve factuelle : ça marche pour des int , des double et des tableaux
Critique réflexive des choix faits :
J’utilisais un “while (size--) en tant que boucle mais on m’a signalé que ce n’était pas très clair,
j’ai donc changé cette partie du code en “while(size>0) { size--; “ .

### Ex2 : 
Difficultés rencontrées :
Je ne sais pas vraiment utiliser les listes chainées, je n’ai pas réussi à faire la fonction
“ordered_insertion” qui est la grande partie de l’exercice. Le problème est donc surtout au
niveau conception.

| Projet | Pts | I/0 | Type | Progr | Module | Compil | Récursion | Tableaux | Pointeurs | Structures | Allocation | Fichier | Bit à bit | Fct Pointer | Biblio |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| TP10 | 3 | 1 | 1 | 1 | | 0 | | 0 | 0 | 0 | 0 |  | | 

## Conclusion
---
Je suis toujours assez partagé entre strictement suivre le TP ou alors maximiser l'expérience utilisateur / la fonction du programme, car la "2nde option" prend + de temps et j'aurais pu faire + de TP / projets si j'avais strictement réalisé les TP. Cependant passer + de temps sur les TP et y faire des améliorations qui ne sont pas demandées m'a été utile + d'une fois donc je pense que je continuerai à le faire quand c'est possible.

## Total points accumulés
---
| Projet | Pts | I/0 | Type | Progr | Module | Compil | Récursion | Tableaux | Pointeurs | Structures | Allocation | Fichier | Bit à bit | Fct Pointer | Biblio |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Total | 44 | 6 | 7 | 7 | 0 | 6 | 5 | 5 | 3 | 2 | 2 | 1 | 0 | 0 | 0 | 

C'est un peu + que les objectfs du semestre 1 pour le total de points.
J'aurais moins de projets pour le semestre 2 vu que j'ai entammé / fait des projets qui y sont.


C'est la fin de ce portfolio pour l'instant, merci d'avoir lu.
