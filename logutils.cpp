#include "logutils.h"

#include <string>
#include <fstream>
#include <sstream>
#include "transaction.h"

#include "logutils.h"
#include "transaction.h"

std::string getCurrentDateTime() {
    std::time_t now = std::time(0);
    std::tm *ltm = std::localtime(&now);

    std::stringstream ss;
    ss << std::put_time(ltm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void logTransaction(const std::string& filename, const Transaction& transaction) {
    std::ofstream logFile(filename, std::ios::app); // Open the log file in append mode

    if (logFile.is_open()) {
        logFile << getCurrentDateTime() << " - Transaction: " << std::endl;
        logFile << "    - Type: " << transaction.typeToStr() << std::endl;
        logFile << "    - Montant: " << transaction.getMontant() << std::endl;
        logFile << "    - Date Heure: " << transaction.getDateHeure() << std::endl;
        logFile << "    - Compte Associé: " << transaction.getCompteAssocie()->getNumeroCompte() << std::endl;
        
        // Add additional details as needed
        if (transaction.getType() == Transaction::Type::Virement) {
            logFile << "    - Bénéficiaire: " << transaction.getBeneficiaryName() << std::endl;
        } else if (transaction.getType() == Transaction::Type::Pret) {
            logFile << "    - ID du prêt: " << transaction.getPretId() << std::endl;
        }

        logFile << std::endl; // Add a line break between transactions
        logFile.close();
    } else {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier journal (" << filename << ")" << std::endl;
    }
}