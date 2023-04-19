#include "player.h"
#include "main.h"


void initPlayer(player_t *player, char name[30], char couleur)
{
    // J'alloue de l'espace mémoire avec Malloc à la liste_chaine
    pawn_header_t *liste_chaine = malloc(sizeof(pawn_header_t));
    movement_history_header_t *movement_history_list = malloc(sizeof(pawn_header_t));
    movement_history_t *movement_history = malloc(sizeof(movement_history_t));

    // On crée la liste des pions
    initPawnList(liste_chaine, couleur);

    // On initialise la liste des mouvements
    initMovementHistoryList(movement_history_list, movement_history);

    if (player == NULL)
    {
         exit(-4);
    }

    // On initialise les valeurs du joueur
    player->_nom = name;
    player->_score = 0;
    player->_couleur = couleur;
    player->p_listPawn = liste_chaine;
    player->p_movementHistory = movement_history_list;
}

void movePawnByPlayer(player_t *player, player_t *opponent)
{
    pawn_t* movingPawn = malloc(sizeof(pawn_t));
    movement_history_t* initialPawn = malloc(sizeof(movement_history_t));
    int tempInitX = 0;
    int tempInitY = 0;
    int tempFinalX = 0;
    int tempFinalY = 0;
    int MovingPawnSelected = 0;
    int continueMove = 1;
    int dejaJouer = 0;
    int isMandatoryMove = 0;
    int isCancelLastMove = 0;
    pawn_t* tempPawn = player->p_listPawn->p_head;

    while(continueMove == 1)
    {
        // c'est crade putain
        movingPawn->_coord_x = 0;
        movingPawn->_coord_y = 0;
        movingPawn->_status = PAWN;
        movingPawn->_state = ALIVE;
        movingPawn->p_next = NULL;
        movingPawn->p_previous = NULL;

        // On vérifie si le joueur a un déplacement obligatoire à faire
        isMandatoryMove = checkMandatoryMove(player, opponent, movingPawn);

        // S'il n'y a pas de mouvement obligatoire
        if (movingPawn->_coord_x == 0 && movingPawn->_coord_y == 0) {
            continueMove = 0;

            if(dejaJouer == 0)
            {
                while(MovingPawnSelected == 0)
                {
                    // On demande les coordonnées initiales du pion à déplacer
                    printf("Please enter X and Y initial coordinate with format X Y (-1 to save or -2 to rewind): ");
                    scanf("%d %d", &tempInitX, &tempInitY);
                    rewind(stdin);

                    if (tempInitX == -1 || tempInitY == -1) {
                        printf("Save in progress ...\n");
                        saveGame(player, opponent);
                        printf("Save Ok\n");
                        printf("Exit game\n");
                        exit(+1);
                    }

                    if (tempInitX == -2 || tempInitY == -2) {
                        printf("Rewind in progress ...\n");
                        isCancelLastMove = cancelLastMove(player, opponent);
                        if (isCancelLastMove == 1){
                            printf("Rewind Ok\n");
                            if (player->_couleur == COLOR_W) {
                                printf("\nTurn of %s\n", player->_nom);
                                displayBoard(player, opponent);
                                movePawnByPlayer(player, opponent);
                            } else {
                                printf("\nTurn of %s\n", opponent->_nom);
                                displayBoard(player, opponent);
                                movePawnByPlayer(opponent, player);
                            }
                        } else {
                            printf("Rewind error\n");
                            printf("No rewind for the first turn\n");
                            isCancelLastMove = 1;
                            break;
                        }
                    }

                    if (tempInitX >= 0 && tempInitX <= 9 && tempInitY >= 0 && tempInitY <= 9)
                    {
                        tempPawn = player->p_listPawn->p_head;

                        // On sélectionne le pion choisi par le joueur
                        while(tempPawn != NULL)
                        {
                            // Si le pion lu a les coordonnées spécifiées
                            if(tempPawn->_coord_x == tempInitX
                            && tempPawn->_coord_y == tempInitY)
                            {
                                if(checkAllMoves(player, opponent, tempPawn) > 0)
                                {
                                    // On récupère ce pion
                                    initialPawn->_init_coord_x = tempPawn->_coord_x;
                                    initialPawn->_init_coord_y = tempPawn->_coord_y;
                                    movingPawn = tempPawn;
                                    MovingPawnSelected = 1;
                                    break;
                                }
                                else
                                {
                                    printf("Selected pawn has no available move.\n");
                                    // Sinon on passe au pion suivant
                                    tempPawn = tempPawn->p_next;
                                }
                            }
                            else
                            {
                                // Sinon on passe au pion suivant
                                tempPawn = tempPawn->p_next;
                            }
                        }
                    }

                    if(MovingPawnSelected == 0)
                    {
                        // Il n'y a pas de pion aux coordonnées saisies
                        printf("Invalid coordinates.\n");
                    }
                }
            }
        }
        else
        {
            if(dejaJouer == 1)
            {
                if(player->_couleur == COLOR_W)
                {
                    displayBoard(player, opponent);
                }
                else
                {
                    displayBoard(opponent, player);
                }
            }

            // On informe le joueur qu'il doit bouger un pion spécifique
            printf("You have to move the pawn on %d %d.\n", movingPawn->_coord_x, movingPawn->_coord_y);
        }

        if(!(dejaJouer == 1 && continueMove == 0))
        {
            if (isCancelLastMove == 1) {
                break;
            }
            while(1)
            {
                // On demande au joueur où il veut déplacer son pion
                printf("Please enter X and Y final coordinate with format X Y : ");
                scanf("%d %d", &tempFinalX, &tempFinalY);
                rewind(stdin);

                // On vérifie si le déplacement est possible
                if (checkAuthorizedMove(player, opponent, movingPawn, tempFinalX, tempFinalY, isMandatoryMove) == 1)
                    break;
                else
                    printf("Unauthorized move. Try again.\n");
            }

            // TODO : va falloir fix ce truc horrible pour retourner dans la liste
            // ça pue le cul, mais au moins ça marche, et j'ai pas le temps de le corriger
            movePawn(movingPawn->p_previous->p_next, opponent, player->_couleur, tempFinalX, tempFinalY);
            appendMovementHistoryList(player->p_movementHistory, initialPawn->_init_coord_x, initialPawn->_init_coord_y, tempFinalX, tempFinalY);
            //displayHistory(player->p_movementHistory);
        }

        dejaJouer = 1;
    }
}