#include <stdio.h>
#include "display.h"

int menu(void)
{
    int userChoice;

    printf("## MENU ##\n");
    printf("1) Player vs Player\n");
    printf("2) Player vs Computer\n");
    printf("3) Load game\n");
    printf("4) Quit\n");
    printf("Please choose an option : ");
    printf("\n");

    scanf("%d", &userChoice);
    rewind(stdin);

    return userChoice;
}

void displayBoard(player_t *pPlayer1, player_t *pPlayer2) {

    char board[BOARD_SIZE][BOARD_SIZE];
    int pionPlace = 0;
    //pawn_t *currentPawnPlayer1 = malloc(sizeof(pawn_t));
    //pawn_t *currentPawnPlayer2 = malloc(sizeof(pawn_t));
    pawn_t* currentPawnPlayer1 = pPlayer1->p_listPawn->p_head;
    pawn_t* currentPawnPlayer2 = pPlayer2->p_listPawn->p_head;

    printf("   0123456789\n");
    printf("   ----------\n");

    for (int incr_row = 0; incr_row < BOARD_SIZE; incr_row++)
    {
        printf("%d |", incr_row);
        for (int incr_column = 0; incr_column < BOARD_SIZE; incr_column++)
        {
            pionPlace = 0;
            currentPawnPlayer1 = pPlayer1->p_listPawn->p_head;
            currentPawnPlayer2 = pPlayer2->p_listPawn->p_head;

            // Vérification de la liste de pions du joueur un
            while (currentPawnPlayer1 != NULL)
            {
                if (currentPawnPlayer1->_coord_x == incr_column
                && currentPawnPlayer1->_coord_y == incr_row
                && currentPawnPlayer1->_state == ALIVE) {
                    if(currentPawnPlayer1->_status == PAWN)
                        board[incr_column][incr_row] = WHITE_PAWN;
                    else
                        board[incr_column][incr_row] = WHITE_DRAUGHT;
                    pionPlace = 1;
                    break;
                } else {
                    currentPawnPlayer1 = currentPawnPlayer1->p_next;
                }
            }

            // Vérification de la liste de pions du joueur deux
            while (currentPawnPlayer2 != NULL)
            {
                if (currentPawnPlayer2->_coord_x == incr_column
                && currentPawnPlayer2->_coord_y == incr_row
                && currentPawnPlayer2->_state == ALIVE) {
                    if(currentPawnPlayer2->_status == PAWN)
                        board[incr_column][incr_row] = BLACK_PAWN;
                    else
                        board[incr_column][incr_row] = BLACK_DRAUGHT;
                    pionPlace = 1;
                    break;
                } else {
                    currentPawnPlayer2 = currentPawnPlayer2->p_next;
                }
            }

            if(pionPlace == 0)
            {
                board[incr_column][incr_row] = FREE_SQUARE;
            }

            printf("%c", board[incr_column][incr_row]);
        }

        printf("\n");
    }
}


void endGame(player_t *pPlayer1, player_t *pPlayer2)
{
    if(pPlayer1->_score == 20)
    {
        printf("%s a gagné !\nIl lui restait %d pion(s).\n", pPlayer2->_nom, (20-pPlayer2->_score));
    }
    else
    {
        printf("%s a gagné !\nIl lui restait %d pion(s).\n", pPlayer1->_nom, (20-pPlayer1->_score));
    }
}