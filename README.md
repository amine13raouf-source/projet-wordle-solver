# Wordle Solver en C

## Description
Ce projet implemente un jeu Wordle et un solveur automatique en langage C
dans le cadre du module ALGO3.

## Contenu du depot
- solver.c : solveur automatique
- wordle.c : logique du jeu Wordle
- words.txt : dictionnaire de mots de 5 lettres
- report.pdf : rapport d’analyse et de justification
- README.md : instructions d’utilisation

## Compilation et Execution
Ouvre le terminal dans le dossier puis tape :
pour wordle :
gcc wordle.c -o wordle 
puis pour executer le programme :
wordle.exe
pour le solver :
gcc solver.c -o solver 
puis pour executer le programme :
solver.exe
## Example usage and sample output
solver :
=== WORDLE SOLVER ===

Tentative 1 : aback | Feedback : X X X X X
Tentative 2 : defer | Feedback : X X X G G
Tentative 3 : giver | Feedback : X G G G G
Tentative 4 : liver | Feedback : X G G G G
Tentative 5 : river | Feedback : G G G G G

 SOLVER A GAGNE !
 wordle :
 === Wordle (version ligne de commande) ===
Essai 1/6 : Entrez une proposition (5 lettres) : aback
[a:X] [b:X] [a:G] [c:X] [k:X]
Essai 2/6 : Entrez une proposition (5 lettres) : beard
[b:X] [e:X] [a:G] [r:X] [d:X]
Essai 3/6 : Entrez une proposition (5 lettres) : coach
[c:X] [o:X] [a:G] [c:X] [h:G]
Essai 4/6 : Entrez une proposition (5 lettres) : frath
Le mot n'existe pas dans le dictionnaire.
Essai 4/6 : Entrez une proposition (5 lettres) : graph
[g:X] [r:X] [a:G] [p:X] [h:G]
Essai 5/6 : Entrez une proposition (5 lettres) : heath
[h:X] [e:X] [a:G] [t:X] [h:G]
Essai 6/6 : Entrez une proposition (5 lettres) : patch
[p:X] [a:Y] [t:X] [c:X] [h:G]
Vous avez perdu. Le mot etait : swash
