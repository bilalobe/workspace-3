
#ifndef BANQUE_H
#define BANQUE_H

#include <random>   // For random number generation
#include <vector>   

#include "compte.h"
#include "pret.h"
#include "client.h" // Include for the Client class
#include "compte.h"
#include "transaction.h"

class GestionnaireBanque {
public:
    std::vector

    // Existing methods
    bool compteExists(int numeroCompte) const;
    std::shared_ptr

    // New methods for Client management
    void nouveauClient(const std::string& nom);
    void modifierClient(int clientId);
    void supprimerClient(int clientId);
    void afficherClients() const; 

    // Custom find methods for Client
    void rechercherClientParNom(const std::string& nom) const; 
    void rechercherClientParId(int clientId) const; 

    // New methods for Compte management
    void creerCompte(int clientId); 
    void modifierCompte(int compteId); 
    void supprimerCompte(int compteId); 
    void afficherComptes() const;
    void rechercherCompte(int compteId) const; 

    // New methods for Transaction management
    void deposer(int compteId, double montant); 
    void retirer(int compteId, double montant); 
    
private:
    Pret pret;
    int dernierIdClient = 1; // Add for generating Client IDs
    int dernierIdCompte = 1;  // Add for generating Compte IDs 
};

#endif 