# Gestion Aéroport

Application console en langage C pour gérer les vols d'un aéroport :
registre des vols, file d'attente de la piste avec priorité (normal / urgence)
et historique des actions avec possibilité d'annuler la dernière opération.

## Fonctionnalités
- Ajouter, rechercher et supprimer un vol du registre
  (numéro, destination, heure de départ, places totales et occupées)
- Afficher le registre dans l'ordre chronologique ou inverse
- Mettre un vol en file d'attente de décollage (priorité normale ou urgence)
- Faire décoller le prochain vol et afficher la file d'attente de la piste
- Annuler la dernière action (ajout, suppression ou décollage)
- Afficher l'historique des opérations
- Libération de la mémoire à la fermeture du programme

## Structures de données utilisées
- Registre des vols : liste ordonnée, parcourable dans les deux sens
- File d'attente de la piste : file avec priorité (normal / urgence)
- Historique : pile, utilisée pour annuler la dernière action

## Menu principal
1. Ajouter un vol au registre
2. Rechercher un vol
3. Supprimer un vol
4. Afficher le registre
5. Enfiler un vol prêt au décollage
6. Faire décoller le prochain vol
7. Afficher la file d'attente piste
8. Annuler la dernière action
9. Afficher l'historique
0. Quitter

## Lancer l'application
1. Ouvrir le projet `GestionAeroport` dans Code::Blocks, puis compiler et exécuter
2. Ou, en ligne de commande : `gcc *.c -o GestionAeroport` puis `./GestionAeroport`

## Exemple de scénario de test
1 (ajouter plusieurs vols) → 4 (vérifier le registre) → 2 (rechercher un vol)
→ 5 (enfiler un vol normal) → 5 (enfiler un vol urgent) → 7 (vérifier la file)
→ 6 (faire décoller) → 9 (historique) → 8 (annuler) → 4 (vérifier le registre) → 0 (quitter)

## Technologies
Langage C · Code::Blocks

## Auteurs
Trecy Biassala, Université Gaston Berger (UGB), Licence 3 Génie Informatique
