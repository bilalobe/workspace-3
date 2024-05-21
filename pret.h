#ifndef PRET_H
#define PRET_H

#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <chrono>
#include <numeric>
#include <iostream>

enum class PretStatut {
    Active,
    Repaid,
    Canceled
};

class Pret {
private:
    PretStatut statut;
    int id;
    double montant;
    double tauxAnnuel;
    double tauxRampe;
    int duree;
    std::chrono::system_clock::time_point dateDebut;
    std::chrono::system_clock::time_point dateRemboursement;
    std::chrono::system_clock::time_point derniereDatePaiement;
    std::vector<Pret::Paiement> paiements;

    std::chrono::system_clock::time_point stringToTimePoint(const std::string &dateStr) const;

public:
    // Constructor
    Pret(int id, double montant, double tauxAnnuel, int duree, const std::string &dateDebutStr, const std::string &dateRemboursementStr, double tauxRampe);

    int getId() const;
    double getMontant() const;
    double getTaux() const;
    int getDuree() const;
    std::string getDateDebut() const;
    std::string getDateRemboursement() const;
    std::chrono::system_clock::time_point getDerniereDatePaiement() const;
    double calculerInteretSimpleDepuisDernierPaiement() const;
    double calculerInteretComposeTotal() const;
    double calculerBalance() const;
    std::vector<Pret::Paiement> getPaiements() const;
    void afficherPret() const;
    void ajouterPaiement(double montant, const std::string &datePaiementStr);

    PretStatut getStatut() const;
    void setStatut(PretStatut nouveauStatut);
    bool isCancelable() const;

    class Paiement {
    public:
        Paiement(double montant, const std::chrono::system_clock::time_point &datePaiement);
        double getMontant() const;
        std::string getDatePaiement() const;

    private:
        double montant;
        std::chrono::system_clock::time_point datePaiement;
    };
};

#endif
