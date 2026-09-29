Gest-Stock


En quoi consiste le projet ?
GestStock est une application console en C destinée à gérer un stock de produits :

•	afficher les produits ;
•	ajouter, modifier et supprimer un produit ;
•	acheter une quantité de produits ;
•	rechercher un produit ;
•	afficher des statistiques ;
•	générer une facture texte.

Les données sont stockées dans produits.csv, avec des factures dans des fichiers .txt.

Ce qui semble déjà réalisé
•	Menu principal.
•	Gestion élémentaire des produits.
•	Génération automatique d’un identifiant.
•	Modification et suppression via fichier temporaire.
•	Recherche par nom.
•	Décrément du stock lors d’un achat.
•	Vérification d’une quantité disponible.
•	Numérotation des factures dans numero_facture.txt.
•	Création de factures avec date, produit, quantité, prix et montant total.
•	Statistiques : nombre de produits, quantité totale, prix moyen, produit le moins cher et le plus cher.
•	Présence d’un README expliquant brièvement l’objectif.

Vérification effectuée
Le projet compile avec GCC, mais avec plusieurs avertissements importants :

•	scanf("%d", &nouveauProduit.prix) utilise %d alors que le prix est un float. Cela peut corrompre la mémoire et produire des résultats incorrects.
•	sscanf utilise &produit.nom au lieu de produit.nom dans commandes.c.
•	Recherche est appelée sans déclaration visible dans main.c.

Ce qui manque ou doit être corrigé en priorité
•	Corriger immédiatement les formats scanf/sscanf (%f pour un float, et tableau de caractères sans &).
•	Vérifier chaque retour de scanf et refuser les valeurs négatives ou absurdes.
•	Empêcher les dépassements de tampon avec des tailles maximales et des formats limités.
•	Gérer les noms de produits contenant des espaces ; scanf("%s") ne les accepte pas.
•	Vérifier le prix, la quantité et l’existence du produit avant modification ou achat.
•	Ajouter les déclarations de fonctions dans les fichiers .h appropriés.
•	Corriger le cas où le fichier de stock est vide : les valeurs du produit minimum/maximum peuvent être non initialisées ou affichées de manière incohérente.
•	Utiliser un fichier temporaire unique et vérifier le résultat de remove et rename.
•	Empêcher l’écrasement ou la perte de données en cas d’arrêt pendant une modification.
•	Améliorer la recherche pour analyser le champ nom plutôt que toute la ligne CSV.
•	Ajouter des tests d’achat, de stock insuffisant, de produit inexistant et de facture.
•	Nettoyer les fichiers Code::Blocks, VS Code et le fichier temporaire ~$pport de Projet.docx avant livraison.

Niveau estimé
Prototype fonctionnel mais non fiable en production tant que les erreurs de format C et de validation des entrées ne sont pas corrigées.
