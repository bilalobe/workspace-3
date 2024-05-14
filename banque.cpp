#include "banque.h"
using namespace std;

std::shared_ptr

void GestionnaireBanque::AjouterNouveauClient(const std::string& nom, const std::string& adresse) {
    // Create a new client
    Client newClient(nom, adresse); // No more uniqueNumeroCompte here

    // Open a new account (assuming you'll implement this in your Client class)
    newClient.OuvrirNouveauCompte("savings"); // Example account type 

    // Add to the client list
    clients.push_back(newClient);
}

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

void Client::supprimerClient(const std::string& nom, const std::string& adresse, std::vector<Client>& clients){
    for (int i = 0; i < clients.size(); i++) {
        if (clients[i].nom == nom && clients[i].adresse == adresse) {
            clients.erase(clients.begin() + i);
            return;
        }
    }
}

