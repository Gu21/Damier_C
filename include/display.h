#ifndef display_H_
#define display_H_

// SYSTEME INCLUDE(S)
#include <stdio.h>
#include <stdlib.h>

// LOCAL INCLUDE(S)
#include "player.h"
#include "pawn.h"

// DEFINE(S)
#define BOARD_SIZE 10
#define WHITE_PAWN 'w'
#define WHITE_DRAUGHT 'W'
#define BLACK_PAWN 'b'
#define BLACK_DRAUGHT 'B'
#define FREE_SQUARE ' '

// STRUCTURE(S)


// LOCAL INCLUDE(S)


// PROTOTYPE(S)
int menu(void);                                                                 // Menu de sélection
void displayBoard(player_t *pPlayer1, player_t *pPlayer2);                      // Affichage du plateau
void displayPlayer(void);                                                       // Affichage des joueurs
void displayScore(void);                                                        // Affichage score des joueurs
void endGame(player_t *pPlayer1, player_t *pPlayer2);                           // Affichage de fin de partie. Annonce le gagnant
void displayMove(int initMoveX, int initMoveY, int finalMoveX, int finalMoveY); // Affichage du déplacement d'un pion

#endif /* !display_H_ */