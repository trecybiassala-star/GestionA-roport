#include <stdio.h>
#include <string.h>

#include "RegistreVols.h"
#include "FileAttente.h"
#include "Pile.h"


/*
   SAISIR UN VOL
   */

Vol saisirVol()
{
    Vol v;

    printf("\n========== SAISIE D'UN VOL ==========\n");

    printf("Numero du vol : ");
    scanf("%7s", v.numVol);

    printf("Destination : ");
    scanf(" %29[^\n]", v.destination);

    printf("Heure de depart (ex : 1430) : ");
    scanf("%d", &v.heureDepart);

    printf("Nombre total de places : ");
    scanf("%d", &v.nbPlaces);

    printf("Places occupees : ");
    scanf("%d", &v.placesOccupees);

    /* Les liens sont initialises */
    v.suiv = NULL;
    v.pred = NULL;

    return v;
}


/*
   AFFICHER UN VOL
 */

void afficherUnVol(Vol v)
{
    printf("Numero       : %s\n", v.numVol);
    printf("Destination  : %s\n", v.destination);
    printf("Heure        : %04d\n", v.heureDepart);
    printf("Places       : %d\n", v.nbPlaces);
    printf("Occupees     : %d\n", v.placesOccupees);
}


/* =========================================================
   CREER UNE ACTION POUR LA PILE
   ========================================================= */

Action creerAction(TypeAction type, Vol v)
{
    Action a;

    a.type = type;
    a.volConcerne = v;
    a.suiv = NULL;

    return a;
}


/*
   MENU REGISTRE
   */

void menuRegistre(Vol **registre)
{
    int choix;
    char numero[8];

    Vol v;
    Vol *trouve;

    do
    {
        printf("\n");
        printf("========================================\n");
        printf("            REGISTRE DES VOLS\n");
        printf("========================================\n");
        printf("1. Ajouter un vol\n");
        printf("2. Rechercher un vol\n");
        printf("3. Supprimer un vol\n");
        printf("4. Afficher chronologiquement\n");
        printf("5. Afficher dans l'ordre inverse\n");
        printf("0. Retour\n");
        printf("========================================\n");

        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
            case 1:

                v = saisirVol();

                if (insererVolTrie(registre, v))
                {
                    printf("\nVol ajoute avec succes.\n");
                }
                else
                {
                    printf("\nImpossible d'ajouter le vol.\n");
                    printf("Le numero existe peut-etre deja.\n");
                }

                break;


            case 2:

                printf("\nNumero du vol a rechercher : ");
                scanf("%7s", numero);

                trouve = rechercherVol(*registre, numero);

                if (trouve != NULL)
                {
                    printf("\n========== VOL TROUVE ==========\n");
                    afficherUnVol(*trouve);
                }
                else
                {
                    printf("\nVol introuvable.\n");
                }

                break;


            case 3:

                printf("\nNumero du vol a supprimer : ");
                scanf("%7s", numero);

                if (supprimerVol(registre, numero))
                {
                    printf("\nVol supprime avec succes.\n");
                }
                else
                {
                    printf("\nVol introuvable.\n");
                }

                break;


            case 4:

                printf("\n========== REGISTRE CHRONOLOGIQUE ==========\n");

                if (*registre == NULL)
                {
                    printf("Le registre est vide.\n");
                }
                else
                {
                    afficherChronologique(*registre);
                }

                break;


            case 5:

                printf("\n========== REGISTRE INVERSE ==========\n");

                if (*registre == NULL)
                {
                    printf("Le registre est vide.\n");
                }
                else
                {
                    afficherInverse(*registre);
                }

                break;


            case 0:
                break;


            default:
                printf("\nChoix invalide.\n");
        }

    } while (choix != 0);
}


/*
   MENU FILE D'ATTENTE
   */

void menuFile(FileAttente *file, Vol *registre)
{
    int choix;
    int urgence;

    char numero[8];

    Vol *trouve;
    Vol vol;

    do
    {
        printf("\n");
        printf("========================================\n");
        printf("          FILE D'ATTENTE PISTE\n");
        printf("========================================\n");
        printf("1. Enfiler un vol\n");
        printf("2. Consulter la tete\n");
        printf("3. Defiler le premier vol\n");
        printf("4. Faire decoller le prochain vol\n");
        printf("5. Afficher la file\n");
        printf("6. Verifier si la file est vide\n");
        printf("0. Retour\n");
        printf("========================================\n");

        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
            case 1:

                if (registre == NULL)
                {
                    printf("\nLe registre est vide.\n");
                    break;
                }

                printf("\nNumero du vol a enfiler : ");
                scanf("%7s", numero);

                trouve = rechercherVol(registre, numero);

                if (trouve == NULL)
                {
                    printf("\nCe vol n'existe pas dans le registre.\n");
                    break;
                }

                printf("\nVol trouve : %s - %s\n",
                       trouve->numVol,
                       trouve->destination);

                printf("\nType :\n");
                printf("0. Normal\n");
                printf("1. Urgence\n");

                printf("Votre choix : ");
                scanf("%d", &urgence);

                if (urgence != 0 && urgence != 1)
                {
                    printf("\nChoix invalide.\n");
                    break;
                }

                enfiler(file, *trouve, urgence);

                printf("\nVol enfile avec succes.\n");

                break;


            case 2:

                if (estVideFile(*file))
                {
                    printf("\nLa file est vide.\n");
                }
                else
                {
                    vol = consulterTeteFile(*file);

                    printf("\n========== TETE DE LA FILE ==========\n");
                    afficherUnVol(vol);
                }

                break;


            case 3:

                if (estVideFile(*file))
                {
                    printf("\nLa file est vide.\n");
                }
                else
                {
                    vol = defiler(file);

                    printf("\n========== VOL DEFILE ==========\n");
                    afficherUnVol(vol);
                }

                break;


            case 4:

                if (estVideFile(*file))
                {
                    printf("\nAucun vol ne peut decoller.\n");
                    printf("La file est vide.\n");
                }
                else
                {
                    vol = consulterTeteFile(*file);

                    printf("\nVol qui va decoller : %s\n",
                           vol.numVol);

                    decollerProchainVol(file);

                    printf("Decollage effectue.\n");
                }

                break;


            case 5:

                printf("\n========== FILE D'ATTENTE ==========\n");

                if (estVideFile(*file))
                {
                    printf("La file est vide.\n");
                }
                else
                {
                    afficherFile(*file);
                }

                break;


            case 6:

                if (estVideFile(*file))
                {
                    printf("\nLa file est vide.\n");
                }
                else
                {
                    printf("\nLa file n'est pas vide.\n");
                }

                break;


            case 0:
                break;


            default:
                printf("\nChoix invalide.\n");
        }

    } while (choix != 0);
}


/*
   MENU PILE / HISTORIQUE
   */

void menuPile(PileHistorique *historique)
{
    int choix;

    do
    {
        printf("\n");
        printf("========================================\n");
        printf("          PILE / HISTORIQUE\n");
        printf("========================================\n");
        printf("1. Ajouter une action manuellement\n");
        printf("2. Depiler la derniere action\n");
        printf("3. Afficher l'historique\n");
        printf("4. Verifier si la pile est vide\n");
        printf("0. Retour\n");
        printf("========================================\n");

        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
            {
                int type;
                Vol v;

                printf("\nType d'action :\n");
                printf("1. AJOUT_VOL\n");
                printf("2. SUPPRESSION_VOL\n");
                printf("3. DECOLLAGE\n");

                printf("Votre choix : ");
                scanf("%d", &type);

                if (type < 1 || type > 3)
                {
                    printf("\nType invalide.\n");
                    break;
                }

                v = saisirVol();

                Action a;

                if (type == 1)
                {
                    a = creerAction(AJOUT_VOL, v);
                }
                else if (type == 2)
                {
                    a = creerAction(SUPPRESSION_VOL, v);
                }
                else
                {
                    a = creerAction(DECOLLAGE, v);
                }

                empilerAction(historique, a);

                printf("\nAction empilee avec succes.\n");

                break;
            }


            case 2:
            {
                Action a;

                if (estVidePile(*historique))
                {
                    printf("\nLa pile est vide.\n");
                }
                else
                {
                    a = depilerAction(historique);

                    printf("\nDerniere action retiree : ");

                    if (a.type == AJOUT_VOL)
                    {
                        printf("AJOUT_VOL");
                    }
                    else if (a.type == SUPPRESSION_VOL)
                    {
                        printf("SUPPRESSION_VOL");
                    }
                    else if (a.type == DECOLLAGE)
                    {
                        printf("DECOLLAGE");
                    }

                    printf("\nVol concerne : %s\n",
                           a.volConcerne.numVol);
                }

                break;
            }


            case 3:

                afficherHistorique(*historique);

                break;


            case 4:

                if (estVidePile(*historique))
                {
                    printf("\nLa pile est vide.\n");
                }
                else
                {
                    printf("\nLa pile contient des actions.\n");
                }

                break;


            case 0:
                break;


            default:
                printf("\nChoix invalide.\n");
        }

    } while (choix != 0);
}


/*
   PROGRAMME PRINCIPAL
    */

int main()
{
    Vol *registre = NULL;

    FileAttente file;

    PileHistorique historique;

    int choix;


    /* Initialisation des trois modules */
    initFile(&file);
    initPile(&historique);


    do
    {
        printf("\n\n");
        printf("============================================\n");
        printf("             GESTION AEROPORT\n");
        printf("============================================\n");
        printf("1. Tester le registre des vols\n");
        printf("2. Tester la file d'attente piste\n");
        printf("3. Tester la pile / historique\n");
        printf("4. Afficher le registre\n");
        printf("5. Afficher la file d'attente\n");
        printf("6. Afficher l'historique\n");
        printf("0. Quitter\n");
        printf("============================================\n");

        printf("Votre choix : ");
        scanf("%d", &choix);


        switch (choix)
        {
            case 1:

                menuRegistre(&registre);

                break;


            case 2:

                menuFile(&file, registre);

                break;


            case 3:

                menuPile(&historique);

                break;


            case 4:

                printf("\n========== REGISTRE ==========\n");

                if (registre == NULL)
                {
                    printf("Le registre est vide.\n");
                }
                else
                {
                    afficherChronologique(registre);
                }

                break;


            case 5:

                printf("\n========== FILE D'ATTENTE ==========\n");

                if (estVideFile(file))
                {
                    printf("La file est vide.\n");
                }
                else
                {
                    afficherFile(file);
                }

                break;


            case 6:

                afficherHistorique(historique);

                break;


            case 0:

                printf("\nFin du programme.\n");

                break;


            default:

                printf("\nChoix invalide.\n");
        }

    } while (choix != 0);


    /* Liberation de la memoire */

    libererFile(&file);
    libererPile(&historique);
    libererRegistre(&registre);

    return 0;
}
