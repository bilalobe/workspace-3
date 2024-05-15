#include "banque.h"
#include "transaction.h"

#include <iostream> 
#include <sstream>
#include <algorithm>
#include <random>
#include <fstream>


using namespace std;


int GestionnaireBanque::genererNumeroCompteUnique() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(10000, 99999); 
    int newNumeroCompte;
    do {
        newNumeroCompte = distribution(generator); 
    } while (compteExists(newNumeroCompte)); // Check against existing accounts in GestionnaireBanque
    return newNumeroCompte;
}

void GestionnaireBanque::nouveauClient(const std::string& nom) {
    std::string clientName;
    std::cout << "Entrez le nom du client: ";
    std::cin.ignore();
    std::getline(std::cin, clientName);

    Client client(dernierIdClient++, clientName);
    clients.push_back(client);
    std::cout << "Nouveau client ajouté avec succès! ID du client: " << client.getId() << std::endl;
}

void GestionnaireBanque::modifierClient(int clientId) {
    for (auto& client : clients) {
        if (client.getId() == clientId) {
            std::cout << "Entrez le nouveau nom du client: ";
            std::string nouveauNom;
            std::cin.ignore();
            std::getline(std::cin, nouveauNom);
            client.setNom(nouveauNom);
            std::cout << "Client modifié avec succès!" << std::endl;
            return;
        }
    }
    std::cout << "Client avec l'ID " << clientId << " non trouvé." << std::endl;
}

void GestionnaireBanque::supprimerClient(int clientId) {
    // Using std::remove_if for efficient removal
    auto newEnd = std::remove_if(clients.begin(), clients.end(),
                                 [clientId](const Client& c) { return c.getId() == clientId; });
    if (newEnd != clients.end()) {
        clients.erase(newEnd, clients.end());
        std::cout << "Client supprimé avec succès!" << std::endl;
    } else {
        std::cout << "Client avec l'ID " << clientId << " non trouvé." << std::endl;
    }
}

void GestionnaireBanque::afficherClients() const {
    if (clients.empty()) {
        std::cout << "Aucun client enregistré." << std::endl;
        return;
    }
    std::cout << "\nListe des clients:" << std::endl;
    for (const auto& client : clients) {
        std::cout << "ID: " << client.getId() << ", Nom: " << client.getNom() << std::endl;
    }
}

void GestionnaireBanque::rechercherClientParNom(const std::string& nom) const {
    bool clientTrouve = false;
    for (const auto& client : clients) {
        if (client.getNom() == nom) {
            std::cout << "Client trouvé: ID: " << client.getId() << ", Nom: " << client.getNom() << std::endl;
            clientTrouve = true;
        }
    }
    if (!clientTrouve) {
        std::cout << "Aucun client trouvé avec le nom \"" << nom << "\"." << std::endl;
    }
}

void GestionnaireBanque::rechercherClientParId(int clientId) const {
    for (const auto& client : clients) {
        if (client.getId() == clientId) {
            std::cout << "Client trouvé: ID: " << client.getId() << ", Nom: " << client.getNom() << std::endl;
            return;
        }
    }
    std::cout << "Aucun client trouvé avec l'ID " << clientId << "." << std::endl;
}

bool GestionnaireBanque::compteExists(int numeroCompte) const {
    for (const auto& compte : comptes) {
        if (compte->getNumeroCompte() == numeroCompte) {
            return true;
        }
    }
    return false;
}

std::shared_ptr<Pret> GestionnaireBanque::getPret(int pretId) const {
    for (const auto& pret : prets.getPrets()) {
        if (pret.getId() == pretId) {
            return std::make_shared<Pret>;
        }
    }
}

void GestionnaireBanque::afficherComptes() const {
    if (comptes.empty()) {
        std::cout << "Aucun compte enregistré." << std::endl;
        return;
    }
    std::cout << "\nListe des comptes:" << std::endl;
    for (const auto& compte : comptes) {
        std::cout << "Numéro de compte: " << compte->getNumeroCompte() << ", Solde: " << compte->getSolde() << std::endl;
    }
}

void GestionnaireBanque::rechercherCompte(int compteId) const {
    for (const auto& compte : comptes) {
        if (compte->getNumeroCompte() == compteId) {
            std::cout << "Compte trouvé: Numéro de compte: " << compte->getNumeroCompte() << ", Solde: " << compte->getSolde() << std::endl;
            return;
        }
    }
    std::cout << "Compte avec l'ID " << compteId << " non trouvé." << std::endl;
}

void GestionnaireBanque::afficherPrets(int clientId) const {
    std::cout << "\n----- Prets -----" << std::endl;
    if (prets.getPrets().empty()) {
        std::cout << "Aucun prêt enregistré." << std::endl;
        return;
    }
    for (const auto& pret : prets.getPrets()) { 
        if (pret.getClientId() == clientId) {
            pret.afficherPret(); 
            std::cout << "------------------------" << std::endl; 
        }
    } 
}

void GestionnaireBanque::afficherTransactionsCompte(int compteId) const {
    std::cout << "\n----- Transactions du compte " << compteId << " -----" << std::endl;
    std::ifstream logFile("transactions.log");
    if (!logFile.is_open()) {
        std::cout << "Erreur: Impossible d'ouvrir le fichier de transactions." << std::endl;
        return;
    }
    std::string line;
    bool transactionsTrouvees = false; 
    while (std::getline(logFile, line)) {
        std::stringstream ss(line);
        std::string dateHeure, type, montantStr, compteStr;

        std::getline(ss, dateHeure, ',');
        std::getline(ss, type, ',');
        std::getline(ss, montantStr, ',');
        std::getline(ss, compteStr, ',');

        if (std::stoi(compteStr) == compteId) {
            double montant = std::stod(montantStr);
            std::cout << "Date: " << dateHeure
                      << ", Type: " << type
                      << ", Montant: " << montant 
                      << std::endl;
            transactionsTrouvees = true;
        }
    }
    logFile.close();
    if (!transactionsTrouvees) {
        std::cout << "Aucune transaction trouvée pour le compte " << compteId << std::endl;
    }
}

void GestionnaireBanque::afficherTransactionsClient(int clientId) const {
    std::cout << "\n----- Transactions du client " << clientId << " -----" << std::endl;
    std::ifstream logFile("transactions.log");
    if (!logFile.is_open()) {
        std::cout << "Erreur: Impossible d'ouvrir le fichier de transactions." << std::endl;
        return;
    }
    std::string line;
    bool transactionsTrouvees = false; 

    while (std::getline(logFile, line)) {
        std::stringstream ss(line);
        std::string dateHeure, type, montantStr, compteStr;

        std::getline(ss, dateHeure, ',');
        std::getline(ss, type, ',');
        std::getline(ss, montantStr, ',');
        std::getline(ss, compteStr, ',');

        int compteId = std::stoi(compteStr);
        // Check if the transaction's account ID is in the client's accounts
        if (std::find(comptesDuClient.begin(), comptesDuClient.end(), compteId) != comptesDuClient.end()) {
            double montant = std::stod(montantStr);
            std::cout << "Date: " << dateHeure
                      << ", Type: " << type
                      << ", Montant: " << montant
                      << ", Compte: " << compteId 
                      << std::endl;
            transactionsTrouvees = true;
        }
    }
    logFile.close();
    if (!transactionsTrouvees) {
        std::cout << "Aucune transaction trouvée pour le client " << clientId << std::endl;
    }
}

void GestionnaireBanque::deposer(int compteId, double montant) {
    for (auto& compte : comptes) {
        if (compte->getNumeroCompte() == compteId) {
            compte->Deposer(montant); 
            std::cout << "Depot de " << montant << " reussi. Nouveau solde: " << compte->getSolde() << std::endl;

            // Log the transaction
            Transaction depositTransaction(Transaction::Type::Depot, montant, getCurrentDateTime(), 
                                            compte); // Assuming getCurrentDateTime() is defined in logutils.h
            logTransaction("transactions.log", depositTransaction);

            return;
        }
    }
    std::cout << "Erreur: Compte avec l'ID " << compteId << " non trouvé." << std::endl;
}

void GestionnaireBanque::retirer(int compteId, double montant) {
    for (auto& compte : comptes) {
        if (compte->getNumeroCompte() == compteId) {
            compte->Retirer(montant); 
            std::cout << "Retrait de " << montant << " reussi. Nouveau solde: " << compte->getSolde() << std::endl;

            // Log the transaction
            Transaction withdrawalTransaction(Transaction::Type::Retrait, montant, getCurrentDateTime(), 
                                            compte); 
            logTransaction("transactions.log", withdrawalTransaction);

            return;
        }
    }
    std::cout << "Erreur: Compte avec l'ID " << compteId << " non trouvé." << std::endl;
}

void GestionnaireBanque::afficherPrets(int clientId) const {
    std::cout << "\n----- Prets -----" << std::endl;

    if (prets.getPrets().empty()) {
        std::cout << "Aucun prêt enregistré." << std::endl;
        return;
    }
    for (const auto& pret : prets.getPrets()) { 
        if (pret.getClientId() == clientId) {
            pret.afficherPret(); 
            std::cout << "------------------------" << std::endl; 
        }
    } 
}

std::shared_ptr<Pret> GestionnaireBanque::getPret(int pretId) const
{
    return std::shared_ptr<Pret>();
}



/* void GestionnaireBanque::sauvegarderClients(const std::string& filename) {
    std::ofstream outputFile(filename);
    json j = json::array(); // Create a JSON array
    for (const auto& client : clients) {
        j.push_back({
            {"id", client.getId()},
            {"nom", client.getNom()}
        });
    }
    outputFile << j << std::endl;
    outputFile.close();
}

void GestionnaireBanque::chargerClients(const std::string& filename) {
    std::ifstream inputFile(filename); 
    if (inputFile.is_open()) {
        json j;
        inputFile >> j;
        for (const auto& item : j) {
            clients.push_back(Client(item["id"], item["nom"]));
        }
        inputFile.close();
    }
} */