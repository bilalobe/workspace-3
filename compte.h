#ifndef COMPTE_H
#define COMPTE_H

#include <string>
#include "client.h"

class Compte {
public:

    Compte(int numeroCompte, double solde, const std::string& type); 
    Compte(int numeroCompte, double solde, int clientId); 

    // ... other members and methods ...


    void Deposer(double montant);
    void Retirer(double montant); 
    void Afficher() const;


    // Getter for Client ID
    int getClientId() const; 
    int getNumeroCompte() const; // Add the accessor methods
    double getSolde() const;
    const std::string& getType() const; 


   void setNumeroCompte(int numeroCompte); // Add the mutator methods
   void setSolde(double solde);
   void setType(std::string type);

private:
    int numeroCompte;
    double solde;
    int clientId;
    std::string type; 
};

#endif
