#include "client.h"
#include "compte.h"
#include "transaction.h"
#include "banque.h"
#include "g_error.h"
#include "logutils.h"
#include <random>  // Include for random number generation
#include <limits>  // For std::numeric_limits
#include <algorithm> 
#include <iostream>

Pret prets;

bool Client::numeroCompteExists(int numeroCompte) const {
    const std::vector<Client>& allClients = gestionnaireBanque.getClients(); // Get all clients
    for (const auto& client : allClients) { 
        if (client.numeroCompteExists(numeroCompte)) {
            return true;
        }
    }
    return false; 
}

void Client::OuvrirNouveauCompte(const std::string& type) {
    std::random_device rd;  
    std::mt19937 generator(rd());  
    std::uniform_int_distribution<int> distribution(10000, 99999);

    int newNumeroCompte;
    do {
        newNumeroCompte = distribution(generator);
    } while (numeroCompteExists(newNumeroCompte)); 

    comptes.push_back(Compte(newNumeroCompte, 0.0, type));
}


bool Client::FermerCompte(int numeroCompte) {
    auto it = std::remove_if(comptes.begin(), comptes.end(), 
                             [numeroCompte](const Compte& compte) { 
                                 return compte.getNumeroCompte() == numeroCompte; 
                             });

    if (it == comptes.end()) { comptes.erase(it, comptes.end()); // Remove erased elements
        return true; // Account closed successfully
    } else {
        return false;
    } 
}

void Client::AfficherComptes() const {
    if (comptes.empty()) {
        std::cout << "Client has no accounts.\n";
        return;
    }

    std::cout << "Accounts for client: " << nom << std::endl;
    for (const auto& compte: comptes) {
        compte.Afficher(); 
    }
}

void Client::afficherSoldeCompte(int numeroCompte) const {
    auto it = std::find_if(comptes.begin(), comptes.end(), 
                           [numeroCompte](const Compte& compte) {
                               return compte.getNumeroCompte() == numeroCompte;
                           });

    if (it != comptes.end()) {
        std::cout << "Account balance: " << it->getSolde() << "\n";
    } else {
        std::cout << "Account not found.\n";
    }
}

void Client::crediterCompte(int numeroCompte, double montant)
{
    auto it = std::find_if(comptes.begin(), comptes.end(), 
                           [numeroCompte](const Compte& compte) {
                               return compte.getNumeroCompte() == numeroCompte;
                           });

    if (it != comptes.end()) {
        it->Deposer(montant);
    } else {
        throw OperationNonAboutieError::InvalidAmountError("Amount non valid");
    }
}

void Client::debiterCompte(int numeroCompte, double montant) {
    auto it = std::find_if(comptes.begin(), comptes.end(),
                            [numeroCompte](const Compte& compte) {
                                return compte.getNumeroCompte() == numeroCompte;
                            });
    if (it != comptes.end()) {
        double solde = it->getSolde(); 
        if (solde >= montant) {
            it->Retirer(montant);

        } else {
            throw OperationNonAboutieError(solde, montant);
        }
    } else {
        throw OperationNonAboutieError::InvalidAccountError("Account not found for debiting.");
    }
} 
                           



const std::string &Client::getNom() const {
    return nom;
}

const std::string &Client::getAdresse() const {
    return adresse;
}

const std::vector<Compte> &Client::getComptes() const {
    return comptes;
}

void Client::setNom(const std::string &nom) {
    this->nom = nom;
}

void Client::setAdresse(const std::string &adresse) {
    this->adresse = adresse;
}

int Client::getNumeroCompte(const std::string &type) const {
  for (const auto& compte : comptes) {
    if (compte.getType() == type) {
      return compte.getNumeroCompte(); 
    }
  }
  return -1; 
}

void Client::ouvrirPret(double montant, double taux, int duree, const std::string& dateDebutStr, 
                        const std::string& dateRemboursementStr, const std::string& dateHeureStr, 
                        const std::shared_ptr<Compte>& compteAssociePtr) {
    // Input Validation 
    if (montant <= 0.0 || taux < 0.0 || duree <= 0) {
        throw std::invalid_argument("Invalid loan parameters.");
    }
    if (dateDebutStr.empty() || dateRemboursementStr.empty()) {
        throw std::invalid_argument("Invalid date format.");
    }

    // Create the Pret object 
    Pret nouveauPret(montant, taux, duree, dateDebutStr, dateRemboursementStr);
    nouveauPret.setCompteAssocie(compteAssociePtr); // Associate the loan with the account

    prets.push_back(nouveauPret);

    // Log the transaction 
    Transaction transaction(Transaction::Type::Pret, montant, dateHeureStr, compteAssociePtr);
    logTransaction("transactions.log", transaction); 

    std::cout << "Loan created successfully.\n";
    std::cout << "Loan details:\n";
    nouveauPret.afficherPret(); 
}




void Client::afficherPrets() const {
    if (prets.empty()) {
        std::cout << "Client has no loans.\n";
        return;
    }

    std::cout << "Loans for client: " << nom << std::endl;
    for (const auto& pret : prets) {
        pret.afficherPret();
    }
}

