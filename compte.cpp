#include "compte.h"
#include "g_error.h" 
#include "logutils.h"
 
#include <iostream> 
#include <algorithm>
using namespace std;

// Constructor
Compte::Compte(int numeroCompte, double solde, const std::string& type) :
    numeroCompte(numeroCompte), solde(solde), type(type) {} 

Compte::Compte(int numero) : numeroCompte(numero), solde(0.0) {}

// Getters
int Compte::getNumeroCompte() const { return numeroCompte; }
double Compte::getSolde() const { return solde; }
const std::string& Compte::getType() const { return type; }

// Deposit method
void GestionnaireBanque::deposer(int compteId, double montant) {
    for (auto& compte : comptes) {
        if (compte->getNumeroCompte() == compteId) {
            compte->Deposer(montant); 
            std::cout << "Depot de " << montant << " reussi. Nouveau solde: " << compte->getSolde() << std::endl;

            // Log the transaction
            Transaction depositTransaction(Transaction::Type::Depot, montant, getCurrentDateTime(), 
                                            compte); // Assuming getCurrentDateTime() is defined in logutils.h
            logTransaction("transactions.log", depositTransaction);

            return;
        }
    }
    std::cout << "Erreur: Compte avec l'ID " << compteId << " non trouvé." << std::endl;
}

void GestionnaireBanque::retirer(int compteId, double montant) {
    for (auto& compte : comptes) {
        if (compte->getNumeroCompte() == compteId) {
            compte->Retirer(montant); 
            std::cout << "Retrait de " << montant << " reussi. Nouveau solde: " << compte->getSolde() << std::endl;

            // Log the transaction
            Transaction withdrawalTransaction(Transaction::Type::Retrait, montant, getCurrentDateTime(), 
                                            compte); 
            logTransaction("transactions.log", withdrawalTransaction);

            return;
        }
    }
    std::cout << "Erreur: Compte avec l'ID " << compteId << " non trouvé." << std::endl;
}
// Display method
void Compte::Afficher() const {
    std::cout << "Account Number: " << numeroCompte << "\n"
              << "Balance: " << solde << "\n"
              << "Type: " << type << std::endl; 
}

void Compte::setNumeroCompte(int numeroCompte)
{
    if (numeroCompte < 0) {
        throw std::invalid_argument("Account number cannot be negative.");
    }
    this->numeroCompte = numeroCompte;
}

void Compte::setSolde(double nouveauSolde)
{
    if (nouveauSolde < 0) {
        throw std::invalid_argument("Account balance cannot be negative.");
    }
    solde = nouveauSolde;
}

void Compte::setType(std::string type)
{
    if (type.empty()) {
        throw std::invalid_argument("Account type cannot be empty.");
    }
    this->type = type;
}

// In banque.cpp

void GestionnaireBanque::afficherComptes() const {
    std::cout << "\n----- Liste des Comptes -----" << std::endl;
    if (comptes.empty()) {
        std::cout << "Aucun compte enregistré." << std::endl;
        return;
    }

    for (const auto& compte : comptes) {
        std::cout << "Numéro de compte: " << compte->getNumeroCompte() << std::endl;
        std::cout << "Solde: " << compte->getSolde() << std::endl; 
        std::cout << "Client associé: " << compte->getClient()->getNom() << std::endl; // Assuming you have a Client object associated with each Compte
        std::cout << "------------------------" << std::endl; 
    }
}

void GestionnaireBanque::modifierCompte(int compteId) {
    for (auto& compte : comptes) {
        if (compte->getNumeroCompte() == compteId) {
            // Implement logic to modify account details
            // (e.g., change account type, update balance [with proper checks])
            std::cout << "Compte modifié avec succès!" << std::endl;
            return;
        }
    }
    std::cout << "Compte avec l'ID " << compteId << " non trouvé." << std::endl;
}

// In banque.cpp
void GestionnaireBanque::supprimerCompte(int compteId) {
    auto it = std::remove_if(comptes.begin(), comptes.end(),
                            [compteId](const auto& compte) { return compte->getNumeroCompte() == compteId; });

    if (it != comptes.end()) {
        comptes.erase(it, comptes.end());
        std::cout << "Compte supprimé avec succès!" << std::endl;
    } else {
        std::cout << "Compte avec l'ID " << compteId << " non trouvé." << std::endl;
    }
}

// In banque.cpp
void GestionnaireBanque::rechercherCompte(int compteId) const {
    for (const auto& compte : comptes) {
        if (compte->getNumeroCompte() == compteId) {
            // Display account details
            std::cout << "Compte trouvé: " << std::endl;
            // ... (Print account information)
            return;
        }
    }
    std::cout << "Compte avec l'ID " << compteId << " non trouvé." << std::endl;
}