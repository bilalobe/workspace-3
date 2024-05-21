#include "pret.h"
#include "logutils.h" // Include for getCurrentDateTime

Pret::Pret(int id, double montant, double tauxAnnuel, int duree, const std::string &dateDebutStr, const std::string &dateRemboursementStr, double tauxRampe)
    : id(id), montant(montant), tauxAnnuel(tauxAnnuel), duree(duree), tauxRampe(tauxRampe), statut(PretStatut::Active) {
    dateDebut = stringToTimePoint(dateDebutStr);
    dateRemboursement = stringToTimePoint(dateRemboursementStr);
    derniereDatePaiement = dateDebut;
}

std::chrono::system_clock::time_point Pret::stringToTimePoint(const std::string &dateStr) const {
    std::tm tm = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

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
    std::time_t dateDebutTime = std::chrono::system_clock::to_time_t(dateDebut);
    std::ostringstream ss;
    ss << std::put_time(std::localtime(&dateDebutTime), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string Pret::getDateRemboursement() const {
    std::time_t dateRemboursementTime = std::chrono::system_clock::to_time_t(dateRemboursement);
    std::ostringstream ss;
    ss << std::put_time(std::localtime(&dateRemboursementTime), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::chrono::system_clock::time_point Pret::getDerniereDatePaiement() const {
    return derniereDatePaiement;
}

double Pret::calculerInteretSimpleDepuisDernierPaiement() const {
    // Your calculation logic
}

double Pret::calculerInteretComposeTotal() const {
    // Your calculation logic
}

double Pret::calculerBalance() const {
    // Your calculation logic
}

std::vector<Pret::Paiement> Pret::getPaiements() const {
    return paiements;
}

void Pret::afficherPret() const {
    // Your display logic
}

void Pret::ajouterPaiement(double montant, const std::string &datePaiementStr) {
    auto datePaiement = stringToTimePoint(datePaiementStr);
    paiements.emplace_back(montant, datePaiement);
    derniereDatePaiement = datePaiement;
}

PretStatut Pret::getStatut() const {
    return statut;
}

void Pret::setStatut(PretStatut nouveauStatut) {
    statut = nouveauStatut;
}

bool Pret::isCancelable() const {
    // Your logic to determine if the Pret is cancelable
}

Pret::Paiement::Paiement(double montant, const std::chrono::system_clock::time_point &datePaiement)
    : montant(montant), datePaiement(datePaiement) {}

double Pret::Paiement::getMontant() const {
    return montant;
}

std::string Pret::Paiement::getDatePaiement() const {
    std::time_t datePaiementTime = std::chrono::system_clock::to_time_t(datePaiement);
    std::ostringstream ss;
    ss << std::put_time(std::localtime(&datePaiementTime), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
