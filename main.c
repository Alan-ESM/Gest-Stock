#include <stdio.h>
#include <stdlib.h>
#include "produits.h"
#include "commandes.h"
#include "statistiques.h"

void afficherMenu() {
    printf("\n");
    printf("\n");
    printf("\n");
    printf( "\033[0;32m                         ****************************************\n");
    printf( "                              Bienvenue Sur GESTOCK KEYCE\n");
    printf( "                         ****************************************\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                           Menu\n");
    printf("                           ----- \n");
    printf("                           1. Afficher les produits \n");
    printf("                           2. Ajouter un produits \n");
    printf("                           3. Modifier un produit\n");
    printf("                           4. Supprimer un produit\n");
    printf("                           5. Acheter des produits\n");
    printf("                           6. Statistiques\n");
    printf("                           7. Recherche\n");
    printf("                           8. Quitter\n");
     printf("\n");
    printf("\n");
    printf("Choisissez une option: ");
}

int lireEntreePositive() {
    int choix;
    char term;
    while (1) {
        if (scanf("%d%c", &choix, &term) != 2 || term != '\n' || choix <= 0) {
            while (getchar() != '\n');  // Efface le buffer
            printf("Entree invalide. Veuillez entrer un entier positif: ");
        } else {
            break;
        }
    }
    return choix;
}

int main() {
    int choix;
    do {
        afficherMenu();
        choix = lireEntreePositive();
        switch (choix) {
            case 1:
                afficherProduits();
                break;
            case 2:
                ajouterProduit();
                break;
            case 3:
                modifierProduit();
                break;
            case 4:
                supprimerProduit();
                break;
            case 5:
                acheterProduits();
                break;
            case 6:
                afficherStatistiques();
                break;
            case 7:
                Recherche();
                break;
            case 8:
                 printf("Au revoir !--------------------------------------\n");
                break;
            default:
                printf("Option invalide. Veuillez reessayer.\n");

        }
    } while (choix != 8);

    return 0;
}
