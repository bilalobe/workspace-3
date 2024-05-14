#include "menu.h"

extern GestionnaireBanque banque;

void afficherMenuPrincipal() {
    int choix;
    do {
        std::cout << "\n----- Menu Principal -----" << std::endl;
        std::cout << "1. Client" << std::endl;
        std::cout << "2. Compte" << std::endl;
        std::cout << "3. Transaction" << std::endl;
        std::cout << "4. Quitter" << std::endl;
        std::cout << "Entrez votre choix: ";
        std::cin >> choix;

        switch (choix) {
            case 1: 
                afficherMenuClient(); 
                break;
            case 2: 
                afficherMenuCompte(); 
                break;
            case 3: 
                afficherMenuTransaction(); 
                break;
            case 4: 
                std::cout << "Au revoir!" << std::endl;
                break;
            default: 
                std::cout << "Choix invalide. Veuillez reessayer." << std::endl;
        }
    } while (choix != 4); 
}

void afficherMenuClient() {
    int choix;
    do {
        std::cout << "\n----- Menu Client -----" << std::endl;
        std::cout << "1. Nouveau Client" << std::endl;
        std::cout << "2. Modifier Client" << std::endl;
        std::cout << "3. Supprimer Client" << std::endl;
        std::cout << "4. Afficher Clients" << std::endl;
        std::cout << "5. Rechercher Client" << std::endl;
        std::cout << "6. Retour au menu principal" << std::endl;
        std::cout << "Entrez votre choix: ";
        std::cin >> choix;

        switch (choix) {
            case 1: {
                // Call the function to create a new client (you'll need to implement this)
                std::string nomClient;
                std::cout << "Entrez le nom du client: ";
                std::cin.ignore(); // Ignore leftover newline character
                std::getline(std::cin, nomClient); // Read the entire line 
                banque.nouveauClient(nomClient); // Placeholder - You'll need to implement this in GestionnaireBanque
                break;
            }
            case 2: {
                // Call the function to modify a client (you'll need to implement this)
                int clientId;
                std::cout << "Entrez l'ID du client à modifier: ";
                std::cin >> clientId;
                banque.modifierClient(clientId);  // Placeholder 
                break;
            }
            case 3: {
                // Call the function to delete a client (you'll need to implement this)
                int clientId;
                std::cout << "Entrez l'ID du client à supprimer: ";
                std::cin >> clientId;
                banque.supprimerClient(clientId);  // Placeholder
                break;
            }
            case 4: 
                // Call the function to display all clients (you'll need to implement this)
                banque.afficherClients(); // Placeholder
                break;
            case 5: {
                // Call the function to search for a client (you'll need to implement this)
                std::string searchTerm;
                std::cout << "Entrez le nom du client à rechercher: ";
                std::cin.ignore();
                std::getline(std::cin, searchTerm);
                banque.rechercherClient(searchTerm); // Placeholder
                break;
            }
            case 6: 
                std::cout << "Retour au menu principal." << std::endl;
                break;
            default: 
                std::cout << "Choix invalide. Veuillez reessayer." << std::endl;
        }
    } while (choix != 6); 
}

void afficherMenuCompte() {
    int choix;
    do {
        std::cout << "\n----- Menu Compte -----" << std::endl;
        std::cout << "1. Nouveau Compte" << std::endl;
        std::cout << "2. Modifier Compte" << std::endl;
        std::cout << "3. Supprimer Compte" << std::endl;
        std::cout << "4. Afficher Comptes" << std::endl;
        std::cout << "5. Rechercher Compte" << std::endl;
        std::cout << "6. Retour au menu principal" << std::endl;
        std::cout << "Entrez votre choix: ";
        std::cin >> choix;

        switch (choix) {
            case 1: {
                // Call the function to create a new account (you'll need to implement this)
                // Assuming you have a function like banque.creerCompte(clientId); 
                int clientId;
                std::cout << "Entrez l'ID du client pour le nouveau compte: ";
                std::cin >> clientId;
                banque.creerCompte(clientId); 
                break;
            }
            // Implement cases 2-5 similarly, calling functions from GestionnaireBanque
            case 6:
                std::cout << "Retour au menu principal." << std::endl;
                break;
            default:
                std::cout << "Choix invalide. Veuillez reessayer." << std::endl;
        }
    } while (choix != 6);
}

void afficherMenuTransaction() {
    int choix;
    do {
        std::cout << "\n----- Menu Transaction -----" << std::endl;
        std::cout << "1. Deposer" << std::endl;
        std::cout << "2. Retirer" << std::endl;
        std::cout << "3. Afficher Transactions" << std::endl;
        std::cout << "4. Retour au menu principal" << std::endl;
        std::cout << "Entrez votre choix: ";
        std::cin >> choix;

        switch (choix) {
            case 1: {
                // Implement deposit logic here
                int compteId;
                double montant;
                std::cout << "Entrez l'ID du compte: ";
                std::cin >> compteId;
                std::cout << "Entrez le montant à déposer: ";
                std::cin >> montant;
                banque.deposer(compteId, montant); // Implement in GestionnaireBanque
                break;
            }
            case 2: {
                // Implement withdrawal logic here 
                int compteId;
                double montant;
                std::cout << "Entrez l'ID du compte: ";
                std::cin >> compteId;
                std::cout << "Entrez le montant à retirer: ";
                std::cin >> montant;
                banque.retirer(compteId, montant); // Implement in GestionnaireBanque
                break;
            }
            case 3: 
                // Call the function to display transactions (you'll need to implement this)
                banque.afficherTransactions(); // Placeholder
                break;
            case 4: 
                std::cout << "Retour au menu principal." << std::endl;
                break;
            default: 
                std::cout << "Choix invalide. Veuillez reessayer." << std::endl;
        }
    } while (choix != 4); 
}
// menu.cpp 
// ... (Other menu functions) ...

void afficherMenuPret() {
    int choix;
    do {
        std::cout << "\n----- Menu Pret -----" << std::endl;
        std::cout << "1. Demander un pret" << std::endl;
        std::cout << "2. Afficher les prets" << std::endl; 
        std::cout << "3. Effectuer un remboursement" << std::endl; 
        // ... Add more options (e.g., modify loan) ...
        std::cout << "4. Retour au menu principal" << std::endl;
        std::cout << "Entrez votre choix: ";
        std::cin >> choix;

        switch (choix) {
            case 1: {
                // Call a function in GestionnaireBanque to handle loan requests
                // (e.g., banque.demanderPret(...))
                break; 
            }
            case 2:
                // Call a function to display loans 
                // (e.g., banque.afficherPrets(...))
                break;
            case 3: {
                // Call a function to record a payment
                // (e.g., banque.enregistrerPaiement(...))
                break; 
            }
            // ... Handle other options ...
            case 4: 
                std::cout << "Retour au menu principal." << std::endl;
                break;
            default: 
                std::cout << "Choix invalide. Veuillez reessayer." << std::endl;
        }
    } while (choix != 4); 
}