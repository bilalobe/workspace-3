#include "compte.h"
#include "g_error.h" 
#include <iostream>

// Constructor
Compte::Compte(int numeroCompte, double solde, const std::string& type) :
    numeroCompte(numeroCompte), solde(solde), type(type) {} 


// Getters
int Compte::getNumeroCompte() const { return numeroCompte; }
double Compte::getSolde() const { return solde; }
const std::string& Compte::getType() const { return type; }

// Deposit method
void Compte::Deposer(double montant) {
    solde += montant; 
}

// Withdraw method
void Compte::Retirer(double montant) {
    if (solde >= montant) {
        solde -= montant;
    } else {
        throw OperationNonAboutieError(solde, montant); // Pass balance and amount
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
