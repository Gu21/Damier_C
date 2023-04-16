#ifndef game_H_
#define game_H_

// SYSTEME INCLUDE(S)
#include <stdio.h>
#include <stdlib.h>

// LOCAL INCLUDE(S)
#include "player.h"
#include "display.h"


// STRUCTURE(S)


// LOCAL INCLUDE(S)


// PROTOTYPE(S)
void game(int IA_J1, int IA_J2);                // Gère la partie
void saveLog(char color, int initMoveX, int initMoveY, int finalMoveX, int finalMoveY);
void saveGame(player_t *player, player_t *opponent);
void loadGame(void);

#endif /* !game_H_ */