#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream> // for stringToTimePoint
#include <cmath> // for pow
#include <numeric>
#include <iostream>

#include "pret.h"


using Paiement = Pret::Paiement; // Now you can use Paiement directly within Pret

class Pret {
private:
    double montant;
    double tauxAnnuel;
    int duree;
    std::chrono::system_clock::time_point dateDebut;
    std::chrono::system_clock::time_point dateRemboursement; 
    std::vector<Paiement> paiements;
    std::chrono::system_clock::time_point derniereDatePaiement; 
    
    static int nextLoanId; 
    
bool operator==(const Pret& other) const {
    return montant == other.montant;
}

Pret& operator=(const Pret& other) {  
    tauxAnnuel = other.tauxAnnuel;
    duree = other.duree;
    dateDebut = other.dateDebut;
    dateRemboursement = other.dateRemboursement;
    paiements = other.paiements;
    derniereDatePaiement = other.derniereDatePaiement;
    return *this;
}



public:
    // Constructor
Pret::Pret(double montant, double taux, int duree, const std::string& dateDebutStr, const std::string& dateRemboursementStr) 
    : montant(montant), tauxAnnuel(taux), duree(duree), dateDebut(stringToTimePoint(dateDebutStr)), 
      dateRemboursement(stringToTimePoint(dateRemboursementStr)), derniereDatePaiement(stringToTimePoint("1970-01-01"))
{}

    Pret::~Pret() {}

    double Pret::getMontant() const
    {
        return montant;
    }

    double Pret::getTaux() const
    {
        return tauxAnnuel;
    }

    int Pret::getDuree() const
    {
        return duree;
    }

    std::string Pret::getDateDebut() const {
        std::time_t debut_time = std::chrono::system_clock::to_time_t(dateDebut);
        std::tm* debut_tm = std::localtime(&debut_time);
        std::stringstream ss;
        ss << std::put_time(debut_tm, "%Y-%m-%d");
        return ss.str();
    }

    std::string Pret::getDateRemboursement() const {
        std::time_t remboursement_time = std::chrono::system_clock::to_time_t(dateRemboursement);
        std::tm* remboursement_tm = std::localtime(&remboursement_time);
        std::stringstream ss;
        ss << std::put_time(remboursement_tm, "%Y-%m-%d");
        return ss.str();
    }
    
    std::chrono::system_clock::time_point getDerniereDatePaiement() const {
        return derniereDatePaiement;
    }
    
    const std::vector<Paiement> &Pret::getPaiements() const
    {
        return paiements;
    }

    void Pret::ajouterPret(const Pret& pret) {
    prets.push_back(pret);
    }

    std::shared_ptr<Pret> Prets::getPret(int pretId) const {
        for (const auto& pret : prets) {
            if (pret.getId() == pretId) {
                return std::make_shared<Pret>(pret);
            }

        }
        return nullptr;
    }

const std::vector<Pret> Prets::getPrets() const {
    return prets;
}

void Prets::enregistrerRemboursement(int pretId, double montant, const std::string& datePaiementStr, int clientId) {
    for (auto& pret : prets) {
        if (pret.getId() == pretId) {
            pret.enregistrerPaiement(montant, datePaiementStr); // Call the Pret::enregistrerPaiement() method
            std::cout << "Remboursement enregistré avec succès pour le prêt ID " << pretId << std::endl;
            return;
        }
    }
    std::cout << "Aucun prêt trouvé avec l'ID " << pretId << "." << std::endl;
}

    void Pret::setCompteAssociePtr(std::shared_ptr<Compte> compteAssociePtr) {

    }

    void Pret::setMontant(double montant)
    {
        montant = montant;
    }

    void Pret::setTaux(double taux)
    {
        tauxAnnuel = taux;
    }

    void Pret::setDuree(int duree)
    {
        duree = duree;
    }

    void Pret::setDateDebut(const std::string& dateDebutStr) {
        dateDebut = stringToTimePoint(dateDebutStr);  // Assign to member variable
    }

    void Pret::setDateRemboursement(const std::string& dateRemboursementStr) {
        dateRemboursement = stringToTimePoint(dateRemboursementStr);
    }

    
    void Pret::ajouterPret(const Pret& pret) {
        pret.setId(nextLoanId++); 
        prets.push_back(pret); 
    }
    
    double calculerInteretSimpleDepuisDernierPaiement() const {
        if (derniereDatePaiement == stringToTimePoint("1970-01-01")) {
            return 0.0; // No payments made yet
        }

        double balance = calculerBalance(); // Get the current balance before adding interest
        auto now = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = now - derniereDatePaiement;
        double time_difference = diff.count() / 365.25; // Account for leap years
        return balance * tauxAnnuel * time_difference;
    }

    double calculerInteretComposeTotal() const {
        double totalAmount = montant * pow((1 + tauxAnnuel), duree);
        return totalAmount - montant;
    }

    double calculerBalance() const {
        double balance = montant;
        double totalPaid = 0.0;

        for (const auto& paiement : paiements) {
            totalPaid += paiement.getMontant();
        }

        // Add simple interest accrued since the last payment
        balance += calculerInteretSimpleDepuisDernierPaiement(); 

        balance -= totalPaid;
        return balance;
    }

    // Record a payment
    void Pret::enregistrerPaiement(double montant, const std::string& datePaiementStr) {
            if (montant <= 0.0) {
            std::cout << "Error: Invalid payment amount.\n";
            return;
        }
        if (getMontant() < montant) {
            std::cout << "Error: Payment exceeds remaining balance.\n";
            return;
        }
    
        double balance = getMontant(); // Use the getter method to access the private member variable
        balance -= montant; 
        paiements.push_back(Paiement(montant, stringToTimePoint(datePaiementStr)));
        // Convert and update last payment date
        derniereDatePaiement = stringToTimePoint(datePaiementStr); 
        std::cout << "Payment recorded successfully.\n";
    }
    void Pret::enregistrerRemboursement(int pretId, double montant, const std::string& datePaiementStr) {
    for (auto& pret : prets) {
        if (pret.getId() == pretId) {
            pret.enregistrerPaiement(montant, datePaiementStr); // Call Pret::enregistrerPaiement()
            std::cout << "Remboursement enregistré avec succès pour le prêt ID " << pretId << std::endl;
            return; 
        }
    }

    std::cout << "Aucun prêt trouvé avec l'ID " << pretId << std::endl;
}
    void afficherPret() const {
        std::cout << "\nLoan Details:\n";
        std::cout << "Amount: " << montant << "\n";
        std::cout << "Annual Rate: " << tauxAnnuel << "\n";
        std::cout << "Duration: " << duree << " years\n";

        std::time_t debut_time = std::chrono::system_clock::to_time_t(dateDebut);
        std::tm* debut_tm = std::localtime(&debut_time);
        std::cout << "Start Date: " << std::put_time(debut_tm, "%Y-%m-%d") << "\n";

        std::time_t remboursement_time = std::chrono::system_clock::to_time_t(dateRemboursement);
        std::tm* remboursement_tm = std::localtime(&remboursement_time);

        std::cout << "End Date: " << std::put_time(remboursement_tm, "%Y-%m-%d") << "\n"; 
        std::cout << "Balance: " << calculerBalance() << "\n";
        std::cout << "Total Interest: " << calculerInteretComposeTotal() << "\n";
        std::cout << "Total Payments: " << std::fixed << std::setprecision(2) << std::accumulate(paiements.begin(), paiements.end(), 0.0, [](double sum, const Paiement& paiement) { return sum + paiement.montant; }) << "\n";
    }

     std::chrono::system_clock::time_point stringToTimePoint(const std::string& dateStr)const {    
        return std::chrono::system_clock::time_point();
    }

    // Helper class to represent a payment
    class Paiement {
    public:
        Paiement(double montant, const std::chrono::system_clock::time_point& datePaiement)
            : montant(montant), datePaiement(datePaiement) {}

        Paiement() {}

        double getMontant() const {
            return montant;
        }

        std::string getDatePaiement() const
        {
            return std::string();
        }
    public:
        double montant;
        std::chrono::system_clock::time_point datePaiement;
    };
};


class Pret::Paiement{

    std::string Paiement::getDatePaiement() const
    {
        return std::string();
    }

};


// Assume you have a global vector for transactions
std::vector<Paiement> transactions;

Pret::Pret(double montant, double taux, int duree, const std::string& dateDebutStr, const std::string& dateRemboursementStr)
    : id(nextLoanId++), montant(montant), tauxAnnuel(taux), duree(duree), dateDebut(stringToTimePoint(dateDebutStr)),
      dateRemboursement(stringToTimePoint(dateRemboursementStr)), derniereDatePaiement(stringToTimePoint("1970-01-01"))
{}

Pret::Pret(int id, double montant, double taux, int duree, const std::string& dateDebutStr, const std::string& dateRemboursementStr)
    : id(id), montant(montant), tauxAnnuel(taux), duree(duree), dateDebut(stringToTimePoint(dateDebutStr)),
      dateRemboursement(stringToTimePoint(dateRemboursementStr)), derniereDatePaiement(stringToTimePoint("1970-01-01"))
{}

// Destructor
Pret::~Pret() {}

// Getters
int Pret::getId() const {
    return id;
}

double Pret::getMontant() const {
    return montant;
}

double Pret::getTaux() const {
    return tauxAnnuel;
}

int Pret::getDuree() const {
    return duree;
}

std::string Pret::getDateDebut() const {
    std::time_t debut_time = std::chrono::system_clock::to_time_t(dateDebut);
    std::tm* debut_tm = std::localtime(&debut_time);
    std::stringstream ss;
    ss << std::put_time(debut_tm, "%Y-%m-%d");
    return ss.str();
}

std::string Pret::getDateRemboursement() const {
    std::time_t remboursement_time = std::chrono::system_clock::to_time_t(dateRemboursement);
    std::tm* remboursement_tm = std::localtime(&remboursement_time);
    std::stringstream ss;
    ss << std::put_time(remboursement_tm, "%Y-%m-%d");
    return ss.str();
}

std::chrono::system_clock::time_point Pret::getDerniereDatePaiement() const {
    return derniereDatePaiement;
}

const std::vector

// Setters
void Pret::setId(int id) {
    this->id = id;
}

void Pret::setMontant(double montant) {
    this->montant = montant;
}

void Pret::setTaux(double taux) {
    tauxAnnuel = taux;
}

void Pret::setDuree(int duree) {
    this->duree = duree;
}

void Pret::setDateDebut(const std::string& dateDebutStr) {
    dateDebut = stringToTimePoint(dateDebutStr); // Assign to member variable
}

void Pret::setDateRemboursement(const std::string& dateRemboursementStr) {
    dateRemboursement = stringToTimePoint(dateRemboursementStr);
}

// Calculate simple interest accrued since last payment
double Pret::calculerInteretSimpleDepuisDernierPaiement() const {
    if (derniereDatePaiement == stringToTimePoint("1970-01-01")) {
        return 0.0; // No payments made yet
    }
    double balance = calculerBalance(); // Get the current balance before adding interest
    auto now = std::chrono::system_clock::now();
    std::chrono::duration

// Calculate total compound interest
double Pret::calculerInteretComposeTotal() const {
    double totalAmount = montant * pow((1 + tauxAnnuel), duree);
    return totalAmount - montant;
}

// Calculate balance
double Pret::calculerBalance() const {
    double balance = montant;
    double totalPaid = 0.0;
    for (const auto& paiement : paiements) {
        totalPaid += paiement.getMontant();
    }
    // Add simple interest accrued since the last payment
    balance += calculerInteretSimpleDepuisDernierPaiement(); 
    balance -= totalPaid;
    return balance;
}

// Record a payment
void Pret::enregistrerPaiement(double montant, const std::string& datePaiementStr) {
    if (montant <= 0.0) {
        std::cout << "Error: Invalid payment amount.\n";
        return;
    }
    if (getMontant() < montant) {
        std::cout << "Error: Payment exceeds remaining balance.\n";
        return;
    }
    double balance = getMontant(); 
    balance -= montant;
    paiements.push_back(Paiement(montant, stringToTimePoint(datePaiementStr)));
    // Convert and update last payment date
    derniereDatePaiement = stringToTimePoint(datePaiementStr);
    std::cout << "Payment recorded successfully.\n";
}

// Helper function to convert date string (YYYY-MM-DD) to time_point
std::chrono::system_clock::time_point Pret::stringToTimePoint(const std::string& dateStr) const {
    std::tm tm = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

// Display loan details
void Pret::afficherPret() const {
    std::cout << "\nLoan Details:\n";
    std::cout << "Amount: " << montant << "\n";
    std::cout << "Annual Rate: " << tauxAnnuel << "\n";
    std::cout << "Duration: " << duree << " years\n";
    std::time_t debut_time = std::chrono::system_clock::to_time_t(dateDebut);
    std::tm* debut_tm = std::localtime(&debut_time);
    std::cout << "Start Date: " << std::put_time(debut_tm, "%Y-%m-%d") << "\n";
    std::time_t remboursement_time = std::chrono::system_clock::to_time_t(dateRemboursement);
    std::tm* remboursement_tm = std::localtime(&remboursement_time);
    std::cout << "End Date: " << std::put_time(remboursement_tm, "%Y-%m-%d") << "\n";
    std::cout << "Balance: " << calculerBalance() << "\n";
    std::cout << "Total Interest: " << calculerInteretComposeTotal() << "\n";
    std::cout << "Total Payments: " << std::fixed << std::setprecision(2) << std::accumulate(paiements.begin(), paiements.end(), 0.0, [](double sum, const Paiement& paiement) { return sum + paiement.montant; }) << "\n";
}
