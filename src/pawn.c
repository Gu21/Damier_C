#include "pawn.h"

//-----Fonction qui initialise la liste des pions--------
void initPawnList(pawn_header_t *liste_chaine, char couleur)
{
    //Je teste si liste_chaine est égale à null
    if (liste_chaine == NULL)
    {
        // Le programme s'arrête avec le exit()
        exit(EXIT_FAILURE);
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

        if(couleur == 'B')
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
        {
            // On précise au header que notre pion est la tête
            liste_chaine->p_head = pion;
        }

        // Si on est en train de créer le dernier pion
        if(i == 19)
        {
            // On précise au header que notre pion est la queue
            liste_chaine->p_tail = pion;
        }

        // On se remet en tête de liste
        lastPawn = liste_chaine->p_head;

        // Tant qu'on a pas atteint le dernier pion de la liste
        while(lastPawn->p_next != NULL)
        {
            // On récupère le pion suivant
            lastPawn = lastPawn->p_next;
        }

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