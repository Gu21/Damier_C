#ifndef pawn_H_
#define pawn_H_

// SYSTEME INCLUDE(S)
#include <stdio.h>
#include <stdlib.h>

// LOCAL INCLUDE(S)
//#include "player.h"
//#include "display.h"

// DEFINE(S)
#define PAWN 'P'
#define QUEEN 'Q'
#define ALIVE 'V'
#define DEAD 'M'
#define COLOR_W 'W'
#define COLOR_B 'B'

// STRUCTURE(S)
// Structure permettant de gérer un pion
typedef struct pawn_s
{
    int _coord_x;
    int _coord_y;
    char _status;                   // Le pion (P) peut devenir Reine (Q).
    char _state;                    // Vivant (V) peut devenir Mort (M).
    char keepBusy;                  // case occupée
    struct pawn_s *p_next;          // Ajouter struct car l'alias n'existe pas encore, il est déclaré après la création de la structure
    struct pawn_s *p_previous;
} pawn_t;


// Structure permettant d'accéder à la tête
// et à la queue d'une liste chainée de pions
typedef struct pawn_header_s
{
    int _length;
    pawn_t* p_head;
    pawn_t* p_tail;
}pawn_header_t;


// PROTOTYPE DE STRUCT (défini dans player.h)
typedef struct player_s player_t;

// LOCAL INCLUDE(S)
#include "player.h"
#include "display.h"


// PROTOTYPE(S)
void initPawnList(pawn_header_t *liste_chaine, char couleur);                                                       // Initialisation de la liste des pions
void initPawn(pawn_header_t *liste_chaine, int i, char couleur);                                                    // Initialisation d'un pion
int checkAuthorizedMove(player_t *player, player_t *opponent, pawn_t *movingPawn, int tempFinalX, int tempFinalY);  // Déplacement autorisé ou non du joueur.
int checkAllMoves(player_t *player, player_t *opponent, pawn_t *movingPawn);
void checkMandatoryMove(player_t *player, player_t *opponent, pawn_t *movingPawn);                                  // Obligation de jouer un pion (manger un pion adverse)
void updatePawnState(pawn_t *pawnEated, player_t *opponent);                                                              // Etat du pion
void updatePawnStatus(pawn_t *movingPawn);                                                                                        // Statut du pion
void movePawn(pawn_t *movingPawn, player_t *opponent, char color, int finalX, int finalY);                          // Déplacement des pions

int isMandatoryMoveValid(player_t *player, player_t *opponent, pawn_t *pawnPlayerChecked);
#endif /* !pawn_H_ */