#include "banque.h"
using namespace std;

std::shared_ptr


int GestionnaireBanque::genererNumeroCompteUnique() {
     std::random_device rd;  
     std::mt19937 generator(rd());  
     std::uniform_int_distribution<int> distribution(10000, 99999);

     int newNumeroCompte;
         bool duplicateFound;
    do {
        duplicateFound = false;
        newNumeroCompte = distribution(generator);
        for (const auto& client : clients) {
            if (client.numeroCompteExists(newNumeroCompte)) {
                duplicateFound = true;
                break; // Duplicate found, try again
            }
        }
    } while (duplicateFound); 

    return newNumeroCompte;
}

bool GestionnaireBanque::compteExists(int numeroCompte) {
    for (const auto& client : clients) {
        if (client.numeroCompteExists(numeroCompte)) {
            return true;
        }
    }
    return false;
}


void GestionnaireBanque::nouveauClient(const std::string& nom) {
    Client client(dernierIdClient++, nom); 
    clients.push_back(client); 
    std::cout << "Nouveau client ajouté avec succès ! ID du client : " << client.getId() << std::endl;
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
            return; // Client found and modified, exit the function
        }
    }
    std::cout << "Client avec l'ID " << clientId << " non trouvé." << std::endl;
}

void GestionnaireBanque::supprimerClient(int clientId) {
    // Using std::remove_if for better efficiency
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
            return; // Client found, exit the function
        }
    }
    std::cout << "Aucun client trouvé avec l'ID " << clientId << "." << std::endl;
}
// In banque.cpp
void GestionnaireBanque::afficherTransactionsCompte(int compteId) const {
    std::cout << "\n----- Transactions du compte " << compteId << " -----" << std::endl;

    std::ifstream logFile("transactions.log");
    if (!logFile.is_open()) {
        std::cout << "Erreur: Impossible d'ouvrir le fichier de transactions." << std::endl;
        return;
    }

    std::string line;
    bool transactionsTrouvees = false; // Flag to check if any transactions were found
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
// In banque.cpp
void GestionnaireBanque::afficherTransactionsClient(int clientId) const {
    std::cout << "\n----- Transactions du client " << clientId << " -----" << std::endl;

    std::ifstream logFile("transactions.log");
    if (!logFile.is_open()) {
        std::cout << "Erreur: Impossible d'ouvrir le fichier de transactions." << std::endl;
        return;
    }

    std::string line;
    bool transactionsTrouvees = false; 

    // Get all account IDs associated with the client
    std::vector

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

std::vector

void GestionnaireBanque::afficherPrets() const {
    std::cout << "\n----- Prets -----" << std::endl;

    if (prets.getPrets().empty()) {
        std::cout << "Aucun prêt enregistré." << std::endl;
        return;
    }

    for (const auto& pret : prets.getPrets()) {
        pret.afficherPret(); 
        std::cout << "------------------------" << std::endl; 
    }
}


void Prets::enregistrerRemboursement(int pretId, double montant, const std::string& datePaiementStr) {
    for (auto& pret : prets) {
        if (pret.getId() == pretId) {
            pret.enregistrerPaiement(montant, datePaiementStr); // Call Pret::enregistrerPaiement()
            std::cout << "Remboursement enregistré avec succès pour le prêt ID " << pretId << std::endl;
            return; 
        }
    }

    std::cout << "Aucun prêt trouvé avec l'ID " << pretId << std::endl;
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