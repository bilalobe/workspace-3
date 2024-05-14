#include "compte.h"
#include "g_error.h" 
#include "logutils.h" 

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
void Compte::Deposer(double montant) {
    if (montant > 0) {
        solde += montant;

        // Construct a Transaction object to log:
        Transaction depositTransaction(Transaction::Type::Depot, montant, getCurrentDateTime(), 
                                        std::make_shared)

        // Log the transaction 
        logTransaction("transactions.log", depositTransaction);

    } else {
        throw std::invalid_argument("Invalid deposit amount: Amount must be positive.");
    }
}

// Withdraw method
void Compte::Retirer(double montant) {
    if (montant > 0 && montant <= solde) {
        solde -= montant;
        std::cout << "Retrait de " << montant << " reussi. Nouveau solde: " << solde << std::endl;
    } else {
        std::cout << "Erreur: Le montant du retrait doit etre positif et inferieur ou egal au solde." << std::endl;
    }
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