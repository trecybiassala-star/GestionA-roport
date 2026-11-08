
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "registreVols.h"


/*
 * Insère un nouveau vol dans la liste doublement chaînée
 * en respectant l'ordre croissant de l'heure de départ.
 */
int insererVolTrie(Vol **tete, Vol v)
{
    Vol *nouveau;
    Vol *courant;

    /* Vérification des paramètres */
    if (tete == NULL)
    {
        return 0;
    }

    /*
     * Le numéro de vol doit être unique.
     * On recherche donc d'abord s'il existe déjà.
     */
    if (rechercherVol(*tete, v.numVol) != NULL)
    {
        printf("Erreur : le vol %s existe deja dans le registre.\n",
               v.numVol);
        return 0;
    }

    /* Allocation dynamique du nouveau maillon */
    nouveau = (Vol *)malloc(sizeof(Vol));

    if (nouveau == NULL)
    {
        printf("Erreur : allocation memoire impossible.\n");
        return 0;
    }

    /*
     * Copie de toutes les informations du vol.
     */
    strcpy(nouveau->numVol, v.numVol);
    strcpy(nouveau->destination, v.destination);

    nouveau->heureDepart = v.heureDepart;
    nouveau->nbPlaces = v.nbPlaces;
    nouveau->placesOccupees = v.placesOccupees;

    /* Le nouveau maillon n'a encore aucun voisin */
    nouveau->suiv = NULL;
    nouveau->pred = NULL;


    /*
     * CAS 1 :
     * La liste est vide.
     */
    if (*tete == NULL)
    {
        *tete = nouveau;
        return 1;
    }


    /*
     * CAS 2 :
     * Le nouveau vol doit être placé avant l'ancien premier.
     */
    if (v.heureDepart < (*tete)->heureDepart)
    {
        nouveau->suiv = *tete;
        (*tete)->pred = nouveau;
        *tete = nouveau;

        return 1;
    }


    /*
     * CAS 3 :
     * On cherche la position correcte dans la liste.
     */
    courant = *tete;

    while (courant->suiv != NULL &&
           courant->suiv->heureDepart <= v.heureDepart)
    {
        courant = courant->suiv;
    }


    /*
     * On insère nouveau après courant.
     */
    nouveau->suiv = courant->suiv;
    nouveau->pred = courant;

    /*
     * Si courant n'est pas le dernier élément,
     * son successeur doit pointer vers nouveau.
     */
    if (courant->suiv != NULL)
    {
        courant->suiv->pred = nouveau;
    }

    /*
     * courant doit maintenant pointer vers nouveau.
     */
    courant->suiv = nouveau;

    return 1;
}


/*
 * Recherche un vol à partir de son numéro.
 */
Vol *rechercherVol(Vol *tete, char *numVol)
{
    Vol *courant = tete;

    while (courant != NULL)
    {
        if (strcmp(courant->numVol, numVol) == 0)
        {
            return courant;
        }

        courant = courant->suiv;
    }

    return NULL;
}


/*
 * Supprime un vol à partir de son numéro.
 */
int supprimerVol(Vol **tete, char *numVol)
{
    Vol *volASupprimer;

    if (tete == NULL || *tete == NULL)
    {
        printf("Erreur : le registre est vide.\n");
        return 0;
    }

    /* Recherche du vol */
    volASupprimer = rechercherVol(*tete, numVol);

    if (volASupprimer == NULL)
    {
        printf("Erreur : le vol %s n'existe pas.\n", numVol);
        return 0;
    }


    /*
     * Si le vol possède un précédent,
     * celui-ci doit sauter le maillon supprimé.
     */
    if (volASupprimer->pred != NULL)
    {
        volASupprimer->pred->suiv = volASupprimer->suiv;
    }
    else
    {
        /*
         * Sinon, le vol est la tête de la liste.
         */
        *tete = volASupprimer->suiv;
    }


    /*
     * Si le vol possède un suivant,
     * celui-ci doit pointer vers le précédent.
     */
    if (volASupprimer->suiv != NULL)
    {
        volASupprimer->suiv->pred = volASupprimer->pred;
    }

    /* Libération de la mémoire */
    free(volASupprimer);

    return 1;
}


/*
 * Affiche les vols du plus tôt au plus tard.
 */
void afficherChronologique(Vol *tete)
{
    Vol *courant = tete;

    if (courant == NULL)
    {
        printf("Le registre est vide.\n");
        return;
    }

    printf("\n===== REGISTRE CHRONOLOGIQUE =====\n");

    while (courant != NULL)
    {
        printf("Vol : %s | Destination : %s | Depart : %04d"
               " | Places : %d/%d\n",
               courant->numVol,
               courant->destination,
               courant->heureDepart,
               courant->placesOccupees,
               courant->nbPlaces);

        courant = courant->suiv;
    }

    printf("==================================\n");
}


/*
 * Affiche les vols du plus tard au plus tôt.
 *
 * Cette fonction utilise directement le pointeur pred,
 * comme demandé dans l'énoncé.
 */
void afficherInverse(Vol *tete)
{
    Vol *courant = tete;

    if (courant == NULL)
    {
        printf("Le registre est vide.\n");
        return;
    }

    /*
     * On avance jusqu'au dernier vol.
     */
    while (courant->suiv != NULL)
    {
        courant = courant->suiv;
    }

    printf("\n===== REGISTRE INVERSE =====\n");

    /*
     * On repart du dernier vol et on remonte
     * avec le pointeur pred.
     */
    while (courant != NULL)
    {
        printf("Vol : %s | Destination : %s | Depart : %04d"
               " | Places : %d/%d\n",
               courant->numVol,
               courant->destination,
               courant->heureDepart,
               courant->placesOccupees,
               courant->nbPlaces);

        courant = courant->pred;
    }

    printf("============================\n");
}


/*
 * Fusionne deux registres triés.
 *
 * Le premier registre est prioritaire en cas de doublon.
 */
Vol *fusionnerRegistres(Vol *l1, Vol *l2)
{
    Vol *resultat = NULL;
    Vol *courant;


    /*
     * On parcourt le premier registre.
     * Tous ses vols sont conservés.
     */
    courant = l1;

    while (courant != NULL)
    {
        insererVolTrie(&resultat, *courant);
        courant = courant->suiv;
    }


    /*
     * On parcourt le deuxième registre.
     *
     * Si un numéro existe déjà dans resultat,
     * insererVolTrie() le détecte et le rejette.
     */
    courant = l2;

    while (courant != NULL)
    {
        if (rechercherVol(resultat, courant->numVol) != NULL)
        {
            printf("Doublon detecte lors de la fusion : "
                   "%s -> vol du premier registre conserve.\n",
                   courant->numVol);
        }
        else
        {
            insererVolTrie(&resultat, *courant);
        }

        courant = courant->suiv;
    }

    return resultat;
}


/*
 * Libère tous les maillons de la liste.
 */
void libererRegistre(Vol **tete)
{
    Vol *courant;
    Vol *suivant;

    if (tete == NULL)
    {
        return;
    }

    courant = *tete;

    while (courant != NULL)
    {
        suivant = courant->suiv;

        free(courant);

        courant = suivant;
    }

    /*
     * Après libération, la tête doit être remise à NULL.
     */
    *tete = NULL;
}
