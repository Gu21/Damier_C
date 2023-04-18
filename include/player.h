#ifndef player_H_
#define player_H_

// SYSTEME INCLUDE(S)
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// LOCAL INCLUDE(S)
#include "pawn.h"

// STRUCTURE(S)
typedef struct player_s {
    char* _nom;
    int _score;
    char _couleur;
    pawn_header_t *p_listPawn;
    movement_history_header_t *p_movementHistory;
} player_t;


// PROTOTYPE(S)
void initPlayer(player_t *player, char name[30], char couleur);     // Initialisation des joueurs
void movePawnByPlayer(player_t *player, player_t *opponent);        // Déplacement des pions par les joueurs
void updateScore(void);                                             // Modification des scores

#endif /* !player_H_ */