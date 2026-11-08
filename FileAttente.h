#ifndef FILEATTENTE_H
#define FILEATTENTE_H

#include "RegistreVols.h"

typedef struct maillonFile
{
    Vol vol;
    int urgence;
    struct maillonFile *suiv;
} MaillonFile;

typedef struct
{
    MaillonFile *tete;
    MaillonFile *queue;
    int taille;
} FileAttente;

void initFile(FileAttente *f);
int estVideFile(FileAttente f);
void enfiler(FileAttente *f, Vol v, int urgence);
Vol defiler(FileAttente *f);
Vol consulterTeteFile(FileAttente f);
void decollerProchainVol(FileAttente *f);
void afficherFile(FileAttente f);
void libererFile(FileAttente *f);

#endif
