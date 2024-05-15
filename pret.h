#ifndef PRET_H
#define PRET_H

#include <string>
#include <vector>
#include <chrono>
#include <memory>

#include "client.h"
#include "transaction.h"
#include "pret.h"
#include "compte.h"
#include "banque.h"
class Pret {
private:
    int id; 
    double montant;
    double tauxAnnuel;
    int duree;
    std::chrono::system_clock::time_point dateDebut;
    std::chrono::system_clock::time_point dateRemboursement;
    const std::vector<Pret> getPrets() const; 
public:
    // Constructor
    Pret(double montant, double taux, int duree, const std::string& dateDebutStr, const std::string& dateRemboursementStr);
    Pret(int id, double montant, double taux, int duree, const std::string& dateDebutStr, const std::string& dateRemboursementStr);

    // Destructor
    ~Pret() {}

    // Getters
    int getId() const;
    double getMontant() const;
    double getTaux() const;
    int getDuree() const;
    std::string getDateDebut() const;
    std::string getDateRemboursement() const;
    std::chrono::system_clock::time_point getDerniereDatePaiement() const;
    const std::vector<Paiement> getPaiements() const;


    // Setters
    void setId(int id);
    void setMontant(double montant);
    void setTaux(double taux);
    void setDuree(int duree);
    void setDateDebut(const std::string& dateDebutStr);
    void setDateRemboursement(const std::string& dateRemboursementStr);

    // Record a payment
    void enregistrerPaiement(double montant, const std::string& datePaiementStr);

    // Display loan details
    void afficherPret() const;

    // Calculate simple interest accrued since last payment
    double calculerInteretSimpleDepuisDernierPaiement() const;

    // Calculate total compound interest
    double calculerInteretComposeTotal() const;

    // Calculate balance
    double calculerBalance() const;

private:
    static int nextLoanId; 
};

// Helper class to represent a payment
class Pret::Paiement {
public:
    Paiement(double montant, const std::chrono::system_clock::time_point& datePaiement)
        : montant(montant), datePaiement(datePaiement) {}
    Paiement() {}
    double getMontant() const {
        return montant;
    }
    std::string getDatePaiement() const {
        return std::string();
    }
private:
    double montant;
    std::chrono::system_clock::time_point datePaiement;
};

#endif