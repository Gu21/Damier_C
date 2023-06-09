#include "pawn.h"

void initMovementHistoryList(movement_history_header_t *liste_chaine, movement_history_t *movement_history)
{
    //Je teste si liste_chaine est égale à null
    if (liste_chaine == NULL || movement_history == NULL)
    {
        // Le programme s'arrête avec le exit()
        exit(-4);
    }

    movement_history->_init_coord_x = 0;
    movement_history->_init_coord_y = 0;
    movement_history->_final_coord_x = 0;
    movement_history->_final_coord_y = 0;
    movement_history->p_next = NULL;
    movement_history->p_previous = NULL;

    //Si c'est ok on rajoute les éléments dans la première structure.
    liste_chaine->_length = 0;
    liste_chaine->p_head = movement_history;
    liste_chaine->p_tail = movement_history->p_next;
}

//-----Fonction qui initialise la liste des pions--------
void initPawnList(pawn_header_t *liste_chaine, char couleur)
{
    //Je teste si liste_chaine est égale à null
    if (liste_chaine == NULL)
    {
        // Le programme s'arrête avec le exit()
        exit(-4);
    }

    //Si c'est ok on rajoute les éléments dans la première structure.
    liste_chaine->_length = 0;
    liste_chaine->p_head = NULL;
    liste_chaine->p_tail = NULL;

    //On boucle sur chaque pion jusqu'au 20éme
    for(int i=0; i<20; i++)
    {
        initPawn(liste_chaine, i, couleur);
    }

}

void initPawn(pawn_header_t *liste_chaine, int i, char couleur)
{
    pawn_t *pion = malloc(sizeof(pawn_t));      // On crée une variable pion qui pointe sur la structure pawn_t et on alloue de l'epace mémoire
    pawn_t *lastPawn = malloc(sizeof(pawn_t));  // On crée une variable lasPawn pour récupérer le dernier élément de la liste

    if(pion != NULL)                            //Si le pion est différent de null
    {
        //On initialise les valeurs par défaut.
        pion->_coord_x = 0;
        pion->_coord_y = 0;
        pion->_status = PAWN;
        //pion->_status = QUEEN;
        pion->_state = ALIVE;
        pion->p_next = NULL;
        pion->p_previous = NULL;

        if(couleur == COLOR_B)
        {
            if(i<5) {
                pion->_coord_x = ((i%5)*2)+1;
                pion->_coord_y = 0;
            } else if(i<10) {
                pion->_coord_x = ((i%5)*2);
                pion->_coord_y = 1;
            } else if(i<15) {
                pion->_coord_x = ((i%5)*2)+1;
                pion->_coord_y = 2;
            } else {
                pion->_coord_x = ((i%5)*2);
                pion->_coord_y = 3;
            }
        }
        else
        {
            if(i<5) {
                pion->_coord_x = 9-(((i%5)*2)+1);
                pion->_coord_y = 9-0;
            } else if(i<10) {
                pion->_coord_x = 9-(((i%5)*2));
                pion->_coord_y = 9-1;
            } else if(i<15) {
                pion->_coord_x = 9-(((i%5)*2)+1);
                pion->_coord_y = 9-2;
            } else {
                pion->_coord_x = 9-(((i%5)*2));
                pion->_coord_y = 9-3;
            }
        }

        // Si on est en train de créer le premier pion
        if(i == 0)
            // On précise au header que notre pion est la tête
            liste_chaine->p_head = pion;

        // Si on est en train de créer le dernier pion
        if(i == 19)
            // On précise au header que notre pion est la queue
            liste_chaine->p_tail = pion;

        // On se remet en tête de liste
        lastPawn = liste_chaine->p_head;

        // Tant qu'on a pas atteint le dernier pion de la liste
        while(lastPawn->p_next != NULL)
            // On récupère le pion suivant
            lastPawn = lastPawn->p_next;

        // Le dernier pion de la liste doit avoir comme next notre nouveau pion
        // et le previous de notre nouveau pion doit pointé sur le dernier pion de la liste
        if(liste_chaine->_length != 0)
        {
            lastPawn->p_next = pion;
            pion->p_previous = lastPawn;
        }

        liste_chaine->_length++;
    }
}

void updatePawnState(pawn_t *pawnEated, player_t *opponent) {
    pawnEated->_coord_x = -1;
    pawnEated->_coord_y = -1;
    pawnEated->_state = DEAD;
    opponent->_score++;

    //pawnEated->p_previous->p_next = pawnEated->p_next;
    //pawnEated->p_next->p_previous = pawnEated->p_previous;
    //free(pawnEated);
}

void updatePawnStatus(pawn_t *movingPawn) {
    movingPawn->_status = QUEEN;
}

int checkMandatoryMove(player_t *player, player_t *opponent, pawn_t *movingPawn)
{
    pawn_t* pawnPlayerChecked = player->p_listPawn->p_head;
    pawn_t* pawnOpponentChecked = opponent->p_listPawn->p_head;

    // Pour chaque pion de player
    while (pawnPlayerChecked != NULL)
    {
        pawnOpponentChecked = opponent->p_listPawn->p_head;

        // dont le state est à V
        if (pawnPlayerChecked->_state == ALIVE)
        {
            // Si c'est un pion
            if (pawnPlayerChecked->_status == PAWN)
            {
                // On vérifie s'il y a un pion adverse présent
                // dans une des 2 cases de devant
                while(pawnOpponentChecked != NULL)
                {
                    // Si le joueur a les pions blancs
                    if(player->_couleur == COLOR_W)
                    {
                        // Si le pion de l'adversaire est a une coordonnée X a +-1 à celle du pion du joueur
                        // et que sa coordonnée Y est à +1 de celle du pion du joueur
                        // et que le pion de l'adversaire est encore en vie
                        if ((pawnOpponentChecked->_coord_x-1 == pawnPlayerChecked->_coord_x || pawnOpponentChecked->_coord_x+1 == pawnPlayerChecked->_coord_x)
                        && (pawnOpponentChecked->_coord_y+1 == pawnPlayerChecked->_coord_y || pawnOpponentChecked->_coord_y-1 == pawnPlayerChecked->_coord_y)
                        && pawnOpponentChecked->_state == ALIVE)
                        {
                            // On vérifie que le déplacement est valide
                            if (isMandatoryMoveValid(player, opponent, pawnPlayerChecked) == 1) {
                                // On sélectionne ce pion
                                *movingPawn = *pawnPlayerChecked;
                                return 1;
                            } else {
                                // Sinon on passe au pion adversaire suivant
                                pawnOpponentChecked = pawnOpponentChecked->p_next;
                            }
                        }
                        else
                        {
                            // Sinon on passe au pion adversaire suivant
                            pawnOpponentChecked = pawnOpponentChecked->p_next;
                        }
                    }
                    else // Si le joueur a les pions noirs
                    {
                        // Si le pion de l'adversaire est a une coordonnée X a +-1 à celle du pion du joueur
                        // et que sa coordonnée Y est à -1 de celle du pion du joueur
                        // et que le pion de l'adversaire est encore en vie
                        if ((pawnOpponentChecked->_coord_x-1 == pawnPlayerChecked->_coord_x || pawnOpponentChecked->_coord_x+1 == pawnPlayerChecked->_coord_x)
                        && (pawnOpponentChecked->_coord_y-1 == pawnPlayerChecked->_coord_y || pawnOpponentChecked->_coord_y+1 == pawnPlayerChecked->_coord_y)
                        && pawnOpponentChecked->_state == ALIVE)
                        {
                            // On vérifie que le déplacement est valide
                            if (isMandatoryMoveValid(player, opponent, pawnPlayerChecked) == 1) {
                                // On sélectionne ce pion
                                *movingPawn = *pawnPlayerChecked;
                                return 1;
                            } else {
                                // Sinon on passe au pion adversaire suivant
                                pawnOpponentChecked = pawnOpponentChecked->p_next;
                            }
                        }
                        else
                        {
                            // Sinon on passe au pion adverse suivant
                            pawnOpponentChecked = pawnOpponentChecked->p_next;
                        }
                    }
                }
            }
            else // Fonctionnement pour la reine
            {
                // Bon, elle me casse les noix cette reine, elle a qu'à marcher comme un pion

                /*while(pawnOpponentChecked != NULL)
                {
                    if (abs(pawnOpponentChecked->_coord_x-pawnPlayerChecked->_coord_x) == abs(pawnOpponentChecked->_coord_y-pawnPlayerChecked->_coord_y))
                    {
                        // Si le déplacement est possible
                        if(IsMandatoryDraughtValid(opponent, pawnPlayerChecked, pawnOpponentChecked) == 1)
                        {
                            // On peut manger
                            *movingPawn = *pawnPlayerChecked;
                            return;
                        }
                        else
                        {
                            // Sinon on passe au pion adversaire suivant
                            pawnOpponentChecked = pawnOpponentChecked->p_next;
                        }
                    }
                    else
                    {
                        // Sinon on passe au pion adversaire suivant
                        pawnOpponentChecked = pawnOpponentChecked->p_next;
                    }
                }*/
            }
        }

        // On passe au pion suivant
        pawnPlayerChecked = pawnPlayerChecked->p_next;
    }
    return 0;
}

int checkAuthorizedMove(player_t *player, player_t *opponent, pawn_t *movingPawn, int tempFinalX, int tempFinalY, int isMandatoryMove)
{
    pawn_t* pawnCurrentPlayer = player->p_listPawn->p_head;
    pawn_t* pawnCurrentOpponent = opponent->p_listPawn->p_head;

    // Vérifier si les coordonnées sont dans le plateau
    if (tempFinalX < 0 || tempFinalX > 9 || tempFinalY < 0 || tempFinalY > 9) {
        return 0;
    }

    // Vérifier si le déplacement est autorisé pour un pion de type pion
    if (movingPawn->_status == PAWN) {
        // Vérifier si le joueur est blanc
        if (player->_couleur == COLOR_W) {
            if (isMandatoryMove == 0) {
                // Déplacement interdit sur l'axe Y pour le pion blanc
                if ((movingPawn->_coord_y <= tempFinalY)
                || ((abs(movingPawn->_coord_y - tempFinalY) != 1)
                && (abs(movingPawn->_coord_y - tempFinalY) != 2))
                || (abs(movingPawn->_coord_y - tempFinalY) != abs(movingPawn->_coord_x - tempFinalX))) {
                    //printf("Unauthorized move for color %c\n", player->_couleur);
                    return 0;
                }
            } else {
                // Déplacement interdit sur l'axe Y pour le pion blanc
                if (((abs(movingPawn->_coord_y - tempFinalY) != 1)
                && (abs(movingPawn->_coord_y - tempFinalY) != 2))
                || (abs(movingPawn->_coord_y - tempFinalY) != abs(movingPawn->_coord_x - tempFinalX))) {
                    //printf("Unauthorized move for color %c\n", player->_couleur);
                    return 0;
                }
            }


            // Déplacement interdit sur l'axe X pour le pion blanc
            if ((movingPawn->_coord_x+2 < tempFinalX && tempFinalX < movingPawn->_coord_x-2)
                || (abs(movingPawn->_coord_x - tempFinalX) != 1 && abs(movingPawn->_coord_x - tempFinalX) != 2)) {
                //printf("Unauthorized move for color %c\n", player->_couleur);
                return 0;
            }

        } else {
            if (isMandatoryMove == 0) {
                // Déplacement interdit sur l'axe Y pour le pion noir
                if ((movingPawn->_coord_y >= tempFinalY)
                || ((abs(movingPawn->_coord_y - tempFinalY) != 1)
                && (abs(movingPawn->_coord_y - tempFinalY) != 2))
                || (abs(movingPawn->_coord_y - tempFinalY) != abs(movingPawn->_coord_x - tempFinalX))) {
                    //printf("Unauthorized move for color %c\n", player->_couleur);
                    return 0;
                }
            } else {
                // Déplacement interdit sur l'axe Y pour le pion noir
                if (((abs(movingPawn->_coord_y - tempFinalY) != 1)
                && (abs(movingPawn->_coord_y - tempFinalY) != 2))
                || (abs(movingPawn->_coord_y - tempFinalY) != abs(movingPawn->_coord_x - tempFinalX))) {
                    //printf("Unauthorized move for color %c\n", player->_couleur);
                    return 0;
                }
            }

            // Déplacement interdit sur l'axe X pour le pion blanc
            if ((movingPawn->_coord_x+2 < tempFinalX && tempFinalX < movingPawn->_coord_x-2)
                || (abs(movingPawn->_coord_x - tempFinalX) != 1 && abs(movingPawn->_coord_x - tempFinalX) != 2)) {
                //printf("Unauthorized move for color %c\n", player->_couleur);
                return 0;
            }
        }

        // Vérifier si les coordonnées finales sont sur une case vide
        // Vérification de la liste de pions du joueur un
        while (pawnCurrentPlayer != NULL)
        {
            if (pawnCurrentPlayer->_coord_x == tempFinalX && pawnCurrentPlayer->_coord_y == tempFinalY
                && pawnCurrentPlayer->_state == ALIVE) {
                // La case n'est pas vide
                //printf("Un pion est present sur la case.\n");
                return 0;
            } else {
                pawnCurrentPlayer = pawnCurrentPlayer->p_next;
            }
        }

        // Vérification de la liste de pions du joueur deux
        while (pawnCurrentOpponent != NULL)
            {
                if (pawnCurrentOpponent->_coord_x == tempFinalX && pawnCurrentOpponent->_coord_y == tempFinalY
                && pawnCurrentOpponent->_state == ALIVE) {
                    // La case n' est pas vide
                    //printf("Un pion est present sur la case.\n");
                    return 0;
                } else {
                    pawnCurrentOpponent = pawnCurrentOpponent->p_next;
                }
            }
    } else {
        // CAS DAME
    }

    return 1;
}

int checkAllMoves(player_t *player, player_t *opponent, pawn_t *movingPawn)
{
    int possibleMoves = 0;

    for(int i=0; i<BOARD_SIZE; i++)
    {
        for(int j=0; j<BOARD_SIZE; j++)
        {
            possibleMoves += checkAuthorizedMove(player, opponent, movingPawn, i, j, 0);
            if(possibleMoves > 0)
                return possibleMoves;
        }
    }

    return possibleMoves;
}

void movePawn(pawn_t *movingPawn, player_t *opponent, char color, int finalX, int finalY)
{
    int initX = movingPawn->_coord_x;
    int initY = movingPawn->_coord_y;
    pawn_t* pawnChecked = opponent->p_listPawn->p_head;

    // On change les coordonnées du pion a déplacer
    movingPawn->_coord_x = finalX;
    movingPawn->_coord_y = finalY;

    // On vérifie si le pion est arrivé à la dernière ligne
    if(color == COLOR_W) {
        // Le pion blanc est arrivé à la dernière ligne
        if(movingPawn->_coord_y == 0)
            updatePawnStatus(movingPawn);
    }
    else {
        // Le pion noir est arrivé à la dernière ligne
        if(movingPawn->_coord_y == 9)
            updatePawnStatus(movingPawn);
    }

    // On vérifie s'il a mangé un pion adverse
    if (movingPawn->_coord_x == initX+2 || movingPawn->_coord_x == initX-2) {
        if(color == COLOR_W) {
            while (pawnChecked != NULL)
            {
                //if ((pawnChecked->_coord_x == initX+1 || pawnChecked->_coord_x == initX-1)
                // && (pawnChecked->_coord_y == initY-1 || pawnChecked->_coord_y == initY+1)) {
                if (pawnChecked->_coord_x == initX+((int)round((float)((float)((float)finalX-(float)initX) / 10.0) * 5.0))
                && pawnChecked->_coord_y == initY+((int)round((float)((float)((float)finalY-(float)initY) / 10.0) * 5.0))) {
                    // On a mangé ce pion
                    updatePawnState(pawnChecked, opponent);
                    break;
                } else {
                    pawnChecked = pawnChecked->p_next;
                }
            }
        } else {
            while (pawnChecked != NULL)
            {
                //if ((pawnChecked->_coord_x == initX+1 || pawnChecked->_coord_x == initX-1)
                // && (pawnChecked->_coord_y == initY+1 || pawnChecked->_coord_y == initY-1)) {
                if (pawnChecked->_coord_x == initX+((int)round((float)((float)((float)finalX-(float)initX) / 10.0) * 5.0))
                && pawnChecked->_coord_y == initY+((int)round((float)((float)((float)finalY-(float)initY) / 10.0) * 5.0))) {
                    // On a mangé ce pion
                    updatePawnState(pawnChecked, opponent);
                    break;
                } else {
                    pawnChecked = pawnChecked->p_next;
                }
            }
        }
    }

    displayMove(color, initX, initY, finalX, finalY);
}

int isMandatoryMoveValid(player_t *player, player_t *opponent, pawn_t *pawnPlayerChecked) {
    int isPawnInOpponentList = 0;
    int isPawnInPlayerList = 0;
    int isPawnInOpponentListAfterEat = 0;
    int isPawnInPlayerListAfterEat = 0;
    int isMoveIsOutOfBoard = 0;
    int isMoveToRight = 0;
    int isMoveToReverseRight = 0;
    int isMoveToLeft = 0;
    int isMoveToReverseLeft = 0;
    pawn_t* opponentList = opponent->p_listPawn->p_head;
    pawn_t* playerList = player->p_listPawn->p_head;

    if (player->_couleur == COLOR_W) {
        // CAS pion blanc (y-1)
        // On vérifie si le pion y-1 x+1 appartient à la liste de l'opposant
        isPawnInOpponentList = isPawnInList(opponentList, pawnPlayerChecked, 1, -1);

        // On vérifie si le pion y-1 x+1 appartient à la liste du joueur
        if (isPawnInOpponentList == 0) {
            isPawnInPlayerList = isPawnInList(playerList, pawnPlayerChecked, 1, -1);
        }

        // On vérifie si le déplacement y-2 x+2 est >0 et <9
        if (isPawnInOpponentList == 1 || isPawnInPlayerList == 1 || isPawnInPlayerList == 0) {
            if (pawnPlayerChecked->_coord_x+2 < 0 || pawnPlayerChecked->_coord_x+2 > 9
                    || pawnPlayerChecked->_coord_y-2 < 0 || pawnPlayerChecked->_coord_y-2 > 9){
                        isMoveIsOutOfBoard = 1;
                    }
        }
        // On vérifie si un pion de la liste du joueur ou de l'opposant est présent sur la case y-2 x+2
        if (isMoveIsOutOfBoard == 0 && isPawnInOpponentList == 1 && isPawnInPlayerList == 0) {
            isPawnInOpponentListAfterEat = isPawnInList(opponentList, pawnPlayerChecked, 2, -2);
            isPawnInPlayerListAfterEat = isPawnInList(playerList, pawnPlayerChecked, 2, -2);

            if (isPawnInOpponentListAfterEat == 0 && isPawnInPlayerListAfterEat == 0) {
                // printf("Right move is possible\n");
                isMoveToRight = 1;
            }
        }

        isMoveIsOutOfBoard = 0;
        // On vérifie si le pion y-1 x-1 appartient à la liste de l'opposant
        isPawnInOpponentList = isPawnInList(opponentList, pawnPlayerChecked, -1, -1);

        if (isPawnInOpponentList == 0) {
            // On vérifie si le pion y-1 x-1 appartient à la liste du joueur
            isPawnInPlayerList = isPawnInList(playerList, pawnPlayerChecked, -1, -1);
        }
        // On vérifie si le déplacement y-2 x-2 est >0 et <9
        if (isPawnInOpponentList == 1 || isPawnInPlayerList == 1 || isPawnInPlayerList == 0) {
            if (pawnPlayerChecked->_coord_x-2 < 0 || pawnPlayerChecked->_coord_x-2 > 9
                    || pawnPlayerChecked->_coord_y-2 < 0 || pawnPlayerChecked->_coord_y-2 > 9){
                        isMoveIsOutOfBoard = 1;
                    }
        }
        // On vérifie si un pion de la liste du joueur ou de l'opposant est présent sur la case y-2 x-2
        if (isMoveIsOutOfBoard == 0 && isPawnInOpponentList == 1 && isPawnInPlayerList == 0) {
            isPawnInOpponentListAfterEat = isPawnInList(opponentList, pawnPlayerChecked, -2, -2);
            isPawnInPlayerListAfterEat = isPawnInList(playerList, pawnPlayerChecked, -2, -2);

            if (isPawnInOpponentListAfterEat == 0 && isPawnInPlayerListAfterEat == 0) {
                //printf("Left move is possible\n");
                isMoveToLeft = 1;
            }
        }


        // CAS pion blanc (y+1)
        isMoveIsOutOfBoard = 0;
        // On vérifie si le pion y+1 x+1 appartient à la liste de l'opposant
        isPawnInOpponentList = isPawnInList(opponentList, pawnPlayerChecked, 1, 1);

        // On vérifie si le pion y+1 x+1 appartient à la liste du joueur
        if (isPawnInOpponentList == 0) {
            isPawnInPlayerList = isPawnInList(playerList, pawnPlayerChecked, 1, 1);
        }

        // On vérifie si le déplacement y+2 x+2 est >0 et <9
        if (isPawnInOpponentList == 1 || isPawnInPlayerList == 1 || isPawnInPlayerList == 0) {

            if (pawnPlayerChecked->_coord_x+2 < 0 || pawnPlayerChecked->_coord_x+2 > 9
                    || pawnPlayerChecked->_coord_y+2 < 0 || pawnPlayerChecked->_coord_y+2 > 9){
                        isMoveIsOutOfBoard = 1;
                    }
        }
        // On vérifie si un pion de la liste du joueur ou de l'opposant est présent sur la case y+2 x+2
        if (isMoveIsOutOfBoard == 0 && isPawnInOpponentList == 1 && isPawnInPlayerList == 0) {
            isPawnInOpponentListAfterEat = isPawnInList(opponentList, pawnPlayerChecked, 2, 2);
            isPawnInPlayerListAfterEat = isPawnInList(playerList, pawnPlayerChecked, 2, 2);

            if (isPawnInOpponentListAfterEat == 0 && isPawnInPlayerListAfterEat == 0) {
                // printf("Reverse right move is possible\n");
                isMoveToReverseRight = 1;
            }
        }

        // On vérifie si le pion y+1 x-1 appartient à la liste de l'opposant
        isPawnInOpponentList = isPawnInList(opponentList, pawnPlayerChecked, -1, 1);

        if (isPawnInOpponentList == 0) {
            // On vérifie si le pion y+1 x-1 appartient à la liste du joueur
            isPawnInPlayerList = isPawnInList(playerList, pawnPlayerChecked, -1, 1);
        }
        // On vérifie si le déplacement y+2 x-2 est >0 et <9
        if (isPawnInOpponentList == 1 || isPawnInPlayerList == 1 || isPawnInPlayerList == 0) {
            if (pawnPlayerChecked->_coord_x-2 < 0 || pawnPlayerChecked->_coord_x-2 > 9
                    || pawnPlayerChecked->_coord_y+2 < 0 || pawnPlayerChecked->_coord_y+2 > 9){
                        isMoveIsOutOfBoard = 1;
                    }
        }
        // On vérifie si un pion de la liste du joueur ou de l'opposant est présent sur la case y+2 x-2
        if (isMoveIsOutOfBoard == 0 && isPawnInOpponentList == 1 && isPawnInPlayerList == 0) {
            isPawnInOpponentListAfterEat = isPawnInList(opponentList, pawnPlayerChecked, -2, 2);
            isPawnInPlayerListAfterEat = isPawnInList(playerList, pawnPlayerChecked, -2, 2);

            if (isPawnInOpponentListAfterEat == 0 && isPawnInPlayerListAfterEat == 0) {
                // printf("Reverse left move is possible\n");
                isMoveToReverseLeft = 1;
            }
        }
    }
    else
    {
        // CAS pion noir (y+1)
        // On vérifie si le pion y+1 x+1 appartient à la liste de l'opposant
        isPawnInOpponentList = isPawnInList(opponentList, pawnPlayerChecked, 1, 1);

        if (isPawnInOpponentList == 0) {
            // On vérifie si le pion y+1 x+1 appartient à la liste du joueur
            isPawnInPlayerList = isPawnInList(playerList, pawnPlayerChecked, 1, 1);
        }
        // On vérifie si le déplacement y+2 x+2 est >0 et <9
        if (isPawnInOpponentList == 1 || isPawnInPlayerList == 1 || isPawnInPlayerList == 0) {
            if (pawnPlayerChecked->_coord_x+2 < 0 || pawnPlayerChecked->_coord_x+2 > 9
                    || pawnPlayerChecked->_coord_y+2 < 0 || pawnPlayerChecked->_coord_y+2 > 9){
                        isMoveIsOutOfBoard = 1;
                    }
        }
        // On vérifie si un pion de la liste du joueur ou de l'opposant est présent sur la case y+2 x+2
        if (isMoveIsOutOfBoard == 0 && isPawnInOpponentList == 1 && isPawnInPlayerList == 0) {
            isPawnInOpponentListAfterEat = isPawnInList(opponentList, pawnPlayerChecked, 2, 2);
            isPawnInPlayerListAfterEat = isPawnInList(playerList, pawnPlayerChecked, 2, 2);

            if (isPawnInOpponentListAfterEat == 0 && isPawnInPlayerListAfterEat == 0) {
                // printf("Right move is possible\n");
                isMoveToRight = 1;
            }
        }

        isMoveIsOutOfBoard = 0;
        // On vérifie si le pion y+1 x-1 appartient à la liste de l'opposant
        isPawnInOpponentList = isPawnInList(opponentList, pawnPlayerChecked, -1, 1);
        if (isPawnInOpponentList == 0) {
            // On vérifie si le pion y+1 x-1 appartient à la liste du joueur
            isPawnInPlayerList = isPawnInList(playerList, pawnPlayerChecked, -1, 1);
        }
        // On vérifie si le déplacement y+2 x-2 est >0 et <9
        if (isPawnInOpponentList == 1 || isPawnInPlayerList == 1 || isPawnInPlayerList == 0) {
            if (pawnPlayerChecked->_coord_x-2 < 0 || pawnPlayerChecked->_coord_x-2 > 9
                    || pawnPlayerChecked->_coord_y+2 < 0 || pawnPlayerChecked->_coord_y+2 > 9){
                        isMoveIsOutOfBoard = 1;
                    }
        }
        // On vérifie si un pion de la liste du joueur ou de l'opposant est présent sur la case y+2 x-2
        if (isMoveIsOutOfBoard == 0 && isPawnInOpponentList == 1 && isPawnInPlayerList == 0) {
            isPawnInOpponentListAfterEat = isPawnInList(opponentList, pawnPlayerChecked, -2, 2);
            isPawnInPlayerListAfterEat = isPawnInList(playerList, pawnPlayerChecked, -2, 2);
            if (isPawnInOpponentListAfterEat == 0 && isPawnInPlayerListAfterEat == 0) {
                // printf("Left move is possible\n");
                isMoveToLeft = 1;
            }
        }

        // CAS pion noir (y-1)
        isMoveIsOutOfBoard = 0;
        // On vérifie si le pion y-1 x+1 appartient à la liste de l'opposant
        isPawnInOpponentList = isPawnInList(opponentList, pawnPlayerChecked, 1, -1);

        if (isPawnInOpponentList == 0) {
            // On vérifie si le pion y-1 x+1 appartient à la liste du joueur
            isPawnInPlayerList = isPawnInList(playerList, pawnPlayerChecked, 1, -1);
        }
        // On vérifie si le déplacement y-2 x+2 est >0 et <9
        if (isPawnInOpponentList == 1 || isPawnInPlayerList == 1 || isPawnInPlayerList == 0) {
            if (pawnPlayerChecked->_coord_x+2 < 0 || pawnPlayerChecked->_coord_x+2 > 9
                    || pawnPlayerChecked->_coord_y-2 < 0 || pawnPlayerChecked->_coord_y-2 > 9){
                        isMoveIsOutOfBoard = 1;
                    }
        }
        // On vérifie si un pion de la liste du joueur ou de l'opposant est présent sur la case y-2 x+2
        if (isMoveIsOutOfBoard == 0 && isPawnInOpponentList == 1 && isPawnInPlayerList == 0) {
            isPawnInOpponentListAfterEat = isPawnInList(opponentList, pawnPlayerChecked, 2, -2);
            isPawnInPlayerListAfterEat = isPawnInList(playerList, pawnPlayerChecked, 2, -2);

            if (isPawnInOpponentListAfterEat == 0 && isPawnInPlayerListAfterEat == 0) {
                // printf("Reverse right move is possible\n");
                isMoveToReverseRight = 1;
            }
        }

        isMoveIsOutOfBoard = 0;
        // On vérifie si le pion y-1 x-1 appartient à la liste de l'opposant
        isPawnInOpponentList = isPawnInList(opponentList, pawnPlayerChecked, -1, -1);
        if (isPawnInOpponentList == 0) {
            // On vérifie si le pion y-1 x-1 appartient à la liste du joueur
            isPawnInPlayerList = isPawnInList(playerList, pawnPlayerChecked, -1, -1);
        }
        // On vérifie si le déplacement y-2 x-2 est >0 et <9
        if (isPawnInOpponentList == 1 || isPawnInPlayerList == 1 || isPawnInPlayerList == 0) {
            if (pawnPlayerChecked->_coord_x-2 < 0 || pawnPlayerChecked->_coord_x-2 > 9
                    || pawnPlayerChecked->_coord_y-2 < 0 || pawnPlayerChecked->_coord_y-2 > 9){
                        isMoveIsOutOfBoard = 1;
                    }
        }
        // On vérifie si un pion de la liste du joueur ou de l'opposant est présent sur la case y-2 x-2
        if (isMoveIsOutOfBoard == 0 && isPawnInOpponentList == 1 && isPawnInPlayerList == 0) {
            isPawnInOpponentListAfterEat = isPawnInList(opponentList, pawnPlayerChecked, -2, -2);
            isPawnInPlayerListAfterEat = isPawnInList(playerList, pawnPlayerChecked, -2, -2);
            if (isPawnInOpponentListAfterEat == 0 && isPawnInPlayerListAfterEat == 0) {
                // printf("Reverse left move is possible\n");
                isMoveToReverseLeft = 1;
            }
        }
    }
    if(isMoveToLeft == 1 || isMoveToRight == 1 || isMoveToReverseLeft == 1 || isMoveToReverseRight == 1){
        return 1;
    } else {
        return 0;
    }
}

int isPawnInList(pawn_t* list, pawn_t *pawnPlayerChecked, int coordX, int coordY){
    while (list != NULL) {
        if (list->_coord_x == pawnPlayerChecked->_coord_x+coordX
        && list->_coord_y == pawnPlayerChecked->_coord_y+coordY
        && list->_state == ALIVE){
            return 1;
            break;
        } else {
            list = list->p_next;
        }
    }
    return 0;
}

int IsMandatoryDraughtValid(player_t *opponent, pawn_t *pawnPlayerChecked, pawn_t *pawnOpponentChecked)
{
    pawn_t* pawnsOpponent = opponent->p_listPawn->p_head;

    if(pawnPlayerChecked->_coord_x - pawnOpponentChecked->_coord_x > 0
    && pawnPlayerChecked->_coord_y - pawnOpponentChecked->_coord_y > 0) // Déplacement Nord-Ouest
    {
        while(pawnsOpponent != NULL)
        {
            if (pawnsOpponent->_coord_x == pawnOpponentChecked->_coord_x - 1
            && pawnsOpponent->_coord_y == pawnOpponentChecked->_coord_y - 1
            && pawnOpponentChecked->_coord_x - 1 < 0
            && pawnOpponentChecked->_coord_x - 1 > 9
            && pawnOpponentChecked->_coord_y - 1 < 0
            && pawnOpponentChecked->_coord_y - 1 > 9)
            {
                printf("\nNO\n");
                printf("O->_coord_x = %d\n", pawnsOpponent->_coord_x);
                printf("O->_coord_y = %d\n", pawnsOpponent->_coord_y);
                printf("C->_coord_x = %d\n", pawnOpponentChecked->_coord_x);
                printf("C->_coord_y = %d\n", pawnOpponentChecked->_coord_y);
                printf("P_X - C_X = %d\n", pawnPlayerChecked->_coord_x - pawnOpponentChecked->_coord_x);
                printf("P_Y - C_Y = %d\n", pawnPlayerChecked->_coord_y - pawnOpponentChecked->_coord_y);
                // Un pion se trouve dans la case suivant le pion adverse
                return 0;
            }
            else
            {
                pawnsOpponent = pawnsOpponent->p_next;
            }
        }
    } else if (pawnPlayerChecked->_coord_x - pawnOpponentChecked->_coord_x > 0
    && pawnPlayerChecked->_coord_y - pawnOpponentChecked->_coord_y < 0) // Déplacement Sud-Ouest
    {
        while(pawnsOpponent != NULL)
        {
            if (pawnsOpponent->_coord_x == pawnOpponentChecked->_coord_x - 1
            && pawnsOpponent->_coord_y == pawnOpponentChecked->_coord_y + 1
            && pawnOpponentChecked->_coord_x - 1 < 0
            && pawnOpponentChecked->_coord_x - 1 > 9
            && pawnOpponentChecked->_coord_y - 1 < 0
            && pawnOpponentChecked->_coord_y - 1 > 9)
            {
                printf("\nSO\n");
                printf("O->_coord_x = %d\n", pawnsOpponent->_coord_x);
                printf("O->_coord_y = %d\n", pawnsOpponent->_coord_y);
                printf("C->_coord_x = %d\n", pawnOpponentChecked->_coord_x);
                printf("C->_coord_y = %d\n", pawnOpponentChecked->_coord_y);
                printf("P_X - C_X = %d\n", pawnPlayerChecked->_coord_x - pawnOpponentChecked->_coord_x);
                printf("P_Y - C_Y = %d\n", pawnPlayerChecked->_coord_y - pawnOpponentChecked->_coord_y);
                // Un pion se trouve dans la case suivant le pion adverse
                return 0;
            }
            else
            {
                pawnsOpponent = pawnsOpponent->p_next;
            }
        }
    } else if (pawnPlayerChecked->_coord_x - pawnOpponentChecked->_coord_x < 0
    && pawnPlayerChecked->_coord_y - pawnOpponentChecked->_coord_y > 0) // Déplacement Nord-Est
    {
        while(pawnsOpponent != NULL)
        {
            if (pawnsOpponent->_coord_x == pawnOpponentChecked->_coord_x + 1
            && pawnsOpponent->_coord_y == pawnOpponentChecked->_coord_y - 1
            && pawnOpponentChecked->_coord_x - 1 < 0
            && pawnOpponentChecked->_coord_x - 1 > 9
            && pawnOpponentChecked->_coord_y - 1 < 0
            && pawnOpponentChecked->_coord_y - 1 > 9)
            {
                printf("\nNE\n");
                printf("O->_coord_x = %d\n", pawnsOpponent->_coord_x);
                printf("O->_coord_y = %d\n", pawnsOpponent->_coord_y);
                printf("C->_coord_x = %d\n", pawnOpponentChecked->_coord_x);
                printf("C->_coord_y = %d\n", pawnOpponentChecked->_coord_y);
                printf("P_X - C_X = %d\n", pawnPlayerChecked->_coord_x - pawnOpponentChecked->_coord_x);
                printf("P_Y - C_Y = %d\n", pawnPlayerChecked->_coord_y - pawnOpponentChecked->_coord_y);
                // Un pion se trouve dans la case suivant le pion adverse
                return 0;
            }
            else
            {
                pawnsOpponent = pawnsOpponent->p_next;
            }
        }
    } else // Déplacement Sud-Est
    {
        while(pawnsOpponent != NULL)
        {
            if (pawnsOpponent->_coord_x == pawnOpponentChecked->_coord_x + 1
            && pawnsOpponent->_coord_y == pawnOpponentChecked->_coord_y + 1
            && pawnOpponentChecked->_coord_x - 1 < 0
            && pawnOpponentChecked->_coord_x - 1 > 9
            && pawnOpponentChecked->_coord_y - 1 < 0
            && pawnOpponentChecked->_coord_y - 1 > 9)
            {
                printf("\nSE\n");
                printf("O->_coord_x = %d\n", pawnsOpponent->_coord_x);
                printf("O->_coord_y = %d\n", pawnsOpponent->_coord_y);
                printf("C->_coord_x = %d\n", pawnOpponentChecked->_coord_x);
                printf("C->_coord_y = %d\n", pawnOpponentChecked->_coord_y);
                printf("P_X - C_X = %d\n", pawnPlayerChecked->_coord_x - pawnOpponentChecked->_coord_x);
                printf("P_Y - C_Y = %d\n", pawnPlayerChecked->_coord_y - pawnOpponentChecked->_coord_y);
                // Un pion se trouve dans la case suivant le pion adverse
                return 0;
            }
            else
            {
                pawnsOpponent = pawnsOpponent->p_next;
            }
        }
    }

    return 1;
}

void appendMovementHistoryList(movement_history_header_t *liste_chaine, int initX, int initY, int finalX, int finalY)
{
    /* Création du nouvel élément */
    movement_history_t *movement = malloc(sizeof(*movement));
    if (liste_chaine == NULL || movement == NULL)
    {
        exit(EXIT_FAILURE);
    }
    movement->_init_coord_x = initX;
    movement->_init_coord_y = initY;
    movement->_final_coord_x = finalX;
    movement->_final_coord_y = finalY;

    /* Insertion de l'élément au début de la liste */
    movement->p_next = liste_chaine->p_head;
    liste_chaine->p_head = movement;
}

void displayHistory(movement_history_header_t *liste_chaine)
{
    if (liste_chaine == NULL)
    {
        exit(EXIT_FAILURE);
    }

    movement_history_t *current = liste_chaine->p_head;

    while (current != NULL)
    {
        printf("%d -> \n", current->_init_coord_x);
        printf("%d -> \n", current->_init_coord_y);
        printf("%d -> \n", current->_final_coord_x);
        printf("%d -> \n", current->_final_coord_y);
        current = current->p_next;
    }
    printf("NULL\n");
}

int cancelLastMove(player_t *player, player_t *opponent)
{
    pawn_t* playerPawntoRewind = player->p_listPawn->p_head;
    pawn_t* opponentPawntoRewind = opponent->p_listPawn->p_head;
    movement_history_t* playerLastMove = player->p_movementHistory->p_head;
    movement_history_t* opponentLastMove = opponent->p_movementHistory->p_head;

    while (playerPawntoRewind != NULL)
    {
        if (playerPawntoRewind->_coord_x == playerLastMove->_final_coord_x
            && playerPawntoRewind->_coord_y == playerLastMove->_final_coord_y){
                playerPawntoRewind->_coord_x = playerLastMove->_init_coord_x;
                playerPawntoRewind->_coord_y = playerLastMove->_init_coord_y;
                break;
        } else {
            playerPawntoRewind = playerPawntoRewind->p_next;
        }
    }

    while (opponentPawntoRewind != NULL)
    {
        if (opponentPawntoRewind->_coord_x == opponentLastMove->_final_coord_x
            && opponentPawntoRewind->_coord_y == opponentLastMove->_final_coord_y){
                opponentPawntoRewind->_coord_x = opponentLastMove->_init_coord_x;
                opponentPawntoRewind->_coord_y = opponentLastMove->_init_coord_y;
                break;
        } else {
            opponentPawntoRewind = opponentPawntoRewind->p_next;
        }
    }

    if (playerPawntoRewind == NULL && opponentPawntoRewind == NULL) {
        return 0;
    }

    return 1;
}