#ifndef COMPTE_H
#define COMPTE_H

#include <string>
#include "client.h" // Include Client.h

enum class TypeCompte { Checking, Savings, MoneyMarket }; // Define account types

class Compte : public std::enable_shared_from_this<Compte> { 
public:
    // Constructor 
    Compte(int numeroCompte, double solde, TypeCompte type, Client& client); 

    // Getters 
    int getNumeroCompte() const;
    double getSolde() const;
    TypeCompte getType() const; 

    // Getters 
    int getNumeroCompte() const;
    double getSolde() const;
    TypeCompte getType() const; 

    // New method to get the Client associated with the account
    Client& getClient() const; 

    // Methods
    void Deposer(double montant);
    void Retirer(double montant);

    // Display method
    void Afficher() const;

    const std::vector<Transaction>& getTransactions() const;

    // Setters (with validation)
    void setNumeroCompte(int numeroCompte);
    void setSolde(double nouveauSolde);
    void setType(TypeCompte type);

private:
    int numeroCompte;
    double solde;
    TypeCompte type; // Store the account type as an enum 
    Client& client; 
    std::vector<Transaction> transactions; // Transaction history
};

#endif