#include "logutils.h"

#include <string>
#include <fstream>
#include "transaction.h"
// ... other includes as needed ...

void logTransaction(const std::string& filename, const Transaction& transaction) {
    std::ofstream logFile(filename, std::ios_base::app); // Open in append mode
    if (logFile.is_open()) {
        // Format the log entry as needed
        logFile << transaction.getDateHeure() << ","
                << transaction.typeToStr() << ","
                << transaction.getMontant() << ","
                << transaction.getCompteAssocie()->getNumeroCompte() << "\n"; 
        logFile.close();
    } else {
        throw std::runtime_error("Unable to open log file " + filename);
    }
}