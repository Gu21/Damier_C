#ifndef pawn_H_
#define pawn_H_

// SYSTEME INCLUDE(S)
#include <stdio.h>
#include <stdlib.h>

// STRUCTURE(S)
// Structure permettant de gérer un pion
typedef struct pawn_s
{
    int _coord_x;
    int _coord_y;
    char _status;                   // Le pion (P) peut devenir Reine (R).
    char _state;                    // Vivant (V) peut devenir Mort (M).
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


// LOCAL INCLUDE(S)


// PROTOTYPE(S)
void initPawnList(pawn_header_t *liste_chaine, char couleur);       // Initialisation de la liste des pions
void initPawn(pawn_header_t *liste_chaine, int i, char couleur);    // Initialisation d'un pion
void checkAuthorizedMove(void);                                     // Déplacement autorisé ou non du joueur.
void checkMandatoryMove(void);                                      // Obligation de jouer un pion (manger un pion adverse)
void updatePawnState(void);                                         // Etat du pion
void updatePawnStatus(void);                                        // Statut du pion
void movePawn(void);                                                // Déplacement des pions

#endif /* !pawn_H_ */