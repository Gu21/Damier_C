#include "pawn.h"

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
        pion->_status = 'P';
        pion->_state = 'V';
        pion->p_next = NULL;
        pion->p_previous = NULL;

        // TODO : FOR TEST ONLY !!!!!
        pion->_coord_x = i%10;
        pion->_coord_y = (i+1)%10;

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
    pawnEated->_state = DEAD;
    opponent->_score++;
}

void updatePawnStatus(pawn_t *movingPawn) {
    movingPawn->_status = QUEEN;
}

void checkMandatoryMove(player_t *player, player_t *opponent, pawn_t *movingPawn)
{
    //pawn_t* pawnPlayerChecked = malloc(sizeof(pawn_t));
    //pawn_t* pawnOpponentChecked = malloc(sizeof(pawn_t));
    pawn_t* pawnPlayerChecked = player->p_listPawn->p_head;
    pawn_t* pawnOpponentChecked = opponent->p_listPawn->p_head;

    // Pour chaque pion de player
    while (pawnPlayerChecked != NULL)
    {
        
        // printf("\npawnPlayer = %p\n", pawnPlayerChecked);
        // printf("P coord X  = %d\n", pawnPlayerChecked->_coord_x);
        // printf("P coord Y  = %d\n", pawnPlayerChecked->_coord_y);
        // printf("P next     = %p\n", pawnPlayerChecked->p_next);

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
                        && pawnOpponentChecked->_coord_y+1 == pawnPlayerChecked->_coord_y
                        && pawnOpponentChecked->_state == ALIVE)
                        {
                            // On vérifie que le déplacement est valide
                            if (isMandatoryMoveValid(player, opponent, pawnPlayerChecked) == 1) {
                                // On sélectionne ce pion
                                *movingPawn = *pawnPlayerChecked;
                                return;
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
                        && pawnOpponentChecked->_coord_y-1 == pawnPlayerChecked->_coord_y
                        && pawnOpponentChecked->_state == ALIVE)
                        {
                            // On vérifie que le déplacement est valide
                            if (isMandatoryMoveValid(player, opponent, pawnPlayerChecked) == 1) {
                                // On sélectionne ce pion
                                *movingPawn = *pawnPlayerChecked;
                                return;
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
            else
            {
                //Fonctionnement pour la reine. Osef actuellement
                // On vérifie s'il y a un pion adverse dans les 4 directions, et ce, même si plusieurs cases les sépare
                    // Si c'est le cas, on vérifie s'il y a au moins une case de libre juste après le pion
                        // Si c'est le cas, movingPawn = pion
                        // On quitte la fonction
                    // Sinon on continue
                // sinon on continue
            }
        }

        // On passe au pion suivant
        pawnPlayerChecked = pawnPlayerChecked->p_next;
    }
}


int checkAuthorizedMove(player_t *player, player_t *opponent, pawn_t *movingPawn, int tempFinalX, int tempFinalY)
{
    // Déclaration de la mémoire
    //pawn_t* pawnCurrentPlayer = malloc(sizeof(pawn_t));
    //pawn_t* pawnCurrentOpponent = malloc(sizeof(pawn_t));

    pawn_t* pawnCurrentPlayer = player->p_listPawn->p_head;
    pawn_t* pawnCurrentOpponent = opponent->p_listPawn->p_head;

    // Vérifier si les coordonnées sont dans le plateau
    if (tempFinalX < 0 || tempFinalX > 9 || tempFinalY < 0 || tempFinalY > 9) {
        //printf("Coordinates are out of board\n");
        return 0;
    }

    // Vérifier si le déplacement est autorisé pour un pion de type pion
    if (movingPawn->_status == PAWN) {
        // Vérifier si le joueur est blanc
        if (player->_couleur == COLOR_W) {
            // Déplacement interdit sur l'axe Y pour le pion blanc
            if ((movingPawn->_coord_y <= tempFinalY) 
            || ((abs(movingPawn->_coord_y - tempFinalY) != 1)
               && (abs(movingPawn->_coord_y - tempFinalY) != 2))
            || (abs(movingPawn->_coord_y - tempFinalY) != abs(movingPawn->_coord_x - tempFinalX))) {
                //printf("Unauthorized move for color %c\n", player->_couleur);
                return 0;
            }

            // Déplacement interdit sur l'axe X pour le pion blanc
            if ((movingPawn->_coord_x+2 < tempFinalX && tempFinalX < movingPawn->_coord_x-2)
                || (abs(movingPawn->_coord_x - tempFinalX) != 1 && abs(movingPawn->_coord_x - tempFinalX) != 2)) {
                //printf("Unauthorized move for color %c\n", player->_couleur);
                return 0;
            }

        } else {
            // Déplacement interdit sur l'axe Y pour le pion noir
            if ((movingPawn->_coord_y >= tempFinalY) 
            || ((abs(movingPawn->_coord_y - tempFinalY) != 1)
               && (abs(movingPawn->_coord_y - tempFinalY) != 2))
            || (abs(movingPawn->_coord_y - tempFinalY) != abs(movingPawn->_coord_x - tempFinalX))) {
                //printf("Unauthorized move for color %c\n", player->_couleur);
                return 0;
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
            possibleMoves += checkAuthorizedMove(player, opponent, movingPawn, i, j);
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
                if ((pawnChecked->_coord_x == initX+1 || pawnChecked->_coord_x == initX-1)
                 && pawnChecked->_coord_y == initY-1) {
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
                if ((pawnChecked->_coord_x == initX+1 || pawnChecked->_coord_x == initX-1)
                 && pawnChecked->_coord_y == initY+1) {
                    // On a mangé ce pion
                    updatePawnState(pawnChecked, opponent);
                    break;
                } else {
                    pawnChecked = pawnChecked->p_next;
                }
            }
        }
    }
}

int isMandatoryMoveValid(player_t *player, player_t *opponent, pawn_t *pawnPlayerChecked) {

    pawn_t* checkP1 = player->p_listPawn->p_head;
    pawn_t* checkP2 = opponent->p_listPawn->p_head;

    if (player->_couleur == COLOR_W){
        while (checkP1 != NULL)
        {
            if ((checkP1->_coord_x == pawnPlayerChecked->_coord_x+2
            && checkP1->_coord_y == pawnPlayerChecked->_coord_y-2 && checkP1->_state == ALIVE)
            || (checkP1->_coord_x == pawnPlayerChecked->_coord_x-2
            && checkP1->_coord_y == pawnPlayerChecked->_coord_y-2 && checkP1->_state == ALIVE)
            ) {
                printf("Emplacement non disponible apres avoir manger\n");
                printf("Coordonnee X:%d\n", pawnPlayerChecked->_coord_x);
                printf("Coordonnee Y:%d\n", pawnPlayerChecked->_coord_y);
                printf("Coordonnee check p1 X:%d\n", checkP1->_coord_x);
                printf("Coordonnee check p1 Y:%d\n", checkP1->_coord_y);
                return 0;
            } else {
                checkP1 = checkP1->p_next;
            }
        }

        while (checkP2 != NULL)
        {
            if ((checkP2->_coord_x == pawnPlayerChecked->_coord_x+2
            && checkP2->_coord_y == pawnPlayerChecked->_coord_y-2 && checkP2->_state == ALIVE)
            || (checkP2->_coord_x == pawnPlayerChecked->_coord_x-2
            && checkP2->_coord_y == pawnPlayerChecked->_coord_y-2 && checkP2->_state == ALIVE)
            ) {
                printf("Emplacement non disponible apres avoir manger\n");
                printf("Coordonnee X:%d\n", pawnPlayerChecked->_coord_x);
                printf("Coordonnee Y:%d\n", pawnPlayerChecked->_coord_y);
                printf("Coordonnee check p2 X:%d\n", checkP2->_coord_x);
                printf("Coordonnee check p2 Y:%d\n", checkP2->_coord_y);
                return 0;
            } else {
                checkP2 = checkP2->p_next;
            }
        }
    } else {
                while (checkP1 != NULL)
        {
            if ((checkP1->_coord_x == pawnPlayerChecked->_coord_x+2
            && checkP1->_coord_y == pawnPlayerChecked->_coord_y+2 && checkP1->_state == ALIVE)
            || (checkP1->_coord_x == pawnPlayerChecked->_coord_x-2
            && checkP1->_coord_y == pawnPlayerChecked->_coord_y+2 && checkP1->_state == ALIVE)
            ) {
                printf("Emplacement non disponible apres avoir manger\n");
                printf("Coordonnee X:%d\n", pawnPlayerChecked->_coord_x);
                printf("Coordonnee Y:%d\n", pawnPlayerChecked->_coord_y);
                printf("Coordonnee check p1 X:%d\n", checkP1->_coord_x);
                printf("Coordonnee check p1 Y:%d\n", checkP1->_coord_y);
                return 0;
            } else {
                checkP1 = checkP1->p_next;
            }
        }

        while (checkP2 != NULL)
        {
            if ((checkP2->_coord_x == pawnPlayerChecked->_coord_x+2
            && checkP2->_coord_y == pawnPlayerChecked->_coord_y+2 && checkP2->_state == ALIVE)
            || (checkP2->_coord_x == pawnPlayerChecked->_coord_x-2
            && checkP2->_coord_y == pawnPlayerChecked->_coord_y+2 && checkP2->_state == ALIVE)
            ) {
                printf("Emplacement non disponible apres avoir manger\n");
                printf("Coordonnee X:%d\n", pawnPlayerChecked->_coord_x);
                printf("Coordonnee Y:%d\n", pawnPlayerChecked->_coord_y);
                printf("Coordonnee check p2 X:%d\n", checkP2->_coord_x);
                printf("Coordonnee check p2 Y:%d\n", checkP2->_coord_y);
                return 0;
            } else {
                checkP2 = checkP2->p_next;
            }
        }
    }

    printf("Emplacement disponible apres avoir manger\n");
    printf("Coordonnee X:%d\n", pawnPlayerChecked->_coord_x);
    printf("Coordonnee Y:%d\n", pawnPlayerChecked->_coord_y);
    return 1;
}