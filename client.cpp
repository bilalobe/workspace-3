#include "client.h"

// Constructor
Client::Client(int id, const std::string& nom) : id(id), nom(nom) {}

// Getters
int Client::getId() const {
    return id;
}

const std::string& Client::getNom() const {
    return nom;
}

std::vector<std::shared_ptr<Compte>> Client::getComptes() const {
    return comptes;
}

std::vector<std::shared_ptr<Pret>> Client::getPrets() const {
    return prets;
}

// Other Methods
void Client::addCompte(const std::shared_ptr<Compte>& compte) {
    comptes.push_back(compte);
}

void Client::addPret(const std::shared_ptr<Pret>& pret) {
    prets.push_back(pret);
}