#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <memory>  // For std::shared_ptr

#include "compte.h"
#include "banque.h" 
#include "logutils.h"  // Include logutils.h for getCurrentDateTime

class Banque;

enum class TransactionType { Depot, Retrait, Virement, Pret };

class Transaction {
public:
    Transaction(TransactionType type, double montant, const std::string& dateHeure,
                const std::shared_ptr<Compte>& compteAssocie, 
                const std::string& beneficiaryName = "",  // Optional beneficiary
                int PretId = -1); // Optional Pret ID

    TransactionType getType() const;
    double getMontant() const;
    const std::string& getDateHeure() const;
    const std::shared_ptr<Compte>& getCompteAssocie() const;
    const std::string& getBeneficiaryName() const; 
    int getPretId() const; 

    void Enregistrer();
    std::string typeToStr() const;
    void Annuler(); 

private:
    TransactionType type;
    double montant;
    std::string dateHeure;
    std::shared_ptr<Compte> compteAssocie; // Using shared_ptr
    std::string beneficiaryName;  // Beneficiary name
    int PretId; // Pret ID 
    static Banque& banque;  // Static member
};

#endif
