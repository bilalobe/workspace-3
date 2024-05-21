#include "transaction.h"
#include "banque.h" // Include the Banque class

// Initialize the static member
Banque& Transaction::banque = *new Banque(); // Initialize the static member

Transaction::Transaction(TransactionType type, double montant, const std::string& dateHeure,
                         const std::shared_ptr<Compte>& compteAssocie, 
                         const std::string& beneficiaryName,
                         int PretId)
    : type(type), montant(montant), dateHeure(dateHeure), compteAssocie(compteAssocie),
      beneficiaryName(beneficiaryName), PretId(PretId) {}

TransactionType Transaction::getType() const {
    return type;
}

double Transaction::getMontant() const {
    return montant;
}

const std::string& Transaction::getDateHeure() const {
    return dateHeure;
}

const std::shared_ptr<Compte>& Transaction::getCompteAssocie() const {
    return compteAssocie;
}

const std::string& Transaction::getBeneficiaryName() const {
    return beneficiaryName;
}

int Transaction::getPretId() const {
    return PretId;
}

std::string Transaction::typeToStr() const {
    switch (type) {
        case TransactionType::Depot:
            return "Depot";
        case TransactionType::Retrait:
            return "Retrait";
        case TransactionType::Virement:
            return "Virement";
        case TransactionType::Pret:
            return "Pret";
        default:
            return "TransactionType Invalide"; // Handle invalid types
    }
}

void Transaction::Enregistrer() {
    std::string dateTime = getCurrentDateTime(); 
    std::cout << dateTime << " - Transaction enregistrée: " << std::endl;
    std::cout << "    - TransactionType: " << typeToStr() << std::endl;
    std::cout << "    - Montant: " << montant << std::endl;
    std::cout << "    - Date Heure: " << dateHeure << std::endl;
    std::cout << "    - Compte Associé: " << compteAssocie->getNumeroCompte() << std::endl; 

    // Now, record the transaction in the Banque class
    banque.enregistrerTransaction(*this); 
}

void Transaction::Annuler() {
    std::string dateTime = getCurrentDateTime();
    std::cout << dateTime << " - Transaction annulée: " << std::endl;
    std::cout << "    - TransactionType: " << typeToStr() << std::endl;
    std::cout << "    - Montant: " << montant << std::endl;
    std::cout << "    - Date Heure: " << dateHeure << std::endl;
    std::cout << "    - Compte Associé: " << compteAssocie->getNumeroCompte() << std::endl; 

    // Implement logic to cancel the transaction
    // You'll need to reverse the effects based on the transaction type
    switch (type) {
        case TransactionType::Depot:
            compteAssocie->setSolde(compteAssocie->getSolde() - montant); // Reverse the deposit
            break;
        case TransactionType::Retrait:
            compteAssocie->setSolde(compteAssocie->getSolde() + montant); // Reverse the withdrawal
            break;
        case TransactionType::Virement: {
            std::shared_ptr<Compte> destinationAccount = banque.getCompteByBeneficiaryName(beneficiaryName);
            if (destinationAccount != nullptr) {
                compteAssocie->setSolde(compteAssocie->getSolde() + montant); // Add to source account
                destinationAccount->setSolde(destinationAccount->getSolde() - montant); // Subtract from destination account
                std::cout << "    - Virement annulé. Solde modifié." << std::endl;
            } else {
                std::cerr << "Erreur: Impossible de trouver le compte du bénéficiaire." << std::endl;
            }
            break;
        }
        case TransactionType::Pret:
            if (banque.annulerPret(PretId)) { // Implement annulerPret in Banque
                std::cout << "    - Prêt annulé. Solde modifié." << std::endl; 
            } else {
                std::cerr << "Erreur: Impossible d'annuler le prêt." << std::endl; 
            }
            break;
        default: 
            std::cerr << "Erreur: Type de transaction non pris en charge pour l'annulation." << std::endl;
            break;
    }
}
