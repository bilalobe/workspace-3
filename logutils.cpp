#include "logutils.h"

#include <string>
#include <fstream>
#include "transaction.h"

std::string getCurrentDateTime() {
    // Get current time point
    const auto now = std::chrono::system_clock::now();

    // Convert to time_t (calendar time)
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    // Convert to local time
    std::tm localTime = *std::localtime(&time);

    // Format the date and time string (using strftime)
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &localTime); 
    return std::string(buffer); 
}

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