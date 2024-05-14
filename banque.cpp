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
    Client client(dernierIdClient++ , nom); // Create Client object
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
            return; 
        }
    }
    std::cout << "Client avec l'ID " << clientId << " non trouvé." << std::endl;
}

void GestionnaireBanque::supprimerClient(int clientId) {
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        if (it->getId() == clientId) {
            clients.erase(it); 
            std::cout << "Client supprimé avec succès!" << std::endl;
            return;
        }
    }
    std::cout << "Client avec l'ID " << clientId << " non trouvé." << std::endl;
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

void GestionnaireBanque::rechercherClient(const std::string& nom) const {
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

void GestionnaireBanque::afficherTransactions() const {
    std::ifstream logFile("transactions.log"); 

    if (!logFile.is_open()) {
        std::cout << "Erreur: Impossible d'ouvrir le fichier de transactions." << std::endl;
        return;
    }

    std::cout << "\n----- Transactions -----" << std::endl;
    std::string line;
    while (std::getline(logFile, line)) {
        std::stringstream ss(line);
        std::string dateHeure, type, montantStr, compteIdStr;

        std::getline(ss, dateHeure, ',');
        std::getline(ss, type, ',');
        std::getline(ss, montantStr, ',');
        std::getline(ss, compteIdStr, ',');

        double montant = std::stod(montantStr);
        int compteId = std::stoi(compteIdStr);

        std::cout << "Date: " << dateHeure 
                << ", Type: " << type
                << ", Montant: " << montant
                << ", Compte: " << compteId << std::endl;
    }

    logFile.close();
}

void GestionnaireBanque::demanderPret() {
    // 1. Get loan details (amount, rate, duration, client ID) from the user.
    // 2. Create a new Pret object with the provided details.
    // 3. Add the new Pret object to the 'prets' vector in GestionnaireBanque.
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