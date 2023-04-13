#ifndef player_H_
#define player_H_

// SYSTEME INCLUDE(S)
#include <stdio.h>
#include <stdlib.h>

// LOCAL INCLUDE(S)
#include "pawn.h"


// STRUCTURE(S)
typedef struct player_s {
    char* _nom;
    int _score;
    char _couleur;
    pawn_header_t *p_listPawn;
} player_t;

// LOCAL INCLUDE(S)


// PROTOTYPE(S)
void initPlayer(player_t *player, char name[30], char couleur);     // Initialisation des joueurs
void movePawnByPlayer(player_t *player);                            // Déplacement des pions par les joueurs
void updateScore(void);                                             // Modification des scores

#endif /* !player_H_ */