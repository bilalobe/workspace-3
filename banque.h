#ifndef BANQUE_H
#define BANQUE_H

#include <random>
#include <vector>
#include <memory> // for shared_ptr

#include "compte.h"
#include "pret.h"
#include "client.h"
#include "logutils.h"
#include "g_error.h"
#include "A:/workspace#2/dependencies/json-develop/include/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;
class Transaction; 
class Pret;      
class GestionnaireBanque
{
public:
    // Constructor
    GestionnaireBanque();

    // Methods for managing Clients
    int creerClient(const std::string &nom);
    void modifierClient(int clientId);
    void supprimerClient(int clientId);
    void afficherClients() const;
    void rechercherClientParNom(const std::string &nom) const;
    void rechercherClientParId(int clientId) const;

    // Methods for managing Accounts
    int creerCompte(int clientId);
    void modifierCompte(int compteId);
    void supprimerCompte(int compteId);
    void afficherComptes() const;
    void rechercherCompte(int compteId) const;
    std::shared_ptr<Compte> getCompteByBeneficiaryName(const std::string &beneficiaryName) const;

    int creerPret(int clientId, double montant, double tauxInteret, int duree, double tauxRampe);
    bool rembourserPret(int pretId, double montant);
    std::vector<Pret> getPrets() const; 

    // Methods for managing Prets
    int demanderPret(int clientId, double montant, int duree, double tauxInteret);
    void rembourserPret(int pretId, double montant, const std::string &datePaiementStr);
    void afficherPrets(int clientId) const;

    
    bool annulerPret(int pretId);
    std::vector<Pret> getPrets() const;
    void afficherPrets(int clientId) const;

    // Methods for managing Transactions
    void deposer(int compteId, double montant);
    void retirer(int compteId, double montant);
    void afficherTransactionsCompte(int compteId) const;
    void afficherTransactionsClient(int clientId) const;
    void enregistrerTransaction(const Transaction& transaction);

    // Methods for saving and loading client data

    void sauvegarderClients(const std::string& filename);
    void chargerClients(const std::string& filename);

private:
    int genererNumeroCompteUnique();
    bool compteExists(int numeroCompte) const;

    int nextClientId = 1;
    int nextAccountId = 1;
    int nextPretId = 1;

    
    std::vector<Client> clients;                  // Vector to store clients
    std::vector<std::shared_ptr<Pret>> prets;     // Vector to store Prets
    std::vector<std::shared_ptr<Compte>> comptes; // Vector to store accounts
    std::vector<Transaction> transactions;
    
};

#endif

