#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <memory>  // For std::shared_ptr
#include "compte.h"
#include "banque.h"

class Banque;
class Transaction {
public:
    enum class Type { Depot, Retrait, Virement, Pret };

    Transaction(Type type, double montant, const std::string& dateHeure,
                 const std::shared_ptr<Compte>& compteAssocie);

    Type getType() const;
    double getMontant() const;
    const std::string& getDateHeure() const;
    const std::shared_ptr<Compte>& getCompteAssocie() const;


    void Enregistrer();
    std::string typeToStr() const;
    void Annuler(); 

private:
    Type type;
    double montant;
    std::string dateHeure;
    std::shared_ptr<Compte> compteAssocie; // Using shared_ptr
    static Banque& banque;  // Static member
};

#endif