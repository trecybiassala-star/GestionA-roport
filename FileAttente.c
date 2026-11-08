
#include <stdio.h>
#include <stdlib.h>

#include "FileAttente.h"


/*
 * Initialise la file.
 */
void initFile(FileAttente *f)
{
    f->tete = NULL;
    f->queue = NULL;
    f->taille = 0;
}


/*
 * Vérifie si la file est vide.
 * Retourne 1 si elle est vide, 0 sinon.
 */
int estVideFile(FileAttente f)
{
    return (f.tete == NULL);
}


/*
 * Ajoute un vol dans la file.
 *
 * urgence = 0 : le vol est ajouté à la fin.
 * urgence = 1 : le vol est placé après les urgences
 *               déjà présentes et avant les vols normaux.
 */
void enfiler(FileAttente *f, Vol v, int urgence)
{
    MaillonFile *nouveau;
    MaillonFile *courant;

    /* Vérification de la valeur d'urgence */
    if (urgence != 0 && urgence != 1)
    {
        printf("Erreur : urgence doit être 0 ou 1.\n");
        return;
    }

    /* Allocation du nouveau maillon */
    nouveau = (MaillonFile *)malloc(sizeof(MaillonFile));

    if (nouveau == NULL)
    {
        printf("Erreur d'allocation mémoire.\n");
        return;
    }

    /* Copie du vol */
    nouveau->vol = v;

    /* Enregistrement du niveau d'urgence */
    nouveau->urgence = urgence;

    /* Pour l'instant, il n'a pas de suivant */
    nouveau->suiv = NULL;


    /*
     * CAS 1 : la file est vide.
     */
    if (estVideFile(*f))
    {
        f->tete = nouveau;
        f->queue = nouveau;
        f->taille++;

        return;
    }


    /*
     * CAS 2 : vol normal.
     *
     * Il est toujours ajouté à la fin.
     */
    if (urgence == 0)
    {
        f->queue->suiv = nouveau;
        f->queue = nouveau;
        f->taille++;

        return;
    }


    /*
     * CAS 3 : vol urgent.
     *
     * S'il n'y a aucun vol urgent en tête,
     * le nouveau vol devient la nouvelle tête.
     */
    if (f->tete->urgence == 0)
    {
        nouveau->suiv = f->tete;
        f->tete = nouveau;
        f->taille++;

        return;
    }


    /*
     * Il existe déjà des urgences.
     *
     * On cherche la dernière urgence.
     */
    courant = f->tete;

    while (courant->suiv != NULL &&
           courant->suiv->urgence == 1)
    {
        courant = courant->suiv;
    }


    /*
     * Insertion après la dernière urgence.
     */
    nouveau->suiv = courant->suiv;
    courant->suiv = nouveau;

    /*
     * Si le nouveau maillon est le dernier,
     * il devient également la queue.
     */
    if (nouveau->suiv == NULL)
    {
        f->queue = nouveau;
    }

    f->taille++;
}


/*
 * Retire le premier vol de la file
 * et retourne ce vol.
 */
Vol defiler(FileAttente *f)
{
    MaillonFile *ancienTete;
    Vol vol;

    /*
     * Création d'un vol vide
     * en cas de file vide.
     */
    vol.numVol[0] = '\0';
    vol.destination[0] = '\0';
    vol.heureDepart = 0;
    vol.nbPlaces = 0;
    vol.placesOccupees = 0;
    vol.suiv = NULL;
    vol.pred = NULL;

    /*
     * Vérification de la file.
     */
    if (f == NULL || estVideFile(*f))
    {
        printf("Erreur : la file est vide.\n");
        return vol;
    }

    /*
     * On mémorise l'ancien premier maillon.
     */
    ancienTete = f->tete;

    /*
     * On récupère le vol.
     */
    vol = ancienTete->vol;

    /*
     * La tête devient le maillon suivant.
     */
    f->tete = ancienTete->suiv;

    /*
     * Si la file est devenue vide,
     * la queue doit également être NULL.
     */
    if (f->tete == NULL)
    {
        f->queue = NULL;
    }

    /*
     * Diminution de la taille.
     */
    f->taille--;

    /*
     * Libération de la mémoire.
     */
    free(ancienTete);

    return vol;
}


/*
 * Consulte le premier vol sans le retirer.
 */
Vol consulterTeteFile(FileAttente f)
{
    Vol vol;

    /*
     * Vol vide retourné si la file est vide.
     */
    vol.numVol[0] = '\0';
    vol.destination[0] = '\0';
    vol.heureDepart = 0;
    vol.nbPlaces = 0;
    vol.placesOccupees = 0;
    vol.suiv = NULL;
    vol.pred = NULL;

    if (estVideFile(f))
    {
        return vol;
    }

    return f.tete->vol;
}


/*
 * Fait décoller le prochain vol.
 */
void decollerProchainVol(FileAttente *f)
{
    Vol vol;

    if (f == NULL || estVideFile(*f))
    {
        printf("Aucun vol en attente.\n");
        return;
    }

    /*
     * On retire le premier vol.
     */
    vol = defiler(f);

    printf("\n===== DECOLLAGE =====\n");
    printf("Vol : %s\n", vol.numVol);
    printf("Destination : %s\n", vol.destination);
    printf("Heure de depart : %04d\n", vol.heureDepart);
    printf("=====================\n");
}


/*
 * Affiche les vols présents dans la file
 * sans modifier la structure.
 */
void afficherFile(FileAttente f)
{
    MaillonFile *courant;

    if (estVideFile(f))
    {
        printf("La file est vide.\n");
        return;
    }

    printf("\n===== FILE D'ATTENTE =====\n");

    courant = f.tete;

    while (courant != NULL)
    {
        printf("Vol : %s | Destination : %s | Depart : %04d | ",
               courant->vol.numVol,
               courant->vol.destination,
               courant->vol.heureDepart);

        if (courant->urgence == 1)
        {
            printf("URGENCE\n");
        }
        else
        {
            printf("NORMAL\n");
        }

        courant = courant->suiv;
    }

    printf("Taille : %d\n", f.taille);
    printf("==========================\n");
}


/*
 * Libère tous les maillons de la file.
 */
void libererFile(FileAttente *f)
{
    MaillonFile *courant;
    MaillonFile *suivant;

    if (f == NULL)
    {
        return;
    }

    courant = f->tete;

    while (courant != NULL)
    {
        suivant = courant->suiv;

        free(courant);

        courant = suivant;
    }

    f->tete = NULL;
    f->queue = NULL;
    f->taille = 0;
}
