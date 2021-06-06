### Vincent DAO
### INFO 1 Semestre 2
# **Portfolio**
## Introduction
---

J'ai eu beaucoup de difficultés avec la lib mlv, du coup j'ai choisi de faire les tp et des projets pour compléter plutôt que de continuer à essayer de faire le shoot'em up / three to go avec la lib mlv. J'aurais sûrement pu faire plus de projets ou tp mais dû à la quantité de projets ainsi qu'une mauvaise organisation / progression sur ces dits projets de ma part, je n'ai pas pu atteindre les 110 points annuels des objectifs 2018.

Source d’aide en cas de difficultés : M. Borie, le cours, internet

Vous trouverez [mon github avec les projets ainsi que ce même document ici](https://github.com/daovincent/ESIPE/tree/main/C) (Document que je conseille de lire sur github plutôt qu'en pdf)

[Les sujets des TP ici](http://igm.univ-mlv.fr/~borie/ressources_info1.php)

[Les grilles d'évaluation pour les différents TP ici](http://igm.univ-mlv.fr/~borie/projet_info1.php)


## Table des matières
[Introduction](#Introduction)

[Les TP réalisés : ](#Les-TP-réalisés)

[TP6](#TP6-backtracking)

["WordCount"](#Projet-WordCount)

[Tee](#Projet-Tee-Unix)

[Msort sur liste chaînées](#Projet-msort)

[TP10](#TP10-tris-listes)

[TP12](#TP12-hashage)


[Total points accumulés](#Total-points-accumulés)
    

## Les TP réalisés
---
TP 6, TP 10, TP 12

## TP6 backtracking
---
Je n'ai pas fait de tests en profondeur mais je pense avoir réussi le TP sans trop de difficultés.


| Projet | Pts | I/0 | Type | Progr | Module | Compil | Récursion | Tableaux | Pointeurs | Structures | Allocation | Fichier | Bit à bit | Fct Pointer | Biblio |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| TP6 | 10 | 1 | 1 | 1 | 1 | 1 | 2 | 1 | 1 | | | 1 | | 

## Projet WordCount
---
L'utilisateur doit donner en argument un fichier texte à l'appel du programme, j'ai ajouté un compteur de caractères ainsi qu'un compteur de lignes parce que pourquoi pas. J'ai pu utiliser ce programme en complémentaire pour vérifier mes résultats pour d'autres TP ainsi que dans d'autres matières. Ce projet a donc surtout été utilitaire pour moi, pour éviter d'allumer google et chercher un word count online...

| Projet | Pts | I/0 | Type | Progr | Module | Compil | Récursion | Tableaux | Pointeurs | Structures | Allocation | Fichier | Bit à bit | Fct Pointer | Biblio |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| wordcount | 5 | 1 | 1 | 1 | | 1 |  | | | | | 1 | | 

## Projet Tee Unix
---
Je ne connaissais pas la commande, maintenant je la connais mais j'avoue ne pas vraiment voir dans quels cas l'utiliser. Mais je n'utilise pas tant que ça les commandes Unix donc c'est normal.
Edit : ce fut un mensonge, je l'ai utilisé pour un tp d'algo qui faisait des print énormes sur le terminal pour trouver la position de chaque mots dans un texte gigantesque.
Pour utiliser le programme, c'est précisé en commentaire mais : commande avec output texte, | (pipe) ./tee +nom fichier output (optionnel). Si aucun nom n'est founi un fichier file.txt sera créé.



| Projet | Pts | I/0 | Type | Progr | Module | Compil | Récursion | Tableaux | Pointeurs | Structures | Allocation | Fichier | Bit à bit | Fct Pointer | Biblio |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| tee | 6 | 2 | 1 | 1 | | 1 |  |  | | | | 1 | | 

## Projet msort
---
Un tri fusion mais avec des listes chaînées ! J'ai pu vérifier avec ce TP que je comprend bien comment faire des listes chaînées ainsi qu'un tri fusion. En revanche j'ai aussi pu voir que je fais toujours des erreurs d'innatention (bloqué pendant un moment parce qu'une fonction renvoyait "NULL" quand il n'y avait qu'un seul élément ou aucun et donc pas besoin de trier, au lieu de renvoyer le dit élément). J'ai voulu ajouter une optimisation sans changer ce qui était déjà là et sans même vérifier si la version sans optimisation fonctionnait correctement, ce qui fût une erreur de ma part ainsi qu'une perte de temps.


| Projet | Pts | I/0 | Type | Progr | Module | Compil | Récursion | Tableaux | Pointeurs | Structures | Allocation | Fichier | Bit à bit | Fct Pointer | Biblio |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| msort | 13 | 1 | 1 | 1 | 1 | 1 | 2 |  | 2 | 2 | 1 |  | | 1 |

## TP10 tris listes
---
J'ai réussi à surmonter ce TP qui me bloquait pendant le premier semestre. Je n'avais jamais utilisé de pointeurs de fonctions avant donc ce fût une découverte pour moi.
Les difficultés que j'ai rencontré sont surtout au niveau de la version récursive de la seule fonction difficile de ce TP, car j'ai encore du mal à penser de manière récursive.
j'ai également pu / dû utiliser le débugger car j'avais fait une erreur bête au niveau du malloc alors que mon programme fonctionnait...

| Projet | Pts | I/0 | Type | Progr | Module | Compil | Récursion | Tableaux | Pointeurs | Structures | Allocation | Fichier | Bit à bit | Fct Pointer | Biblio |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| TP10 | 11 | 2 | 1 | 1 | | 1 | 1 |  | 2 | 1 | 1 | 1 | | 

## TP12 hashage
---
Valgrind pour montrer que les malloc sont faits correctement, assez pratique.


| Projet | Pts | I/0 | Type | Progr | Module | Compil | Récursion | Tableaux | Pointeurs | Structures | Allocation | Fichier | Bit à bit | Fct Pointer | Biblio |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| TP12 | 11 | 2 | 1 | 1 | | 1 |  | 1 | 1 | 2 | 1 | 1 | | 


## Conclusion
---
J'ai découvert beaucoup de choses intéressantes à faire en C sur ce semestre. J'ai beaucoup aimé la génération de pdf pour les arbres en algorithmique.
J'ai commencé beaucoup de projets en C car les sujets m'intéressaient (shoot'em up, compresser une image, three to go) mais apprendre à utiliser la bibliothèque MLV que je n'avais jamais vu avant m'a pris trop de temps, et encore je ne pense pas pouvoir l'utiliser correctement. Du coup, je n'ai rien que je peux montrer pour ces projets. Pour la compression d'image (Projet Quadtree) je n'ai juste pas vraiment compris comment m'y prendre mais j'aimerais retourner dessus quand j'aurai plus de connaissances et de temps, après tout le sujet fait 13 pages de pdf.

## Total points accumulés
---
| Projet | Pts | I/0 | Type | Progr | Module | Compil | Récursion | Tableaux | Pointeurs | Structures | Allocation | Fichier | Bit à bit | Fct Pointer | Biblio |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Total | 56 | 9 | 6 | 6 | 2 | 6 | 5 | 2 | 6 | 5 | 3 | 5 | 0 | 1 | 0 | 

Mon total de points pour le semestre 2 est de 56, et le total de l'année est de 100.
J'ai donc fourni + de travail qu'au premier semestre. 
Je suis un peu en dessous des objectifs 2018 (110 points) mais cela m'a permis de constater que ma capacité à résoudre des problèmes me prend plus de temps que ce à quoi je m'attendais. 
J'ai du coup également passé une partie de mon temps à expliquer comment s'y prendre à d'autres personnes dans la promo pour différents problèmes et ça m'a permis de mieux les comprendre moi même.


C'est la fin de ce portfolio pour l'instant, merci d'avoir lu.
