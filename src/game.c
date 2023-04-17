#include "game.h"


void game(int IA_J1, int IA_J2, int isLoad)
{
    char J1_name[30];
    char J2_name[30];
    player_t* J1 = malloc(sizeof(player_t));
    player_t* J2 = malloc(sizeof(player_t));

    // Initialisation du Joueur 1
    if(IA_J1 == 0) // Le joueur 1 n'est pas une IA
    {
        printf("\nPlayer 1, please enter your name : ");
        scanf("%s", J1_name);
        rewind(stdin);
    }
    else // Le joueur 1 est une IA
        sscanf("Player 1", "%s", J1_name);

    // Initialisation du Joueur 2
    if(IA_J2 == 0) // Le joueur 2 n'est pas une IA
    {
        printf("\nPlayer 2, please enter your name : ");
        scanf("%s", J2_name);
        rewind(stdin);
    }
    else // Le joueur 2 est une IA
        sscanf("Player 2", "%s", J2_name);

    // On initialise les 2 joueurs
    initPlayer(J1, J1_name, COLOR_W);
    initPlayer(J2, J2_name, COLOR_B);

    // On charge la partie
    if (isLoad == 1) {
        loadGame(J1, J2);
    }
    
    // On affiche la board en début de partie
    displayBoard(J1, J2);

    // Déroulement de la partie tant qu'un joueur n'a pas un score de 20
    while (J1->_score < 20 && J2->_score < 20)
    {
        // Au tour de J1
        if(J1->_score < 20 && J2->_score < 20)
        {
            printf("\nTurn of %s\n", J1->_nom);

            // On affiche le terrain
            displayBoard(J1, J2);

            // Il bouge un pion
            movePawnByPlayer(J1, J2);
        }

        // Au tour de J2
        if(J1->_score < 20 && J2->_score < 20)
        {
            printf("\nTurn of %s\n", J2->_nom);

            // On affiche le terrain
            displayBoard(J1, J2);

            // Il bouge un pion
            movePawnByPlayer(J2, J1);
        }
    }

    // On affiche la fin de partie
    endGame(J1, J2);

    // On libère les joueurs à la fin de la partie
    free(J1);
    free(J2);
}

void saveLog(char color, int initMoveX, int initMoveY, int finalMoveX, int finalMoveY) {

    char input[15];
    // Ouverture du fichier en écriture ou création du fichier
    FILE *fp = fopen("./log/log.txt", "a");

    // Vérification si l'ouverture du fichier s'est bien passée
    if (fp == NULL)
    {
        printf("Le fichier log.txt n'a pas pu être ouvert\n");
        exit(-1);
    }

    snprintf(input, sizeof input, "%c / %d %d / %d %d\n", color, initMoveX, initMoveY, finalMoveX, finalMoveY);

    // Vérification que l'écriture dans le fichier s'est bien passée
    if (fputs(input, fp) == EOF) { // Texte à ajouter dans le fichier
        fputs("Erreur lors de l'ecriture d'une ligne\n", stderr);
        exit(-2);
    }

    // Vérification que la fermeture du fichier s'est bien passée
    if (fclose(fp) == EOF)
    {
        fputs("Erreur lors de la fermeture du flux\n", stderr);
        exit(-3);
    }
}

void saveGame(player_t *player, player_t *opponent) {
    char input[440];

    // Ouverture du fichier en écriture ou création du fichier
    FILE *fp = fopen("./save/save.txt", "w");

    // Vérification si l'ouverture du fichier s'est bien passée
    if (fp == NULL)
    {
        printf("Le fichier save.txt n'a pas pu etre ouvert\n");
        exit(-1);
    }

    pawn_t* playerList = player->p_listPawn->p_head;
    pawn_t* opponentList = opponent->p_listPawn->p_head;

    while (playerList != NULL) {
        snprintf(input, sizeof input, "%c/%d/%d/%c/%c\n",
            player->_couleur, playerList->_coord_x, playerList->_coord_y, playerList->_state, playerList->_status);
        fputs(input, fp);
        playerList = playerList->p_next;
    }

    while (opponentList != NULL) {
        snprintf(input, sizeof input, "%c/%d/%d/%c/%c\n",
            opponent->_couleur, opponentList->_coord_x, opponentList->_coord_y, opponentList->_state, opponentList->_status);
        fputs(input, fp);
        opponentList = opponentList->p_next;
    }
    
    // Pour la fin du fichier
    snprintf(input, sizeof input, "E");
    fputs(input, fp);

    // Vérification que la fermeture du fichier s'est bien passée
    if (fclose(fp) == EOF)
    {
        fputs("Erreur lors de la fermeture du flux\n", stderr);
        exit(-3);
    }

    free(playerList);
    free(opponentList);
}

void loadGame(player_t *J1, player_t *J2) {

    char buf[255];
    // Ouverture du fichier en lecture
    FILE *fp = fopen("./save/save.txt", "r");

    // Vérification si l'ouverture du fichier s'est bien passée
    if (fp == NULL)
    {
        printf("Le fichier save.txt n'a pas pu être ouvert\n");
        exit(-1);
    }
    printf("Ouverture du fichier ok\n");
    pawn_t* playerList = J1->p_listPawn->p_head;
    pawn_t* opponentList = J2->p_listPawn->p_head;

    char* coordX;
    char* coordY;

    do
    {
        // On lit une ligne
        fgets(buf, sizeof buf, fp);

        // On vérifie que la ligne n'est pas vide
        if(*buf == 'E')
            break;

        // à enregistrer dans le pointeur
        if (buf[0] == 'W') {
            coordX = &buf[2];
            coordY = &buf[4];
            playerList->_coord_x = (int)strtol(coordX, NULL, 10);
            playerList->_coord_y= (int)strtol(coordY, NULL, 10);
            playerList->_state= buf[6];
            playerList->_status= buf[8];
            playerList = playerList->p_next;
            // printf("%s", buf);
        } else {
            coordX = &buf[2];
            coordY = &buf[4];
            opponentList->_coord_x = (int)strtol(coordX, NULL, 10);
            opponentList->_coord_y= (int)strtol(coordY, NULL, 10);
            opponentList->_state= buf[6];
            opponentList->_status= buf[8];
            opponentList = opponentList->p_next;
            //printf("%s", buf);
        }
        
    } while (1);

    // Vérification que la fermeture du fichier s'est bien passée
    if (fclose(fp) == EOF)
    {
        fprintf(stderr, "Erreur lors de la fermeture du flux\n");
        exit(-3);
    }
}