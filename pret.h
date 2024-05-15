#ifndef PRET_H
#define PRET_H

#include <string>
#include <vector>
#include <chrono>
#include <memory>

#include "client.h"
#include "transaction.h"
#include "pret.h"
class Pret {
public:
    Pret(double montant, double taux, int duree, const std::string& dateDebut, const std::string& dateRemboursement);
    ~Pret();

    double getMontant() const;
    double getTaux() const;
    int getDuree() const;
    std::string getDateDebut() const;
    std::string getDateRemboursement() const;

    void setMontant(double montant);
    void setTaux(double taux);
    void setDuree(int duree);
    void setDateDebut(const std::string& dateDebut);
    void setDateRemboursement(const std::string& dateRemboursement);
    void setCompteAssocie(const std::shared_ptr<Compte>& compteAssociePtr);

    void enregistrerPaiement(double montant, const std::string& datePaiement);
    void afficherPret() const;
    const std::vector<Paiement>& getPaiements() const;
    std::shared_ptr<Compte> getCompteAssociePtr() const;

private:
    double montant;
    double tauxAnnuel;
    int duree;
    std::chrono::system_clock::time_point dateDebut;
    std::chrono::system_clock::time_point dateRemboursement;
    std::chrono::system_clock::time_point derniereDatePaiement;
    std::vector<Pret> prets; 
    std::shared_ptr<Compte> compteAssociePtr;
    std::vector<Paiement> paiements;

    // Helper function to convert date string (YYYY-MM-DD) to time_point
    std::chrono::system_clock::time_point stringToTimePoint(const std::string& dateStr);

    // Helper function to calculate simple interest since last payment
    double calculerInteretSimpleDepuisDernierPaiement() const;

    // Helper function to calculate total compound interest
    double calculerInteretComposeTotal() const;

    // Helper function to calculate balance
    double calculerBalance() const;

    void ajouterPret(const Pret& pret);
};

class Paiement {
public:
    Paiement(double montant, const std::chrono::system_clock::time_point& datePaiement)
        : montant(montant), datePaiement(datePaiement) {}

    // Getter for montant
    double getMontant() const { return montant; }

    // Getter for datePaiement
    std::chrono::system_clock::time_point getDatePaiement() const { return datePaiement; }

private:
    double montant;
    std::chrono::system_clock::time_point datePaiement;
};

#endif
