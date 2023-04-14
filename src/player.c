#include "player.h"


void initPlayer(player_t *player, char name[30], char couleur)
{
    pawn_header_t *liste_chaine = malloc(sizeof(pawn_header_t));       //J'alloue de l'espace mémoire avec Malloc à la liste_chaine

    // On crée la liste des pions
    initPawnList(liste_chaine, couleur);

    if (player == NULL)
    {
         exit(-4);
    }

    // On initialise les valeurs du joueur
    player->_nom = name;
    player->_score = 0;
    player->_couleur = couleur;
    player->p_listPawn = liste_chaine;
}

void movePawnByPlayer(player_t *player, player_t *opponent)
{
    pawn_t* movingPawn = malloc(sizeof(pawn_t));
    // pawn_t* tempPawn = malloc(sizeof(pawn_t));
    int tempInitX = 0;
    int tempInitY = 0;
    int tempFinalX = 0;
    int tempFinalY = 0;
    int MovingPawnSelected = 0;

    pawn_t* tempPawn = player->p_listPawn->p_head;

    // On vérifie si le joueur a un déplacement obligatoire à faire
    checkMandatoryMove(player, opponent, movingPawn);

    // S'il n'y a pas de mouvement obligatoire
    if (movingPawn->_coord_x == 0 && movingPawn->_coord_y == 0) {
        while(MovingPawnSelected == 0)
        {
            // On demande les coordonnées initiales du pion à déplacer
            printf("Please enter X and Y initial coordinate with format X Y : ");
            scanf("%d %d", &tempInitX, &tempInitY);
            rewind(stdin);

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
    else
    {
        // On informe le joueur qu'il doit bouger un pion spécifique
        printf("You have to move the pawn on %d %d.\n", movingPawn->_coord_x, movingPawn->_coord_y);
    }

    while(1)
    {
        // On demande au joueur où il veut déplacer son pion
        printf("Please enter X and Y final coordinate with format X Y : ");
        scanf("%d %d", &tempFinalX, &tempFinalY);
        rewind(stdin);

        // On vérifie si le déplacement est possible
        if (checkAuthorizedMove(player, opponent, movingPawn, tempFinalX, tempFinalY) == 1)
            break;
        else
            printf("Unauthorized move. Try again.\n");
    }

    // TODO : va falloir fix ce truc horrible pour retourner dans la liste
    // ça pue le cul, mais au moins ça marche, et j'ai pas le temps de le corriger
    movePawn(movingPawn->p_previous->p_next, opponent, player->_couleur, tempFinalX, tempFinalY);

    // free(tempPawn);
    //free(movingPawn);
}