#include "game.h"


void game(int IA_J1, int IA_J2)
{
    char J1_name[30];
    char J2_name[30];
    player_t* J1 = malloc(sizeof(player_t));
    player_t* J2 = malloc(sizeof(player_t));

    // Initialisation du Joueur 1
    if(IA_J1 == 0) // Le joueur 1 n'est pas une IA
    {
        printf("\nJoueur 1, veuillez saisir votre nom : ");
        scanf("%s", J1_name);
    }
    else // Le joueur 1 est une IA
        sscanf("Player 1", "%s", J1_name);

    // Initialisation du Joueur 2
    if(IA_J2 == 0) // Le joueur 2 n'est pas une IA
    {
        printf("\nJoueur 2, veuillez saisir votre nom : ");
        scanf("%s", J2_name);
    }
    else // Le joueur 2 est une IA
        sscanf("Player 2", "%s", J2_name);

    // On initialise les 2 joueurs
    initPlayer(J1, J1_name, 'W');
    initPlayer(J2, J2_name, 'B');

    // On affiche la board en début de partie
    displayBoard(J1, J2);

    // Déroulement de la partie tant qu'un joueur n'a pas un score de 20
    /*while (J1->_score < 20 && J2->_score < 20)
    {
        // Au tour de J1
        if(J1->_score < 20 && J2->_score < 20)
        {
            printf("Au tour de %s\n", J1->_nom);

            // On affiche le terrain
            displayBoard(J1, J2);

            // Il bouge un pion
            movePawnByPlayer(J1);

            // On affiche le terrain après le déplacement
            displayBoard(J1, J2);
        }

        // Au tour de J2
        if(J1->_score < 20 && J2->_score < 20)
        {
            printf("Au tour de %s\n", J2->_nom);

            // On affiche le terrain
            displayBoard(J1, J2);

            // Il bouge un pion
            movePawnByPlayer(J2);

            // On affiche le terrain après le déplacement
            displayBoard(J1, J2);
        }
    }

    // On affiche la fin de partie
    endGame();*/

    // On libère les joueurs à la fin de la partie
    free(J1);
    free(J2);
}
