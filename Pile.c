#include <stdio.h>
#include <stdlib.h>

#include "Pile.h"


/* =====================================================
   Initialiser la pile
   ===================================================== */

void initPile(PileHistorique *p)
{
    p->sommet = NULL;
    p->taille = 0;
}


/* =====================================================
   Vérifier si la pile est vide
   ===================================================== */

int estVidePile(PileHistorique p)
{
    return (p.sommet == NULL);
}


/* =====================================================
   Empiler une action
   ===================================================== */

void empilerAction(PileHistorique *p, Action a)
{
    Action *nouveau;

    nouveau = malloc(sizeof(Action));

    if (nouveau == NULL)
    {
        printf("Erreur d'allocation memoire.\n");
        return;
    }

    nouveau->type = a.type;
    nouveau->volConcerne = a.volConcerne;

    nouveau->suiv = p->sommet;

    p->sommet = nouveau;
    p->taille++;
}


/* =====================================================
   Depiler une action
   ===================================================== */

Action depilerAction(PileHistorique *p)
{
    Action a;
    Action *temp;

    if (estVidePile(*p))
    {
        printf("Pile vide.\n");

        a.type = AJOUT_VOL;
        a.volConcerne.suiv = NULL;
        a.volConcerne.pred = NULL;
        a.suiv = NULL;

        return a;
    }

    temp = p->sommet;

    a = *temp;

    p->sommet = temp->suiv;

    free(temp);

    p->taille--;

    a.suiv = NULL;

    return a;
}


/* =====================================================
   Afficher l'historique
   ===================================================== */

void afficherHistorique(PileHistorique p)
{
    Action *courant;
    int i = 1;

    if (estVidePile(p))
    {
        printf("\nHistorique vide.\n");
        return;
    }

    printf("\n===== HISTORIQUE =====\n");

    courant = p.sommet;

    while (courant != NULL)
    {
        printf("%d. ", i);

        if (courant->type == AJOUT_VOL)
        {
            printf("AJOUT");
        }
        else if (courant->type == SUPPRESSION_VOL)
        {
            printf("SUPPRESSION");
        }
        else if (courant->type == DECOLLAGE)
        {
            printf("DECOLLAGE");
        }

        printf(" - Vol %s - %s\n",
               courant->volConcerne.numVol,
               courant->volConcerne.destination);

        courant = courant->suiv;
        i++;
    }
}


/* =====================================================
   Liberer la pile
   ===================================================== */

void libererPile(PileHistorique *p)
{
    while (!estVidePile(*p))
    {
        depilerAction(p);
    }
}

