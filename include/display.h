#ifndef display_H_
#define display_H_

// SYSTEME INCLUDE(S)
#include <stdio.h>
#include <stdlib.h>

// LOCAL INCLUDE(S)
#include "player.h"
#include "pawn.h"

// STRUCTURE(S)


// LOCAL INCLUDE(S)


// PROTOTYPE(S)
int menu(void);                                                                         // Menu de sélection
void displayBoard(player_t *pPlayer1, player_t *pPlayer2);                              // Affichage du plateau
void displayPlayer(void);                                                               // Affichage des joueurs
void displayScore(void);                                                                // Affichage score des joueurs
void endGame(void);                                                                     // Affichage de fin de partie. Annonce le gagnant

#endif /* !display_H_ */