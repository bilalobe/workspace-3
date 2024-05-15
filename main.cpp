#include <iostream>
#include <vector>

#include "client.cpp"
#include "compte.cpp"
#include "transaction.cpp"
#include "banque.cpp" 
#include "pret.cpp" 
#include "pret.h"


using namespace std;

// Function Declarations (moved from menu.h)
void afficherMenuPrincipal();
void afficherMenuClient();
void afficherMenuCompte(); 
void afficherMenuTransaction();
void afficherSousMenuTransactions();
void demanderPret();
void afficherMenuPret(); 
void afficherSousMenuRechercherClient();

// Global variable to store the currently logged-in client ID (initialize to -1 for no user)
int clientIdSession = -1; 

int main() {
    int choix;

    do {
        std::cout << "\n----- Menu Principal -----" << std::endl;
        std::cout << "1. Se Connecter" << std::endl;
        std::cout << "2. Quitter" << std::endl;
        std::cout << "Entrez votre choix: ";
        std::cin >> choix;

        switch (choix) {
            case 1: {
                int clientId;
                std::cout << "Entrez votre ID client: ";
                std::cin >> clientId;
                // Implement client authentication here (e.g., check against a list of clients)
                // For now, we'll just set the session ID
                clientIdSession = clientId;
                std::cout << "Connexion réussie!" << std::endl;
                afficherMenuPrincipal(); // Display the main menu after login
                break;
            }
            case 2:
                std::cout << "Au revoir!" << std::endl;
                break;
            default:
                std::cout << "Choix invalide. Veuillez réessayer." << std::endl;
        }
    } while (choix != 2);

    return 0;
}

void afficherMenuPrincipal() {
    int choix;
    do {
        std::cout << "\n----- Menu Principal -----" << std::endl;
        std::cout << "1. Client" << std::endl;
        std::cout << "2. Compte" << std::endl;
        std::cout << "3. Transaction" << std::endl;
        std::cout << "4. Déconnexion" << std::endl; // Add a logout option
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
                clientIdSession = -1; // Clear the session ID on logout
                std::cout << "Déconnexion réussie!" << std::endl;
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
        std::cout << "6. Prets" << std::endl; // Moved "Prets" to be a submenu of Client
        std::cout << "7. Retour au menu principal" << std::endl; // Updated choice number
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
                int clientId;
                std::cout << "Entrez l'ID du client à supprimer: ";
                std::cin >> clientId;
                banque.supprimerClient(clientId);  // Placeholder
                break;
            }
            case 4: 
                banque.afficherClients(); 
                break;
 
            case 5: 
                afficherSousMenuRechercherClient(); // Call the new sub-submenu
                break;

            case 6: 
                afficherMenuPret();
                break;

            case 7: // Updated choice number
                std::cout << "Retour au menu principal." << std::endl;
                break;
            default: 
                std::cout << "Choix invalide. Veuillez reessayer." << std::endl;
        }
    } while (choix != 7); // Updated choice number 
}


void afficherSousMenuRechercherClient() {
    int choix;
    do {
        std::cout << "\n----- Sous-Menu Rechercher Client -----" << std::endl;
        std::cout << "1. Rechercher par nom" << std::endl;
        std::cout << "2. Rechercher par ID" << std::endl;
        std::cout << "3. Retour au Menu Client" << std::endl;
        std::cout << "Entrez votre choix: ";
        std::cin >> choix;

        switch (choix) {
            case 1: {
                std::string nomClient;
                std::cout << "Entrez le nom du client à rechercher: ";
                std::cin.ignore();
                std::getline(std::cin, nomClient);
                banque.rechercherClientParNom(nomClient); // Implement in GestionnaireBanque
                break;
            }
            case 2: {
                int clientId;
                std::cout << "Entrez l'ID du client à rechercher: ";
                std::cin >> clientId;
                banque.rechercherClientParId(clientId); // Implement in GestionnaireBanque
                break;
            }
            case 3: 
                std::cout << "Retour au Menu Client." << std::endl;
                break;
            default: 
                std::cout << "Choix invalide. Veuillez reessayer." << std::endl;
        } 
    } while (choix != 3);
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
                // Call the function to create a new account 
                int clientId;
                std::cout << "Entrez l'ID du client pour le nouveau compte: ";
                std::cin >> clientId;
                banque.creerCompte(clientId); 
                break;
            }
            case 2: { // Modifier Compte
                int compteId;
                std::cout << "Entrez l'ID du compte à modifier : ";
                std::cin >> compteId;

                // Check if the account exists
                if (banque.compteExists(compteId)) { 
                    banque.modifierCompte(compteId);  
                } else {
                    std::cout << "Erreur: Compte avec l'ID " << compteId << " non trouvé." << std::endl;
                    // Optionally, you can allow the user to re-enter the account ID here:
                    std::cout << "Voulez-vous réessayer ? (o/n): ";
                    char reponse;
                    std::cin >> reponse;
                    if (reponse != 'o' && reponse != 'O') {
                        break; // Exit the 'Modifier Compte' case
                    } 
                }
                break;
            }
            case 3: {
                // Call the function to delete an account
                int compteId;
                std::cout << "Entrez l'ID du compte à supprimer : ";
                std::cin >> compteId;
                banque.supprimerCompte(compteId); 
                break;
            }
            case 4: 
                // Call the function to display all accounts
                banque.afficherComptes(); 
                break;
            case 5: {
                // Call the function to search for an account
                int compteId;
                std::cout << "Entrez l'ID du compte à rechercher : ";
                std::cin >> compteId;
                banque.rechercherCompte(compteId); 
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
                afficherSousMenuTransactions();  // Call the sub-submenu function
                break; 
            case 4: 
                std::cout << "Retour au menu principal." << std::endl;
                break;
            default: 
                std::cout << "Choix invalide. Veuillez reessayer." << std::endl;
        }
    } while (choix != 4); 
}

void afficherSousMenuTransactions() {
    int choix;
    do {
        std::cout << "\n----- Sous-Menu Transactions -----" << std::endl;
        std::cout << "1. Afficher toutes les transactions" << std::endl; 
        std::cout << "2. Afficher les transactions d'un compte" << std::endl;
        std::cout << "3. Afficher les transactions d'un client" << std::endl;
        std::cout << "4. Retour au menu Transactions" << std::endl;
        std::cout << "Entrez votre choix: ";
        std::cin >> choix;

        switch (choix) {
            case 1:
                banque.afficherTransactions();
                break;
            case 2: {
                int compteId;
                std::cout << "Entrez l'ID du compte: ";
                std::cin >> compteId;
                banque.afficherTransactionsCompte(compteId); // Implement in GestionnaireBanque
                break;
            }
            case 3: {
                int clientId;
                std::cout << "Entrez " ;
                std::cin >> clientId;
                banque.afficherTransactionsClient(clientId); // Implement in GestionnaireBanque
                break;
            }
            case 4:
                std::cout << "Retour au menu Transactions." << std::endl;
                break;
                
            default:
                std::cout << "Choix invalide. Veuillez reessayer." << std::endl;
        }
    } while (choix != 4);
}
void afficherMenuPret() {
    int choix;
    do {
        std::cout << "\n----- Menu Pret -----" << std::endl;
        std::cout << "1. Demander un pret" << std::endl;
        std::cout << "2. Afficher mes prets" << std::endl; 
        std::cout << "3. Effectuer un remboursement" << std::endl; 
        std::cout << "4. Retour au Menu Client" << std::endl; // Changed to return to Client menu
        std::cout << "Entrez votre choix: ";
        std::cin >> choix;

        switch (choix) {
            case 1: {
                demanderPret(); 
                break; 
            }

            case 2: { 
                // Call a function to display loans 
                banque.afficherPrets(clientIdSession);
                break;
            }
            case 3: {
                int pretId;
                double montant;
                std::string datePaiementStr;

                std::cout << "Entrez l'ID du prêt : ";
                std::cin >> pretId;

                std::shared_ptr<Pret> pret;

                if (pret != nullptr) {
                    std::cout << "Entrez le montant du remboursement : ";
                    std::cin >> montant;
                    std::cout << "Entrez la date du remboursement (YYYY-MM-DD) : ";
                    std::cin >> datePaiementStr;
                    banque.enregistrerRemboursement(pret, montant, datePaiementStr, clientIdSession);
                } else {
                    std::cout << "Aucun prêt trouvé avec l'ID " << pretId << "." << std::endl;
                }
                break; 
            }
            case 4:
                std::cout << "Retour au Menu Client." << std::endl; // Return to Client menu
                break;
            default: 
                std::cout << "Choix invalide. Veuillez reessayer." << std::endl;
        }
    } while (choix != 4); 
}
