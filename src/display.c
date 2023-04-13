#include <stdio.h>
#include "display.h"

#define BOARD_SIZE 10
#define WHITE_PAWN 'w'
#define WHITE_DRAUGHT 'W'
#define BLACK_PAWN 'b'
#define BLACK_DRAUGHT 'B'
#define FREE_SQUARE ' '

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

    return userChoice;
}

void displayBoard(player_t *pPlayer1, player_t *pPlayer2) {

    char board[BOARD_SIZE][BOARD_SIZE];
    int pionPlace = 0;
    pawn_t *currentPawnPlayer1 = pPlayer1->p_listPawn->p_head;
    pawn_t *currentPawnPlayer2 = pPlayer2->p_listPawn->p_head;

    for (int incr_row = 0; incr_row < BOARD_SIZE; incr_row++)
    {
        for (int incr_column = 0; incr_column < BOARD_SIZE; incr_column++)
        {
            pionPlace = 0;
            currentPawnPlayer1 = pPlayer1->p_listPawn->p_head;
            currentPawnPlayer2 = pPlayer2->p_listPawn->p_head;

            // Vérification de la liste de pions du joueur un
            while (currentPawnPlayer1 != NULL)
            {
                if (currentPawnPlayer1->_coord_x == incr_column && currentPawnPlayer1->_coord_y == incr_row) {
                    board[incr_column][incr_row] = WHITE_PAWN;
                    pionPlace = 1;
                    break;
                } else {
                    currentPawnPlayer1 = currentPawnPlayer1->p_next;
                }
            }

            // Vérification de la liste de pions du joueur deux
            while (currentPawnPlayer2 != NULL)
            {
                if (currentPawnPlayer2->_coord_x == incr_column && currentPawnPlayer2->_coord_y == incr_row) {
                    board[incr_column][incr_row] = BLACK_PAWN;
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