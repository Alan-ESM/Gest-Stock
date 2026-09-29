#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "produits.h"

void Recherche() {
    char nom[50];
    FILE* fptr;
    char content[1000];
    int found = 0;  // Variable pour suivre si un produit est trouve

    printf("Entrez le produit que vous recherchez : ");
    scanf("%50s", nom);  // Limite à 50 caracteres pour eviter le depassement de tampon

    fptr = fopen("produits.csv", "r");
    if (fptr != NULL) {
        while (fgets(content, 1000, fptr)) {
            if (strstr(content, nom) != NULL) { // Verifie si le nom est dans la ligne
                printf("Produit trouvé : %s", content);
                found = 1;
                break; // On arrete des qu'on trouve le  produit correspondant
            }
        }
        fclose(fptr);

        if (!found) {
            printf("Produit non trouve.\n");
        }
    } else {
        printf("Echec de l'ouverture du fichier.\n");
    }
}



void acheterProduits() {
    int id;
    int quantite;

    printf("Entrez L'ID du produit a acheter: \n");
    scanf("%d", &id);
    printf("Entrez Quantite a acheter: \n");
    scanf("%d", &quantite);

    FILE *fichier = fopen("produits.csv", "r");
    FILE *tempFichier = fopen("temp.csv", "w");
    if (fichier
         == NULL || tempFichier == NULL) {
        printf("Erreur: Impossible d'ouvrir les fichiers\n");
        return;
    }

    char ligne[256];
    int trouver = 0;
    Produit produitAchete;
    while (fgets(ligne, sizeof(ligne), fichier)) {
        Produit produit;
        sscanf(ligne, "%d,%[^,],%d,%f", &produit.id, &produit.nom, &produit.quantite, &produit.prix);
        if (produit.id == id) {
            if (produit.quantite >= quantite) {
                produit.quantite -= quantite;
                produitAchete = produit; // Sauvegarder le produit acheté pour la facture
                trouver = 1;
            } else {
                printf("Quantite insuffisante en stock.\n");
                fclose(fichier);
                fclose(tempFichier);
                remove("temp.csv");
                return;
            }
        }
        fprintf(tempFichier, "%d,%s,%d,%.2f\n", produit.id, produit.nom, produit.quantite, produit.prix);
    }
    fclose(fichier);
    fclose(tempFichier);

    if (trouver) {
        remove("produits.csv");
        rename("temp.csv", "produits.csv");
        printf("Achat effectue avec succes.\n");

        // Générer le numéro de facture unique
        FILE *numFactureFile = fopen("numero_facture.txt", "r");
        int numeroFacture = 1;
        if (numFactureFile != NULL) {
            fscanf(numFactureFile, "%d", &numeroFacture);
            fclose(numFactureFile);
            numeroFacture++;
        }

        numFactureFile = fopen("numero_facture.txt", "w");
        fprintf(numFactureFile, "%d", numeroFacture);
        fclose(numFactureFile);

        // Obtenir la date et l'heure actuelles
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char date[100];
        strftime(date, sizeof(date)-1, "%d/%m/%Y %H:%M:%S", t);

        // Calculer le montant total
        float montantTotal = quantite * produitAchete.prix;

        // Créer le fichier de facture
        char nomFacture[50];
        sprintf(nomFacture, "facture_%d.txt", numeroFacture);

        FILE *factureFichier = fopen(nomFacture, "w");
        if (factureFichier == NULL) {
            printf("Erreur: Impossible de créer la facture\n");
            return;
        }

        fprintf(factureFichier, "---------------------------------------\n");
        fprintf(factureFichier, "                FACTURE                \n");
        fprintf(factureFichier, "---------------------------------------\n");
        fprintf(factureFichier, "Numero de facture : %d\n", numeroFacture);
        fprintf(factureFichier, "Date : %s\n\n", date);
        fprintf(factureFichier, "Produit achete : %s\n", produitAchete.nom);
        fprintf(factureFichier, "Quantite : %d\n", quantite);
        fprintf(factureFichier, "Prix unitaire : %.2f\n", produitAchete.prix);
        fprintf(factureFichier, "Montant total : %.2f\n", montantTotal);
        fprintf(factureFichier, "---------------------------------------\n");
        fprintf(factureFichier, "Merci pour votre achat !\n");
        fclose(factureFichier);

        printf("Facture generee : %s\n", nomFacture);

    } else {
        remove("temp.csv");
        printf("Produit non trouve.\n");
    }
}
