#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include <memory>

#include "compte.h" // Include Compte.h 
#include "pret.h" // Include Pret.h 

class Client {
public:
    // Constructor
    Client(int id, const std::string& nom);

    // Getters
    int getId() const;
    const std::string& getNom() const;
    std::vector<std::shared_ptr<Compte>> getComptes() const; 
    std::vector<std::shared_ptr<Pret>> getPrets() const; 

    // Other methods
    void addCompte(const std::shared_ptr<Compte>& compte);
    void addPret(const std::shared_ptr<Pret>& pret); 

private:
    int id;
    std::string nom;
    std::vector<std::shared_ptr<Compte>> comptes;
    std::vector<std::shared_ptr<Pret>> prets;
};

#endif