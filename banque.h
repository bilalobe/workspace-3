#ifndef BANQUE_H
#define BANQUE_H

#include <random>   // For random number generation
#include <vector>   // For storing clients
#include "client.h"
#include "transaction.h"
class GestionnaireBanque {
public:

    bool compteExists(int numeroCompte) {
        for (const auto& client : clients) {
            if (client.numeroCompteExists(numeroCompte)) {
                return true;
            }
        }
        return false;
    }

    std::vector<Client>& getClients() {
        return clients;
    }

private:
    std::vector<Client> clients;
    void AjouterNouveauClient(const std::string &nom, const std::string &adresse);
    void supprimerClient(const std::string& nom, const std::string& adresse, std::vector<Client>& clients);

    int genererNumeroCompteUnique();
};
#endif