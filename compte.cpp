#include "compte.h"
#include "g_error.h" 
#include "logutils.h" 
#include <iostream> 
#include <algorithm>

using namespace std;

Compte::Compte(int numeroCompte, double solde, TypeCompte type, Client& client) :
    numeroCompte(numeroCompte), solde(solde), type(type), client(client) { 
      if (numeroCompte < 0) {
        throw std::invalid_argument("Account number cannot be negative.");
    }
    if (solde < 0) {
        throw std::invalid_argument("Account balance cannot be negative.");
    }
}


TypeCompte Compte::getType() const {
    return type;
}

void Compte::setType(TypeCompte type) {
    this->type = type;
}

Client& Compte::getClient() const {
    return client;
}

// Getters
int Compte::getNumeroCompte() const { return numeroCompte; }
double Compte::getSolde() const { return solde; }
TypeCompte Compte::getType() const { return type; }

// Setters

void Compte::Deposer(double montant) {
    if (montant <= 0) {
        throw std::invalid_argument("Deposit amount must be positive.");
    }
    solde += montant;
    std::string dateTime = getCurrentDateTime();
    transactions.push_back(Transaction(Transaction::Type::Depot, montant, dateTime, shared_from_this()));
    logTransaction("transactions.log", Transaction(Transaction::Type::Depot, montant, dateTime, shared_from_this()));
}
void Compte::Retirer(double montant) {
    if (montant <= 0) {
        throw std::invalid_argument("Withdrawal amount must be positive.");
    }
    if (solde < montant) {
        throw OperationNonAboutieError(solde, montant);
    }
    solde -= montant;
    std::string dateTime = getCurrentDateTime();
    transactions.push_back(Transaction(Transaction::Type::Retrait, montant, dateTime, shared_from_this()));
    logTransaction("transactions.log", Transaction(Transaction::Type::Retrait, montant, dateTime, shared_from_this()));
}

const std::vector<Transaction>& Compte::getTransactions() const {
    return transactions;
}

void Compte::Afficher() const {
    std::cout << "Numéro de compte: " << numeroCompte << std::endl;
    std::cout << "Solde: " << solde << std::endl;
    std::cout << "Type de compte: " << TypeCompteToString(type) << std::endl; // Use a helper function for the account type string
    std::cout << "Client associé: " << client.getNom() << std::endl; // Display client name
    std::cout << "Historique des transactions:" << std::endl;
    for (const auto& transaction : transactions) {
        std::cout << "  - Type: " << transaction.typeToStr() << std::endl;
        std::cout << "  - Montant: " << transaction.getMontant() << std::endl;
        std::cout << "  - Date et heure: " << transaction.getDateHeure() << std::endl;
        std::cout << std::endl; // Add a line break between transactions
    }
}

// Helper function to convert TypeCompte to a string
std::string TypeCompteToString(TypeCompte type) {
    switch (type) {
        case TypeCompte::Checking:
            return "Chèque";
        case TypeCompte::Savings:
            return "Épargne";
        case TypeCompte::MoneyMarket:
            return "Marché monétaire";
        default:
            return "Type de compte inconnu";
    }
}

void Compte::setNumeroCompte(int numeroCompte) {
    if (numeroCompte < 0) {
        throw std::invalid_argument("Account number cannot be negative.");
    }
    this->numeroCompte = numeroCompte;
}

void Compte::setSolde(double nouveauSolde) {
    if (nouveauSolde < 0) {
        throw std::invalid_argument("Account balance cannot be negative.");
    }
    solde = nouveauSolde;
}


void Compte::setType(TypeCompte type) {
    this->type = type; // No need for validation 
}