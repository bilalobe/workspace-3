#include "banque.h"
#include "transaction.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <random> // For rand()

// Constructor
GestionnaireBanque::GestionnaireBanque() {
    // ... (other initialization)
    clients = std::vector<Client>(); // Initialize the clients vector
    comptes = std::vector<std::shared_ptr<Compte>>(); // Initialize the comptes vector
    prets = std::vector<std::shared_ptr<Pret>>(); // Initialize the prets vector
    transactions = std::vector<Transaction>(); // Initialize the transactions vector
    nextClientId = 1; // Initialize the next client ID
    nextAccountId = 1; // Initialize the next account ID
    nextPretId = 1; // Initialize the next Pret ID
}

// Client Management

int GestionnaireBanque::creerCompte(int clientId) {
    // Find the client
    auto it = find_if(clients.begin(), clients.end(), 
                        [&](const Client& c) { return c.getId() == clientId; });

    if (it != clients.end()) {
        // Create a new account for the client (using make_shared)
        auto newCompte = std::make_shared<Compte>(nextAccountId++, 0.0, TypeCompte::Checking, *it); 
        comptes.push_back(newCompte); 
        it->addCompte(newCompte); // Add the account to the client's list

        return newCompte->getNumeroCompte();
    } else {
        cout << "Erreur: Client introuvable." << endl;
        return -1; // Indicate an error
    }
}

void GestionnaireBanque::modifierClient(int clientId) {
    // Implement logic to modify client details (name, etc.)
    // ...
    cout << "Modification du client (TODO)" << endl;
}

void GestionnaireBanque::supprimerClient(int clientId) {
    // Implement logic to delete a client (remove accounts and Prets)
    // ...
    cout << "Suppression du client (TODO)" << endl;
}

void GestionnaireBanque::afficherClients() const {
    if (clients.empty()) {
        cout << "Aucun client enregistré." << endl;
        return;
    }
    cout << "Clients:" << endl;
    for (const auto& client : clients) {
        cout << " - ID: " << client.getId() << ", Nom: " << client.getNom() << endl;
    }
}

void GestionnaireBanque::rechercherClientParNom(const std::string& nom) const {
    // Implement logic to search for a client by name
    // ...
    cout << "Recherche de client par nom (TODO)" << endl;
}

void GestionnaireBanque::rechercherClientParId(int clientId) const {
    // Implement logic to search for a client by ID
    // ...
    cout << "Recherche de client par ID (TODO)" << endl;
}

// Account Management

int GestionnaireBanque::creerCompte(int clientId) {
    // Find the client
    auto it = find_if(clients.begin(), clients.end(), 
                        [&](const Client& c) { return c.getId() == clientId; });

    if (it != clients.end()) {
        // Create a new account for the client
        auto newCompte = make_shared<Compte>(nextAccountId++, *it);
        comptes.push_back(newCompte);
        it->addCompte(newCompte); // Add the account to the client's list

        return newCompte->getNumeroCompte();
    } else {
        cout << "Erreur: Client introuvable." << endl;
        return -1; // Indicate an error
    }
}

void GestionnaireBanque::modifierCompte(int compteId) {
    // Implement logic to modify an account (e.g., change the limit)
    // ...
    cout << "Modification du compte (TODO)" << endl;
}

void GestionnaireBanque::supprimerCompte(int compteId) {
    // Implement logic to delete an account
    // ...
    cout << "Suppression du compte (TODO)" << endl;
}

void GestionnaireBanque::afficherComptes() const {
    if (comptes.empty()) {
        cout << "Aucun compte enregistré." << endl;
        return;
    }

    cout << "Comptes:" << endl;
    for (const auto& compte : comptes) {
        cout << " - Numéro: " << compte->getNumeroCompte() << ", Solde: " << compte->getSolde() << endl;
    }
}

void GestionnaireBanque::rechercherCompte(int compteId) const {
    // Implement logic to search for an account
    // ...
    cout << "Recherche de compte (TODO)" << endl;
}

std::shared_ptr<Compte> GestionnaireBanque::getCompteByBeneficiaryName(const std::string& beneficiaryName) const  {
    for (const auto& compte : comptes) {
        if (compte->getClient().getNom() == beneficiaryName) {
            return compte;
        }
    }
    return nullptr; // Not found
}

// Pret Management

int GestionnaireBanque::demanderPret(int clientId, double montant, int duree, double tauxInteret) {
    // Find the client
    auto it = find_if(clients.begin(), clients.end(), 
                        [&](const Client& c) { return c.getId() == clientId; });

    if (it != clients.end()) {
        // Create a new Pret
        auto newPret = make_shared<Pret>(nextPretId++, montant, tauxInteret, duree, "2023-12-01", "2025-12-01");
        prets.push_back(newPret);
        it->addPret(newPret);
        return newPret->getId();
    } else {
        cout << "Erreur: Client introuvable." << endl;
        return -1; // Indicate an error
    }
}

void GestionnaireBanque::rembourserPret(int pretId, double montant, const std::string& datePaiementStr) {
    // Find the Pret
    auto it = find_if(prets.begin(), prets.end(), 
                        [&](const std::shared_ptr<Pret>& p) { return p->getId() == pretId; });
    if (it != prets.end()) {
        // Register the payment
        (*it)->ajouterPaiement(montant, datePaiementStr);

        // Log the payment
        std::string dateTime = getCurrentDateTime(); 
        std::cout << dateTime << " - Paiement de prêt ID: " << pretId << " - Montant: " << montant << std::endl; 
    } else {
        cout << "Erreur: Prêt introuvable." << endl;
    }
}

int GestionnaireBanque::creerPret(int clientId, double montant, double tauxInteret, int duree, double tauxRampe)
{
    // ... (Implement logic to create a new Pret)
    // ... (Find the client, generate a unique Pret ID, create a new Pret object)
    
    // Example (assuming you have a vector of clients):
    auto it = std::find_if(clients.begin(), clients.end(), 
                            [&](const Client& client) { return client.getId() == clientId; });
    if (it != clients.end()) {
        int newPretId = nextPretId++; // Generate a unique Pret ID
        std::shared_ptr<Pret> nouveauPret = std::make_shared<Pret>(newPretId, montant, tauxInteret, duree, getCurrentDateTime(), getCurrentDateTime(), tauxRampe); // Create a new Pret object
        prets.push_back(nouveauPret);
        it->ajouterPret(nouveauPret);
        return newPretId;
    } 
    
    return -1; // Indicate an error 
}

bool GestionnaireBanque::rembourserPret(int pretId, double montant)
{
    // ... (Implement logic to repay a Pret)
    // ... (Find the Pret, update the balance, and potentially calculate interest)

    // Example (assuming you have a vector of prets):
    auto it = std::find_if(prets.begin(), prets.end(), 
                            [&](const std::shared_ptr<Pret>& pret) { 
                                return pret->getId() == pretId; 
                            });
    if (it != prets.end()) {
        (*it)->ajouterPaiement(montant, getCurrentDateTime());
        // ... (Update the Pret balance based on your logic)
        return true; // Indicate success
    }
    return false; // Indicate failure
}



std::vector<Pret> GestionnaireBanque::getPrets() const {
    std::vector<Pret> allPrets;
    for (const auto& pret : prets) { // Access the prets vector
        allPrets.push_back(*pret);
    }
    return allPrets;
}

void GestionnaireBanque::afficherPrets(int clientId) const {
    auto it = std::find_if(clients.begin(), clients.end(), 
                            [&](const Client& client) { return client.getId() == clientId; });
    if (it != clients.end()) {
        it->afficherPrets();
    } else {
        std::cout << "Erreur: Client ID " << clientId << " introuvable." << std::endl;
    }
}

bool GestionnaireBanque::annulerPret(int pretId) {
    auto it = std::find_if(prets.begin(), prets.end(), 
                            [&](const std::shared_ptr<Pret>& pret) { return pret->getId() == pretId; });
    if (it != prets.end() && (*it)->isCancelable()) {
        (*it)->setStatut(PretStatut::Canceled);
        return true; // Indicate success
    }
    std::cerr << "Erreur: Le prêt ne peut pas être annulé." << std::endl;
    return false; // Indicate failure
}

void GestionnaireBanque::rembourserPret(int pretId, double montant, const std::string& datePaiementStr) {
    auto it = std::find_if(prets.begin(), prets.end(), 
                            [&](const std::shared_ptr<Pret>& p) { return p->getId() == pretId; });
    if (it != prets.end()) {
        (*it)->ajouterPaiement(montant, datePaiementStr);
        std::cout << getCurrentDateTime() << " - Paiement de prêt ID: " << pretId << " - Montant: " << montant << std::endl;
    } else {
        std::cout << "Erreur: Prêt introuvable." << std::endl;
    }
}

int GestionnaireBanque::creerPret(int clientId, double montant, double tauxInteret, int duree, double tauxRampe) {
    auto it = std::find_if(clients.begin(), clients.end(), 
                            [&](const Client& client) { return client.getId() == clientId; });
    if (it != clients.end()) {
        int newPretId = nextPretId++;
        auto nouveauPret = std::make_shared<Pret>(newPretId, montant, tauxInteret, duree, getCurrentDateTime(), getCurrentDateTime(), tauxRampe);
        prets.push_back(nouveauPret);
        it->ajouterPret(nouveauPret);
        return newPretId;
    }
    return -1; // Indicate an error
}

// Transaction Management

void GestionnaireBanque::deposer(int compteId, double montant) {
    // Find the account
    auto it = find_if(comptes.begin(), comptes.end(), 
                        [&](const std::shared_ptr<Compte>& c) { return c->getNumeroCompte() == compteId; });
    if (it != comptes.end()) {
        (*it)->Deposer(montant); // Deposit into the account
        cout << "Dépôt effectué avec succès." << endl;
    } else {
        cout << "Erreur: Compte introuvable." << endl;
    }
}

void GestionnaireBanque::retirer(int compteId, double montant) {
    // Find the account
    auto it = find_if(comptes.begin(), comptes.end(), 
                        [&](const std::shared_ptr<Compte>& c) { return c->getNumeroCompte() == compteId; });
    if (it != comptes.end()) {
        (*it)->Retirer(montant); // Withdraw from the account
        cout << "Retrait effectué avec succès." << endl;
    } else {
        cout << "Erreur: Compte introuvable." << endl;
    }
}

void GestionnaireBanque::afficherTransactionsCompte(int compteId) const {
    for (const auto& client : clients) {
        for (const auto& compte : client.getComptes()) {
            if (compte.getId() == compteId) {
                compte.afficherTransactions();
                return;
            }
        }
    }
    std::cout << "Erreur: Compte ID " << compteId << " introuvable." << std::endl;
}

void GestionnaireBanque::afficherTransactionsClient(int clientId) const {
    auto it = std::find_if(clients.begin(), clients.end(), 
                            [&](const Client& client) { return client.getId() == clientId; });
    if (it != clients.end()) {
        it->afficherTransactions();
    } else {
        std::cout << "Erreur: Client ID " << clientId << " introuvable." << std::endl;
    }
}

void GestionnaireBanque::enregistrerTransaction(const Transaction& transaction) {
    // Assuming transactions are stored within accounts or clients
    for (auto& client : clients) {
        for (auto& compte : client.getComptes()) {
            if (compte.getId() == transaction.getCompteId()) {
                compte.ajouterTransaction(transaction);
                return;
            }
        }
    }
    std::cerr << "Erreur: Transaction non enregistrée, compte ID introuvable." << std::endl;
}

void GestionnaireBanque::sauvegarderClients(const std::string& filename) {
    nlohmann::json j;
    for (const auto& client : clients) {
        j["clients"].push_back(client.toJson());
    }
    std::ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4); // Pretty print with 4 spaces
        file.close();
    } else {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier pour sauvegarde." << std::endl;
    }
}

void GestionnaireBanque::chargerClients(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        nlohmann::json j;
        file >> j;
        file.close();
        clients.clear();
        for (const auto& clientJson : j["clients"]) {
            Client client;
            client.fromJson(clientJson);
            clients.push_back(client);
        }
    } else {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier pour chargement." << std::endl;
    }
}

int GestionnaireBanque::genererNumeroCompteUnique() {
    int numeroCompte;
    do {
        numeroCompte = rand() % 1000000; // Generate a random 6-digit number
    } while (compteExists(numeroCompte));
    return numeroCompte;
}

bool GestionnaireBanque::compteExists(int numeroCompte) const {
    for (const auto& client : clients) {
        for (const auto& compte : client.getComptes()) {
            if (compte.getId() == numeroCompte) {
                return true;
            }
        }
    }
    return false;
}

bool GestionnaireBanque::rembourserPret(int pretId, double montant) {
    auto it = std::find_if(prets.begin(), prets.end(), 
                            [&](const std::shared_ptr<Pret>& pret) { return pret->getId() == pretId; });
    if (it != prets.end()) {
        (*it)->ajouterPaiement(montant, getCurrentDateTime());
        return true; // Indicate success
    }
    return false; // Indicate failure
}