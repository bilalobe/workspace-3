#include "client.h"

Client::Client(int id, const std::string& nom, const std::string& adresse) 
    : id(id), nom(nom), adresse(adresse) {}

// Getters
int Client::getId() const {
    return id;
}

std::string Client::getNom() const {
    return nom;
}

std::string Client::getAdresse() const {
    return adresse; 
}

