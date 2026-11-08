#ifndef REGISTREVOLS_H
#define REGISTREVOLS_H

typedef struct vol
{
    char numVol[8];
    char destination[30];
    int heureDepart;
    int nbPlaces;
    int placesOccupees;

    struct vol *suiv;
    struct vol *pred;
} Vol;

int insererVolTrie(Vol **tete, Vol v);

Vol *rechercherVol(Vol *tete, char *numVol);

int supprimerVol(Vol **tete, char *numVol);

void afficherChronologique(Vol *tete);

void afficherInverse(Vol *tete);

Vol *fusionnerRegistres(Vol *l1, Vol *l2);

void libererRegistre(Vol **tete);

#endif
