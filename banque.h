
#ifndef BANQUE_H
#define BANQUE_H

#include <random>   // For random number generation
#include <vector>   

#include "compte.h"
#include "pret.h"
#include "client.h" 
#include "compte.h"
#include "transaction.h"
#include "logutils.h"
#include "g_error.h"

class GestionnaireBanque {
public:

    // Existing methods
    int genererNumeroCompteUnique();
    bool compteExists(int numeroCompte) const;

    // New methods for Client management
    void nouveauClient(const std::string& nom);
    void modifierClient(int clientId);
    void supprimerClient(int clientId);
    void afficherClients() const; 

    // Custom find methods for Client
    void rechercherClientParNom(const std::string& nom) const; 
    void rechercherClientParId(int clientId) const; 

    std::shared_ptr<Pret> getPret(int pretId) const;  

    // New methods for Compte management
    void creerCompte(int clientId); 
    void modifierCompte(int clientId); 
    void supprimerCompte(int compteId); 
    void afficherComptes() const;
    void rechercherCompte(int compteId) const; 

    // New methods for Transaction management
    void deposer(int compteId, double montant); 
    void retirer(int compteId, double montant); 

    void afficherTransactionsCompte(int compteId) const;
    void afficherTransactionsClient(int clientId) const;

    void afficherPrets(int clientId) const;


private:
    int numeroCompte;
    double solde;

    Pret pret;
    int dernierIdClient = 1; // Add for generating Client IDs
    int dernierIdCompte = 1;  // Add for generating Compte IDs 
    std::vector<Pret> prets;
    std::vector<Compte> comptesDuClient;
    std::vector<Client> clients;
    std::vector<std::shared_ptr<Compte>> comptes;
};

#endif 