#ifndef G_ERROR_H
#define G_ERROR_H

#include <stdexcept>
#include <sstream>
#include <system_error>

class OperationNonAboutieError : public std::runtime_error {
public:
    OperationNonAboutieError(double solde, double montant)
        : std::runtime_error(createErrorMessage(solde, montant)) {}

    class InvalidAccountError : public std::runtime_error {
    public:
        InvalidAccountError(const std::string& message)
            : std::runtime_error("Erreur de compte: " + message) {}
    };

    class InvalidAmountError : public std::runtime_error {
    public:
        InvalidAmountError(const std::string& message)
            : std::runtime_error("Erreur de montant: " + message) {} 
    };

private:
    static std::string createErrorMessage(double solde, double montant) {
        std::stringstream ss;
        ss << "Operation non aboutie: Solde insuffisant. Solde actuel: "
           << solde << ", Montant: " << montant;
        return ss.str();
    }
};

#endif
