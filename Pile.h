#ifndef PILE_H
#define PILE_H

#include "RegistreVols.h"

typedef enum
{
    AJOUT_VOL,
    SUPPRESSION_VOL,
    DECOLLAGE
} TypeAction;

typedef struct action
{
    TypeAction type;
    Vol volConcerne;
    struct action *suiv;
} Action;

typedef struct
{
    Action *sommet;
    int taille;
} PileHistorique;

/* Primitives */
void initPile(PileHistorique *p);
int estVidePile(PileHistorique p);
void empilerAction(PileHistorique *p, Action a);
Action depilerAction(PileHistorique *p);

/* Historique */
void afficherHistorique(PileHistorique p);
void libererPile(PileHistorique *p);

#endif
