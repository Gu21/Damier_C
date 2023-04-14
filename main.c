#include "main.h"

int main()
{
    int choix = 0;

    while(1)
    {
        choix = menu();

        switch(choix)
        {
            case 1:     // PvP
                game(0, 0);
                break;

            case 2:     // PvE
                game(0, 1);
                break;

            case 3:
                break;

            case 4:     // Quitter
                return 0;
                break;

            default:
                printf("Choix inconnu");
                break;
        }
    }
}




/*
joueur
    nom
    score
    couleur
    pointeur sur le début et la fin d'une liste chainée stockant la liste de ses pions


pion
    coord_x
    coord_y
    status (par défaut pion, peut devenir reine)
    etat (par défaut vivant, peut devenir mort)


Pion blanc : b
Pion noir  : n
Dame blanc : B
Dame noire : N


  X 0 1 2 3 4 5 6 7 8 9
Y ╔════════════════════
0 ║ b   b   b   b   b   
1 ║   b   b   b   b   b 
2 ║
3 ║
4 ║
5 ║
6 ║
7 ║
8 ║
9 ║

*/