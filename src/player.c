#include "player.h"


void initPlayer(player_t *player, char name[30], char couleur)
{
    pawn_header_t *liste_chaine = malloc(sizeof(pawn_header_t));       //J'alloue de l'espace mémoire avec Malloc à la liste_chaine

    // On crée la liste des pions
    initPawnList(liste_chaine, couleur);

    if (player == NULL)
    {
         exit(EXIT_FAILURE);
    }

    // On initialise les valeurs du joueur
    player->_nom = name;
    player->_score = 0;
    player->_couleur = couleur;
    player->p_listPawn = liste_chaine;
}

/*void movePawnByPlayer(player_t *player)
{
    
}*/