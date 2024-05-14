#include "transaction.h"
#include "banque.h" // Include the banque.h header file
#include "compte.h"
#include "client.h"
#include "logutils.h"
#include "g_error.h"
#include "pret.h"

#include <fstream>
#include <sstream>
#include <vector>


extern GestionnaireBanque banque; 

Transaction::Transaction(Type type, double montant, const std::string& dateHeure, 
                       const std::shared_ptr<Compte>& compteAssocie) 
    : type(type), montant(montant), dateHeure(dateHeure), compteAssocie(compteAssocie) {}

void Transaction::Enregistrer() {
    std::ofstream transactionsFile("transactions.txt", std::ios_base::app); 
    if (transactionsFile.is_open()) {
        transactionsFile << typeToStr() << "," 
                        << montant << ","
                        << dateHeure << "," 
                        << compteAssocie->getNumeroCompte() << "\n";
        transactionsFile.close(); 
    } else {
        throw std::runtime_error("Failed to open transactions file for writing."); 
    }
}

std::string Transaction::typeToStr() const {
    switch (type) {
        case Type::Depot: return "Depot";
        case Type::Retrait: return "Retrait";
        case Type::Virement: return "Virement";
    }
}

void Transaction::Annuler() {
    if (type != Type::Retrait) {
        throw std::logic_error("Only withdrawal transactions can be canceled."); 
    }

    std::vector<Transaction> allTransactions = readTransactionsFromFile();

    // Find the transaction to cancel
    int transactionIndex = -1;
    for (int i = 0; i < allTransactions.size(); ++i) {
        if (allTransactions[i].getCompteAssocie()->getNumeroCompte() == compteAssocie->getNumeroCompte() &&
            allTransactions[i].getMontant() == montant &&
            allTransactions[i].getDateHeure() == dateHeure) {
            transactionIndex = i;
            break;
        }
    }

    if (transactionIndex != -1) {
        allTransactions.erase(allTransactions.begin() + transactionIndex); 
        writeTransactionsToFile(allTransactions); 

        compteAssocie->Deposer(montant); // Update account balance
    } else {
        throw std::runtime_error("Transaction to cancel not found."); 
    }
}

bool Transaction::numeroCompteExists(int numeroCompte, const GestionnaireBanque& banque) const {
    return banque.compteExists(numeroCompte); 
}

// Helper functions 
std::vector<Transaction> readTransactionsFromFile() {
    std::vector<Transaction> transactions;
    std::ifstream file("transactions.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            transactions.push_back(parseTransactionFromLine(line));
        }
        file.close();
    } else {
        throw 
    }
    return transactions;
}

Transaction parseTransactionFromLine(const std::string& line) {
    std::stringstream ss(line);
    std::string typeStr, montantStr, dateHeureStr, compteNumeroStr;

    std::getline(ss, typeStr, ',');
    std::getline(ss, montantStr, ',');
    std::getline(ss, dateHeureStr, ',');
    std::getline(ss, compteNumeroStr, ',');

    Transaction::Type type;
    if (typeStr == "Depot") {
        type = Transaction::Type::Depot;
    } else if (typeStr == "Retrait") {
        type = Transaction::Type::Retrait;
    } else if (typeStr == "Virement") {
        type = Transaction::Type::Virement;
    } else {
        throw std::runtime_error("Invalid transaction type encountered: " + typeStr);
    }

    double montant = std::stod(montantStr);
    std::string dateHeure = dateHeureStr;
    int compteNumero = std::stoi(compteNumeroStr);
    std::shared_ptr

    // Get the Compte object from the global 'banque' 
    std::shared_ptr<Compte> compteAssocie = banque.getCompte(compteNumero); // You need to implement 'getCompte' in 'GestionnaireBanque' 

    // Handle cases where the account doesn't exist
    if (!compteAssocie) {
        throw std::runtime_error("Account with number " + std::to_string(compteNumero) + " not found.");
    }

    return Transaction(type, montant, dateHeure, compteAssocie);
}

void writeTransactionsToFile(const std::vector<Transaction>& transactions) {
    std::ofstream file("transactions.txt");
    if (file.is_open()) {
        for (const auto& transaction : transactions) {
            file << transaction.typeToStr() << "," 
                 << transaction.getMontant() << ","
                 << transaction.getDateHeure() << "," 
                 << transaction.getCompteAssocie()->getNumeroCompte() << "\n"; 
        }
        file.close();
    } else {
        throw std::runtime_error("Failed to open transactions file for writing.");
    }
}

// Getters
Transaction::Type Transaction::getType() const {
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